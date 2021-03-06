/* hashDict.cpp
 *
 * CS 121-01.Bolden....g++ from CS server...........Ethan Hinkle
 * May 2, 2020....Dell Inspiron Intel Core i5
 * hink9661@vandals.uidaho.edu
 *
 * This is the functions file for Assignment #5, using sourced hash
 * table code to analyze the loading factor's effects
 *--------------------------------------------------------------------
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "hashDict.h"

using namespace std;

ifstream infile;

/* Hash - Generate hash value for string s */
unsigned Hash(char *s){
  unsigned hashVal;
  for(hashVal = 0; *s != '\0'; s++){
    hashVal = *s + 31 * hashVal; /* finds askii value of s */
  }
  return  hashVal % HASH_TABLE_SIZE; /* returns a value in the table */
}

/* Lookup - Look for s in hashTable */
NListPtr Lookup(char *s){
  NListPtr np;
  for(np = hashTable[Hash(s)]; np != NULL; np = np->next){ /* look at bucket */
    if(strcmp(s, np->name) == 0){
      return np;  /* item is found */
    }
  }
  return NULL;  /* item is not found */
}

/* probe - check how many probes it takes to find a word in a bucket */
int probe(char *s){
  NListPtr np;
  int probe = 0;
  for(np = hashTable[Hash(s)]; np != NULL; np = np->next){
    probe ++;
    if(strcmp(s, np->name) == 0){
      return probe;  /* item is found */
    }
  }
}

/* searchTable - checks if word is in the table and how many probes were needed */
void searchTable(string s){
  char* word = new char [s.length()+1];
  strcpy(word, s.c_str());
  NListPtr np = Lookup(word);
  if(np == NULL){ /* item was not found */
    cout << s << " is not within the hash table." << endl;
  }
  else{
    cout << s << " was found in the hash table." << endl;
    cout << "It took " << probe(word) << " probes to find it." << endl;
  }
}

/* Insert - Put (name, defn) in hash table */
NListPtr insert(char *name){
  unsigned hashVal;
  NListPtr np;
  if((np = Lookup(name)) == NULL){  /* not found */
    np = (NListPtr) malloc(sizeof(*np));
    if(np == NULL || (np->name = Strdup(name)) == NULL){ /* check if valid */
      return NULL;
    }
    hashVal = Hash(name);
    np->next = hashTable[hashVal];
    hashTable[hashVal] = np;
  }
  return np;
}

/* buildTable - builds the hash table from an extenal file */
void buildTable(string s){
  string name;
  infile.open(s.c_str());
  while(getline(infile, name)){ /* run through file until NULL */
    char* word = new char [name.length()+1];
    strcpy(word, name.c_str()); /* turn std::string into char* */
    (void)insert(word);
  }
}

/* printTable - print the hash table contents */
void printTable(){
  NListPtr np;
  cout << "Hash table contents:" << endl;
  cout << "--------------------\n" << endl;
  for(int i = 0; i < HASH_TABLE_SIZE; i++ ){ /* loop until table size is reached */
    np = hashTable[i];
    while(np != NULL){ /* items are in bucket */
      cout << i << ": " << np->name << endl;
      np = np->next;
    }
  }
}

/* minBucket - get the smallest bucket size */
int minBucket(){
  NListPtr np;
  int min;
  for(int i = 0; i < HASH_TABLE_SIZE; i++ ){ /*search whole table */
    np = hashTable[i];
    int count = 0;
    while(np != NULL){ /* loop bucket */
      count ++; /* count items */
      np = np->next;
    }
    if(i == 0){ /* begining of the table, insert value as smallest */
      min = count;
    }
    if(count < min){ /* checck if new value is smaller than prev min */
      min = count;
    }
  }
  return min;
}

/* maxBucket - get the biggest bucket size */
int maxBucket(){
  NListPtr np;
  int max;
  for(int i = 0; i < HASH_TABLE_SIZE; i++ ){ /*search whole table */
    np = hashTable[i];
    int count = 0;
    while(np != NULL){ /* loop bucket */
      count ++; /* count items */
      np = np->next;
    }
    if(i == 0){ /* begining of the table, insert value as biggest */
      max = count;
    }
    if(count > max){ /* checck if new value is smaller than prev min */
      max = count;
    }
  }
  return max;
}

/* checkBucket - see how many enteries are in a bucket */
int checkBucket(int x){
  NListPtr np;
  int count = 0;
  np = hashTable[x]; /* go to specified table location */
  while(np != NULL){ /* search bucket */
    count ++;
    np = np->next;
  }
  return count;
}

/* findEmpty - find and tally all empty buckets */
int findEmpty(){
  NListPtr np;
  int empty = 0;
  for(int i = 0; i < HASH_TABLE_SIZE; i++ ){
    np = hashTable[i];
    int count = 0;
    while(np != NULL){ /* count entries in a bucket */
      count ++;
      np = np->next;
    }
    if(count == 0){ /* if bucket is empty */
      empty ++;
    }
  }
  return empty;
}

/* Strdup - Make a duplicate copy of s */
static char *Strdup(const char *s){
  char *p;
  p = (char *) malloc(strlen(s)+1);
  if(p != NULL){
    strcpy(p,s);
  }
  return p;
}

/* menu - small user interface to complete assignment objectives */
void menu(){
  int num;
  string word;
  cout << "The hash table's size is " << HASH_TABLE_SIZE << "." << endl;
  cout << "The smallest bucket contains " << minBucket() << " items." << endl;
  cout << "The largest bucket contains " << maxBucket() << " items." << endl;
  cout << "There are "<< findEmpty() << " empty buckets." << endl;
  do{
    cout << "Please input a valid table location to see how many entries are there: ";
    cin >> num;
    if(num < 0 || num > (HASH_TABLE_SIZE - 1)){ /* search was invalid */
      cout << "Error. Value must be between " << (HASH_TABLE_SIZE - 1) << " and 0." << endl;
    }
  }while(num < 0 || num > (HASH_TABLE_SIZE - 1)); /* was the search valid */
  cout << "There are " << checkBucket(num) << " entries in bucket " << num << "." << endl;
  cout << "Input ten words to find in the table." << endl;
  for(int i = 0; i < 10; i++){ /* loop for 10 words */
    cout << "Please type the word you would like to search : ";
    cin >> word;
    searchTable(word);
  }
}
