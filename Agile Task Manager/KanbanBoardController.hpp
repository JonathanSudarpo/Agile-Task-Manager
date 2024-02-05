#pragma once 
#include <iostream>
#include "User.hpp"
#include "Project.hpp"
#include "KanbanBoardModel.hpp"
#include <stdlib.h>

using namespace std;

enum KSTATE {load_screen, login_screen, main_menu, project_menu, task_menu, log_out, view_my_projects, work_on_project, create_project, update_task};

//Represents the KanbanBoardController Class
class KanbanBoardController {
public:
  void run();
};