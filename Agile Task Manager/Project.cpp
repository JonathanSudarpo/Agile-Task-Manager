#include "Project.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <vector>

using namespace std;

// Represents the Project Constructor
Project::Project(char *projectName, vector<Task *> tasks,
                 map<User *, enum permLevel> userPerms) {
  this->projectName = projectName;
  this->tasks = tasks;
  this->projectID = generateUID(id_project);
  this->userPerms = userPerms;
}

Project::Project(char *projectName) {
  this->projectName = projectName;
  this->projectID = generateUID(id_project);
}

// Setters
void Project::setProjectName(char *c) { this->projectName = c; }

// Getters

char *Project::getProjectName() { return this->projectName; }

int Project::getProjectID() { return this->projectID; }

vector<Task *> Project::getTasks() { return this->tasks; }

Task *Project::getTask(int taskID) {
  for (auto a : this->getTasks()) {
    if (a->getTaskID() == taskID) {
      return a;
    }
  }
  throw invalid_argument("no task");
}

map<User *, permLevel> Project::getUserPerms() { return this->userPerms; }

enum permLevel Project::getUserPerm(User *u) {
  for (auto a : this->userPerms) {
    if (a.first->getID() == u->getID()) {
      return a.second;
    }
  }
  return noperm;
}

// Other Methods
// Represents the view task
void Project::viewTask(Task *task) { return; }

// Represents the view project
void Project::viewProject() { return; }

// Represents the delete task from the project
void Project::deleteTask(Task *task) {
  for (auto t = this->tasks.begin(); t != this->tasks.end(); t++) {
    if ((*t)->getTaskID() == task->getTaskID()) {
      this->tasks.erase(t);
    }
  }
}

// Represents add User which allows to add user to the project
void Project::addUser(User *user, permLevel perm) {
  this->userPerms.insert({user, perm});
  return;
}

// Updates the sprint for all tasks within it.
void Project::updateSprint(Date curDay) {
  for (auto t = this->tasks.begin(); t != this->tasks.end(); t++) {
    (*t)->updateSprint(curDay);
  }
}

// Represent the Method which enables to add Tasks in the project.
void Project::addTasks(Task *tasks) {
  this->tasks.push_back(tasks);
  return;
}
// Represent the  updateProject which enables to update the project when
// needed
void Project::updateProject(Project project) { return; }

// It checks if the project contains given user.
bool Project::hasUser(int userId) {
  for (auto a : this->userPerms) {
    if (a.first->uniqueID == userId) {
      return true;
    }
  }
  return false;
}

// Generates the bounds of functions that a User can use.
int Project::getUserCommands(User *u) {
  map<User *, permLevel> allUsers = this->getUserPerms();
  auto it = allUsers.find(u);
  enum permLevel ret = it->second;

  int funcBound = 0;

  switch (ret) {
  case assistant:
    funcBound = 2;
  case developer:
    funcBound = 5;
  case manager:
    funcBound = 8;
  case boardowner:
    funcBound = 9;
  }
  return funcBound;
}

// Prints all the users in the project
void Project::printAllUser() {
  int count = 1;
  cout << "==================== All Users ====================" << endl;
  for (auto a : this->userPerms) {
    cout << "=== " << count << "." << a.first->getUserName() << endl;
  }
}
