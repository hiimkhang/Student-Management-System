#ifndef _COURSE_H
#define _COURSE_H

#include "_SchoolYear.h"
#include <iostream>
#include <string>
using namespace std;

struct Course;
struct SchoolYear;
struct Student;


// Function to get data of all courses in a specific semester from a text file.
void getDataCoursesInSemester(SchoolYear*& schoolyear);

// Function to get data of all students in a specific course from a text file.
void getDataStudentInCourse(Student*& studentincourse);

// Function to get score of courses from a text file.
void getDataCourseScore(SchoolYear*& schoolyear, Student* student);

// Function to export list of students in a specific course into a text file.
void exportListStudentInCourse(SchoolYear* schoolyear);

// Function to update a course information.
void updateCourseInfo(SchoolYear*& schoolyear);

// Function to import score of a student into a text file.
void importScoreboard(SchoolYear*& schoolyear);

// Function to let a student unenroll a course (only available during the course register time)
void removeEnrolled();

// Function to let staff delete a course.
void deleteCourse(SchoolYear*& schoolyear);

void displayCourseInSemester(SchoolYear*& schoolyear);

void displayCourseWhenDayExceed(SchoolYear*& schoolyear);
void displayCourseForStudent(SchoolYear*& schoolyear);

void displayCoursesStudentsExceed(SchoolYear*& schoolyear);
void viewScore(SchoolYear* schoolyear);
void viewCourseEnrolled();

#endif