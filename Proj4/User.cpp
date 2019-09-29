/*****************************************
 ** File:    User.cpp
 ** Project: UMBC Battleship, Fall 2017
 ** Author:  Nicholas J Long
 ** Date:    1/15/2017
 ** Section:
 ** E-mail: nlong2@umbc.edu
 **
 ** A child of player. This is the class that is
 ** used if a human player is playing the game.
 ** It offers a basic interface for the human
 ** to decide where to attack.
 **
 ***********************************************/
#include "User.h"

// User (Constructor)
// Calls Player's constructor
User::User(): Player() {}
// User (Overloaded Constructor)
// Calls Player's overloaded constructor
User::User(string file): Player(file) {}
// makeMove
// Given oppoents grid, returns nothign
void User::makeMove(Grid* grid) {

  int xCoord;
  int yCoord;
  do {

    cout << "Enter x (column): ";
    cin >> xCoord;
    cout << "Enter y (row):  ";
    cin >> yCoord;
  }while(grid->alreadyTried(xCoord, yCoord) == true
	 || (yCoord < 0 || yCoord > 9)
	 || (xCoord < 0 || xCoord > 9));

  if(grid->attack(xCoord, yCoord) == 3)
    cout << "You" << "\033[1;31m Hit\033[0m" << endl;
  else
    cout << "You" << "\033[1;34m Missed\033[0m" << endl;
}
// printBoard
// Given nothing, returns nothing
void User::printBoard() {
  cout << "******PLAYER******" << endl;
  cout << m_grid->print(false);
}
