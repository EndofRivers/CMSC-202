#include "Cipher.h"

/* PRIVATE VARIABLES
  Mode m_mode; //Uses enum to manage type of cipher
  CipherString* m_cipherString; //Linked List of the cipher string
  char m_caesar_key; //Used for Caesar ciphers as the key
  string m_vig_key; //Used for Vigenere ciphers as the key
 */

// Name: Cipher(char) - Overloaded constructor for Caesar cipher
// Preconditions - Caesar cipher is defined
// Postconditions - Constructor for the Caesar cipher (sets m_mode to CAESAR)
Cipher::Cipher(char caesarKey) {

  m_caesar_key = caesarKey;
  m_mode = CAESAR;
}// Cipher Constructor Caesar

// Name: Cipher(char) - Overloaded constructor for Caesar cipher
// Preconditions - Caesar cipher is defined
// Postconditions - Constructor for the Caesar cipher (sets m_mode to CAESAR)
Cipher::Cipher(string vigKey) {

  m_vig_key = vigKey;
  m_mode = VIGENERE;
}// Cipher Constructor Vigenere

// Name: Cipher(char) - Overloaded constructor for Caesar cipher
// Preconditions - Caesar cipher is defined
// Postconditions - Constructor for the Caesar cipher (sets m_mode to CAESAR)
Cipher::Cipher() {

  m_mode = ONG;
}// Cipher Constructor Ong

// Name: setPlainText
// Preconditions - File with text is available (in current directory)
// Postconditions - Stores file text in m_cipherString
void Cipher::setPlainText(string plainText) {

  //Sending file name to Cipherstring
  m_cipherString = new CipherString(plainText.c_str());
}// setPlainText

// Name: encrypt
// Preconditions - m_cipherString populated
// Postconditions - Calls correct encryption function based on the cipher chosen
void Cipher::encrypt() {

  //Calls the correct encryption depending on user input
  switch(m_mode) {

    //Caeasr Encryption
  case 1:
    m_cipherString->encryptCaesar(m_caesar_key);
    break;

    //Ong Encryption
  case 2:
    m_cipherString->encryptOng();
    break;

    //Vingenere Encryption
  case 3:
    m_cipherString->encryptVigenere(m_vig_key);
    break;
  }// switch
}// encript

// Name: decrypt
// Preconditions - m_cipherString populated and encrypted
// Postconditions - Calls correct decryption function based on the cipher chosen
void Cipher::decrypt(){

  //Calls the correct encryption depending on user input
  switch(m_mode) {

    //Caesar Encryption
  case 1:
    m_cipherString->decryptCaesar(m_caesar_key);
    break;

    //Ong Encryption
  case 2:
    m_cipherString->decryptOng();
    break;

    //Vingenere Encryption
  case 3:
    m_cipherString->decryptVigenere(m_vig_key);
    break;
  }// switch
}// decript

// Name: changeKey
// Preconditions - key exists
// Postconditions - Key is updated
void Cipher::changeKey(string key) {

}// changeKey

// Name: printString
// Preconditions - m_cipherString populated
// Postconditions - Outputs the value of m_cipherString
void Cipher::printString() {

  //Prints linked list through operator<< overloading
  cout << *m_cipherString;
}// printString
