/* hashDictMain.cpp
 *
 * CS 121-01.Bolden....g++ from CS server...........Ethan Hinkle
 * May 2, 2020....Dell Inspiron Intel Core i5
 * hink9661@vandals.uidaho.edu
 *
 * This is the int main() file for Assignment #5, using sourced hash
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

int main(){
  string file;
  cout << "Please input file: ";
  cin >> file;
  buildTable(file);
  menu();
  return 0;
}
