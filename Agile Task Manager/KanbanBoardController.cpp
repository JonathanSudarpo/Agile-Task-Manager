

#include "KanbanBoardController.hpp"
#include "Project.hpp"
#include "User.hpp"
#include "Utils.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

User *createUser();
Task *createTask(Date cur);

// Runs the program
void KanbanBoardController::run() {

  // Current User
  User *curUser;
  // Current State
  int curState = load_screen;
  // Current Project
  int curProject;
  // Current TaskID
  int curTaskID;
  // cur task 
  Task *curTask;
  // Model
  KanbanBoardModel model;
  // Game Loop
  while (true) {
    switch (curState) {
      // Loading Screen
    case load_screen: {
      int choice = 0;
      while (choice != 2) {
        cout << "Press 2 to start a new Kanban "
                "Board."
             << endl;
        cin >> choice;
      }
      if (choice == 2) {
        curState = login_screen;
        curProject = 0;
        cout << endl << "Creating owner." << endl;

        User *owner = createUser();
        model = KanbanBoardModel();
        model.setOwner(owner);
        model.addUser(owner);
        cout << "What is the current day (dd mm yyyy): ";
        Date cur;
        cin >> cur;
        model.setCurDay(new Date(cur));
        cout << "What is the sprint length: ";
        int slength;
        cin >> slength;
        model.setSprintLength(slength);
      } else {
        // load logic
        // model = load from...
      }
    }
      // Login Screen
    case login_screen: {
      cout << "Kanban Board" << endl;
      int login_choice = 0;
      while (login_choice != 1 && login_choice != 2) {
        cout << "Press 1 to log in or 2 to save and quit" << endl;
        cin >> login_choice;
      }
      // Allows User to Login
      if (login_choice == 1) {
        string user;
        string pass;
        int count = 0;
        do {
          cout << "Please enter username: ";
          cin >> user;
          cout << "Please enter password: ";
          cin >> pass;
          count++;
        } while (!model.logIn(user, pass) && count < 3);
        if (count == 3) {
          break;
        } else {
          curState = main_menu;
        }
      } else {
        // save logic
        return;
      }
    }

      // Main Menu
    case main_menu: {

      int minFuncBound = 0;
      int maxFuncBound;
      curUser = model.getCurUser();
      bool flag = true;
      int mainMenuOpt;

      while (flag) {
        int opt;
        cout << "Current User: " << curUser->getUserName() << endl;
        if (curUser->getID() == model.getOwner()->getID()) {
          printMainMenuOwner();
          maxFuncBound = 6;
        } else {
          printMainMenuUser();
          maxFuncBound = 2;
        }
        // Gets user option
        cin >> opt;

        if (opt < minFuncBound || opt > maxFuncBound) {
          cout << "Invalid option! Please try again." << endl;
          continue;
        } else {
          mainMenuOpt = opt;
          flag = false;
          continue;
        }
      }

      if (mainMenuOpt == 0) {
        // Logout
        curState = log_out;
      }
      if (mainMenuOpt == 1) {
        // View projects
        curState = view_my_projects;
      }
      if (mainMenuOpt == 2) {
        // Work on projects
        curState = work_on_project;
      }
      if (mainMenuOpt == 3) {
        // Create new project
        curState = create_project;
      }
      if (mainMenuOpt == 4) {
        // Delete a project
        cout << "Project ID to delete: " << endl;
        int pr;
        cin >> pr;
        try {
          model.deleteProject(pr);
          cout << "Project with ID " << pr << " deleted succesfully." << endl
               << endl;
        } catch (...) {
          cout << "Invalid ID number." << endl << endl;
        }
      }
      if (mainMenuOpt == 5) {
        // Update date
        Date *cur = new Date(model.getCurDay()->getDay() + 1,
                             model.getCurDay()->getMonth(),
                             model.getCurDay()->getYear());
        model.setCurDay(cur);
        model.updateSprint();
      }
      if (mainMenuOpt == 6) {
        // Adds User
        model.addUser(createUser());
        cout << "Created New User" << endl << endl;
      }
      break;
    }

    case log_out: {
      cout << "Logging out... " << endl;
      curState = login_screen;
      break;
    }
      // View All Projects
    case view_my_projects: {
      model.viewMyProjects(curUser);
      cout << endl << endl << endl;
      curState = main_menu;
      break;
    }
      // View Project Commands
    case work_on_project: {
      int projID;
      int minFuncBound = 0;
      // Asks for User's project ID.
      cout << "Please Enter Your Project ID: " << endl;
      cin >> projID;
      curProject = projID;
      // Gets the corresponding project.
      Project *curProj;
      try {
        curProj = model.getProject(projID);
        if (!curProj->hasUser(curUser->getID())) {
          cout << "You do not have permission to view this project." << endl;
          curState = main_menu;
          break;
        } else {
          curState = project_menu;
          break;
        }
      } catch (...) {
        curState = main_menu;
        cout << "Project not found." << endl;
        cout << endl << endl;
        break;
      }
    }
      // Menu for Project
    case project_menu: {
      int funcChoice;
      Project *curProj = model.getProject(curProject);
      // Gets the user's perm level in the project.
      enum permLevel curUserPerms = curProj->getUserPerm(curUser);

      // Sets the function boundary.
      int maxFuncBound = setFuncBoundary(curUserPerms);

      // Prints the respective function.
      printUserFunc(maxFuncBound);
      cin >> funcChoice;
      if (funcChoice < 0 || funcChoice > maxFuncBound) {
        cout << "Invalid Option. Please Redo." << endl;
        break;
      }
      if (funcChoice == 0) {
        // Logout
        curState = main_menu;
        break;
      }
      if (funcChoice == 1) {
        // View KanbanBoard
        model.viewKanbanBoard();
        break;
      }
      if (funcChoice == 2) {
        // Print All Tasks
        model.printAllTask(curProj);
        curState = project_menu;
        break;
      }
      if (funcChoice == 3) {
        // Add tasks
        curProj->addTasks(createTask(*model.getCurDay()));
        curState = project_menu;
        break;
      }
      if (funcChoice == 4) {
        // Update Task
        cout << "Please Enter the Task ID you want to Update: " << endl;
        cin >> curTaskID;
        curState = update_task;
        try {
          curProj->getTask(curTaskID);
        } catch (...) {
          cout << "Invalid task ID" << endl;
        }
        break;
      }
      if (funcChoice == 5) {
        // Delete Task
        int taskID;
        cout << "Please Enter the Task ID you want to delete: " << endl;
        cin >> taskID;
        try {
          curTask = curProj->getTask(taskID);
        } catch (...) {
          cout << "Task not found." << endl;
          cout << endl << endl;
          break;
        }

        curProj->deleteTask(curTask);
      }
      if (funcChoice == 6) {
        int UID;
        enum permLevel pl;
        int input;
        cout << "Please Enter the User ID of who you want to invite: " << endl;
        cin >> UID;
        User *u;
        for (auto user : model.getUsersList()) {
          if (user.second->getID() == UID) {
            u = user.second;
          }
        }
        if (u != nullptr) {
          cout << "Please choose one of the permission level for the User: "
               << endl;
          cout << "1. noperms" << endl;
          cout << "2. assistant" << endl;
          cout << "3. developer" << endl;
          cout << "4. manager" << endl;

          cin >> input;
          if (input < 1 || input > 4) {
            cout << "Invalid Option. Try Again!" << endl;
            continue;
          } else {
            pl = intToPerm(input);
          }
          curProj->addUser(u, pl);
        } else {
          cout << "User not found in system." << endl;
          cout << endl << endl;
          break;
        }
      }
      if (funcChoice == 7) {
        curProj->printAllUser();
        break;
      }
    }
    case update_task: {
      Project *curProj = model.getProject(curProject);
      curTask = curProj->getTask(curTaskID);
      int funcChoice;
      int minFuncBound = 0;
      enum permLevel curUserPerms = curProj->getUserPerm(curUser);
      int maxFuncBound = setFuncBoundaryUpdateTask(curUserPerms);
      // Prints the respective function.
      printUpdateTask(maxFuncBound);
      cin >> funcChoice;
      if (funcChoice < 0 || funcChoice > maxFuncBound) {
        cout << "Invalid Option. Please Redo." << endl;
        break;
      }
      if (funcChoice == 0) {
        // Main Menu
        curState = main_menu;
        break;
      } else if (funcChoice == 1) {
        // Update Status
        cout << "Updating status. What status would you like?" << endl;
        status stat;
        cout << "(1) todo, (2)doing, (3) done" << endl;
        int opt = 0;
        cin >> opt;
        switch (opt) {
        case 1:
          stat = todo;
          break;
        case 2:
          stat = doing;
          break;
        case 3:
          stat = done;
          break;
        }
        curTask->updateStatus(stat);
        cout << "Updated status to option " << stat << endl;
      } else if (funcChoice == 2) {
        // Update Description
        char *newDescription;
        cout << "Enter the description you would like to update the task with: "
             << endl;
        cin >> newDescription;
        curTask->updateDescription(newDescription);

      } else if (funcChoice == 3) {
        int opt;
        // Update Task Type
        cout << "Enter the type you would like to update the task with: "
             << endl;
        cout << "(1) User Story, (2) misc: task, (3) build, (4) test, (5) "
                "debug, (6) documentation, (7) review"
             << endl;
        cin >> opt;
        if (opt < 1 || opt > 7) {
          cout << "Invalid Option!" << endl;
          break;
        }

        taskType typeNum = intToTaskType(opt);
        curTask->updateTaskType(typeNum);

      } else if (funcChoice == 4) {
        int opt;
        cout << "Enter the priority you would like to update the task with: "
             << endl;
        cout << "(1) high, (2) medium, (3) low" << endl;
        cin >> opt;
        if (opt < 1 || opt > 3) {
          cout << "Invalid Option!" << endl;
          break;
        }

        priority prioNum = intToPriority(opt);
        curTask->updatePriority(prioNum);
        // Update Task Priority
      } else if (funcChoice == 5) {
        cout << "Enter the new deadline (dd mm yyyy format): ";
        Date newDead;
        cin >> newDead;
        curTask->updateDate(newDead);
        // Update Deadline
      } else if (funcChoice == 6) {
        // Add Assignee
        cout << "Enter assigne ID: ";
        int uniqueid;
        cin >> uniqueid;
        User *newUser;
        for (User *u : model.getUsers()) {
          if (u->getID() == uniqueid) {
            curTask->updateAssignee(u);
          }
        }

      } else if (funcChoice == 7) {
        cout << "Enter user ID to remove: ";
        int removeid;
        cin >> removeid;
        vector<User *> users = curTask->getAssignees();
        for (auto a = users.begin(); a != users.end(); a++) {
          if ((*a)->getID() == removeid) {
            curTask->getAssignees().erase(a);
          }
        }
        curState = update_task;
      }
      break;
    }
    case create_project: {
      cout << "Project Name: ";
      string name;
      cin >> name;
      model.createProject(name);
      curState = main_menu;
      break;
    }
    }
  }
}
// Allows to create user and asks for the following information.
User *createUser() {
  cout << "Please enter the user info." << endl;
  char *name = new char[256];
  char *email = new char[256];
  char *nationality = new char[256];
  string userName;
  string password;
  Date dob;

  cout << "Name: ";
  cin >> name;

  cout << "Email: ";
  cin >> email;

  cout << "Nationality: ";
  cin >> nationality;

  cout << "Date of birth in day month year format: ";
  cin >> dob;

  // Convert the name to a std::string object.
  string stringName = string(name);
  cout << "Username: ";
  cin >> userName;
  cout << "Password: ";
  cin >> password;
  cout << "Please take note of your username and password" << endl
       << "Username = " << userName << endl
       << "Password = " << password << endl;

  // Dynamically allocate the ownerContact and owner objects using the new
  // keyword.
  Contact *ownerContact = new Contact(name, email, nationality, dob);
  User *owner = new User(userName, ownerContact, password);

  // Return the address of the dynamically allocated owner object.
  return owner;
}

Task *createTask(Date cur) {
  cout << "Creating task" << endl;
  cout << "What type of task is it?" << endl;
  cout << "(1) User Story" << endl;
  cout << "(2) Misc. Task" << endl;
  cout << "(3) Build" << endl;
  cout << "(4) Test" << endl;
  cout << "(5) Debug" << endl;
  cout << "(6) Documentation" << endl;
  cout << "(7) Review" << endl;
  taskType type;
  int selection = 0;
  while (selection < 1 || selection > 7) {
    selection = 0;
    cin >> selection;
  }
  switch (selection) {
  case 1:
    cout << "User Story Selected" << endl;
    type = userStory;
    break;
  case 2:
    cout << "Misc Task Selected" << endl;
    type = t_task;
    break;
  case 3:
    cout << "Build Selected" << endl;
    type = build;
    break;
  case 4:
    cout << "Test Selected" << endl;
    type = test;
    break;
  case 5:
    cout << "Debug Selected" << endl;
    type = debug;
    break;
  case 6:
    cout << "Documentation Selected" << endl;
    type = documentation;
    break;
  case 7:
    cout << "Review Selected" << endl;
    type = review;
    break;
  }
  cout << "Task due date (dd mm yyyy): ";
  Date due;
  cin >> due;
  cout << "What priority should the task be?" << endl;
  cout << "(1) high, (2) meidum, (3) low" << endl;
  int prioSelection = 0;
  priority prio;
  while (prioSelection < 1 || prioSelection > 3) {
    selection = 0;
    cin >> prioSelection;
  }
  switch (prioSelection) {
  case 1:
    cout << "High Priority" << endl;
    prio = high;
    break;
  case 2:
    cout << "Medium Priority" << endl;
    prio = medium;
    break;
  case 3:
    cout << "Low Priority" << endl;
    prio = low;
    break;
  }
  cout << "What would you like the description to be?" << endl;
  char *desc = new char[128];
  cin >> desc;
  Task *ret = new Task(cur, due, desc, type, todo, prio);
  return ret;
}