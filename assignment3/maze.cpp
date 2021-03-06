/* maze.cpp
 *
 * CS 121-01.Bolden....g++ on CS server.............Ethan Hinkle
 * Febuary 28, 2020....Dell Inspiron Intel Core i5..hink9661@vandals.uidaho.edu
 *
 * List of all the functions used in Assignment #3, using a linked list queue to navigate a maze given by a text file
 *---------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>
#include "maze.h" /* allows for prototypes and the class to be read */

using namespace std;

/* class constructor */
maze::maze(){
  start = NULL;
  end = start;
}

/* reads the input for a text file to create a maze */
void maze::read(string file){
  ifstream infile; /* creates an ifstream object called infile */
  infile.open(file.c_str()); /* reads file into infile */
  infile >> length; /* fetches the first variable in the file for the maze length */
  infile >> height; /* fetches the second variable in the file for the maze height */
  char tile;
  pArr = new char*[length]; /* makes pArr into a pointer to a dynamic array */
  for(int i = 0; i < length; ++i){
    pArr[i] = new char[height]; /* fills pArr with dynamic arrays */
  }
  for(int y = 0; y < height; y++){ /* loop to fill pArr with the maze tiles */
    for(int x = 0; x < length; x++){
      infile >> tile; /* fetches current tile in list */
      pArr[x][y] = tile;
    }
  }
}

/* prints the maze array */
void maze::print(){
  for(int y = 0; y < height; y++){ /* double loop to print maze */
    cout << "|"; /* puts maze in a box for viewing */
    for(int x = 0; x < length; x++){
      cout << pArr[x][y];
    }
    cout << "|" << endl;
  }
}

/* clears the array for future use */
void maze::clearArr(){
  for(int i = 0; i < length; ++i) {
    delete [] pArr[i]; /* deletes arrays in array */
  }
  delete [] pArr; /* deletes dynamic array */
}

/* this function adds a position in an array to a linked list */
void maze::enqueue(int x, int y){
  NodePtr n = new node;
  n -> column = x; /* sets horizontal array value */
  n -> row = y; /* sets vertical array value */
  n -> next = NULL; /* sets next data member to NULL */
  if(start == NULL){ /* if the list is empty check */
    start = n;
    end = start;
  }else{ /* if the list is not empty */ 
    end -> next = n;
    end = end -> next;
  }
}

/* this function removes the front of a linked list */
void maze::dequeue(){
  NodePtr curr;
  if(start != NULL){ /* only runs if list is occupied */
    curr = start;
    start = start -> next;
    curr -> next = NULL;
    delete curr; /* deletes front of list */
  }
}

/* this function runs the maze and checks to see if it is solvable */
void maze::solve(){
  int posX; /* int for the position on the x axis of the array */
  int posY; /* int for the position on the y axis of the array */
  for(int y = 0; y < height; y++){ /* loop to find the maze start */
    for(int x = 0; x < length; x++){
      if(pArr[x][y] == 'S'){
	posX = x;
	posY = y;
      }
    }
  }
  bool solved = false; /* bool for if the maze is solved */
  bool failure = false; /* bool for if the maze is proven unsolvable */
  while(solved == false && failure == false){ /* loop to run the maze */
    adjacentAdd(posX, posY); /* stores valid adjacent tiles in queue */
    failure = isEmpty(); /* checks if the queue is empty and therefore maze is unsolvable */
    if(failure == false){ /* if maze is still valid go to next queued item */
      posX = firstColumn(); /* sets posX to the Column in the queue */
      posY = firstRow(); /* sets posY to the Row in the queue */
      pArr[posX][posY] = '!'; /* sets current tile to ! on maze */
      dequeue(); /* dequeues current position */
    }
    solved = exit(posX, posY); /* checks if any adjacent tiles are the exit */
  }
  deleteAll();
  if(solved == true){ /* checks if maze is solved and tells result */
    cout << "The maze you inputed was solvable." << endl;
  }else{
    cout << "The maze you inputed is unfortunately unsolvable." << endl;
  }
}

/* function to check all adjacent tiles for valid moves */
void maze::adjacentAdd(int x, int y){
  int adjX[4] = {0,1,0,-1}; /* arrays of the x and y positions in the array of adjacent tiles */
  int adjY[4] = {1,0,-1,0};
  for(int i = 0; i < 4; i++){ /* loop to run through all 4 adjacent tiles */
    if(x + adjX[i] >= 0 && y + adjY[i] >= 0 && x + adjX[i] < length && y + adjY[i] < height){ /* checks if adjacent tile is within the array bounds */
      if(pArr[x + adjX[i]][y + adjY[i]] == '.'){ /* checks if adjacent tile is valid */
	enqueue(x + adjX[i], y + adjY[i]); /* adds valid tile to queue */
	pArr[x + adjX[i]][y + adjY[i]] = '?'; /* changes added tile to ? in maze to avoid repeat */
      }
    }
  }
}

/* checks if the exit to the maze has been found */
bool maze::exit(int x, int y){
  bool a = false;
  int adjX[4] = {0,1,0,-1}; /* arrays of the x and y positions in the array of adjacent tiles */
  int adjY[4] = {1,0,-1,0};
  for(int i = 0; i < 4; i++){ /* loop to run through all 4 adjacent tiles */
    if(x + adjX[i] >= 0 && y + adjY[i] >= 0 && x + adjX[i] < length && y + adjY[i] < height){ /* checks if adjacent tile is within the array bounds */
      if(pArr[x + adjX[i]][y + adjY[i]] == 'G'){ /* checks if adjacent tile is valid */
	a = true; /* sets a to true */
      }
    }
  }
  return a; /* returns bool a */
}

/* fetches the column of the first item in the linked list */
int maze::firstColumn(){
  int a;
  if(start != NULL){ /* checks if list is empty */
    a = start->column;
  }
  return a;
}

/* fetches the row of the first item in the linked list */
int maze::firstRow(){
  int a;
  if(start != NULL){ /* checks if list is empty */
    a = start->row;
  }
  return a;
}

/* checks if the queue is empty */
bool maze::isEmpty(){
  if(start == NULL){ /* if list is empty */
    return true;
  }else{
    return false;
  }
}

/* clears the linked list */
void maze::deleteAll(){
  NodePtr del;
  while(start != NULL){ /* while list is not empty */
    dequeue();
  }
  start = NULL;
}
