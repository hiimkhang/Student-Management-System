#ifndef _SCHOOLYEAR_H
#define _SCHOOLYEAR_H
#include "Header.h"
#include "_Class.h"
#include "_Semester.h"
#include "_Staff.h"
#include "_Student.h"
#include "_Course.h"
#include "Console.h"

// Struct to define information of a student.
struct Student {
    int No, StudentID, SocialID;
    float totalMark, finalMark, midtermMark, otherMark;
    string studentPassword = "12345678";
    string Firstname, Lastname;
    string Gender;
    string DoB;
    string studentClass;
    Student* pNext;
    string* courseOfStudent;
    /*Course* courseOfStudent;*/
};

// Struct to define information of a course.
struct Course {
    string courseID, courseName;
    string teacherName;
    int creditNum;
    int maxNum_ofStudents = 50;
    int numOfStudents;
    string courseDate;
    string courseSession;
    Student* studentInCourse;
    Course* pNext;
};

// Struct to define information of a staff.
struct Staff {
    string nameStaff;
    string staffAccount, staffPassword = "staff";
    Course* staffCourse;
    Staff* pNext;
};

// Struct to define information of a class.
struct Class {
    string className;
    Student* student;
    Staff* staff;
    Class* pNext;
};

// Struct to define information of a semester.
struct Semester {
    int no;
    string start_date, end_date, register_start_date, register_end_date, teacher_name;
    int max_NoS[50];
    Class* classes;
    Course* course;
    Semester* pNext;
};

// Struct to define information of a schoolyear.
struct SchoolYear {
    string year;
    Class* classes;
    SchoolYear* pNext;
    Student* student;
    Semester* semester = nullptr;
    Staff* staff;
};

// Function to get data of schoolyears from a text file.
void getDataSchoolYear(SchoolYear*& school_year, string path);

void displayYear(SchoolYear* pHead);

// Function to create a new schoolyear.
void createNewYear(SchoolYear*& school_year);

void displaySchoolYearForStaff(Staff* staff, Student* student, SchoolYear*& schoolyear);
void displaySchoolYearForStudent(Staff* staff, Student* student, SchoolYear*& schoolyear);

string displaySelectedYearForStaff(Staff* staff, Student* student, SchoolYear* schoolyear);
string displaySelectedYearForStudent(Staff* staff, Student* student, SchoolYear* schoolyear);

#endif