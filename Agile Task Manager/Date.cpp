#include "Date.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

// Constructor
Date::Date(int day, int month, int year) {
  this->day = day;
  this->month = month;
  this->year = year;
  this->adjustDates();
}

// Contains the information about the date.
void Date::updateWithDays(int days) {
  this->year = days / 360;
  this->month = (days % 360) / 30;
  this->day = (days % 360) % 30;
}

// Allows us to ajust the dates when required.
void Date::adjustDates() { updateWithDays(getDays()); }

// Setters
void Date::updateDay(int day) { this->day = day; }
void Date::updateMonth(int month) { this->month = month; }
void Date::updateYear(int year) { this->year = year; }

// Getters
int Date::getDays() { return this->year * 360 + this->month * 30 + this->day; }
int Date::getDay() { return this->day; }
int Date::getMonth() { return this->month; }
int Date::getYear() { return this->year; }

// It overloadeds addition and subtraction operators
Date Date::operator+(const Date &d) {
  Date newDate(this->day + d.day, this->month + d.month, this->year + d.year);
  return newDate;
}
Date Date::operator-(const Date &d) {
  Date newDate(this->day - d.day, this->month - d.month, this->year - d.year);
  return newDate;
}
istream &operator>>(istream &is, Date &dt) {
  int day;
  int month;
  int year;
  is >> day >> month >> year;
  dt.updateDay(day);
  dt.updateMonth(month);
  dt.updateYear(year);
  dt.adjustDates();
  return is;
}

ostream &operator<<(ostream &os, const Date &dt) {
  os << dt.day << "/" << dt.month << "/" << dt.year;
  return os;
}