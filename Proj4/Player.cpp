/*****************************************
 ** File:    Player.cpp
 ** Project: UMBC Battleship, Fall 2017
 ** Author:  Nicholas J Long
 ** Date:    1/15/2017
 ** Section:
 ** E-mail: nlong2@umbc.edu
 **
 ** Player is the parent class of both User
 ** and Computer. It is too genaric to be used
 ** without a child.
 **
 ***********************************************/
#include "Player.h"

// Player (Constructor)
// Creates a new Grid, returns nothing
Player::Player() {
  m_grid = new Grid();
}
// Player (Overloaded Constructor)
// Creates a new grid based on file, returns nothing
Player::Player(string file) {
  m_grid = new Grid(file);
}
// Player (Destructor)
// Deletes grid and sets to NULL, returns nothing
Player::~Player() {
  delete m_grid;
  m_grid = NULL;
}
// hasLost
// Given nothing, returns bool if there are any ships left
bool Player::hasLost() {
  return m_grid->noOccupiedLeft();
}
// getGrid
// Given nothing, returns grid
Grid* Player::getGrid() {
  return m_grid;
}
// printBoard
// Given nothing, returns nothing
void Player::printBoard() {
  m_grid->print(false);
}
