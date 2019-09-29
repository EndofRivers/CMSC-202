/**********************************************************
 ** File:    Troop.cpp
 ** Project: CMSC 202 Project 2, Fall 2017
 ** Author:  Nicholas Long
 ** Date:    10/19/17
 ** Section: 0103
 ** Email:   nlong2@umbc.edu
 **
 ** This file contains the troop class for Project 2
 ** This program code can do the following:
 ** Constructs the troop with given information
 ** Get and Set the troop's name (string)
 ** Get and Set the troop's health (int)
 ** Get the troop's damage (int)
 ** Get the troop's target (string)
 ** Get the troop's ifFlying (bool)
 **
 ** Also works in tangent with Attack() from Game.cpp
 ** by checking to see if an attack will connect or not
 ** Then updating the target's health
 **
 **********************************************************/
#include "Troop.h"

// Troop
// Constructor
// Given a troop's name, health, damage, target, and isFlying
// Returns nothing
// Sets a troops values
Troop::Troop(string name, int health, int damage, string target, bool isFlying) {

  m_name = name;
  m_health = health;
  m_damage = damage;
  m_target = target;
  m_isFlying = isFlying;
}// Troop Constructor

// GetName
// Given nothing, returns Troop's name (string)
string Troop::GetName() {

  return m_name;
}// GetName

// SetName
// Given a string value, returns nothing
// Sets a troop's new name to given value
void Troop::SetName(string name) {

  m_name = name;
}// SetName

// GetHealth
// Given nothing, returns troop's health (int)
int Troop::GetHealth() {

  return m_health;
}// GetHealth

// SetHealth
// Given an int value, returns nothing
// Sets a tropo's new health to given value
void Troop::SetHealth(int health) {

  m_health = health;
}// SetHealth

// GetDamage
// Given nothing, returns troop's damage (int)
int Troop::GetDamage() {

  return m_damage;
}// GetDamage

// GetTarget
// Given nothing, returns troop's target (string)
string Troop::GetTarget() {


  return m_target;
}// GetTarget

// GetIsFlying
// Given nothing, returns troop's isFlying (bool)
bool Troop::GetIsFlying() {

  return m_isFlying;
}// GetIsFlying

// AttackTroop
// Given troop object reference, returns nothing
// Checks the values of isFlying and target
// Attacks based on those values
void Troop::AttackTroop(Troop &troop){

  // If target is flying and if troop can attack flying
  // Then attack goes through and damage is done
  if(troop.GetIsFlying() == true && m_target == "Both") {

    cout << m_name << " attacks " << troop.GetName()
	 << " in the sky!" << endl;

    cout << "Damage Occuring " << m_damage << endl;

    // Lower target's health based on troop's damage
    troop.SetHealth(troop.GetHealth() - m_damage);
  }// if

  // else If target is flying, but troop cannot attack flying
  // Then attack does not go through, and no damage is done
  else if(troop.GetIsFlying() == true && m_target == "Ground") {

    // Tell the player that the attack had no effect
    cout << m_name << " cannot attack the " << troop.GetName()
	 << " due to it flying!" << endl;
  }// else if

  // else If target is not flying and troop can attack flying
  // Then attack goes through and damage is done
  else if(troop.GetIsFlying() == false && m_target == "Both") {

    cout << m_name << " attacks " << troop.GetName()
	 << " from the ground!" << endl;

    cout << "Damage Occurring " << m_damage << endl;

    // Lower target's health based on troop's damage
    troop.SetHealth(troop.GetHealth() - m_damage);
  }// else if

  // else If target is not flying and troop can only attack ground
  // Then attack goes through and damage is done
  else if(troop.GetIsFlying() == false && m_target == "Ground") {

    cout << m_name << " attacks " << troop.GetName() 
	 << " on the ground!" << endl;

    cout << " Damage Occurring " << m_damage << endl;

    // Lower target's health based on troop's damage
    troop.SetHealth(troop.GetHealth() - m_damage);
  }//else if
}// AttackTroop
