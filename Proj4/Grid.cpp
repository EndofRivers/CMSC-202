/*****************************************
 ** File:    Grid.cpp
 ** Project: UMBC Battleship, Fall 2017
 ** Author:  Nicholas J Long
 ** Date:    1/15/2017
 ** Section: 
 ** E-mail: nlong2@umbc.edu
 **
 ** This will create the grid and populate it.
 ** Grid offers functions that assist with the
 ** flow of the game by returning bool variables
 ** that check the status of a square.
 **
 ***********************************************/
#include "Grid.h"

// Grid (Constructor)
// Fills in grid completely EMPTY
Grid::Grid() {
  for(int i = 0; i < SIZE; i++) {
    for(int j = 0; j < SIZE; j++) {
      m_grid[i][j] = EMPTY;
    }
  }
}
// Grid (Overloaded Contructor)
// Fills grid based on given file
Grid::Grid(string file) {

  fstream inputStream; // fstream variables
  int shipSize; // Temp holds the size of ship
  int shipCol; // Temp holds the Col of ship
  int shipRow; // Temp holds the Row of ship
  char shipOrientation; // Temp holds the orientation of ship
  int sizeCheck; // Temp holds if the size will go out of bounds

  inputStream.open(file.c_str());

  // Fill in the grid with EMPTY
  for(int i = 0; i < SIZE; i++) {
    for(int j = 0; j < SIZE; j++) {
      m_grid[i][j] = EMPTY;
    }
  }

  // loops until end of file is reached
  while(inputStream.good()) {

    // Initialize the temp variables
    inputStream >> shipSize >> shipCol
		>> shipRow >> shipOrientation;

    // Loops for the size of current ship
    // and fills in grid with ships
    for(int i = 0; i < shipSize; i++){

      if(shipOrientation == VERTICAL) {
	sizeCheck = shipRow + shipSize;

	// Checks if the ship will go out of bounds
	if(sizeCheck <= 10)
	  m_grid[shipRow + i][shipCol] = OCCUPIED;
	else
	  m_grid[shipRow - i][shipCol] = OCCUPIED;
      }
      if(shipOrientation == HORIZONTAL) {
	sizeCheck = shipCol + shipSize;

	// Checks if the ship will go out of bounds
	if(sizeCheck <= 10)
	  m_grid[shipRow][shipCol + i] = OCCUPIED;
	else
	  m_grid[shipRow][shipCol - i] = OCCUPIED;
      }
    }
  }
  inputStream.close();
}
// alreadyTried
// Given coordinates, returns if hit (true) or miss (false)
bool Grid::alreadyTried(int x, int y) {
  if(m_grid[y][x] == MISS || m_grid[y][x] == HIT)
    return true;
  else
    return false;
}
// isMiss
// Given coordinates, returns bool if the square is miss(true) or not(false)
bool Grid::isMiss(int x, int y) {
  if(m_grid[y][x] == MISS)
    return true;
  else
    return false;
}
// attack
// Given coordinates, returns int based on HIT(3) or MISS(2)
int Grid::attack(int x, int y) {
  if(m_grid[y][x] == OCCUPIED) {
    m_grid[y][x] = HIT;
    return HIT;
  }
  else {
    m_grid[y][x] = MISS;
    return MISS;
  }
}
// noOccupiedLeft
// Given nothing, returns bool if ships exist(false) or not(true)
bool Grid::noOccupiedLeft() {
  for(int i = 0; i < SIZE; i++) {
    for(int j = 0; j < SIZE; j++) {
      if(m_grid[i][j] == OCCUPIED) {
	return false;
      }
    }
  } return true;
}
// print
// given boolean, returns string
string Grid::print(bool hideShips) {

  stringstream ss; // stringstream variables

  // Formats and populates the stringstream
  ss << "  0 1 2 3 4 5 6 7 8 9" << endl;
  for(int i = 0; i < SIZE; i++) {

    ss << i << " ";
    for(int j = 0; j < SIZE; j++) {

      if(m_grid[i][j] == EMPTY) {
	ss << ". ";
      }
      else if(m_grid[i][j] == OCCUPIED) {
	if(hideShips == true)
	  ss << ". ";
	else
	  ss << "# ";
      }
      else if(m_grid[i][j] == HIT) {

	ss << "\033[1;31mx\033[0m ";
      }
      else if(m_grid[i][j] == MISS) {

	ss << "\033[1;34mo\033[0m ";
      }
    }
    ss << endl;
  }return ss.str();
}
