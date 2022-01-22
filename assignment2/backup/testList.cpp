/* testList.cpp
 *
 * CS 121.Bolden.........Compiler version...........Ethan Hinkle
 * Febuary 9, 2020.......Computer & CPU.............hink9661@vandals.uidaho.edu
 *
 * Brief description of program and objective.
 *---------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>
#include "list.h"

using namespace std;

int main(){
  string file;
  cout << "What file would you like me to read?" << endl;
  cin >> file;
  read(file);
  return 0;
}
