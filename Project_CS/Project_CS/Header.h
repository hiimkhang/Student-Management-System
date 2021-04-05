#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <fstream>
#include "string.h"
using namespace std;

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
    string courseDate[6] = { "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    string courseSession[4] = { "07:30", "09:30", "13:30", "15:30" };
    Course* pNext;
};


struct Class {
    string className;
    Student* student;
    Class* pNext;
};

struct Student {
    int No, StudentID, SocialID;
    string studentPassword = "12345678";
    string Firstname, Lastname; 
    string Gender;
    string DoB;
};

<<<<<<< HEAD
=======
struct Staff {
    string nameStaff;
    string staffAccount, staffPassword = "staff";
    Staff* pNext;
};

void loginStaff(Staff*& staff);


>>>>>>> 3decbec48ede187a5afb4aff7352b78c908dc0e7
#endif