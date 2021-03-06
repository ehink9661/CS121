/* hashDict.h
 *
 * CS 121-01.Bolden....g++ from CS server...........Ethan Hinkle
 * May 2, 2020....Dell Inspiron Intel Core i5
 * hink9661@vandals.uidaho.edu
 *
 * This is the prototype file for Assignment #5, using sourced hash
 * table code to analyze the loading factor's effects
 *--------------------------------------------------------------------
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

struct nList{  /* table entry: */
  char *name;  /* defined name */
  struct nList *next;  /* next entry in chain */
};
typedef struct nList *NListPtr;

unsigned Hash(char *);
NListPtr Lookup(char *);
int probe(char *);
void searchTable(string);
NListPtr insert(char *);
void printTable();
void buildTable(string);
int minBucket();
int maxBucket();
int checkBucket();
int findEmpty();
void menu();
static char *Strdup(const char *);
const int HASH_TABLE_SIZE = 49957;
static NListPtr hashTable[HASH_TABLE_SIZE];

