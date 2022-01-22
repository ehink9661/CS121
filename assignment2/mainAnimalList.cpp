/* mainAnimalList.cpp
 *
 * CS 121-01.Bolden.........g++ on CS server..............Ethan Hinkle
 * Febuary 9, 2020..........Dell Inspiron Intel Core i5...hink9661@vandals.uidaho.edu
 *
 * This is the int main function for assignment #2, using a text file of animals to edit and print a linked list.
 *---------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>
#include "animalList.h"

using namespace std;

int main(){
  string file;
  int cont = 0;
  cout << "Hello. " << endl;
  do{
    cout << "What file would you like me to read?" << endl;
    cin >> file;
    read(file);
    cout << "Do you wish to read another file? Yes(1), No(0)" << endl;
    cin >> cont;
    clear();
  }while(cont == 1);
  cout << "Goodbye!" << endl;
  return 0;
}
