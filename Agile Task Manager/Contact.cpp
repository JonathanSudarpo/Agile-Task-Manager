#include "Contact.hpp"
#include "Date.hpp"
#include <cstring>
#include <stdlib.h>

using namespace std;

// Constructor
Contact::Contact(char *name, char *email, char *nationality, Date dob) {
  this->name = name;
  this->email = email;
  this->nationality = nationality;
  this->dob = dob;
}

// It updates the current Contact's name to the supplied name.
void Contact::updateName(char *name) { this->name = name; }

// It updates the current Contact's email to the supplied email.
void Contact::updateEmail(char *email) { this->email = email; }

// It updates the current Contact's nationality to the supplied nationality.
void Contact::updateNationality(char *nationality) {
  this->nationality = nationality;
}

// It updates the current Contact's date of birth with the supplied date of
// birth.
void Contact::updateDob(Date dob) { this->dob = dob; }

// It gets the current Contact's name.
char *Contact::getName() { return name; }

// It gets current Contact's email.
char *Contact::getEmail() { return email; }

// It gets the current Contact's nationality.
char *Contact::getNationality() { return nationality; }

// It gets the current Contact's date of birth.
Date Contact::getDob() { return dob; }

ostream &operator<<(ostream &os, const Contact &cs) {
  Date dob1 = cs.dob;
  os << cs.name << " " << cs.email << " " << cs.nationality << " "
     << dob1.getDay() << " " << dob1.getMonth() << " " << dob1.getYear()
     << endl;
  return os;
}
istream &operator>>(istream &is, Contact &cs) {
  is >> cs.name >> cs.email >> cs.nationality >> cs.dob;
}