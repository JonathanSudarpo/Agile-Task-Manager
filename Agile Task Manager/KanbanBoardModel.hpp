#pragma once
#include "Date.hpp"
#include "Project.hpp"
#include "User.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

class Date;
class User;
class Project;
class Task;

// It represents KanbanBoardModel
class KanbanBoardModel {
  friend class User;
  friend class Date;
  friend class Task;
  friend class Project;
// KanbanBoardModel Contains the following
private:
  map<string, User *> usersList;
  User *owner;
  User *curUser;
  vector<Project *> projectsList;
  int sprintLength;
  Date *curDay;

public:
  KanbanBoardModel(User *owner){
    this->owner = owner;
    this->usersList.insert({owner->getUserName(), owner});
  }
  // Represennts the KanbanBoardModel Constructor
  KanbanBoardModel(map<string, User *> usersList, User *owner,
                   vector<Project *> projectsList, int sprintLength,
                   Date *curDay) {
    this->usersList = usersList;
    this->owner = owner;
    this->projectsList = projectsList;
    this->sprintLength = sprintLength;
    this->curDay = curDay;
  }

  // RULE OF 5: 
  // Represebt the default constructor
  KanbanBoardModel() {
    this->owner = new User();
    this->sprintLength = 0;
    this->curDay = new Date();
  }

  // Represents the destructor
  ~KanbanBoardModel() {
    for (auto i = usersList.begin(); i != usersList.end(); i++) {
      delete[] i->second;
    }
    free(owner);
    for (auto i = projectsList.begin(); i != projectsList.end(); i++) {
      delete[] i.base();
    }
    free(curDay);
  }

  // getters
  Project * getProject(int proid);

  map<string, User *> getUsersList() { return usersList; }
  User *getOwner() { return owner; }
  vector<Project *> getProjectsList() { return projectsList; }
  int getSprintLength() { return sprintLength; }
  Date *getCurDay() { return curDay; }
  User* getCurUser() {return curUser;}

  // Setters
// It allows to set the owner
  void setOwner(User *owner) { this->owner = owner; }

// It sets the project list
  void setProjectsList(vector<Project *> projectsList) {
    this->projectsList = projectsList;
  }
// It sets the the length of the sprint length
  void setSprintLength(int sprintLength) { this->sprintLength = sprintLength; }

// It sets the current day
  void setCurDay(Date *curDay) { this->curDay = curDay; }

// It allows to create user
  void createUser(User *user);

//It allows to create project 
  void createProject(string projectName);

//It allows to delete the project
  void deleteProject(int projectID);

//It see if the the project is deleted or not
  bool deleteProject(string projectName);

  Project *getProject(string projectName);
  vector<User *> getUsers();
  void updateSprint();
  void viewMyProjects(User* u); 
  void viewKanbanBoard();
  void printKanbanElems(vector<Task*> t); 
  void printAllTask(Project *p); 
  // void printAllUsers();
  

//adds user
void addUser(User * user);
// Checks if the supplied user exists in the model. 
User* hasUser(string userName);



// Repesents the Log in and log out methods
  bool logIn(string username, string password);
  void logOut();
// Show Board Methods
  vector<Project *> userProjects();

};