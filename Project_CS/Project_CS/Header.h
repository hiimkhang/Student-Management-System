#ifndef _HEADER_H
#define _HEADER_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "_SchoolYear.h"
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <direct.h>

using namespace std;
struct Staff;
struct Student;
struct SchoolYear;

void displayLogin(Staff* staff, Student* student, SchoolYear* schoolYear);

// Function to count the number of lines in a text file (eof).
int numberOfLine(string filename);

// Function to display when login successfully.
void loadingSuccess();

// Function to add 0 into a date if its format is not right (Ex: 24/1/2021 -> 24/01/2021).
string add0(string date);

// Function to deallocate the link list after being used.
void deleteList(Staff*& pHead);

// Function to compare two dates, return -1 if date1 > date2, +1 vice versa, 0 if equal.
int date_cmp(const char* d1, const char* d2);

// Function to add number of day into a given date.
void DatePlusDays(struct tm* date, int days);

// Function to add number of day into a given date.
string addDays(string date1, int days);

void welcome();

#endif