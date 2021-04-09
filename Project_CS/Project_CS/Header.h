#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
using namespace std;

struct Student {
    int No, StudentID, SocialID;
    string studentPassword = "12345678";
    string Firstname, Lastname;
    string Gender;
    string DoB;
};


struct Class {
    string className;
    Student* student;
    Class* pNext;
};


struct SchoolYear {
    string year;
    Class* classes;
    SchoolYear* pNext;
};

struct Semester {
    int no;
    string start_date, end_date, register_start_date, register_end_date;
};

struct Course {
    string courseID, courseName;
    string teacherName;
    int creditNum;
    int maxNum_ofStudents = 50;
    string courseDate[6] = { "MON", "TUE", "WED", "THU", "FRI", "SAT" };
    string courseSession[4] = { "07:30", "09:30", "13:30", "15:30" };
    Course* pNext;
};

struct Staff {
    string nameStaff;
    string staffAccount, staffPassword = "staff";
    Staff* pNext;
};

bool loginStaff(Staff* staff);
void getDataStaff(Staff* &pHead, string filename);
void getDataSchoolYear(SchoolYear*& school_year, string path);
void displayYear(SchoolYear* pHead);
void deleteList(Staff*& pHead);
void createNewYear(SchoolYear*& school_year);

// Display menus function
void displayLogin(Staff *staff, SchoolYear *schoolyear);
void loadingSuccess()
#endif

