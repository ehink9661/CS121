/* animalList.h
 *
 * CS 121.Bolden.........g++ from CS server...........Ethan Hinkle
 * Febuary 9, 2020.......Dell Inspiron Intel Core i5..hink9661@vandals.uidaho.edu
 *
 * This file contains the struct and the prototypes for our assignment #2, using linked list to sort a list of animals from a text file
 *---------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// struct of node to allow for there to be a string and a pointer used in the implementation of the linked list
struct Node{
  string animal; // string for the animal stored in the node
  struct Node* next; // pointer to the next value in a linked list
};
typedef struct Node* NodePtr; // creates a node pointer called NodePtr

void add(string); // add data to linked list, input being the item
void remove(string); // remove data from linked list, input being the item
void read(string); // reads the text file to find the commands used, the input being the text files name
int count(string); // counts how many of string animal are in the linked list
void print(); // prints the linked list currently stored in the function
void clear(); // clears the linked list of all data
