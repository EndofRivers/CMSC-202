/*****************************************
 ** File:    main.cpp
 ** Project: UMBC Battleship, Fall 2017
 ** Author:  Nicholas J Long
 ** Date:    1/15/2017
 ** Section:
 ** E-mail: nlong2@umbc.edu
 **
 ** This holds the main method for the Battleship
 ** project. Everything is run from here
 **
 ***********************************************/
#include "Player.h"
#include "Computer.h"
#include "User.h"

int main(int argc, char* argv[]) {

  string file1 = argv[1]; // holds the first file passed
  string file2 = argv[2]; // holds the second file passed

  Computer computerOne(file1); // computer one object
  Player* computerOnePtr = &computerOne; // Player pointer for vector

  Computer computerTwo(file2); // computer two object
  Player* computerTwoPtr = &computerTwo; // Player pointer for vector

  User user(file2); // User object
  Player* userPtr = &user; // Player pointer for vector

  User userTwo(file1);
  Player* userPtrTwo = &userTwo;

  vector<Player*> players; // Holds all of the current players

  // Populate the vector
  players.push_back(userPtr);
  players.push_back(computerOnePtr);
  players.push_back(computerTwoPtr);
  //  players.push_back(userPtrTwo);

  int coin = 0; // determines if User vs Comp or Comp vs Comp
  int numTurns = 0; // Counts the number of turns in Comp vs Comp

  if(argv[1] > 0) {
    cout << "Ships Loaded" << endl;
  }

  else {
    cout << "No text file loaded - try make run1" << endl;
    return 0;
  }

  // Awesome Text Art by Matthew Bace
  cout << "                                      |__" << endl
       << "                                      |\\/" << endl
       << "                                      ---" << endl
       << "                                    / | [" << endl
       << "                             !      | |||" << endl
       << "                           _/|     _/|-++'" << endl
       << "                       +  +--|    |--|--|_ |-" << endl
       << "                    { /|__|  |/\\__|  |--- |||__/" << endl
       << "                   +---------------___[}-_===_.'____                 /\\ " << endl
       << "                ____`-' ||___-{]_| _[}-  |     |_[___\\==--            \\/   _" << endl
       << " __..._____--==/___]_|__|_____________________________[___\\==--____,------' .7 "<< endl
       << "|                                                                     BB-61/ " << endl
       << " \\_________________________________________________________________________| " << endl
       << "  Matthew Bace " << endl
       << "\033[1;31m Welcome to UMBC Battleship\033[0m" << endl;

  // Press 1 for User vs Comp and 2 for Comp vs Comp
  do {

    cout << endl << "\033[1;34m Press 1 to Insert Coin...\033[0m" << endl;
    cin >> coin;
  }while (coin < 1 || coin > 2);

  // User vs Computer
  if(coin == 1) {
    // While nobody has lost
    while(players.at(1)->hasLost() == false &&
	  user.hasLost() == false) {
      
      players.at(1)->printBoard();
      players.at(0)->printBoard();

      // Player 1 Attack if nobody has lost
      if(players.at(1)->hasLost() == false && players.at(0)->hasLost() == false)
	players.at(0)->makeMove(players.at(1)->getGrid());
      
      //Confirm victory for Player 1
      if(players.at(1)->hasLost() == true) {	
	cout << "Player has sunk all of the Computer's battleships!" << endl;
	players.at(1)->printBoard();
	players.at(0)->printBoard();
      }// if

      // Computer attack if nobody has lost
      if(players.at(1)->hasLost() == false && players.at(0)->hasLost() == false)
	players.at(1)->makeMove(players.at(0)->getGrid());

      // Confirm victory for Computer
      if(players.at(0)->hasLost() == true) {
	cout << "The computer has sunk all of your battleships! Insert coin to try again!" << endl;
	players.at(1)->printBoard();
	players.at(0)->printBoard();
      }
    }//while
  }

  // Computer vs Computer
  if(coin == 2) {
    // While nobody has lost
    while(players.at(1)->hasLost() == false &&
          players.at(2)->hasLost() == false) {

      numTurns++;
      players.at(1)->printBoard();
      players.at(2)->printBoard();

      // Attacks if nobody has lost
      if(players.at(1)->hasLost() == false && players.at(2)->hasLost() == false)
        players.at(2)->makeMove(players.at(1)->getGrid());

      // Checks if Computer 1 has won
      if(players.at(1)->hasLost() == true) {
        cout << "Computer 2 wins!" << endl;
	cout << "NUMBER OF ROUNDS: " << numTurns << endl;
	players.at(1)->printBoard();
	players.at(2)->printBoard();
      }

      // Attacks if nobody has lost
      if(players.at(1)->hasLost() == false && players.at(2)->hasLost() == false)
        players.at(1)->makeMove(players.at(2)->getGrid());

      // Checks if COmputer 2 has won
      if(players.at(2)->hasLost() == true) {
        cout << "Computer 1 wins!" << endl;
	cout << "NUMBER OF ROUNDS: " << numTurns << endl;
	players.at(1)->printBoard();
	players.at(2)->printBoard();
      }
    }
  }
}
