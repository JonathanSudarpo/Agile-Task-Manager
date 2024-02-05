#include "Utils.hpp"
#include "KanbanBoardModel.hpp"
#include "User.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

// Represents the user class
class User;
class Project;

// Generates a unique ID depending on the type of ID it's for.
int generateUID(enum IDTYPE type) {
  string fileName;
  // It determines which past UID to read.
  switch (type) {
  case id_task:
    fileName = "taskUID.txt";
    break;
  case id_user:
    fileName = "userUID.txt";
    break;
  case id_project:
    fileName = "projectUID.txt";
    break;
  }

  // It reads the Past UID from file
  ifstream file(fileName, ios_base::in);
  int UID;
  file >> UID;
  int returnValue = UID;

  // Increment UID so no duplicates.
  UID++;

  // update UID in file
  ofstream myfile;
  myfile.open(fileName);
  myfile << UID;
  myfile.close();

  // cout << returnValue << endl; // Testing
  return returnValue;
}

// Prints the main menu for regular users
void printMainMenuUser() {
  cout << "==================== MAIN MENU ====================" << endl;
  cout << "=== Please Enter One of the Following Options:===" << endl;
  cout << "=== 0. Logout                                 ===" << endl;
  cout << "=== 1. View myProjects.                       ===" << endl;
  cout << "=== 2. Work on Project.                       ===" << endl;
  cout << "=================================================" << endl;
}

// Prints the main menu for owners.
void printMainMenuOwner() {
  cout << "==================== MAIN MENU ====================" << endl;
  cout << "=== Please Enter One of the Following Options:===" << endl;
  cout << "=== 0. Logout                                 ===" << endl;
  cout << "=== 1. View myProjects.                       ===" << endl;
  cout << "=== 2. Work on Project.                       ===" << endl;
  cout << "=== 3. Create Project.                        ===" << endl;
  cout << "=== 4. Delete Project.                        ===" << endl;
  cout << "=== 5. Move Sprint Forward.                   ===" << endl;
  cout << "=== 6. Create New User.                       ===" << endl;
  cout << "=================================================" << endl;
}

// Options for Working on Projects
char func0[100] = "Main Menu";
char func1[100] = "View KanbanBoard";
char func2[100] = "View myTask";
char func3[100] = "Create Task";
char func4[100] = "Update Task";
char func5[100] = "Delete Task";
char func6[100] = "Invite Users";
char func7[100] = "View All Users";

char *projectOptions[8] = {func0, func1, func2, func3,
                           func4, func5, func6, func7};

// Options for Updating Tasks
char updateTask0[100] = "Main Menu";
char updateTask1[100] = "Update Status";
char updateTask2[100] = "Update Description";
char updateTask3[100] = "Update Task Type";
char updateTask4[100] = "Update Task Priority";
// Only Manager and Owners can access the func. below
char updateTask5[100] = "Update Deadline";
char updateTask6[100] = "Add Assignee";
char updateTask7[100] = "Remove Assignee";

char *updateTaskOptions[8] = {updateTask0, updateTask1, updateTask2,
                              updateTask3, updateTask4, updateTask5,
                              updateTask6, updateTask7};

// Sets the upper bound for which functions a user can have
int setFuncBoundary(enum permLevel p) {
  if (p == assistant) {
    return 2;
  } else if (p == developer) {
    return 5;
  } else if (p == manager || p == boardowner) {
    return 6;
  }
  return 0;
}
// It sets the boundry of the update task
int setFuncBoundaryUpdateTask(enum permLevel p) {
  if (p == developer) {
    return 5;
  } else {
    return 8;
  }
}
// It prints the user function layout
void printUserFunc(int funcBound) {
  int count = 1;
  cout << "==================== Project Dashboard ====================" << endl;
  cout << "======== Please Enter One of the Following Options: =======" << endl;
  for (int i = 0; i < funcBound; i++) {
    cout << "=== " << i << ". " << projectOptions[i] << endl;
    count++;
  }

  cout << "===========================================================" << endl;
}
// It prints the update task layout
void printUpdateTask(int funcBound) {
  cout << "==================== Update Task ====================" << endl;
  cout << "======== Please Enter One of the Following Options: =======" << endl;
  for (int i = 0; i < funcBound; i++) {
    cout << "=== " << i << ". " << updateTaskOptions[i] << endl;
  }

  cout << "=====================================================" << endl;
}

// Gets perm Level based on int supplied.
enum permLevel intToPerm(int i) {
  if (i == 1) {
    return noperm;
  }
  if (i == 2) {
    return assistant;
  }
  if (i == 3) {
    return developer;
  }
  if (i == 4) {
    return manager;
  }
  if (i == 5) {
    return boardowner;
  }
}
// Gets taskType based on int supplied.
enum taskType intToTaskType(int i) {
  if (i == 1) {
    return userStory;
  }
  if (i == 2) {
    return t_task;
  }
  if (i == 3) {
    return build;
  }
  if (i == 4) {
    return test;
  }
  if (i == 5) {
    return debug;
  }
  if (i == 6) {
    return documentation;
  }
  if (i == 7) {
    return review;
  }
}

// Gets priority based on the int supplied.
enum priority intToPriority(int i) {
  if (i == 1) {
    return high;
  }
  if (i == 2) {
    return medium;
  }
  if (i == 3) {
    return low;
  }
}