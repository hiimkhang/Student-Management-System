#ifndef _CLASS_H
#define _CLASS_H

#include "_SchoolYear.h"
#include <iostream>
#include <string>
using namespace std;

struct Class;
struct SchoolYear;
struct Staff;
struct Student;

// Function to get data of classes from a text file.
void getDataClass(SchoolYear*& Schoolyear);

// Function to get data of all students in a specific class from a text file.
void getDataStudentinClass(SchoolYear*& schoolyear);

// Function to create a new class for a specific schoolyear.
void createClassForYear(SchoolYear*& Schoolyear);

void displayClass(SchoolYear* schoolyear);
void displayMenuClass(Staff* staff, Student* student, SchoolYear*& schoolyear);
void displayStudentInClass(SchoolYear*& schoolyear, Student* student);

#endif