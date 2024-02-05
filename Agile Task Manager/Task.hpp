#pragma once 
#include <iostream>
#include <vector>
#include <map> 
#include <cstring>
#include <stdlib.h>
#include "User.hpp"
#include "Utils.hpp"
//#include "KanbanBoardModel.hpp"

using namespace std; 

// Represents the user class 
class User;

// Represents the utils class
class Utils;

// Represents the task class 
class Task {
friend class User;
friend class Utils;

// The class task contains the following:
private:
  int uniqueID; // Shouldn't need to update
  vector<User *> assignee;
  Date createdDate; // Shouldn't need to update
  Date dueDate; // Size
  char* description; 
  taskType type; // type enum from utils 
  status status; // status enum from utils
  priority priority;  // priority enum from utils

public:
// It represents the  Task constructor (Automatically assigns uniqueID, and potentially Date in future?)
Task(vector<User*> assignee, Date createdDate, Date dueDate, char* description, taskType type, enum status status, enum priority priority);
Task(Date createdDate, Date dueDate, char* description, taskType type, enum status status, enum priority priority);

// Rule of 5

// Destructor
~Task() {
  this->assignee.clear();
  free(this->description);
}

// Copy Constructor
Task(const Task &other) {
  this->uniqueID = other.uniqueID;
  this->assignee = other.assignee; // Copy
  this->createdDate = Date(other.createdDate);
  this->dueDate = Date(other.dueDate);
  this->description = new char[strlen(other.description)+1];
  strcpy(this->description, other.description); 
  this->type = other.type;
  this->status = other.status; 
  this->priority = other.priority; 
}

// Copy Assignment
Task &operator=(const Task &other) {
  if (this == &other) {
    return *this;
  }
  this->uniqueID = other.uniqueID;
  this->assignee.clear();
  this->assignee = other.assignee; // Copy
  this->createdDate = other.createdDate;
  this->dueDate = other.dueDate;
  delete[] description; 
  this->description = new char[strlen(other.description)+1];
  strcpy(this->description, other.description); 
  this->type = other.type;
  this->status = other.status; 
  this->priority = other.priority; 

  return *this; 
  
}

// Move Constructor
Task(Task &&other) {
  this->uniqueID = other.uniqueID;
  this->assignee = other.assignee;
  this->createdDate = move(other.createdDate);
  this->dueDate = move(other.dueDate);
  this->description = other.description; 
  other.description = nullptr;
  this->type = other.type;
  this->status = other.status; 
  this->priority = other.priority; 
  
}

// Move Assignment 
Task &operator=(Task &&other) {
  if (this == &other) {
    return *this; 
  }

  this->uniqueID = other.uniqueID;

  this->assignee = other.assignee;
  other.assignee.clear(); 
  
  this->createdDate = move(other.createdDate);
  
  this->dueDate = move(other.dueDate);

  delete[] this->description;
  this->description = other.description; 
  other.description = nullptr;
  
  this->type = other.type;
  
  this->status = other.status; 
  
  this->priority = other.priority; 

  return *this;

  
}

// Setters
  void updateAssignee(User* newAssignee);
  void updateStatus(enum status newStatus);
  void updatePriority(enum priority newPriority);
  void updateDescription(char* newDescription);
  void updateTaskType(enum taskType newType);
  void updateDate(Date newdate);

// Getters
  int getTaskID();
  vector<User *> getAssignees();
  enum status getStatus();
  enum priority getPriority();
  enum taskType getTaskType();
  char* getTaskDescription();
  Date getTaskDueDate();
  Date getTaskCreatedDate();

// Other methods:
  void addAssignee(User* u);
  Date taskTimeTillDue(); 
  bool isTaskDue(Date current);

  void updateSprint(Date curDay);

};