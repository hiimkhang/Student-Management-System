#pragma once
#include <iostream>
#include <fstream>
#include <string>
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


struct YearSchool {
    string year;
    Class* classes;
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

bool loginStaff(Staff*& staff);
void getData(Staff* &staff, string filename);
void display(Staff* pHead);
void deleteList(Staff*& pHead);

