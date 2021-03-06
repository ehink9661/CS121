/* TVTree.h
 *
 * CS 121-01.Bolden....g++ from CS server...........Ethan Hinkle
 * April 9, 2020....Dell Inspiron Intel Core i5
 * hink9661@vandals.uidaho.edu
 *
 * This is the class and protopype file for Assignment #4, creating a
 * searchable TV guide from a tree and external file
 *--------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

class TVBST{
 private:
  struct Node{ /* linked list struct */
    string actor; /* string for the actor stored in the node */
    struct Node* next; /* pointer to the next value in the linked list */
  };
  typedef struct Node* NodePtr; /* creates a node pointer called NodePtr */

  struct  BSTreeNode{ /* binary search tree struct */
    string title; /* title of show */
    int start; /* start date */
    int end; /* end date */
    string genre; /* genre of the show */
    NodePtr list; /* pointer to a linked list containing the actors */
    struct BSTreeNode* leftPtr; /* pointer to the left child in the tree */
    struct BSTreeNode* rightPtr; /* pointer to the right child in the tree */
  };
  typedef struct BSTreeNode* BSTreePtr; /* creates a BSTreeNode pointer called BSTreePtr */
  BSTreePtr rootPtr = NULL;/* root of the BST */
 public:
  TVBST();
  void addActor(string, NodePtr&);
  void addData(BSTreePtr&, string);
  void printList(NodePtr);
  void printAll(BSTreePtr);
  void deleteAll(BSTreePtr&);
  void deleteList(NodePtr&);
  void searchShow();
  void checkTitle(BSTreePtr, string);
  void searchActor();
  bool searchList(NodePtr, string);
  void checkActor(BSTreePtr, string);
  void searchDate();
  void checkDate(BSTreePtr, int);
  void buildGuide(string);
  void searchMenu();
};
