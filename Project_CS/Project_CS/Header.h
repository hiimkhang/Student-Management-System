#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "Console.h"


using namespace std;

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

struct Semester {
    short no, school_year;
    string start_date, end_date, register_start_date, register_end_date, teacher_name;
    int ID, number_of_credits;
    int max_NoS[50];
    Semester* pNext;
};

struct SchoolYear {
    string year;
    Class* classes = nullptr;
    SchoolYear* pNext;
    Semester* semester = nullptr;
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

// Get Input
void getDataStaff(Staff* &pHead, string filename);
void getDataSchoolYear(SchoolYear*& school_year, string path);
void getDataStudent(Student*& pHead, string filename);
void getDataClass(SchoolYear*& Schoolyear);
void createClassForYear(SchoolYear*& Schoolyear);
void createSemester(SchoolYear*& Schoolyear);
void deleteList(Staff*& pHead);
void createNewYear(SchoolYear*& school_year);

// Login Functions
void changePassStaff(Staff*& staff, Student* student,SchoolYear *schoolyear, string path);
void changePassStudent(Staff* staff, Student*& student, SchoolYear* schoolyear, string path);
bool loginStaff(Staff* staff);
bool loginStudent(Student* student);


// Display menus function
void displayLogin(Staff *staff, Student *student, SchoolYear *schoolyear);
void displayLoginStaff(Staff* staff, Student* student, SchoolYear* schoolyear);
void displaySchoolYear(Staff* staff, Student* student, SchoolYear* &schoolyear);
void displayStaffProfile(Staff* staff);
void displayLoginStudent(Staff* staff, Student* student, SchoolYear* schoolyear);
void displayStudentProfile(Student*& student, string path);
void displayClass(SchoolYear* schoolyear);
void displaySemester(Staff* staff, Student* student, SchoolYear* schoolyear, string& year);
void displayYear(SchoolYear* pHead);
void displayStudentYear(SchoolYear* pHead);

// Others
int numberOfLine(string filename);
void loadingSuccess();


