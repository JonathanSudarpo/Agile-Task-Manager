#include "Task.hpp"
#include "Date.hpp"
#include "Utils.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

// Represents the constructor for task
// Inside it contains the User, created date, the day when it is due, The
// description of the task, the type, and the status fo the tasks.
Task::Task(vector<User *> assignee, Date createdDate, Date dueDate,
           char *description, taskType type, enum status status,
           enum priority priority) {
  this->uniqueID = generateUID(id_task);
  this->assignee = assignee;
  this->createdDate = createdDate;
  this->dueDate = dueDate;
  this->description = description;
  this->type = type;
  this->status = status;
  this->priority = priority;
}

// Constructor
Task::Task(Date createdDate, Date dueDate, char *description, taskType type,
           enum status status, enum priority priority) {
  this->uniqueID = generateUID(id_task);
  this->createdDate = createdDate;
  this->dueDate = dueDate;
  this->description = description;
  this->type = type;
  this->status = status;
  this->priority = priority;
}

// Updates the date
void Task::updateDate(Date newdate) { this->dueDate = newdate; }

// Setters
void Task::updateAssignee(User* newAssignee){
  this->assignee.push_back(newAssignee);
}


// Updates task status
void Task::updateStatus(enum status newStatus) {
  this->status = newStatus; }

// Updates task priority
void Task::updatePriority(enum priority newPriority) {
  this->priority = newPriority;
}

// Update task description. 
void Task::updateDescription(char *newDescription) {
  this->description = newDescription;
}

// Task update task type
void Task::updateTaskType(enum taskType newType) {
  this->type = newType; }

// Getters

// Gets the task id.
int Task::getTaskID() {
  return this->uniqueID; }

// Gets the Task assignees
vector<User *> Task::getAssignees() {
  return this->assignee; }

// Gets the task status.
enum status Task::getStatus() {
  return this->status; }

// Gets task priority.
enum priority Task::getPriority() {
  return this->priority; }

// Gets task type
enum taskType Task::getTaskType() {
  return this->type; }

// Gets task description.
char *Task::getTaskDescription() {
  return this->description; }

// Gets the task due date
Date Task::getTaskDueDate() {
  return this->dueDate; }

// ets the task created date
Date Task::getTaskCreatedDate() {
  return this->createdDate; }

// Other Methods
// Represents the method to add assignee
void Task::addAssignee(User *u) {
  this->assignee.push_back(u); }

// Represents the the time till which the task is suppose to be done by.
Date Task::taskTimeTillDue() {
  Date timeLeft = this->createdDate - this->dueDate;
  return timeLeft;
}
// Tells if the Task is due or not by checking the time left
bool Task::isTaskDue(Date current) {
  Date timeLeft = taskTimeTillDue();
  return (timeLeft.getDays() < 0);
}

// Updates the sprint.
void Task::updateSprint(Date curDay) {
  if (this->status == doing) {
    if (curDay.getDays() > this->dueDate.getDays()) {
      this->status = done;
    }
  }
}
