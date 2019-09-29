/*****************************************
 ** File:    Computer.cpp
 ** Project: UMBC Battleship, Fall 2017
 ** Author:  Nicholas J Long
 ** Date:    1/15/2017
 ** Section:
 ** E-mail: nlong2@umbc.edu
 **
 ** A child of Player. This is the computer
 ** variant of the player. The computer will
 ** fire randomly in a checkered pattern until
 ** it hits a ship. Once it hits a ship, the
 ** computer will sink it by checking the
 ** entire ship as well as it's surrounding
 ** squares.
 **
 ***********************************************/
#include "Computer.h"

// Computer (Constructor)
// Calls Player's Constructor, sets coordinates to -1
Computer::Computer(): Player() {
  m_xLast = -1;
  m_yLast = -1;
  m_xCenter = -1;
  m_yCenter = -1;
}
// Computer (Overloaded Constructor)
// Calls Player's Overloaded sets coordinates to -1
Computer::Computer(string file): Player(file) {
  m_xLast = -1;
  m_yLast = -1;
  m_xCenter = -1;
  m_yCenter = -1;
}
// makeMove
// Given other players grid, makes an attack
void Computer::makeMove(Grid* grid) {

  srand(time(NULL));

  // Randomly firing to search for ships
  if(m_xLast == -1 || m_yLast == -1) {

    getNewCoordinates(grid);
  }

  if(m_xCenter == -1 || m_yCenter == -1) {

    makeRandomAttack(grid, false);
  }

  // Begin targetting and sinking ship
  else {

    // Checks if the random shooting has already
    // hit and missed a square bordering the ship
    // Recenters coordinates to continue attacking
    if(grid->alreadyTried(m_xLast, m_yLast -1) == true
       && grid->isMiss(m_xLast, m_yLast - 1) == true)
      m_yLast = m_yCenter;

    if(grid->alreadyTried(m_xLast, m_yLast + 1) == true
       && grid->isMiss(m_xLast, m_yLast + 1) == true)
      m_yLast = m_yCenter;

    if(grid->alreadyTried(m_xLast + 1, m_yLast) == true
       && grid->isMiss(m_xLast + 1, m_yLast) == true)
      m_xLast = m_xCenter;

    if(grid->alreadyTried(m_xLast - 1, m_yLast) == true
       && grid->isMiss(m_xLast - 1, m_yLast) == true)
      m_xLast = m_xCenter;

    // Checks the square above (x, y)
    // Attacks if it has not been checked
    // Recenters coordinate if MISS
    if(grid->alreadyTried(m_xLast, m_yLast - 1) == false
       && (m_yLast - 1) <= 9) {

      m_yLast--;
      if(makeRegularAttack(grid) == false)
	m_yLast = m_yCenter;
    }
    // Checks the square below (x, y)
    // Attacks if it has not been checked
    // Recenters coordinate if MISS
    else if(grid->alreadyTried(m_xLast, m_yLast + 1) == false
	    && (m_yLast + 1) >= 0) {

      m_yLast++;
      if(makeRegularAttack(grid) == false)
        m_yLast = m_yCenter;
    }
    // Checks the square to the right of (x, y)
    // Attacks if it has not been checked
    // Recenters coordinate if MISS
    else if(grid->alreadyTried(m_xLast + 1, m_yLast) == false
	    && (m_xLast + 1) <= 9) {

      m_xLast++;
      if(makeRegularAttack(grid) == false)
        m_xLast = m_xCenter;
    }
    // Checks the square to the left of (x, y)
    // Attacks if it has not been checked
    // Recenters coordinate if MISS
    else if(grid->alreadyTried(m_xLast - 1, m_yLast) == false
	    && (m_xLast - 1) >= 0) {

      m_xLast--;
      if(makeRegularAttack(grid) == false)
        m_xLast = m_xCenter;
    }
    // Ship has been sunk
    // Gets a new random coordinate and attacks
    else {
      getNewCoordinates(grid);
      makeRandomAttack(grid, true);
    }
  }
}
// printBoard
// Given nothing, returns nothing
void Computer::printBoard() {
  cout << "******COMPUTER******" << endl;
  cout << m_grid->print(true);
}
// makeRegularAttack
// Given opponents grid, returns if attack hit(true) or not(false)
bool Computer::makeRegularAttack(Grid* grid) {

  // Calls Grid's attack, only entering the if statement if the attack hits(3)
  if(grid->attack(m_xLast, m_yLast) == 3) {
    cout << "Computer" << "\033[1;31m Hit\033[0m" << endl;
    return true;
  }
  else {
    cout << "Computer" << "\033[1;34m Missed\033[0m" << endl;
    return false;
  }
}
// makeRandomAttack
// Given oppoents grid and a reset bool, Returns nothing
void Computer::makeRandomAttack(Grid* grid, bool reset) {

  // Calls Grid's attack, only entering the if statement if the attack hits(3)
  if(grid->attack(m_xLast, m_yLast) == 3) {

    cout << "Computer" << "\033[1;31m Hit\033[0m" << endl;
    // On hit, set the center point for the computer to shoot around
    m_xCenter = m_xLast;
    m_yCenter = m_yLast;
  }
  else {
    cout << "Computer" << "\033[1;34m Missed\033[0m" << endl;

    // Completely reset the center point if true
    if(reset) {
      m_xCenter = -1;
      m_yCenter = -1;
    }
    getNewCoordinates(grid);
  }
}
// getNewCoordiantes
// Given opponents grid, returns nothing
void Computer::getNewCoordinates(Grid* grid) {

  // Will randomly generate a coordinate that has not been hit
  // between (0-9,0-9) and forces one to be odd and the other even
  // Creates a randomly firing checkered pattern
  do {
    m_xLast = rand() % 10;
    m_yLast = rand() % 10;
  }while(grid->alreadyTried(m_xLast, m_yLast) == true
	 || m_xLast % 2 == m_yLast % 2);
}
