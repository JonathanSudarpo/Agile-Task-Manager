#include "KanbanBoardModel.hpp"
#include "User.hpp"
#include <iomanip>
#include <iostream>
#include <map>
#include <stdlib.h>

using namespace std;

// It checks if user is owner, if so adds username and user to map.
void KanbanBoardModel::createUser(User *user) {
  if (*this->curUser == *this->owner) {
    this->usersList.insert({user->getUserName(), user});
  }
}

vector<User *> KanbanBoardModel::getUsers() {
  vector<User *> ret;
  for (auto a : this->getUsersList()) {
    ret.push_back(a.second);
  }
  return ret;
}

// updates the sprint for all projects and tasks;
void KanbanBoardModel::updateSprint() {
  for (auto p = this->projectsList.begin(); p != projectsList.end(); p++) {
    (*p)->updateSprint(*curDay);
  }
}

// creates project
void KanbanBoardModel::createProject(string projectName) {
  int n = projectName.length();

  // declaring character array
  char *projectChar = new char[n + 1];
  strcpy(projectChar, projectName.c_str());

  Project *a = new Project(projectChar);

  a->addUser(this->owner, boardowner);
  this->projectsList.push_back(a);
}

// It deletes given project id if the user is owener.
void KanbanBoardModel::deleteProject(int projectID) {
  for (auto i = this->projectsList.begin(); i != this->projectsList.end();
       i++) {
    if ((*i)->getProjectID() == projectID) {
      this->projectsList.erase(i);
      return;
    }
  }
  throw invalid_argument("Invalid ID");
}

// Gets the Project from the given project ID.

// Contains the Log in and log out methods
bool KanbanBoardModel::logIn(string username, string password) {
  try {
    if (usersList.at(username)->checkPass(password)) {
      this->curUser = usersList.at(username);
      cout << "Correct Credentials" << endl;
      return true;
    } else {
      cout << "Incorrect Credentials" << endl;
      return false;
    }
  } catch (const std::out_of_range &oor) {
    cout << "Username not in system." << endl;
    return false;
  }
}
void KanbanBoardModel::logOut() { this->curUser = nullptr; }

// adds user
void KanbanBoardModel::addUser(User *user) {
  this->usersList.insert({user->getUserName(), user});
}

// Gets the projects of the currently logged in user.
vector<Project *> KanbanBoardModel::userProjects() {
  vector<Project *> ret;
  for (auto i = this->projectsList.begin(); i != this->projectsList.end();
       i++) {
    if ((*i)->hasUser(this->curUser->getID())) {
      ret.push_back((*i));
    }
  }
  return ret;
}

Project *KanbanBoardModel::getProject(int proid) {
  for (auto p = this->projectsList.begin(); p != this->projectsList.end();
       p++) {
    if ((*p)->getProjectID() == proid) {
      return *p;
    }
  }
  throw invalid_argument("Invalid ID");
}

// Views all the projects of the given user.
void KanbanBoardModel::viewMyProjects(User *u) {
  int numOfProj = this->projectsList.size();
  vector<Project *> proj = this->projectsList;
  int currUID = u->getID();
  int count = 1;

  cout << "==================== MY PROJECTS ====================" << endl;
  for (int i = 0; i < numOfProj; i++) {
    Project *currProj = proj.at(i);

    if (currProj->hasUser(currUID)) {
      char *currProjName = currProj->getProjectName();

      cout << "=== Project " << count << ":" << endl;
      cout << "===        - Name: " << currProjName << endl;
      cout << "===        - ID: " << currProj->getProjectID() << endl;
      count++;
    }
  }
  cout << "=====================================================" << endl;

  return;
}

void KanbanBoardModel::printKanbanElems(vector<Task *> t) {
  int count = 1;
  int assigneeNum = 1;
  for (auto it : t) {
    assigneeNum = 1;
    cout << "===" << count << ". " << endl;
    cout << "=== ID: " << it->getTaskID()  << endl;
    cout << "=== Date Created: " << it->getTaskCreatedDate() << endl;
    cout << "=== Due Date: " << it->getTaskDueDate() << endl;
    cout << "=== Type: " << it->getTaskType() << endl;
    cout << "=== Priority: " << it->getPriority() << endl;
    cout << "=== Description: " << it->getTaskDescription() << endl;
    cout << "=== Assignees: " << endl;
    vector<User *> curAssignee = it->getAssignees();
    for (auto user : curAssignee) {
      cout << "===" << assigneeNum << ". Name: " << user->getUserName()
           << "ID: " << user->getID() << endl;
      assigneeNum++;
    }
    count++;
  }
}

void KanbanBoardModel::viewKanbanBoard() {
  vector<Project *> proj = this->projectsList;
  int max = proj.size();
  cout << "=================================== KANBAN BOARD "
          "==================================="
       << endl;

  vector<Task *> TODO, DOING, DONE;

  // Puts the tasks in the right category
  for (int i = 0; i < max; i++) {
    // All Tasks within current project.
    vector<Task *> projTask = proj.at(i)->getTasks();
    // For each task
    for (auto it : projTask) {
      if (it->getStatus() == todo) {
        TODO.push_back(it);
      } else if (it->getStatus() == doing) {
        DOING.push_back(it);
      } else if (it->getStatus() == done) {
        DONE.push_back(it);
      }
    }
  }
  cout << "===" << setw(30) << "TO-DO:" << endl;
  this->printKanbanElems(TODO);
  cout << "===" << setw(30) << "DOING:" << endl;
  this->printKanbanElems(DOING);
  cout << "===" << setw(30) << "DONE:" << endl;
  this->printKanbanElems(DONE);
}

void KanbanBoardModel::printAllTask(Project *p) {
  int count = 1;
  cout << "==================== All Tasks ====================" << endl;
  for (auto task : p->getTasks()) {
    cout << "===" << count << "." << endl;
    cout << "Task ID: " << task->getTaskID() << endl;
    cout << "Task Description: " << task->getTaskDescription() << endl;
    cout << "Due Date: " << task->getTaskDueDate() << endl;
    count++;
  }
}

User *KanbanBoardModel::hasUser(string userName) {
  for (auto a : this->usersList) {
    if (a.first == userName) {
      return a.second;
    }
  }
  return nullptr;
}

// void KanbanBoardModel::printAllUsers() {
//   int count = 1;
//   cout << "==================== All Users ====================" << endl;
//   for (auto a : this->usersList) {
//     cout << "=== " << count << "." << a.first << endl;
//   }
// }