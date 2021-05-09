#ifndef _STAFF_H
#define _STAFF_H
#include "_SchoolYear.h"
#include <iostream>
#include <string>
using namespace std;

struct Staff;
struct SchoolYear;
struct Student;


// Function to get data of staffs from a text file.
void getDataStaff(Staff*& pHead, string filename);

// Function to let a staff changes her/his password.
void changePassStaff(Staff*& staff, Student* student, SchoolYear* schoolyear, string path);

// Function to check if the staff's account & password inputted by user is correct or not.
bool loginStaff(Staff* staff);

void displayLoginStaff(Staff* staff, Student* student, SchoolYear* schoolyear);

void displayStaffProfile(Staff* staff);

#endif
