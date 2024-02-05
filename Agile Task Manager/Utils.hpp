#pragma once 
#include <stdlib.h>

using namespace std;

//#include "KanbanBoardModel.hpp"
// 

// Represents the permissions levels 
enum permLevel {noperm, assistant, developer, manager, boardowner};

// Represents the status of the task to see if it is done or in process or is to be done 
enum status {todo, doing, done};

// Represents the priority levels which tells how important is the task and which one should be done first.
enum priority {high, medium, low};

// Represents the type of task
enum taskType {userStory, t_task, build, test, debug, documentation, review}; 

// Represents the different  user types 
enum IDTYPE {id_task, id_user, id_project};

// Generates the UID 
int generateUID(enum IDTYPE); 

void printMainMenuUser();

void printMainMenuOwner(); 

void printUserFunc(int funcBound);

void printUpdateTask(int funcBound);

int setFuncBoundaryUpdateTask(enum permLevel); 

int setFuncBoundary(enum permLevel); 

// void saveKanbanBoard(KanbanBoardModel model);

enum permLevel intToPerm(int i); 

enum taskType intToTaskType(int i); 

enum priority intToPriority(int i); 