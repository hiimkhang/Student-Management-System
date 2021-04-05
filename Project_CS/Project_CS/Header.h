#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <fstream>
#include "string.h"
using namespace std;

struct Course {

};

struct Semester {
    int no;
    string start_date, end_date, register_start_date, register_end_date;
    C
};

struct Class {
    string classname;
    Student* student;
    Class* pNext;
};

struct YearSchool {
    string year;
    Class* classes;
    YearSchool* pNext;

};

struct Student{
    int No, StudentID, SocialID;
    string Firstname, Lastname; 
    string Gender;
    string DoB;
};

// Function to input First name and Last name of student.
void inputName (char *name);
// Function to input student's information using handwork.
void inputInfo (StudentInfo &SI);
// Function to input student's information using CSV file.
void loadInfo (StudentInfo &SI, char *filename);
#endif