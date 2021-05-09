#ifndef _SEMESTER_H
#define _SEMESTER_H

#include "_SchoolYear.h"
#include <iostream>
#include <string>
using namespace std;

struct Semester;
struct SchoolYear;
struct Staff;
struct Student;

// Function to get data of semesters from a text file.
void getDataSemester(SchoolYear*& schoolyear);

// Function to create a new semester for a specific schoolyear.
void createSemester(SchoolYear*& Schoolyear);

void displaySemester(Staff* staff, Student* student, SchoolYear* schoolyear);

void displaySemesterForStudent(Staff* staff, Student* student, SchoolYear* schoolyear);

#endif