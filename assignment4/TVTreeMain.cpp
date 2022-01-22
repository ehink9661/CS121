/* TVTreeMain.cpp
 *
 * CS 121-01.Bolden....g++ from CS server...........Ethan Hinkle
 * April 9, 2020....Dell Inspiron Intel Core i5
 * hink9661@vandals.uidaho.edu
 *
 * This is the main for Assignment #4, creating a searchable TV guide
 * from a tree and external file
 *--------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "TVTree.h"

using namespace std;

int main(){
  TVBST g1; /* class variable for the guide is created */
  string name = "TVData.txt"; /* file name is set to string name */
  g1.buildGuide(name); /* created guide based on string name */
  g1.searchMenu(); /* opens user search menu */
  return 0;
}
