/* list.cpp
 *
 * CS 121.Bolden.........g++ from CS server...........Ethan Hinkle
 * Febuary 9, 2020.......Computer & CPU.............hink9661@vandals.uidaho.edu
 *
 * Brief description of program and objective.
 *---------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>
#include "list.h" // allows for prototypes and struct to be read

using namespace std;

NodePtr head; // points to the head of the list

// prints the linked list in order until reaching a NULL value
void print(){
  NodePtr p = head; // creates pointer p equal to head
  cout << "----------" << endl;
  while(p != NULL){ // loop to keep printing unitl the head of the list is NULL
    cout << p->animal << endl;
    p = p->next; // moves to next item in list
  }
  cout << "----------" << endl;
}

// adds a data value to the end of a linked list
void add(string a){
  NodePtr n = new Node; // creates a new node on the list
  n->animal = a; // sets the data of the node
  n->next = NULL; // sets the next value to NULL on the list
  if(head == NULL){ // runs if this is the first value in the linked list
    head = n; // puts the node at the begining
  }
  else{ // runs if not the first value in the list
    n->next = head; // points node n to the head of the list 
    head = n; // sets head equal to node n
  }
  cout << "Added " << a << endl; // says what was added to the list
}

// runs a function that deletes the word that is inputed as the string value
void remove(string a){
  NodePtr p = head; // creates pointer p equal to head
  if(p == NULL){ // if the list is empty
    cout << "Error!" << endl;
  }
  else{ // list is not empty
    NodePtr curr = head; // creates value for current location equal to head
    NodePtr prev = head; // creates value for previous location equal to head
    while(curr != NULL && curr->animal != a){ // loops until the node with the animal is found or the list ends, if said word to be deleted does not exist
      prev = curr; // walks prev to the current locationin the list
      curr = curr->next; // walks curr to the next value in the list
    }
    if(curr != NULL){ // runs if a value was found in the list
      if(curr == prev){ // value to be deleted was at the begining of the list
	head = curr->next; // moves the head of the list to the next node
      }
      else{
	prev->next = curr->next; // moves the pointer of the prevoius node to the next node
      }
      curr->next = NULL; // deletes the pointer on the current node to the next node to avoid error
      delete curr; // deletes the data stored in curr to save memory
      cout << "Deleted " << a << endl; // says what was deleted from the list if it existed
    }
  }
}

void read(string a){ // reads the text file for commands, the only input being the name of the file
  ifstream infile; // this creates an ifstream object called infile
  infile.open(a.c_str()); // this connects infile to the text file imported, a
  string word; // string to store the word/command read in the text file
  while(infile >> word){
    if(word == "add"){
      infile >> word;
      add(word);
    }
    else if(word == "delete" || word == "remove"){
      infile >> word;
      remove(word);
    }
    else if(word == "show"){
      print();
    }
  }
}
