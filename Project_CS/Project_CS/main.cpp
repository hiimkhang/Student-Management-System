#pragma once
#include "Header.h"

string g_account;
int g_ID;
string g_selectyear;
string g_selectClass;
string g_selectCourse;
int g_selectSemester;
string g_Time = "28/08/2021";

int main() {
	fixConsoleWindow();
	setConsoleWindow(800, 600);
	Staff* staff = nullptr;
	Student* student = nullptr;
	SchoolYear* schoolYear = nullptr;
	getDataStaff(staff, "Staff.csv");
	getDataStudent(student, "Student.csv");
	getDataSchoolYear(schoolYear, "school_year.txt");
	displayLogin(staff, student, schoolYear); 
	return 0;
}