#pragma once
#include "Date.hpp"
#include <cstring>
#include <iostream>
#include <stdlib.h>

using namespace std;

// This represent the Date class 
class Date;

// This represnes the contact class 
class Contact {
  friend class Date;
friend ostream& operator<<(ostream& os, const Contact& cs);
friend istream &operator>>(istream &is, Contact &cs);
// All the details which are inside contact information
private:
  char *name;
  char *email;
  char *nationality;
  Date dob;

public:
  // This represents the Constructor
  Contact(char *name, char *email, char *nationality, Date dob);

  // RULE OF 5: 
  // Default constructor
  Contact() {
    this->name = nullptr;
    this->email = nullptr;
    this->nationality = nullptr;
    this->dob = Date();
  }
  // This is the Destructor
  ~Contact() {
    free(name);
    free(email);
    free(nationality);
  }

  // This is the Copy constructor
  Contact(const Contact &other) {
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    this->email = new char[strlen(other.email) + 1];
    strcpy(this->email, other.email);
    this->nationality = new char[strlen(other.nationality) + 1];
    strcpy(this->nationality, other.nationality);
    this->dob = Date(other.dob);
  }

  // Copy Assignment
  Contact &operator=(const Contact &other) {
    if (this == &other) {
      return *this;
    }
    delete[] name;
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    delete[] email;
    this->email = new char[strlen(other.email) + 1];
    strcpy(this->email, other.email);
    delete[] nationality;
    this->nationality = new char[strlen(other.nationality) + 1];
    strcpy(this->nationality, other.nationality);
    this->dob = other.dob;

    return *this;
  }

  // Move Constructor
  Contact(Contact &&other) {
    this->name = other.name;
    other.name = nullptr;

    this->email = other.email;
    other.email = nullptr;

    this->nationality = other.nationality;
    other.nationality = nullptr;

    this->dob = move(other.dob);
  }

  // Move Assignment
  Contact &operator=(Contact &&other) {
    if (this == &other) {
      return *this;
    }

    delete[] this->name;
    this->name = other.name;
    other.name = nullptr;

    delete[] this->email;
    this->email = other.email;
    other.email = nullptr;

    delete[] this->nationality;
    this->nationality = other.nationality;
    other.nationality = nullptr;

    this->dob = move(other.dob);

    return *this;
  }

// Setters

// It updates the current Contact's name to the supplied name. 
  void updateName(char *name);
// It updates the current Contact's email to the supplied email. 
  void updateEmail(char *email); 
// It updates the current Contact's nationality to the supplied nationality. 
  void updateNationality(char *nationality);
// It updates the current Contact's date of birth to the supplied date of birth. 
  void updateDob(Date dob);

  // Getters
  char *getName();
  char *getEmail();
  char *getNationality();
  Date getDob(); 
   
};
