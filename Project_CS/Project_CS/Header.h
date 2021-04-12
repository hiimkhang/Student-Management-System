#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "Console.h"

using namespace std;

static string ACCOUNT{};

struct Student {
    int No, StudentID, SocialID;
    string studentPassword = "12345678";
    string Firstname, Lastname;
    string Gender;
    string DoB;
    Student* pNext;
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
    string teacherCourse = "N/A";
    string teacherClass = "N/A";
    Staff* pNext;
};

void getDataStaff(Staff* &pHead, string filename);
void getDataSchoolYear(SchoolYear*& school_year, string path);
void displayYear(SchoolYear* pHead);
void deleteList(Staff*& pHead);
void createNewYear(SchoolYear*& school_year);

// Login Functions
void changePassStaff(Staff*& staff, SchoolYear *schoolyear, string path);
void changePassStudent(Student*& student, SchoolYear* schoolyear, string path);
bool loginStaff(Staff* &staff);
bool loginStudent(Student* student);


// Display menus function
void displayLogin(Staff *staff, Student *student, SchoolYear *schoolyear);
void loadingSuccess();
void displayLoginStaff(Staff *staff, SchoolYear *schoolyear);
void getDataStudent(Student*& pHead, string filename);
void displaySchoolYear();
void displayStaffProfile(Staff* &staff);
void displayLoginStudent(Student* student, SchoolYear* schoolyear);
void displayStudentProfile(Student* student);

// Others
int numberOfLine(string filename);
void changeACCOUNT( string s);

