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

#endif