#pragma once
#include "Contact.hpp"
#include "Project.hpp"
#include "Utils.hpp"
//#include "KanbanBoardModel.hpp"
#include <iostream>
#include <cstring> 
#include <vector>
#include <stdlib.h>
using namespace std;

// Represents the project class.
class Project;

// Represents the user class 
class User {
  friend class Project;
  friend class Contact;
//friend void saveKanbanBoard(KanbanBoardModel model);
friend ostream& operator<<(ostream& os, const User& us);
friend istream &operator>>(istream &is, User &us);

// The user class contains the following information 
private:
  int uniqueID;
  string userName;
  Contact *contactDetails;
  size_t hashedPass;
  vector<Project *> userProjects; // instantiates by default

public:

  // Represents the default constructor for user
  User();

  User(string userName, Contact *contactDetails, string pass,
       vector<Project *> userProjects);

  User(string userName, Contact *contactDetails, string pass);
  // Setters
  void updateUserName(string userName);
  void updateContactDetails(Contact *contactDetails);
  void updatePass(string newPass);

  void addProject(Project *project);

  void removeProject(int projectID);
  // Methods
  bool checkPass(string guess);

  bool operator==(const User &rhs) const;

  string getUserName();

  int getID(){return this->uniqueID;}
};