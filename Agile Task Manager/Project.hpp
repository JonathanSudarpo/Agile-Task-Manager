#pragma once 
#include "Task.hpp"
#include "User.hpp"
#include "Utils.hpp"
//#include "KanbanBoardModel.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <stdlib.h>
using namespace std;

// Represents the task class
class Task;
// Represents the task User
class User;
// Represents the task Project 
class Project{
//friend void saveKanbanBoard(KanbanBoardModel model);
friend class Task;
friend class User;

// Class Projects contains the following information
private:
  char * projectName;
  int projectID;
  vector<Task*> tasks;
  map<User*, permLevel> userPerms; 

public:
// Represents the constructor for Project
  Project(char* projectName, vector<Task*> tasks, map<User*, enum permLevel> userPerms);
  Project(char* projectName);

// Rule of 5 

// Represents the destructor
  ~Project() {
    free(this->projectName); 
   
    // Clears the tasks
    this->tasks.clear(); 

  }

// Copy Constructor
Project(const Project &other) {
  this->projectName = new char[strlen(other.projectName) + 1];
  strcpy(this->projectName, other.projectName); 
  this->projectID = other.projectID;
  this->tasks.clear(); 
  this->tasks = other.tasks;
  this->userPerms.clear(); 
  this->userPerms.insert(other.userPerms.begin(), other.userPerms.end()); 
}

// Copy Assignment
Project &operator=(const Project &other) {
  if (this == &other) {
    return *this; 
  }

  delete[] projectName; 
  this->projectName = new char[strlen(other.projectName) + 1]; 
  strcpy(this->projectName, other.projectName); 

  this->projectID = other.projectID; 

  this->tasks.clear(); 
  this->tasks = other.tasks; 

  this->userPerms.clear(); 
  this->userPerms.insert(other.userPerms.begin(), other.userPerms.end()); 

  return *this;
}

// Move Constructor
Project(Project &&other) {
  this->projectName = other.projectName;
  other.projectName = nullptr; 

  this->projectID = other.projectID;

  this->tasks = other.tasks; 
  other.tasks.clear(); 

  this->userPerms.clear();
  this->userPerms.insert(other.userPerms.begin(), other.userPerms.end()); 
  other.userPerms.clear();
}

// Move Assignment
Project &operator=(Project &&other) {
  if (this == &other) {
    return *this;
  }

  delete[] this->projectName;
  this->projectName = other.projectName;
  other.projectName = nullptr;
  
  this->projectID = other.projectID;
  
  this->tasks = other.tasks; 
  
  this->userPerms.clear();
  this->userPerms.insert(other.userPerms.begin(), other.userPerms.end()); 
  other.userPerms.clear();

  return *this;
}


// Setters
void setProjectName(char* c);

// getters
char* getProjectName(); 
int getProjectID();
vector<Task*> getTasks();
Task* getTask(int taskID); 
map<User*, permLevel> getUserPerms();
enum permLevel getUserPerm(User* u); 


// Methods
// Method views the task 
void viewTask(Task* task);

// Method views the project 
void viewProject();

// Method views the task 
void deleteTask(Task* task); 

// Method adds the user and asks for the permission levels
void addUser(User * user, permLevel perm);

// Method enables adding tasks 
void addTasks(Task* tasks);

// Method enables to update the project
void updateProject(Project project);

//Updates the sprint for all tasks within it.
void updateSprint(Date curDay);

// Prints all the users in the project
void printAllUser(); 

// Checks whether there is a user or not
bool hasUser(int userId);

// -----
int getUserCommands(User* UID); 

};