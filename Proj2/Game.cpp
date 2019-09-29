/***********************************************************
 ** File:    Game.cpp
 ** Project: CMSC 202 Project 2, Fall 2017
 ** Author:  Nicholas Long
 ** Date:    10/19/17
 ** Section: 0103
 ** Email:   nlong2@umbc.edu
 **
 ** This file contains the bulk of the code for Project 2.
 ** This program code will do the following: 
 ** Ask the user for the required information
 ** Read the data in from a file and populate the Vectors
 ** Control the flow of the game
 ** Check for victory and dead troops
 ** Allow player to attack and change troops
 ** Display current troops
 **
 **
 **********************************************************/
#include "Game.h"


// Game
// Constructor
// Given nothing, returns nothing
// Asks the player for information and calls functions to start game
Game::Game() {

  cout << "What is your name?" << endl;
  getline(cin, m_name);

  // Asks player for a number between 2-5
  // Asks again if invalid input
  do {
    cout << "How many troops would you like? (2-5)" << endl;
    cin >> m_max;
  }while (m_max < 2 || m_max > 5);


  LoadTroops();
  RandomizeTeam();

  /* DEBUG FUNCTION
     Tests to see if Troops were loaded in successfullu

     DisplayTroops();

  */

  StartGame();
} // Game Constructor


// LoadTroops
// Given Nothing, Returns nothing
// Populates the m_troop vector using given file
void Game::LoadTroops() {

  fstream inputStream; // used to read in data from file
  string name; // Tempoarily Holds a troops name
  int health; // Tempoarily Holds a troops health
  int damage; // Tempoarily Holds a troops damage
  string target; // Tempoarily Holds a troops target
  bool isFlying; // Tempoarily Holds if a troop can fly

  // Open File
  inputStream.open(PROJ2_TROOPS.c_str());

  // Loops until it reaches the end of the file
  while(inputStream.good()) {

    // Extracts data from file
    inputStream >> name >> health >> damage >> target >> isFlying;

    // Populate m_troop with Troop objects
    m_troop.push_back(Troop(name, health, damage, target, isFlying));
  }// while
}// LoadTroops


// RandomizeTeam
// Given nothing, returns nothing
// Populates m_player and m_computer randomly
void Game::RandomizeTeam() {

  srand(time(NULL));

  // Loops equal to how many troops the player wants on their team
  for(int i = 0; i < m_max; i++) {
    
    // Randomly generates a number between 0-48
    // And populates m_player and m_computer
    m_player.push_back(m_troop.at(rand() % 49));
    m_computer.push_back(m_troop.at(rand() % 49));
  }// For
  cout << "Both teams have been populated." << endl;
}// RandomizeTeam

void Game::StartGame() {

  // Calls MainMenu() until either m_computer or m_player is empty
  do {
    MainMenu();
  }while(m_computer.empty() != true && m_player.empty() != true);

  // If m_player is empty, then computer wins
  if(m_player.empty() == true) {

    cout << "Computer wins!" << endl;
  }// if

  // If m_computer is empty, then player wins
  if(m_computer.empty() == true) {

    cout << m_name << " wins!" << endl;
  }// if
}// StartGame


// DisplayTroops
// Given nothing, returns nothing
// DEBUG FUNCTION
// Prints every troop from m_troop to the screen
void Game::DisplayTroops() {

  cout << "*******************" << endl;
  cout << "Troops" << endl;

  // Loops equal to the size of m_troop
  for(int i = 0; i < (int) m_troop.size(); i++) {

    // Print troop name and health to screen
    cout << m_troop.at(i).GetName() << " " << m_troop.at(i).GetHealth() << endl;
  }// For
}// DisplayTroops


// ChangeTroop
// Given nothing, returns nothing
// Allows the player to change which troop to attack with
void Game::ChangeTroop() {

  // Loops until a number 1 to the size of m_player minus one is input
  do {

    DisplayTeam();

    // Sets m_curTroop based on player input
    cout << "Which troop do you want to use?" << endl;
    cin >> m_curTroop;
    m_curTroop--;

    cout << "*******************" << endl;
  }while(m_curTroop < 0 || m_curTroop > (int) m_player.size() - 1);
}// ChangeTroop


// MainMenu
// Given nothing, Returns nothing
// Controls the flow of the game by given the player choices
// Player can do any of the following: 
// Display Teams, Change Troop, Attack, or Quit
void Game::MainMenu() {

  int menuChoice; // Holds player's menu choice

  DisplayTeams();

  // Print Menu and Ask user for choice
  cout << "What would you like to do?" << endl;
  cout << "1. Display Team" << endl;
  cout << "2. Change Current Troop" << endl;
  cout << "3. Attack!" << endl;
  cout << "4. Quit" << endl;
  cin >> menuChoice;
    
  // Switch controls flow for the game
  switch(menuChoice){

    // Display m_player and m_computer
  case 1:
    DisplayTeams();
    break;
    
    // Allow player to change m_curTroop
  case 2:
    ChangeTroop();
    break;
    
    // Allow player to attack with m_curTroop
  case 3:
    Attack();
    break;

    // call exit if player wishes to quit
  case 4:
    exit(1);
    break;
  }// Switch
}// MainMenu


// DisplayTeams
// Given nothing, returns nothing
// Prints m_player and m_computer to the screen
void Game::DisplayTeams() {

  cout << "*******************" << endl;
  cout << m_name << "'s Team" << endl;

  // Loops equal to the size of m_player
  for(int i = 0; i < (int) m_player.size(); i++) {

    // Print troop name and health
    cout << m_player.at(i).GetName() << " " << m_player.at(i).GetHealth() << endl;
  }// For

  cout << "*******************" << endl;
  cout << "Computer's Team" << endl;

  // Loops equal to the size of m_computer
  for(int i = 0; i < (int) m_computer.size(); i++) {

    //Print troop name and health
    cout << m_computer.at(i).GetName() << " " << m_computer.at(i).GetHealth() << endl;
  }// For

  cout << "*******************" << endl;
}// DisplayTeams


// DisplayTeam
// Given nothing, return nothing
// Prints only m_player's troop
void Game::DisplayTeam() {

  cout << "*******************" << endl;
  cout << m_name << "'s Team" << endl;

  // Loops equal to the size of m_player
  for(int i = 0; i < (int) m_player.size(); i++) {

    // Print a numbered menu of the troop's name and health
    cout << i + 1 << ". " << m_player.at(i).GetName() << " "
	 << m_player.at(i).GetHealth() << endl;
  }// For
}// DisplayTeam


// Attack
// Given nothing, Returns nothing
// Allows the player and computer to attack each other
void Game::Attack() {

  // Player's turn
  if(m_curPlayer == 0) {

    // Only attacks if troops are left, player attack
    if(m_computer.empty() != true && m_player.empty() != true)
      m_player.at(m_curTroop).AttackTroop(m_computer.at(0));

    // If health was lowered below 0, remove that troop from game
    if(m_computer.at(0).GetHealth() <= 0) {

      cout << m_computer.at(0).GetName() << " dies!" << endl;
      m_computer.erase(m_computer.begin());
    }// if

    // Only attacks if troops are left, computer attack
    if(m_computer.empty() != true && m_player.empty() != true)
      m_computer.at(0).AttackTroop(m_player.at(0));

    // If health was lowered below 0, remove that troop from game
    if(m_player.at(0).GetHealth() <= 0) {

      cout << m_player.at(0).GetName() << " dies!" << endl;
      m_player.erase(m_player.begin());

      // If the player has chosen a specific troop to attack with
      // This will keep that choice accurate.
      if(m_curTroop > 0)
	m_curTroop--;
    }// if

    // Set next turn to computer's turn
    m_curPlayer = 1;
  }// if

  // Computer's Turn
  else if(m_curPlayer == 1) {

    // Only attacks if troops are left, computer attack
    if(m_computer.empty() != true && m_player.empty() != true)
      m_computer.at(0).AttackTroop(m_player.at(0));

    // If health was lowered below 0, remove that troop from game
    if(m_player.at(0).GetHealth() <= 0) {

      cout << m_player.at(0).GetName() << " dies!" << endl;
      m_player.erase(m_player.begin());

      // If the player has chosen a specific troop to attack with
      // This will keep that choice accurate.
      if(m_curTroop > 0)
	m_curTroop--;
    }// if

    // Only attacks if troop are left, player attack
    if(m_computer.empty() != true && m_player.empty() != true)
      m_player.at(m_curTroop).AttackTroop(m_computer.at(0));

    // If health was lowered below 0, remove that troop from game
    if(m_computer.at(0).GetHealth() <= 0) {

      cout << m_computer.at(0).GetName() << " dies!" << endl;
      m_computer.erase(m_computer.begin());
    }// if

    // Set next turn to player's turn
    m_curPlayer = 0;
  }// else if
}// Attack
