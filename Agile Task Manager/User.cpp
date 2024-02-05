#include "User.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

// It is the Default constructor for user.
User::User() {
  this->uniqueID = generateUID(id_user);
  this->userName = "";
  this->contactDetails = new Contact();
  this->userProjects = {};
}

// It is the constructor for User.
User::User(string userName, Contact *contactDetails, string pass,
           vector<Project *> userProjects) {
  this->uniqueID = generateUID(id_user); // Unique ID
  this->userName = userName;
  this->contactDetails = contactDetails;
  this->hashedPass = hash<string>{}(pass);
  this->userProjects = userProjects;
}

// It is the constructor for User.
User::User(string userName, Contact *contactDetails, string pass) {
  this->uniqueID = generateUID(id_user); // Unique ID
  this->userName = userName;
  this->contactDetails = contactDetails;
  this->hashedPass = hash<string>{}(pass);
}

// Setters

// It updates this users username to the given username
void User::updateUserName(string userName) { this->userName = userName; }

// It updates the User's contact details to the given contact details.
void User::updateContactDetails(Contact *contactDetails) {
  this->contactDetails = contactDetails;
}

// It updates user password to given password
void User::updatePass(string newPass) {
  this->hashedPass = hash<string>{}(newPass);
}

// It adds the project to the User.
void User::addProject(Project *project) {
  this->userProjects.push_back(project);
}
// It removes the project from the User.
void User::removeProject(int projectID) {
  for (auto it3 = userProjects.begin(); it3 != userProjects.end(); ++it3) {
    if ((*it3)->getProjectID() == projectID) {
      userProjects.erase(it3);
    }
  }
}

// Getters
// Gets the User's UserName
string User::getUserName() { return this->userName; }

// Other Methods
// It checks users are equal or not
bool User::operator==(const User &rhs) const {
  return this->uniqueID == rhs.uniqueID && this->userName == rhs.userName;
}

// It checks whether the Password is correct or not
bool User::checkPass(string guess) {
  return this->hashedPass == hash<string>{}(guess);
}

ostream &operator<<(ostream &os, const User &us) {
  os << us.userName << " " << us.uniqueID << " " << us.hashedPass << " "
     << us.contactDetails << " ";
  return os;
}

istream &operator>>(istream &is, User &us) {
  is >> us.userName >> us.uniqueID >> us.hashedPass >> *us.contactDetails;
  return is;
}
