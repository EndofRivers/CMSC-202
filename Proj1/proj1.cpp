/************************************************************
 ** File: proj1.cpp
 ** Project: True Grit Snacks
 ** Author: Nicholas Long
 ** Date: 09/15/2017
 ** Section: 0103
 ** E-mail: nlong2@umbc.edu
 **
 ** This program is a text based snack kiosk for True Grits.
 ** It will promt the user through a variety of different
 ** menus and options. Once the order is complete, it will
 ** prints their receipt to the screen as well as save it
 ** for further reference.
 **
 ***********************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const double SALES_TAX = 0.06; // Maryland Sales Tax
const int MENU_ARRAY = 10; // Size of menu array
const int MAX_ORDERS = 3; // Maximum order size
const char MENU_FILE[20] = "proj1_items.txt"; // name of menu text file
const char RECEIPT_FILE[20] = "Receipt.txt"; // name of the receipt text file

void mainMenu();
void loadTable(double[], string[]);
void printMenu(double[], string[]);
void manageOrder(double[], string[]);
void writeReceipt(int[][2], double[], string[], int);
void viewReceipt();

// main
// where the program execution starts, return 0
int main() {

  mainMenu();
  return 0;
}// main

// mainMenu
// Given nothing, controls the flow of the program
void mainMenu() {

  int menuSelection; // Used to navigate switch
  string menuItems[MENU_ARRAY]; // holds the menu item names as strings
  double menuPrices[MENU_ARRAY]; // holds the menu prices as doubles

  // fills the empty arrays menuPrices and menuItems
  loadTable(menuPrices, menuItems);

  cout << "Welcome to the True Grit Snack Bar" << endl;

  // Loops until user selects 3 and exits
  while(menuSelection != 3) {

    // Loops until valid input selected (1-3)
    do {

      cout << "What would you like to do?: " << endl;
      cout << "1. New Order" << endl;
      cout << "2. View Receipts" << endl;
      cout << "3. Exit" << endl;
      cin >> menuSelection;
    } while(menuSelection > 3 || menuSelection < 1);

    // Calls different fuctions with switch depending on previous input
    switch(menuSelection) {

    case 1:
      manageOrder(menuPrices, menuItems);
      break;

    case 2:
      viewReceipt();
      break;

    case 3:
      cout << "Thank you for using True Grit Snack Bar" << endl;
      break;
    }// switch
  }// while
}// mainMenu

// manageOrder
// Given menu items and prices, 
void manageOrder(double menuPrices[], string menuItems[]) {

  int currentOrder[MAX_ORDERS][2]; // Consumers current order
  string yesNo = "y"; // determines if the consumer would like to order again
  int timesOrdered = 0; // counts how many times the consumer has ordered

  // loops a total of 3 times as per project requirements
  for(int i = 0; i < MAX_ORDERS; i++) {

    printMenu(menuPrices, menuItems);
    
    for(int j = 1; j > -1; j--) {
      if(j == 1) {

	cout << "What would you like to buy?: " << endl;
	cin >> currentOrder[i][j];
	
	// if-statement validates consumer input
	if(currentOrder[i][j] < 1 || currentOrder[i][j] > 10) {

	  printMenu(menuPrices, menuItems);
	  j = 2;
	}// if
      }// if
      
      if(j == 0) {

	cout << "How many would you like to buy?: " << endl;
	cin >> currentOrder[i][j];

	// if-statement validate consumer input
	if(currentOrder[i][j] < 1) {

	  printMenu(menuPrices, menuItems);
	  j = 1;
	}// if
      }// if
    }// for

    do {    
      cout << "Do you want to add more items? (y/n):" << endl;
      cin >> yesNo;
    }while(yesNo != "n" && yesNo != "y");
    
    timesOrdered++;
    
    // closes the for loop if consumer is finished
    if(yesNo == "n") {

      i = MAX_ORDERS;
    }// if

  }// for

  writeReceipt(currentOrder, menuPrices, menuItems, timesOrdered);
}// manageOrder

// writeReceipt
// Given what consumer ordered and quantity, how many times they ordered, 
// and the menu items and prices. Returns nothing.
void writeReceipt(int currentOrder[][2], double menuPrices[],
		  string menuItems[], int timesOrdered) {

  ofstream outputStream; // creation of the fstream variable
  double subTotal; // total price before taxes
  double totalPrice; // Price of the entire order, including taxes
  double totalTax; // total tax that is added to the subTotal

  // Sets currency precision for the receipt
  outputStream.setf(ios::fixed);
  outputStream.setf(ios::showpoint);
  outputStream.precision(2);

  // Opens the Receipt file, which holds the last order completed.
  outputStream.open("Receipt.txt");

  // Outputs the receipt header to the screen as well as to the receipt file
  cout << "Your Order: " << endl;
  outputStream << "Your Order: " << endl;

  cout << setw(20) << "Qnty";
  outputStream << setw(20) << "Qnty";

  cout << setw(20) << "Item";
  outputStream << setw(20) << "Item";

  cout << setw(20) << "Price" << endl;
  outputStream << setw(20) << "Price" << endl;

  // Loops as many times as the consumer ordered, cannot exceed three loops
  for(int i = 0; i < timesOrdered; i++) {

    for(int j = 0; j < 2; j++) {

      if(j == 0) {

	// Prints the quantity of each item to the screen
	// Also writes the same information to the receipt file
	cout << setw(20) << currentOrder[i][j];
	outputStream << setw(20) << currentOrder[i][j];
      }// if

      if(j == 1) {

	// Prints the name of the item to the screen
	// Also writes the same information to the receipt file
	cout << setw(20) << menuItems[currentOrder[i][j] - 1];
	outputStream << setw(20) << menuItems[currentOrder[i][j] - 1];

	// Prints the price of the item to the screen
	// Also writes the same information to the receipt file
	cout << setw(20) << menuPrices[currentOrder[i][j] - 1] << endl;
	outputStream << setw(20) << menuPrices[currentOrder[i][j] - 1] << endl;

	// Calucates the subTotal of the order
	subTotal = subTotal + menuPrices[currentOrder[i][j] - 1] * currentOrder[i][j-1];
      }// if
    }// for
  }// for

  // Calculations for the remaining totals
  totalTax = subTotal * SALES_TAX;
  totalPrice = totalTax + subTotal;

  // Prints the totals to the screen and writing them to the receipt
  cout << "Subtotal: " << subTotal << endl;
  outputStream << "Subtotal: " << subTotal << endl;

  cout << "Tax: " << totalTax << endl;
  outputStream << "Tax: " << totalTax << endl;

  cout << "Total: " << totalPrice << endl;
  outputStream << "Total: " << totalPrice << endl;

  cout << "Receipt Written" << endl;
  outputStream << "Receipt Written" << endl;

  outputStream.close();
}// writeReceipt

// viewReceipt
// given nothing, prints the information from the receipt file to the screen
void viewReceipt() {

  fstream inputStream; // Creation of the fstream variable
  string nextLine; // used to print a line from receipt file

  inputStream.open(RECEIPT_FILE);

  // Loops until it reaches the end of the file
  while(inputStream.good()) {

    getline(inputStream, nextLine);
    cout << nextLine << endl;
  }// while

  inputStream.close();
}// viewReceipt


void loadTable(double menuPrices[], string menuItems[]) {

  fstream inputStream; // creating fstream variable

  inputStream.open(MENU_FILE); 

  // Extracts data from the text file
  for(int i = 0; i < MENU_ARRAY; i++) {

    getline(inputStream, menuItems[i], ',');
    inputStream >> menuPrices[i];

    if(inputStream.peek() == '\n') {

      inputStream.ignore();
    }// if
  }// for

  cout << "The item list was successfully loaded" << endl;

  inputStream.close();
}// loadTable

// printMenu
// given menu items and menu prices, returns nothing
void printMenu(double menuPrices[], string menuItems[]) {

  // Sets precision for cout
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);

  // Prints the menu information using setw for formatting
  cout << setw(20) << "Number";
  cout << setw(20) << "Item";
  cout << setw(20) << "Price" << endl;

  for(int i = 0; i < MENU_ARRAY; i++) {

    cout << setw(20) << i + 1 << ".";
    cout << setw(20) << menuItems[i];
    cout << setw(20) << "$" <<  menuPrices[i] << endl;
  }// for
}// printMenu
