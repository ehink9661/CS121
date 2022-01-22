/* maze.h
 *
 * CS 121-01.Bolden....g++ from CS server...........Ethan Hinkle
 * Febuary 28, 2020....Dell Inspiron Intel Core i5..hink9661@vandals.uidaho.edu
 *
 * This file contains the struct, class and the prototypes for our assignment #3, using a linked list queue to navigate maze given by a text file
 *---------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* class of node to allow for there to be a string and a pointer used in the implementation of the linked list */
class maze{
 private:
  struct node{
    int column; /* stores the column of the array position */
    int row; /* stores the row of the array position */
    struct node* next; // pointer to the next value in a linked list
  };
  typedef struct node* NodePtr; /* creates a node pointer called NodePtr */
  NodePtr start; /* points to the begining of the queue */
  NodePtr end; /* points to the end of the queue */
  int length; /* stores the length of the maze */
  int height; /* stores the height of the maze */
  char **pArr; /* double pointer to the dynamic array of dynamic arrays to be 2D */
 public:
  maze(); /* class constructor */
  void read(string); /* reads the input for a text file to create a maze */
  void enqueue(int, int); /* this function adds a position in an array to a linked list */
  void dequeue(); /* this function removes the front of a linked list */
  void solve();/* this function runs the maze and checks to see if it is solvable */
  void print(); /* prints the maze array */
  void clearArr(); /* clears the array for future use */
  int firstColumn(); /* fetches the column of the first item in the linked list */
  int firstRow(); /* fetches the row of the first item in the linked list */
  void adjacentAdd(int, int); /* function to check all adjacent tiles for valid moves */
  bool isEmpty(); /* checks if the queue is empty */
  bool exit(int, int); /* checks if the exit to the maze has been found */
  void deleteAll(); /* clears the linked list */
};
