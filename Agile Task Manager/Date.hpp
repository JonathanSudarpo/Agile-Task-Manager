#pragma once
#include <iostream>
#include <stdlib.h>

using namespace std;

// Represents the date class
class Date {
  // Since the calendar is weird we have decided that each year has 12 months,
  // each month as 30 days. So a year is 360 days not 365 technically.

// It contains everything which comes under date
private:
  int day;
  int month;
  int year;


  void updateWithDays(int days);
// it allows us to adjust the dates.
  void adjustDates();

public:
friend ostream& operator<<(ostream& os, const Date& dt);
friend istream &operator>>(istream &is, Date &dt);
  // Represents the constructor
  Date() : day(0), month(0), year(0) {}
  Date(int day, int month, int year);

  // It represents the Destructor, all primitive so nothing needed.
  ~Date() {}

  // Copy constructor
  Date(const Date &other) {
    day = other.day;
    month = other.month;
    year = other.year;
  }

  // Copy Assignment
  Date &operator=(const Date &other) {
    if (this == &other) {
      return *this;
    }
    day = other.day;
    month = other.month;
    year = other.year;

    return *this;
  }
  // Move Constructor
  Date(Date &&other) {
    day = other.day;
    month = other.month;
    year = other.year;
  }
  // Move Assignment
  Date &operator=(Date &&other) {
    if (this == &other) {
      return *this;
    }
    day = other.day;
    month = other.month;
    year = other.year;
    return *this;
  }

  // Setters
  void updateDay(int day);
  void updateMonth(int month);
  void updateYear(int year);

  // Getters
  int getDays();
  int getDay();
  int getMonth();
  int getYear();

  // Overloaded addition and subtraction operators
  Date operator+(const Date &d);
  Date operator-(const Date &d);
};

//Overloaded >> operator
istream& operator>> (istream& is, Date& dt);

//Overloaded << operator
ostream &operator<<(ostream &os, const Date &dt);