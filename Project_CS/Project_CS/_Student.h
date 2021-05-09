#ifndef _STUDENT_H
#define _STUDENT_H

#include "_SchoolYear.h"
#include <iostream>
#include <string>
using namespace std;

struct Student;
struct SchoolYear;
struct Staff;
struct Student;


// Function to get data of students from a text file.
void getDataStudent(Student*& pHead, string filename);

// Function to let the user input list of student from a text file.
void inputStudent();

// Function to update a student grade.
void updateStudentResult(SchoolYear* schoolyear);

// Function to let a student changes her/his password.
void changePassStudent(Staff* staff, Student*& student, SchoolYear* schoolyear, string path);

// Function to check if the student's account & password inputted by user is correct or not.
bool loginStudent(Student* student);

void displayLoginStudent(Staff* staff, Student* student, SchoolYear* schoolyear);

void displayStudentProfile(Student*& student, string path);

void enroll();

bool checkEnroll();

#endif