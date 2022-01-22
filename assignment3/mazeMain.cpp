/* mazeMain.cpp
 *
 * CS 121-01.Bolden....g++ from CS server...........Ethan Hinkle
 * Febuary 28, 2020....Dell Inspiron Intel Core i5..hink9661@vandals.uidaho.edu
 *
 * This file contains the int main() for our assignment #3, using a linked list queue to navigate a maze given by a text file
*---------------------------------------------------------------------
*/

#include <iostream>
#include <fstream>
#include <string>
#include "maze.h" /* allows for prototypes and the class to be read */

using namespace std;

int main(){
  cout << "Hello! Are you ready to solve some mazes? Great!" << endl;
  cout << "First here are some exaxmple mazes." << endl;
  maze m1; /* creates maze variable m1 */
  string file = "testMaze.txt"; /* creates string variable */
  int cont = 1; /* contilue variable */
  cout << "Here is a simple maze that can be solved" << endl;
  m1.read(file); /* reads string file */
  m1.print(); /* prints maze for viewing by user */
  m1.solve(); /* attempts to solve the maze in the array */
  cout << "Here is that maze solved." << endl;
  m1.print(); /* prints now completed maze */
  m1.clearArr(); /* clears array for future use */
  file = "testMaze2.txt";
  cout << "Now here is a maze that can not be solved." << endl;
  m1.read(file);
  m1.print();
  m1.solve();
  cout << "Here is that maze after the program has determined that the maze is unsolvable." << endl;
  m1.print();
  m1.clearArr();
  cout << "Now you try. Please note we will not print these mazes to save space." << endl;
  while(cont == 1){ /* loop for user to run multiple mazes */
    cout << "Please input your maze file." << endl;
    cin >> file;
    m1.read(file);
    m1.solve();
    m1.clearArr();
    cout << "Do you wish to solve another maze? Yes(1) No(0)" << endl;
    cin >> cont;
  }
  cout << "Goodbye!" << endl;
  return 0;
}
