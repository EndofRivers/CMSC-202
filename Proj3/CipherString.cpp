#include "CipherString.h"
 
 /***** PRIVATE VARIABLES
  Node* m_head; //Node pointer that is the head of the linked list
  int m_size; //Size of the linked list (number of nodes)
  **** */

// Name: CipherString - default constructor
// Preconditions - None
// Postconditions - Creates a new CipherString
CipherString::CipherString() {

  m_head = NULL;
  m_size = 0;
}// CipherString Constructor


// Name: CipherString - overloaded constructor
// Preconditions - None
// Postconditions - Creates a new CipherString (using char*)
CipherString::CipherString(const char* MESSAGE_CHAR) {

  m_head = NULL;
  m_size = 0;
  loadMessage(MESSAGE_CHAR);
}// CipherString Constructor


// Name: ~CipherString - destructor
// Preconditions - None
// Postconditions - Destroys CipherString
CipherString::~CipherString() {

  Node *temp = m_head; // temp node to itterate through list

  //loops until temp is NULL
  while(temp != NULL) {

    //Delete temp information
    Node* next = temp->getNext();
    delete temp;
    temp = next;
    m_size--;
  }// while
  
  //Set m_head to NULL to complete deletion
  m_head = NULL;
}// CipherSTring Destructor


// Name: loadMessage
// Preconditions - File (with text in it) is passed to function
// Postconditions - Opens file and loads one character at a time into the linked list
void CipherString::loadMessage(const char* MESSAGE_CHAR) {

  fstream inputStream; // Creation of the fstream variable
  char ch; // placeholder variable for the characters in MESSAGE_CHAR

  inputStream.open(MESSAGE_CHAR);

  // loops until end of file
  while(inputStream.good()) {

    inputStream >> noskipws >> ch;

    //Adds ch to the linked list
    addCharacter(ch);
  }// while
}// loadMessage


// Name: addCharacter
// Preconditions - Linked list exists
// Postconditions - Adds character to end of linked list
void CipherString::addCharacter(char addChar) {

  Node *node = new Node(addChar); // New node to add to list

  // if linked list is empty
  if(m_head == NULL) {
    m_head = node;
  }// if
  
  // if linked list is not empty
  else {
    Node *temp = m_head; //
    
    // loops until the end of list
    while(temp->getNext() != NULL) {

      // itterates through list
      temp = temp->getNext();
    }// while

    // places new node at the end of list
    temp->setNext(node);

    m_size++;
  }// else
}// addCharacter


// Name: encryptOng
// Preconditions - Linked list exists
// Postconditions - For each consonent, adds a node with "o", adds a node with "n"
// adds a node with "g". Every "letter" is separated with a "-" and each word is
// seperated by a space.
void CipherString::encryptOng() {

  Node *temp = m_head; // temp file for itteration
  Node *toChange; // node variable to know which to change
  char ch; // placeholder for the current data value
  bool isConsonant = true; // bool to switch on and off consonants

  Node *node; // new node variable

  // Sets temp to head, loops until the end of list, and itterates through list
  for(temp = m_head; temp != NULL; temp = temp->getNext()) {

    // set ch to the current data value saved in temp
    ch = temp->getChar();

    // Checks if the char in temp is a vowel
    // then updates isConsonant accordingly
    if(ch == 'a' || ch == 'A' || ch == 'e' || ch == 'E' ||
       ch == 'i' || ch == 'I' || ch == 'o' || ch == 'O' ||
       ch == 'u' || ch == 'U')
      isConsonant = false;
    else
      isConsonant = true;

    // if the value is a Consonant, and not a space or a newline char
    if(isConsonant == true  && ch != ' ' && ch != '\n') {

      //loops four times to switch between o, n ,g, and -
      for(int i = 0; i < 4; i++) {
	if(i == 0)
	  node = new Node('o');
	if(i == 1)
	  node = new Node('n');
	if(i == 2)
	  node = new Node('g');
	if(i == 3)
	  node = new Node('-');

	// if it is adding a hypen, and the next char is not a space
	// or a new line
	if(i == 3){
	  if(temp->getNext()->getChar() != ' '
	     && temp->getNext()->getChar() != '\n') {
	    toChange = temp->getNext();
	    temp->setNext(node);
	    node->setNext(toChange);
	    temp = temp->getNext();
	  }// if
	}// if

	// otherwise add the node normally
	else {
	  toChange = temp->getNext();
	  temp->setNext(node);
	  node->setNext(toChange);
	  temp = temp->getNext();
	}//else

      }// for
    }// if

    // if the char is a vowel, and not a space or a newline char
    if(isConsonant == false  && ch != ' ' && ch != '\n') {

      node = new Node('-');

      // adds a - in front of every vowel
      // unless the next character is a space or a newline
      if(temp->getNext()->getChar() != ' '
	 && temp->getNext()->getChar() != '\n') {

	toChange = temp->getNext();
	temp->setNext(node);
	node->setNext(toChange);
	temp = temp->getNext();
      }// if
    }// if
  }// for
}// encryptOng


// Name: decryptOng
// Preconditions - Linked list exists
// Postconditions - For each consonent, adds a node with "o", adds a node with "n"
// adds a node with "g". Every "letter" is separated with a "-" and each word is
// seperated by a space
void CipherString::decryptOng() {

  Node *temp = m_head; // temp node for itteration

  // Deleteion Nodes
  Node *o = NULL;
  Node *n = NULL;
  Node *g = NULL;
  Node *hyphen = NULL;

  char ch; // placeholder variables for the current value in temp
  bool isConsonant = true; // checks if the current char is a consonant

  // sets temp to head, loops until temp is null, itterates through list
  for(temp = m_head; temp != NULL; temp = temp->getNext()) {

    // set ch to the current data in temp
    ch = temp->getChar();

    // Checks if the char in temp is a vowel
    // then updates isConsonant accordingly
    if(ch == 'a' || ch == 'A' || ch == 'e' || ch == 'E' ||
       ch == 'i' || ch == 'I' || ch == 'o' || ch == 'O' ||
       ch == 'u' || ch == 'U')
      isConsonant = false;
    else
      isConsonant = true;

    // if the value is a Consonant, and not a space or a newline char
    // also if the next character ahead of temp is a space
    // or a new line
    if(isConsonant == true  && ch != ' ' && ch != '\n') {
      if(temp->getNext()->getChar() != ' '
         && temp->getNext()->getChar() != '\n') {

	// Setting up the deleteion notes
	o = temp->getNext();
	n = temp->getNext()->getNext();
	g = temp->getNext()->getNext()->getNext();
	hyphen = temp->getNext()->getNext()->getNext()->getNext();
	
	// resetting temp to its new value
	temp->setNext(temp->getNext()->getNext()->getNext()->getNext()->getNext());
	
	//delete Deletion nodes
	delete o;
	delete n;
	delete g;
	delete hyphen;
      }//if
    }// if

    // if the value is a vowel, and not a space or a newline char
    // also if the next character ahead of temp is a space
    // or a new line
    if(isConsonant == false && ch != ' ' && ch != '\n') {
      if(temp->getNext()->getChar() != ' '
         && temp->getNext()->getChar() != '\n') {

	//Setting up deletion nodes
	hyphen = temp->getNext();

	//resetting temp to new value
	temp->setNext(temp->getNext()->getNext());

	//delete Deletion nodes
	delete hyphen;
      }//if
    }// if
  }// for
}// decryptOng


// Name: encryptCaesar
// Preconditions - Linked list exists
// Postconditions - Shifts each character "right" by the int provided.
// See project document for additional details.
void CipherString::encryptCaesar(int caesarInt) {

  Node *temp;// node for itteration
  char ch; // placeholder for the value in temp

  // sets temp to head, loops until temp is null, itterations through list
  for(temp = m_head; temp != NULL; temp = temp->getNext()) {

    // sets ch to the value in temp
    ch = temp->getChar();

    //if ch is not a space or ascii equivelent 10
    if(ch != ' ' && ch != 10) {

      // Do the arithmatic onto ch
      ch = (ch - caesarInt) % 127;

      // set new value of temp
      temp->setChar(ch);
    }// if
  }//for
}// encryptCaesar


// Name: decryptCaesar
// Preconditions - Linked list exists
// Postconditions - Shifts each character "left" by the int provided.
// See project document for additional details.
void CipherString::decryptCaesar(int caesarInt) {

  Node *temp; // temp node for itteration
  char ch; // placeholder for the data in temp

  // sets temp to head, loops until temp is null, itterations through list
  for(temp = m_head; temp != NULL; temp = temp->getNext()) {

    // set ch to the data in temp
    ch = temp->getChar();

    //if ch is not a space or ascii equivelent 10
    if(ch != ' ' && ch != 10) {

      // do the arithmatic onto ch
      ch = (ch + caesarInt) % 127;

      // set temp to new ch value
      temp->setChar(ch);
    }// if
  }//for
}// decryptCaesae



// Name: encryptVigenere
// Preconditions - Linked list exists
// Postconditions - Shifts each character by the character (in string) provided.
// See project document for additional details.
void CipherString::encryptVigenere(string vigString) {

  Node *temp; // temp node for itteration
  char ch; // placeholder for the data in temp
  char *ptr; // pointer to hold char of vigString


  // sets temp to head, loops until temp is null, itterations through list
  for(temp = m_head; temp != NULL; temp = temp->getNext()) {
    
    int j = 0; // keeps track of where it is currently in the vigString

    // goes back to the start of the vigString if the code is longer
    // than the string
    if(j >(int) vigString.length())
      j = 0;

    // set ptr and ch to their appopraite values
    ptr = &vigString.at(j);
    ch = temp->getChar();

    // if ch is not a space of ascii 10
    if(ch != ' ' && ch != 10) {

      // do the arithmatic onto ch
      ch = (ch - *ptr) % 127;

      // get the new value of temp
      temp->setChar(ch);
    }// if

    // itterate through j
    j++;
  }// for
}// encryptVigenere


// Name: decryptVigenere
// Preconditions - Linked list exists
// Postconditions - Shifts each character by the character (in string) provided
// See project document for additional details.
void CipherString::decryptVigenere(string vigString) {

  char *ptr; // pointer char for vigStrin
  Node *temp; // temp node for itteration
  char ch; // holds the char data from temp


  // sets temp to head, loops until temp is null, itterations through list
  for(temp = m_head; temp != NULL; temp = temp->getNext()) {


    int j = 0; // keeps track of where it is currently in the vigString

    // goes back to the start of the vigString if the code is longer
    // than the string
    if(j >(int) vigString.length())
      j = 0;

    // sets ptr and ch to their approprate values
    ptr = &vigString.at(j);
    ch = temp->getChar();

    // if ch is not a space or ascii value 10
    if(ch != ' ' && ch != 10) {

      // character arithmatic onto ch
      ch = (ch + *ptr) % 127;

      // set temp to new value
      temp->setChar(ch);
    }// if

    // iterrates through the vigString
    j++;
  }// for
}// decryptVingenere


// Name: getSize
// Preconditions - Linked list exists
// Postconditions - Return size of structure
int CipherString::getSize() {

  return m_size;
}// getSize


// Name: operator<< (overloaded insertion operator)
// Preconditions - Linked list exists
// Postconditions - Iterates over the linked list and prints each char in each node
// In this case, friend means that it is accessible outside the class (like public)
ostream& operator<<(ostream& os, const CipherString& CIPHER_STRING) {

  Node *temp; // temp node for itteration

  // sets temp to head, loops until temp is null, itterations through list
  for(temp = CIPHER_STRING.m_head; temp != NULL; temp = temp->getNext()){

    os << temp->getChar(); 
  }// for
  return os; 
}// operator<< overload
