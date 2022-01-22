/* TVTree.cpp
 *
 * CS 121-01.Bolden....g++ from CS server...........Ethan Hinkle
 * April 9, 2020....Dell Inspiron Intel Core i5
 * hink9661@vandals.uidaho.edu
 *
 * This is the functions  file for Assignment #4, creating a
 * searchable TV guide from a tree and external file
 *--------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "TVTree.h"

using namespace std;

ifstream infile;

/* constructor */
TVBST::TVBST(){
}

/* adds actors to a linked list in the BST, actor's name and the list ptr are inputs*/ 
void TVBST::addActor(string a, NodePtr & h){
  NodePtr n = new Node; /* creates a new node on the list */
  int first = a.find_first_not_of(" \t\n");
  int last = a.find_last_not_of(" \t\n");
  a = a.substr(first, last-first+1);
  n->actor = a; /* sets the data of the node */
  n->next = NULL; /* sets the next value to NULL on the list */
  if(h == NULL){ /* runs if this is the first value in the linked list */
    h = n; /* puts the node at the begining */
  }
  else{ /* runs if not the first value in the list */
    n->next = h; /* points node n to the head of the list */
    h = n; /* sets head equal to node n */
  }
}

/* adds data alphabetically into the BST, input the title and the BST pointer */
void TVBST::addData(BSTreePtr & t, string a){
  if(t == NULL){ /* if the current pointer is empty */
    BSTreePtr newPtr = new BSTreeNode; /* new node is created */
    string line;
    newPtr->title = a; /* add title to node */
    getline(infile, line, '-');
    int date = atoi(line.c_str()); /* converts string to int */
    newPtr->start = date;
    getline(infile, line, ')');
    date = atoi(line.c_str());
    getline(infile, line); /* sink for '\n' at the end of line 1 */
    newPtr->end = date;
    getline(infile, line);
    newPtr->genre = line;
    getline(infile, line); /* takes URL but no insert */
    getline(infile, line);
    NodePtr head = NULL; /* creates head ptr for the actors list */
    while(!line.empty()){ /* loops while actors are still in the list */
      addActor(line, head); /* call addActor to insert into the list */
      getline(infile, line); /* fetch next actor */
    }
    newPtr->list = head;
    newPtr->leftPtr = NULL;
    newPtr->rightPtr = NULL;
    t = newPtr;
  }else{
    string line = t->title;
    if(strcmp(a.c_str(), line.c_str()) <= 0){ /* compares current node with input title and inserts if input is smaller than current/ comes before in alphabet */
      addData(t->leftPtr, a); /* recursion if is before in alphabet */
    }else{
      addData(t->rightPtr, a); /* recursion if is after in alphabet */
    }
  }
}

/* prints actors stored in list */
void TVBST::printList(NodePtr p){
  cout << "|";
  while(p != NULL){ /* loop to keep printing unitl the head of the list is NULL */
    cout << p->actor << "|";
    p = p->next; /* moves to next item in list */
  }
  cout << endl;
}

/* prints all shows stored in the tree in-order/ alphabetical */
void TVBST::printAll(BSTreePtr t){
  if(t != NULL){
    printAll(t->leftPtr); /* recursion left */
    cout << t->title << "|"; /* print current title */
    printAll(t->rightPtr); /* recursion right */
  }
}

/* deletes the tree after use in post order/ leafs go first */
void TVBST::deleteAll(BSTreePtr & t){
  if(t != NULL){ /* still values in tree */
    deleteAll(t->leftPtr); /* recursion left */
    deleteAll(t->rightPtr); /* recursion right */
    deleteList(t->list); /* delete the linked list seperately */
    t->leftPtr = NULL; /* set leftPtr to NULL (already done if leafs */
    t->rightPtr = NULL; /* set rightPtr to NULL (already done if leafs */
    delete t; /* delete the node */
    t = NULL; /* set the node to NULL */
  }
}

/* deletes the linked list */
void TVBST::deleteList(NodePtr & p){
  while(p != NULL){ /* while list is not empty */
    NodePtr curr = p;
    p = curr->next; /* p (head) is set to the next value */
    curr->next = NULL; /* next ptr is set to NULL for current node */
    delete curr; /* deletes current node */
  }
}

/* builds the TV guide BST */
void TVBST::buildGuide(string s){
  string name;
  infile.open(s.c_str()); /* reads file into infile */
  while(getline(infile, name, '(')){ /* reads the title */
    int first = name.find_first_not_of(" \t\n"); /* find first non blank char */
    int last = name.find_last_not_of(" \t\n"); /* find last non blank char */
    name = name.substr(first, last-first+1); /* trim string */
    addData(rootPtr, name); /* call addData for current title */
  }
}

/* searches tree based on title name, input tree ptr and show name */
void TVBST::checkTitle(BSTreePtr t, string s){
  if(t != NULL){ /* have not fully searched the tree */
    checkTitle(t->leftPtr, s); /* recursion left */
    string m = t->title;
    if(strcmp(s.c_str(), m.c_str()) == 0){
      printList(t->list); /* print list of actors in show */
    }
    checkTitle(t->rightPtr, s); /* recursion right */
  }
}

/* searches the actors list for inputed actor, input list ptr and actor */
bool TVBST::searchList(NodePtr p, string s){
  bool found = false;
  while(p != NULL){ /* loop to keep printing unitl the head of the list is NULL */
    string a = p->actor;
    if(!strcmp(s.c_str(), a.c_str())){ /* checks if equal and if equal 0 */
      found = true;
    }
    p = p->next; /* moves to next item in list */
  }
  return found; /* return true if actor is in show */
}

/* search for an actor in a show, input tree ptr and actor name */
void TVBST::checkActor(BSTreePtr t, string s){
  if(t != NULL){ /* node contains data */
    checkActor(t->leftPtr, s); /* reccursion left */
    if(searchList(t->list, s)){ /* if searchList returns true */
      cout << t->title << "|"; 
    }
    checkActor(t->rightPtr, s); /* recursion right */
  }
}

/* searches shows based on decade of release, input tree ptr and the start date */
void TVBST::checkDate(BSTreePtr t, int x){
  int y = x;
  if(t != NULL){ /* node contains data */
    checkDate(t->leftPtr, x); /* recursion left */
    int z = t-> start;
    for(int i = 0; i < 10; i++){ /* loops for 10 "years" */
      if(z == y){ /* years match/ show was released within 10 years of date */
	cout << t->title << "|";
      }
      y++; /* add one year */
    }
    checkDate(t->rightPtr, x); /* recursion left */
  }
}

/* prompt for searching for cast of a show */
void TVBST::searchShow(){
  string title;
  cout << "Please Input a Show to See its Cast: ";
  getline(cin, title); /* get user input */
  cout << title << " Cast: ";
  checkTitle(rootPtr, title); /* fetches cast list */
}

/* prompt for searching for shows containing actor */
void TVBST::searchActor(){
  string actor;
  cout << "Please Input an Actor to See Their Shows: ";
  getline(cin, actor); /* get user input */
  cout << actor << "'s Shows: |";
  checkActor(rootPtr, actor); /* fetch shows starring actor */
  cout << endl;
}

/* prompt for searching for shows released durring and the decade following a year */
void TVBST::searchDate(){
  string line;
  cout << "Please Input the First Year of the Search Decade: ";
  getline(cin, line); /* get input date */
  int date = atoi(line.c_str());
  cout << "Shows released in the decade following " << date << ": |";
  checkDate(rootPtr, date); /* fetches the shows in that decade */
  cout << endl;
}

/* user menu for commands */
void TVBST::searchMenu(){
  string line;
  bool exit = false; /* exit menu loop variable */
  cout << "Hello, and welcome to your TV Guide." << endl;
  do{
    cout << "Options:" << endl;
    cout << "See All Available Shows (1)" << endl;
    cout << "Search Shows Cast (2)" << endl;
    cout << "Search Actor's Shows (3)" << endl;
    cout << "Search Decade of Release (4)" << endl;
    cout << "Exit the Guide (5)" << endl;
    getline(cin, line);
    int input = atoi(line.c_str()); /* make user input into an int */
    switch(input){ /* switch statement for menu commands */
    case 1:
      cout << "|";
      printAll(rootPtr); /* prints all shows in tree */
      cout << endl;
      break;
    case 2:
      searchShow(); /* opens title search function */
      break;
    case 3:
      searchActor(); /*opens actor search function */
      break;
    case 4:
      searchDate(); /* opens date search function */
      break;
    case 5:
      exit = true; /* breaks loop */
      deleteAll(rootPtr); /* deletes all nodes in the tree before closing */
      break;
    default:
      cout << "Invalid Input" << endl;
      break;
    }
  }while(!exit); /* loops whie exit if false */
    cout << "Goodbye!" << endl;
}
