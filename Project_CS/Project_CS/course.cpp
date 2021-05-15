#pragma once
#include "_Course.h"
#include "Console.h"

extern string g_account;
extern int g_ID;
extern string g_selectyear;
extern int g_selectSemester;
extern string g_selectClass;
extern string g_selectCourse;
extern string g_Time;

void exportListStudentInCourse(SchoolYear* schoolyear) {

	while (schoolyear->year != g_selectyear) {
		schoolyear = schoolyear->pNext;
	}
	while (schoolyear->semester->no != g_selectSemester) {
		schoolyear->semester = schoolyear->semester->pNext;
	}
	getDataCoursesInSemester(schoolyear);
	while (schoolyear->semester->course->courseID != g_selectCourse) {
		schoolyear->semester->course = schoolyear->semester->course->pNext;
	}
	getDataStudentInCourse(schoolyear->semester->course->studentInCourse);
	ofstream out;
	ifstream in;
	system("cls");
	cout << "\n\n\t\tPlease input the link of your .csv file (Ex:C:\\DocumentsClass\\20CTT1.csv):\n\t\t";
	string s;
	getline(cin, s);
	out.open(s);
	if (numberOfLine(s) == 0) {
		in.open("Student.csv");
		getline(in, s);
		out << s << endl;
	}
	in.close();
	Student* pCur = schoolyear->semester->course->studentInCourse;
	if (out) {
		while (pCur) {
			out << pCur->StudentID << ",";
			out << pCur->Firstname << ",";
			out << pCur->Lastname << ",";
			out << pCur->Gender << ",";
			out << pCur->DoB << ",";
			out << pCur->studentClass << ",";
			out << pCur->SocialID << "\n";
			/*cout << pCur->StudentID << ",";
			cout << pCur->Firstname << ",";
			cout << pCur->Lastname << ",";
			cout << pCur->Gender << ",";
			cout << pCur->DoB << ",";
			cout << pCur->studentClass << ",";
			cout << pCur->SocialID << "\n";*/
			pCur = pCur->pNext;
		}
		cout << "\n\n\t\t\t\tExport students learning " << g_selectCourse <<
			" successfully!";
		out.close();
	}
	else cout << "\n\t\t\t\tERROR. Can't open file...";
}

void importScoreboard(SchoolYear*& schoolyear) {
	system("cls");
	
	string choice;
	do {
		if (g_Time != "") {
			gotoXY(21, 4); cout << "Date: " << g_Time;
		}
		gotoXY(21, 5); cout << "==================================================================";
		Textcolor(Blue);
		gotoXY(47, 8); cout << "SEMESTER " << g_selectSemester;
		Textcolor(7);
		cout << "\n\n\n\t\t\t\t1. Create template to import scoreboard \n";
		cout << "\n\t\t\t\t2. Import scoreboard \n";
		cout << "\n\t\t\t\t3. Exit \n";
		cout << "\n\n\t\t\t\t" << char(26) << " Please input your option: ";
		cin >> choice;
		cin.ignore();
		if (choice == "1") {
			cout << "\n\t\t\t Input link's location (in your computer) to export scoreboard template: \n\t\t\t";
			string s;
			getline(cin, s);
			ofstream out;
			out.open(s);
			out << "No,StudentID,Student FullName,Total Mark,Final Mark,Midterm Mark,Other Mark\n";
			ifstream in;
			in.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_student.csv");
			string str;
			getline(in, str);
			for (int i = 1; i <= numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_student.csv") - 1; i++) {
				out << i << ",";
				getline(in, str, ',');
				out << str << ",";
				getline(in, str, ',');
				out << str << " ";
				getline(in, str, ',');
				out << str << ",";
				getline(in, str, ',');
				out << ",";
				getline(in, str, ',');
				out << ",";
				getline(in, str, ',');
				out << ",";
				getline(in, str, ',');
				out << ",";
				getline(in, str, '\n');
				out << "\n";
			}
			in.close();
			out.close();
			cout << "\n\t\t\t\tCreated!";
			cout << "\n\n\t\t\t\tPress any key to continue";
			_getch();
			system("cls");
		}
		else if (choice == "2") {
			cout << "\n\t\t\t\t" << char(26) << " Import link that contents template: ";
			string s;
			getline(cin, s);
			ifstream in;
			in.open(s);
			if (in) {
				ofstream out;
				out.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_score.csv");
				string str;
				if (out) {
					getline(in, str);
					out << str << endl;
					for (int i = 1; i <= numberOfLine(s) - 1; i++) {
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, ',');
						if (str == "") str = "0";
						if (stoi(str) > 10) str = "10";
						if (stoi(str) < 0) str = "0";
						out << str << ",";
						getline(in, str, ',');
						if (str == "") str = "0";
						if (stoi(str) > 10) str = "10";
						if (stoi(str) < 0) str = "0";
						out << str << ",";
						getline(in, str, ',');
						if (str == "") str = "0";
						if (stoi(str) > 10) str = "10";
						if (stoi(str) < 0) str = "0";
						out << str << ",";
						getline(in, str, '\n');
						if (str == "") str = "0";
						if (stoi(str) > 10) str = "10";
						if (stoi(str) < 0) str = "0";
						out << str << "\n";
					}
					out.close();
					cout << "\n\t\t\t\tCompleted! \n";
					cout << "\n\n\t\t\t\tPress any key to continue";
				}
				in.close();
			}
			else {
				cout << "\n\t\t\t\tFailed! \n";
				cout << "\n\n\t\t\t\tPress any key to continue";
			}
			_getch();
			system("cls");
		}
		else if (choice == "3") {
			break;
		}
		else {
			cout << "\n\t\t\t\tInvalid input\n\t" << char(26) << " Please enter your option again: ";
			Sleep(1000);
		}
	} while (choice != "3");
}

void getDataScore(SchoolYear*& schoolyear, string path) {
	int no, studentID;
	float total_mark, final_mark, midterm_mark, other_mark;
	string Student_full_name;
	ifstream in;
	SchoolYear* pCur = new SchoolYear;
	in.open(path);
	if (in) {
		for (int i = 1; i <= numberOfLine(path) - 1; i++) {
			if (schoolyear == nullptr) {
				schoolyear = new SchoolYear;
				pCur = schoolyear;
			}
			else {
				pCur->pNext = new SchoolYear;
				pCur = pCur->pNext;
			}
			while (pCur && pCur->year != g_selectyear)
				pCur = pCur->pNext;
			if (pCur == nullptr) {
				cout << "\n\t\t\t\tThere is no schoolyear match your search";
				return;
			}
			while (pCur->semester && pCur->semester->no != g_selectSemester)
				pCur->semester = pCur->semester->pNext;
			if (pCur->semester == nullptr) {
				cout << "\n\t\t\t\tThere is no semester match your search";
				return;
			}
			while (pCur->semester->course->courseID != g_selectCourse)
				pCur->semester->course = pCur->semester->course->pNext;
			if (pCur->semester->course == nullptr) {
				cout << "\n\t\t\t\tThere is no course match your search";
				return;
			}
			in >> no;
			char z;
			in >> z;
			in >> studentID;
			getline(in, Student_full_name, ',');
			in >> total_mark;
			in >> z;
			in >> final_mark;
			in >> z;
			in >> midterm_mark;
			in >> z;
			in >> other_mark;
			in >> z;
			while (pCur->semester->course->studentInCourse->StudentID != studentID) {
				pCur->semester->course->studentInCourse->totalMark = total_mark;
				pCur->semester->course->studentInCourse->finalMark = final_mark;
				pCur->semester->course->studentInCourse->midtermMark = midterm_mark;
				pCur->semester->course->studentInCourse->otherMark = other_mark;
				pCur->pNext = nullptr;
			}
		}
		in.close();
	}
	else cout << "\t\t\t\t\nERROR \n";
}

void getDataCourseScore(SchoolYear*& schoolyear, Student* student) {
	ifstream in;
	ofstream out;
	string path = to_string(g_ID) + "_Semester" + to_string(g_selectSemester) + "_Course.csv";
	string* CourseIDdata = new string[numberOfLine(path) - 1];
	string* totalMark = new string[numberOfLine(path) - 1];
	in.open(path);
	if (in.is_open()) {
		string str;
		getline(in, str, '\n');
		for (int i = 0; i < numberOfLine(path) - 1; ++i) {
			getline(in, str, ',');
			getline(in, str, ',');
			CourseIDdata[i] = str;
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, '\n');
		}
		in.close();
	}
	else cout << "\n\n\t\t\t\tCan not open file directory";

	for (int i = 0; i < numberOfLine(path) - 1; ++i) {
		string path2 = g_selectyear + "_Semester" + to_string(g_selectSemester) +
			"_Course_" + CourseIDdata[i] + "_score.csv";
		in.open(path2);
		if (in.is_open()) {
			string str, strID = "1";
			getline(in, str, '\n');
			while (strID != to_string(g_ID)) {
				getline(in, str, ',');
				getline(in, strID, ',');
				getline(in, str, ',');
				getline(in, totalMark[i], ',');
				getline(in, str, ',');
				getline(in, str, ',');
				getline(in, str, '\n');
			}
			in.close();
		}
		else cout << "\n\n\t\t\t\tCan not open directory file";
	}
	system("cls");
	setConsoleWindow(800, 600);
	getDataSemester(schoolyear);
	getDataCoursesInSemester(schoolyear);

	Semester* tempSemester = schoolyear->semester;
	while (tempSemester && tempSemester->no != g_selectSemester)
		tempSemester = tempSemester->pNext;

	if (g_Time != "") {
		gotoXY(21, 4); cout << "Date: " << g_Time;
	}
	gotoXY(21, 5); cout << "==================================================================";
	Textcolor(Blue);
	gotoXY(47, 8); cout << "SEMESTER " << g_selectSemester;
	gotoXY(40, 9); cout << "(" << add0(tempSemester->start_date) << " -- " << add0(tempSemester->end_date) << ")";
	gotoXY(44, 10); cout << "STUDENT " << g_ID;
	Textcolor(7);

	gotoXY(15, 14); cout << "Course name";
	gotoXY(55, 14); cout << "Course ID"; //25
	gotoXY(67, 14); cout << "Credits";  // 12
	gotoXY(77, 14); cout << "Total grade"; // 10

	gotoXY(10, 16); cout << "===================================================="
		"=================================";

	int y = 18, i = 0;

	if (numberOfLine(path) == 1) {
		gotoXY(15, 18); cout << "N/A";
		gotoXY(55, 18); cout << "N/A";
		gotoXY(67, 18); cout << "N/A";
		gotoXY(77, 18); cout << "N/A";
	}
	else {
		while (i < numberOfLine(path) - 1) {
			Course* tempCourse = tempSemester->course;
			while (tempCourse && tempCourse->courseID != CourseIDdata[i])
				tempCourse = tempCourse->pNext;
			if (tempCourse) {
				gotoXY(15, y); cout << tempCourse->courseName;
				gotoXY(55, y); cout << tempCourse->courseID;
				gotoXY(67, y); cout << tempCourse->creditNum;
				gotoXY(77, y); cout << totalMark[i];
			}
			y++; i++;
		}
	}
	gotoXY(38, y + 4); cout << "Press any key to return...";
	_getch();
	system("cls");
	delete[]CourseIDdata, totalMark;
}

void viewScore(SchoolYear* schoolyear) {
	system("cls");
	setConsoleWindow(900, 700);
	gotoXY(18, 5); cout << "\t\t\t\t" << char(3) << " VIEW SCOREBOARD " << char(3) << endl;
	gotoXY(8, 7); cout << "===========================================================================================================" << endl;
	string str;
	ifstream in;
	int y = 10;
	in.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_score.csv");
	if (in.is_open()) {
		getline(in, str, ',');
		gotoXY(2, y); cout << str;
		getline(in, str, ',');
		gotoXY(7, y); cout << str;
		getline(in, str, ',');
		gotoXY(23, y); cout << str;
		getline(in, str, ',');
		gotoXY(58, y); cout << str;
		getline(in, str, ',');
		gotoXY(73, y); cout << str;
		getline(in, str, ',');
		gotoXY(88, y); cout << str;
		getline(in, str, '\n');
		gotoXY(103, y); cout << str;
		y += 2;
		for (int i = 2; i <= numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_score.csv"); i++) {
			getline(in, str, ',');
			gotoXY(2, y); cout << str;
			getline(in, str, ',');
			gotoXY(7, y); cout << str;
			getline(in, str, ',');
			gotoXY(23, y); cout << str;
			getline(in, str, ',');
			gotoXY(58, y); cout << str;
			getline(in, str, ',');
			gotoXY(73, y); cout << str;
			getline(in, str, ',');
			gotoXY(93, y); cout << str;
			getline(in, str, '\n');
			gotoXY(110, y); cout << str;
			y++;
		}
		in.close();
	}
	else cout << "\n\n\t\t\t\tFailed to open directory file(No imported board).";
}

void getDataStudentInCourse(Student*& studentincourse) {
	studentincourse = nullptr;
	ifstream in;
	Student* pCur = nullptr;
	ofstream out;
	out.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_student.csv", ios::app);
	if (numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_student.csv") == 0) {
		string s;
		in.open("Student.csv");
		getline(in, s);
		out << s << endl;
		in.close();
	}
	out.close();
	in.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_student.csv");
	if (in) {
		string str;
		getline(in, str);
		for (int i = 1; i <= numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_student.csv") - 1; i++) {
			if (studentincourse == nullptr) {
				studentincourse = new Student;
				pCur = studentincourse;
			}
			else {
				pCur->pNext = new Student;
				pCur = pCur->pNext;
			}
			in >> pCur->StudentID;
			char c;
			in >> c;
			getline(in, pCur->Firstname, ',');
			getline(in, pCur->Lastname, ',');
			getline(in, pCur->Gender, ',');
			getline(in, pCur->DoB, ',');
			getline(in, pCur->studentClass, ',');
			in >> pCur->SocialID;
			in >> c;
			getline(in, pCur->studentPassword, '\n');
			pCur->pNext = nullptr;
		}
		in.close();
	}
	else {
		cout << "\t\t\t\t\nERROR\n";
	}
}

void getDataCoursesInSemester(SchoolYear*& schoolyear) {
	ifstream in;
	SchoolYear* pCur1 = schoolyear;
	while (pCur1->semester && pCur1->semester->no != g_selectSemester) {
		pCur1->semester = pCur1->semester->pNext;
	}
	pCur1->semester->course = nullptr;
	Course* pCur = nullptr;
	in.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv");
	if (in) {
		string str;
		int credits, numberOfStudents;
		char c;
		getline(in, str);
		for (int i = 1; i <= numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv") - 1; i++) {
			if (pCur1->semester->course == nullptr) {
				pCur1->semester->course = new Course;
				pCur = schoolyear->semester->course;
			}
			else {
				pCur->pNext = new Course;
				pCur = pCur->pNext;
			}
			getline(in, pCur->courseName, ',');
			getline(in, pCur->courseID, ',');
			in >> credits;
			pCur->creditNum = credits;
			in >> c;
			getline(in, pCur->teacherName, ',');
			in >> numberOfStudents;
			pCur->numOfStudents = numberOfStudents;
			in >> c;
			getline(in, pCur->courseDate, ',');
			getline(in, pCur->courseSession, '\n');
			pCur->pNext = nullptr;
		}
		in.close();
	}
	else {
		cout << "\t\t\t\t\nERROR\n";
	}
}

void updateCourseInfo(SchoolYear*& schoolyear) {
	ifstream in;
	ofstream out;
	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(Blue);
	gotoXY(42, 8); cout << "UPDATE COURSE " << g_selectCourse;
	Textcolor(7);
	getDataCoursesInSemester(schoolyear);

	string courseName, courseID, teacherName, DoW, session1, session2, title;
	string courseName1, courseID1, teacherName1, DoW1, session1t, session2t;
	string path = g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv";
	int credit, NoS, credit1, NoS1;

	Course* pCur = schoolyear->semester->course;
	while (pCur && pCur->courseID != g_selectCourse)
		pCur = pCur->pNext;

	out.open(path, ios::app);
	if (numberOfLine(path) == 0) {
		out << title << endl;
	}
	out.close();

	gotoXY(30, 12); cout << "1. Course name: " << pCur->courseName;
	gotoXY(30, 14); cout << "2. Course ID: " << pCur->courseID;
	gotoXY(30, 16); cout << "3. Number of credits: " << pCur->creditNum;
	gotoXY(30, 18); cout << "4. Teacher in charge: " << pCur->teacherName;
	gotoXY(30, 20); cout << "5. Number of students: " << pCur->numOfStudents;
	gotoXY(30, 22); cout << "6. Day of the week: " << pCur->courseDate;
	gotoXY(30, 24); cout << "7. Session: " << pCur->courseSession;
	gotoXY(30, 26); cout << "8. Exit";
	gotoXY(30, 28); cout << char(26) << " Enter the section you want to update: ";
	char choice = getchar(), comma;
	cin.ignore(100, '\n');
	switch (choice) {
	case '1':
		gotoXY(70, 12); cout << char(26) << " Enter new course name: ";
		getline(cin, courseName1, '\n');
		in.open(path);
		if (in) {
			out.open("tempSemester.csv");
			getline(in, title, '\n');
			out << title << endl;
			for (int i = 1; i <= numberOfLine(path) - 1; i++) {
				getline(in, courseName, ',');
				if (courseName == pCur->courseName)
					out << courseName1 << ",";
				else out << courseName << ",";
				getline(in, courseID, ',');
				out << courseID << ",";
				in >> credit;
				in >> comma;
				out << credit << ",";
				getline(in, teacherName, ',');
				out << teacherName << ",";
				//Course name,Course ID,credits,teacher name,number of students,day,time
				in >> NoS;
				in >> comma;
				out << NoS << ",";
				getline(in, DoW, ',');
				out << DoW << ",";
				getline(in, session1, '\n');
				out << session1 << "\n";
			}
			out.close();
			in.close();
			remove(path.c_str());
			rename("tempSemester.csv", path.c_str());
		}
		else {
			cout << "\n\n\t\t\t\tCan not open file directory.";
		}
		cout << "\n\t\t\t\t      Course name has been changed successfully!\n";
		Sleep(2000);
		system("cls");
		updateCourseInfo(schoolyear);
		break;
	case '2':
		gotoXY(70, 14); cout << char(26) << " Enter new course ID: ";
		getline(cin, courseID1, '\n');
		in.open(path);
		if (in) {
			out.open("tempSemester.csv");
			getline(in, title, '\n');
			out << title << endl;
			for (int i = 1; i <= numberOfLine(path) - 1; i++) {
				getline(in, courseName, ',');
				out << courseName << ",";
				getline(in, courseID, ',');
				if (courseName == pCur->courseName)
					out << courseID1 << ",";
				else out << courseID << ",";
				in >> credit;
				in >> comma;
				out << credit << ",";
				getline(in, teacherName, ',');
				out << teacherName << ",";
				in >> NoS;
				in >> comma;
				out << NoS << ",";
				getline(in, DoW, ',');
				out << DoW << ",";
				getline(in, session1, '\n');
				out << session1 << "\n";
			}
			out.close();
			in.close();
			remove(path.c_str());
			rename("tempSemester.csv", path.c_str());
		}
		else {
			cout << "\n\n\t\t\t\tCan not open file directory.";
		}
		cout << "\n\t\t\t\t      Course ID has been changed successfully!\n";
		Sleep(2000);
		system("cls");
		updateCourseInfo(schoolyear);
		break;
	case '3':
		gotoXY(70, 16); cout << char(26) << " Enter new number of credits: ";
		cin >> credit1; cin.ignore();
		in.open(path);
		if (in) {
			out.open("tempSemester.csv");
			getline(in, title, '\n');
			out << title << endl;
			for (int i = 1; i <= numberOfLine(path) - 1; i++) {
				getline(in, courseName, ',');
				out << courseName << ",";
				getline(in, courseID, ',');
				out << courseID << ",";
				in >> credit;
				if (courseName == pCur->courseName)
					out << credit1 << ",";
				else out << credit << ",";
				in >> comma;
				getline(in, teacherName, ',');
				out << teacherName << ",";
				in >> NoS;
				in >> comma;
				out << NoS << ",";
				getline(in, DoW, ',');
				out << DoW << ",";
				getline(in, session1, '\n');
				out << session1 << "\n";
			}
			out.close();
			in.close();
			remove(path.c_str());
			rename("tempSemester.csv", path.c_str());
		}
		else {
			cout << "\n\n\t\t\t\tCan not open file directory.";
		}
		cout << "\n\t\t\t\t      Number of credits has been changed successfully!\n";
		Sleep(2000);
		system("cls");
		updateCourseInfo(schoolyear);
		break;
	case '4':
		gotoXY(70, 18); cout << char(26) << " Enter new teacher in charge's name: ";
		getline(cin, teacherName1, '\n');
		in.open(path);
		if (in) {
			out.open("tempSemester.csv");
			getline(in, title, '\n');
			out << title << endl;
			for (int i = 1; i <= numberOfLine(path) - 1; i++) {
				getline(in, courseName, ',');
				out << courseName << ",";
				getline(in, courseID, ',');
				out << courseID << ",";
				in >> credit;
				in >> comma;
				out << credit << ",";
				getline(in, teacherName, ',');
				if (courseName == pCur->courseName)
					out << teacherName1 << ",";
				else out << teacherName << ",";
				//Course name,Course ID,credits,teacher name,number of students,day,time
				in >> NoS;
				in >> comma;
				out << NoS << ",";
				getline(in, DoW, ',');
				out << DoW << ",";
				getline(in, session1, '\n');
				out << session1 << "\n";
			}
			out.close();
			in.close();
			remove(path.c_str());
			rename("tempSemester.csv", path.c_str());
		}
		else {
			cout << "\n\n\t\t\t\tCan not open file directory.";
		}
		cout << "\n\t\t\t\t      Teacher in charged's has been changed successfully!\n";
		Sleep(2000);
		system("cls");
		updateCourseInfo(schoolyear);
		break;
	case '5':
		gotoXY(70, 20); cout << char(26) << " Enter new number of students: ";
		cin >> NoS1; cin.ignore();
		in.open(path);
		if (in) {
			out.open("tempSemester.csv");
			getline(in, title, '\n');
			out << title << endl;
			for (int i = 1; i <= numberOfLine(path) - 1; i++) {
				getline(in, courseName, ',');
				out << courseName << ",";
				getline(in, courseID, ',');
				out << courseID << ",";
				in >> credit;
				in >> comma;
				out << credit << ",";
				getline(in, teacherName, ',');
				out << teacherName << ",";
				//Course name,Course ID,credits,teacher name,number of students,day,time
				in >> NoS;
				if (courseName == pCur->courseName)
					out << NoS1 << ",";
				else out << NoS << ",";
				in >> comma;
				getline(in, DoW, ',');
				out << DoW << ",";
				getline(in, session1, '\n');
				out << session1 << "\n";
			}
			out.close();
			in.close();
			remove(path.c_str());
			rename("tempSemester.csv", path.c_str());
		}
		else {
			cout << "\n\n\t\t\t\tCan not open file directory.";
		}
		cout << "\n\t\t\t      Number of students has been changed successfully!\n";
		Sleep(2000);
		system("cls");
		updateCourseInfo(schoolyear);
		break;
	case '6':
		gotoXY(30, 31); cout << "(If there are more than one day, separate with &, ex: TUE & WED)";
		gotoXY(30, 30); cout << "Enter new day of the week that the course will take place: ";
		getline(cin, DoW1, '\n');
		in.open(path);
		if (in) {
			out.open("tempSemester.csv");
			getline(in, title, '\n');
			out << title << endl;
			for (int i = 1; i <= numberOfLine(path) - 1; i++) {
				getline(in, courseName, ',');
				out << courseName << ",";
				getline(in, courseID, ',');
				out << courseID << ",";
				in >> credit;
				in >> comma;
				out << credit << ",";
				getline(in, teacherName, ',');
				out << teacherName << ",";
				in >> NoS;
				in >> comma;
				out << NoS << ",";
				getline(in, DoW, ',');
				if (courseName == pCur->courseName)
					out << DoW1 << ",";
				else out << DoW << ",";
				getline(in, session1, '\n');
				out << session1 << "\n";
			}
			out.close();
			in.close();
			remove(path.c_str());
			rename("tempSemester.csv", path.c_str());
		}
		else {
			cout << "\n\n\t\t\t\tCan not open file directory.";
		}
		cout << "\n\t\t\t\t      New schedule has been changed successfully!\n";
		Sleep(2000);
		system("cls");
		updateCourseInfo(schoolyear);
		break;
	case '7':
		gotoXY(70, 30); cout << "There are 4 sessions available";
		gotoXY(80, 31); cout << "07:30"; gotoXY(89, 31); cout << "09:30";
		gotoXY(80, 32); cout << "13:30"; gotoXY(89, 32); cout << "15:30";
		gotoXY(30, 30); cout << "Enter new session 1: ";
		getline(cin, session1t, '\n');
		gotoXY(30, 32); cout << "Enter new session 2: ";
		getline(cin, session2t, '\n');
		in.open(path);
		if (in) {
			out.open("tempSemester.csv");
			getline(in, title, '\n');
			out << title << endl;
			for (int i = 1; i <= numberOfLine(path) - 1; i++) {
				getline(in, courseName, ',');
				out << courseName << ",";
				getline(in, courseID, ',');
				out << courseID << ",";
				in >> credit;
				in >> comma;
				out << credit << ",";
				getline(in, teacherName, ',');
				out << teacherName << ",";
				in >> NoS;
				in >> comma;
				out << NoS << ",";
				getline(in, DoW, ',');
				out << DoW << ",";
				getline(in, session1, '\n');
				if (courseName == pCur->courseName)
					out << session1t << " & " << session2t << "\n";
				else out << session1 << "\n";
			}
			out.close();
			in.close();
			remove(path.c_str());
			rename("tempSemester.csv", path.c_str());
		}
		else {
			cout << "\n\n\t\t\t\tCan not open file directory.";
		}
		cout << "\n\t\t\t\t      New session has been changed successfully!\n";
		Sleep(2000);
		system("cls");
		updateCourseInfo(schoolyear);
		break;
	case '8':
		Sleep(1000);
		system("cls");
		displayCourseInSemester(schoolyear);
		break;
	default:
		gotoXY(30, 30); cout << "Invalid input";
		gotoXY(30, 32); cout << "Try again in 2...";
		Sleep(1000);
		gotoXY(30, 32); cout << "Try again in 1...";
		Sleep(1000);
		system("cls");
		updateCourseInfo(schoolyear);
		break;
	}


	out.open(path, ios::app);
	if (out) {
		out << courseName << ",";
		out << courseID << ",";
		out << credit << ",";
		out << teacherName << ",";
		out << NoS << ",";
		out << DoW << ",";
		out << session1 + " & " + session2 << "\n";
		out.close();
		cout << "\n\t\t\t      Course has been added successfully!";
	}
	else cout << "\n\t\t\t      Unable to open file " << path;
}

void displayCourseInSemester(SchoolYear*& schoolyear) {
	setConsoleWindow(1000, 600);
	ofstream out;
	ifstream in;
	int y = 16, No = 0, check = 1;

	string title = { "Course name,Course ID,credits,teacher name,"
	"number of students,day,time" };

	string path = g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv";

	out.open(path, ios::app);
	if (numberOfLine(path) == 0) {
		out << title << endl;
	}
	out.close();

	getDataCoursesInSemester(schoolyear);
	Semester* tempSemester = schoolyear->semester;
	while (tempSemester && tempSemester->no != g_selectSemester)
		tempSemester = tempSemester->pNext;

	Course* pCurCase2 = schoolyear->semester->course;
	Course* pCurCase3 = schoolyear->semester->course;
	Course* tempCourse = tempSemester->course; // Will be used to add course later;

	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "==========================================================================================";
	Textcolor(Blue);
	gotoXY(63, 8); cout << "SEMESTER " << g_selectSemester;
	gotoXY(56, 9); cout << "(" << add0(tempSemester->start_date) << " -- " << add0(tempSemester->end_date) << ")";
	Textcolor(7);

	gotoXY(05, 12); cout << "Course name";
	gotoXY(45, 12); cout << "Course ID"; //25
	gotoXY(57, 12); cout << "Credits";  // 12
	gotoXY(67, 12); cout << "Teacher"; // 10
	gotoXY(85, 12); cout << "NoS"; // 18
	gotoXY(91, 12); cout << "Day"; // 6
	gotoXY(103, 12); cout << "Session"; // 12

	gotoXY(02, 14); cout << "===================================================="
		"=========================================================================";

	if (numberOfLine(path) == 1) {
		gotoXY(05, 16); cout << "N/A";
		gotoXY(45, 16); cout << "N/A";
		gotoXY(57, 16); cout << "N/A";
		gotoXY(67, 16); cout << "N/A";
		gotoXY(85, 16); cout << "N/A";
		gotoXY(91, 16); cout << "N/A";
		gotoXY(103, 16); cout << "N/A";
	}
	else {
		while (tempSemester->course) {
			gotoXY(05, y); cout << tempSemester->course->courseName;
			gotoXY(45, y); cout << tempSemester->course->courseID;
			gotoXY(57, y); cout << tempSemester->course->creditNum;
			gotoXY(67, y); cout << tempSemester->course->teacherName;
			gotoXY(85, y); cout << tempSemester->course->numOfStudents;
			gotoXY(91, y); cout << tempSemester->course->courseDate;
			gotoXY(103, y); cout << tempSemester->course->courseSession;
			y++; No++;
			tempSemester->course = tempSemester->course->pNext;
		}
	}

	string courseName, courseID, teacherName, DoW, session1, session2;
	string credit, NoS;


	gotoXY(45, y + 4); cout << "1. Add course";
	gotoXY(45, y + 5); cout << "2. Update course information";
	gotoXY(45, y + 6); cout << "3. Delete course";
	gotoXY(45, y + 7); cout << "4. Exit";
	gotoXY(45, y + 8); cout << "Enter your choice: ";
	char choice = getchar();
	cin.ignore(100, '\n');
	switch (choice) {
	case '1':
		// Add course;
		system("cls");
		setConsoleWindow(800, 600);
		if (g_Time != "") {
			gotoXY(26, 4); cout << "Date: " << g_Time;
		}
		gotoXY(26, 5); cout << "=======================================================";
		Textcolor(Blue);
		gotoXY(48, 8); cout << "SEMESTER " << g_selectSemester;
		gotoXY(41, 9); cout << "(" << add0(tempSemester->start_date) << " -- " << add0(tempSemester->end_date) << ")";
		gotoXY(46, 10); cout << "ADDING  COURSE";
		Textcolor(7);

		tempSemester->course = new Course;

		gotoXY(30, 12); cout << "Course name: ";
		getline(cin, courseName, '\n');
		gotoXY(30, 14); cout << "Course ID: ";
		getline(cin, courseID, '\n');

		while (tempCourse && (tempCourse->courseName != courseName
			&& tempCourse->courseID != courseID))
			tempCourse = tempCourse->pNext;

		if (tempCourse) {
			gotoXY(30, 16); cout << "This course has already existed!";
			Sleep(2000);
			system("cls");
			displayCourseInSemester(schoolyear);
			return;
		}

		gotoXY(30, 16); cout << "Number of credits: ";
		getline(cin, credit, '\n');
		gotoXY(30, 18); cout << "Teacher in charge: ";
		getline(cin, teacherName, '\n');
		gotoXY(30, 20); cout << "Number of students: ";
		getline(cin, NoS, '\n');
		gotoXY(30, 23); cout << "(If there is more than one day, separate with &, ex: TUE & WED)";
		gotoXY(30, 22); cout << "Day of the week: ";
		getline(cin, DoW, '\n');
		gotoXY(70, 25); cout << "There are 4 sessions available";
		gotoXY(80, 26); cout << "07:30"; gotoXY(89, 26); cout << "09:30";
		gotoXY(80, 27); cout << "13:30"; gotoXY(89, 27); cout << "15:30";
		gotoXY(30, 25); cout << "First session: ";
		getline(cin, session1, '\n');
		cout << endl;
		while (session1 != "7:30" && session1 != "07:30" &&
			session1 != "9:30" && session1 != "09:30" &&
			session1 != "13:30" && session1 != "15:30") {
			cout << "\t\t\t      Invalid input, try again: ";
			getline(cin, session1, '\n');
		}
		cout << "\n\t\t\t      Second session: ";
		getline(cin, session2, '\n');
		cout << endl;
		while (session2 != "7:30" && session2 != "07:30" &&
			session2 != "9:30" && session2 != "09:30" &&
			session2 != "13:30" && session2 != "15:30") {
			cout << "\t\t\t      Invalid input, try again: ";
			getline(cin, session2, '\n');
		}

		out.open(path, ios::app);
		if (out) {
			out << courseName << ",";
			out << courseID << ",";
			out << stoi(credit) << ",";
			out << teacherName << ",";
			out << stoi(NoS) << ",";
			out << DoW << ",";
			out << session1 + " & " + session2 << "\n";
			out.close();
			cout << "\n\t\t\t      Course has been added successfully!";
		}
		else cout << "\n\t\t\t      Unable to open file " << path;
		Sleep(2500);
		system("cls");
		displayCourseInSemester(schoolyear);
		break;
	case '2':
		// Update course info;

		gotoXY(45, y + 11); cout << "Enter course ID: ";
		getline(cin, courseID, '\n');
		while (pCurCase2 && pCurCase2->courseID != courseID) {
			pCurCase2 = pCurCase2->pNext;
		}
		if (!pCurCase2) {
			gotoXY(45, y + 12); cout << "Course ID " << courseID << " doesn't exist.";
			Sleep(2000);
			system("cls");
			displayCourseInSemester(schoolyear);
		}
		else {
			g_selectCourse = courseID;
			system("cls");
			setConsoleWindow(800, 600);
			updateCourseInfo(schoolyear);
		}
		break;
	case '3':
		// Delete course;
		gotoXY(45, y + 11); cout << "Enter course ID: ";
		getline(cin, courseID, '\n');
		while (pCurCase2 && pCurCase2->courseID != courseID) {
			pCurCase2 = pCurCase2->pNext;
		}
		if (!pCurCase2) {
			gotoXY(45, y + 12); cout << "Course ID " << courseID << " doesn't exist.";
		}
		else {
			g_selectCourse = courseID;
			deleteCourse(schoolyear);
			gotoXY(45, y + 13); cout << "Delete course " << courseID << " successfully!";
		}
		Sleep(2000);
		system("cls");
		displayCourseInSemester(schoolyear);
		break;
	case '4':
		system("cls");
		setConsoleWindow(800, 600);
		displaySemester(schoolyear->staff, schoolyear->student, schoolyear);
		break;
	default:
		system("cls");
		displayCourseInSemester(schoolyear);
		break;
	}
}

void displayCourseWhenDayExceed(SchoolYear*& schoolyear) {
	setConsoleWindow(1000, 600);
	ofstream out;
	ifstream in;
	int y = 16, No = 0, check = 1;

	string title = { "Course name,Course ID,credits,teacher name,"
	"number of students,day,time" };

	string path = g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv";

	out.open(path, ios::app);
	if (numberOfLine(path) == 0) {
		out << title << endl;
	}
	out.close();
	getDataCoursesInSemester(schoolyear);
	Semester* tempSemester = schoolyear->semester;
	while (tempSemester && tempSemester->no != g_selectSemester)
		tempSemester = tempSemester->pNext;

	Course* pCur4 = tempSemester->course;
	Course* tempCourse = tempSemester->course, * curCase1 = tempSemester->course; // Will be used to add course later;
	Course* curCase2 = tempSemester->course, * curCase3 = tempSemester->course, * curCase4 = tempSemester->course;

	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "==========================================================================================";
	Textcolor(Blue);
	gotoXY(63, 8); cout << "SEMESTER " << g_selectSemester;
	gotoXY(56, 9); cout << "(" << add0(tempSemester->start_date) << " -- " << add0(tempSemester->end_date) << ")";
	Textcolor(7);

	gotoXY(05, 12); cout << "Course name";
	gotoXY(45, 12); cout << "Course ID"; //25
	gotoXY(57, 12); cout << "Credits";  // 12
	gotoXY(67, 12); cout << "Teacher"; // 10
	gotoXY(85, 12); cout << "NoS"; // 18
	gotoXY(91, 12); cout << "Day"; // 6
	gotoXY(103, 12); cout << "Session"; // 12

	gotoXY(02, 14); cout << "===================================================="
		"=========================================================================";

	if (numberOfLine(path) == 1) {
		gotoXY(05, 16); cout << "N/A";
		gotoXY(45, 16); cout << "N/A";
		gotoXY(57, 16); cout << "N/A";
		gotoXY(67, 16); cout << "N/A";
		gotoXY(85, 16); cout << "N/A";
		gotoXY(91, 16); cout << "N/A";
		gotoXY(103, 16); cout << "N/A";
	}
	else {
		while (tempSemester->course) {
			gotoXY(05, y); cout << tempSemester->course->courseName;
			gotoXY(45, y); cout << tempSemester->course->courseID;
			gotoXY(57, y); cout << tempSemester->course->creditNum;
			gotoXY(67, y); cout << tempSemester->course->teacherName;
			gotoXY(85, y); cout << tempSemester->course->numOfStudents;
			gotoXY(91, y); cout << tempSemester->course->courseDate;
			gotoXY(103, y); cout << tempSemester->course->courseSession;
			y++; No++;
			tempSemester->course = tempSemester->course->pNext;
		}
	}

	gotoXY(45, y + 4); cout << "1. Export list of student into a csv file";
	gotoXY(45, y + 5); cout << "2. Import scoreboard";
	gotoXY(45, y + 6); cout << "3. View scoreboard";
	gotoXY(45, y + 7); cout << "4. Update a student result";
	gotoXY(45, y + 8); cout << "5. Exit";
	gotoXY(45, y + 9); cout << char(26) << " Enter your choice: ";
	char choice = getchar();
	string courseID;
	cin.ignore(100, '\n');
	switch (choice) {
	case '1': // Sonw
		gotoXY(95, y + 4); cout << char(26) << " Enter course ID: ";
		getline(cin, courseID, '\n');
		g_selectCourse = courseID;
		while (curCase1 && curCase1->courseID != courseID) {
			curCase1 = curCase1->pNext;
		}
		if (!curCase1) {
			gotoXY(95, y + 4); cout << "Course ID " << courseID << " doesn't exist.";
			Sleep(2000);
			system("cls");
			displayCourseWhenDayExceed(schoolyear);
		}
		else {
			g_selectCourse = courseID;
			system("cls");
			setConsoleWindow(800, 600);
			exportListStudentInCourse(schoolyear);
		}
		cout << "\n\n\t\t\t\tPress any key to exit \n";
		_getch();
		system("cls");
		displayCourseWhenDayExceed(schoolyear);
		break;
	case '2': // Mountain
		gotoXY(70, y + 5); cout << char(26) << " Enter course ID: ";
		getline(cin, courseID, '\n');
		while (curCase2 && curCase2->courseID != courseID) {
			curCase2 = curCase2->pNext;
		}
		if (!curCase2) {
			gotoXY(70, y + 5); cout << "Course ID " << courseID << " doesn't exist.";
			Sleep(2000);
			system("cls");
			displayCourseWhenDayExceed(schoolyear);
		}
		else {
			g_selectCourse = courseID;
			system("cls");
			setConsoleWindow(800, 600);
			importScoreboard(schoolyear);
		}
		system("cls");
		displayCourseWhenDayExceed(schoolyear);
		break;
	case '3': // Som
		gotoXY(70, y + 6); cout << char(26) << " Enter course ID: ";
		getline(cin, courseID, '\n');
		while (curCase3 && curCase3->courseID != courseID) {
			curCase3 = curCase3->pNext;
		}
		if (!curCase3) {
			gotoXY(70, y + 6); cout << "Course ID " << courseID << " doesn't exist.";
			Sleep(2000);
			system("cls");
			displayCourseWhenDayExceed(schoolyear);
		}
		else {
			g_selectCourse = courseID;
			system("cls");
			viewScore(schoolyear);
		}
		cout << "\n\n\t\t\t\t\t\tPress any key to exit \n";
		_getch();
		system("cls");
		setConsoleWindow(800, 600);
		displayCourseWhenDayExceed(schoolyear);
		break;
	case '4': // Khang
		gotoXY(80, y + 7); cout << char(26) << " Enter course ID: ";
		getline(cin, courseID);
		while (curCase4 && curCase4->courseID != courseID) {
			curCase4 = curCase4->pNext;
		}
		if (!curCase4) {
			gotoXY(80, y + 4); cout << "Course ID " << courseID << " doesn't exist.";
			Sleep(2000);
			system("cls");
			displayCourseWhenDayExceed(schoolyear);
		}
		else {
			g_selectCourse = courseID;
			system("cls");
			setConsoleWindow(800, 600);
			updateStudentResult(schoolyear);
		}
		cout << "\n\n\t\t\t\tPress any key to exit \n";
		_getch();
		system("cls");
		displayCourseWhenDayExceed(schoolyear);
		break;
	case '5':
		system("cls");
		displaySemester(schoolyear->staff, schoolyear->student, schoolyear);
		break;
	default:
		gotoXY(31, y + 11); cout << "Try again in 2...";
		Sleep(1000);
		gotoXY(31, y + 11); cout << "Try again in 1...";
		Sleep(1000);
		system("cls");
		displaySemester(schoolyear->staff, schoolyear->student, schoolyear);
		break;
	}

}

void displayCourseForStudent(SchoolYear*& schoolyear) {
	setConsoleWindow(1000, 600);
	ofstream out;
	ifstream in;
	int y = 18, No = 0, check = 1;

	string title = { "Course name,Course ID,credits,teacher name,"
	"number of students,day,time" };

	string path = g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv";

	out.open(path, ios::app);
	if (numberOfLine(path) == 0) {
		out << title << endl;
	}
	out.close();
	getDataCoursesInSemester(schoolyear);
	Semester* tempSemester = schoolyear->semester;
	while (tempSemester && tempSemester->no != g_selectSemester)
		tempSemester = tempSemester->pNext;

	Course* tempCourse = tempSemester->course, * courseCase2 = tempSemester->course; // Will be used to add course later;

	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "==========================================================================================";
	Textcolor(Blue);
	gotoXY(63, 8); cout << "SEMESTER " << g_selectSemester;
	gotoXY(56, 9); cout << "(" << add0(tempSemester->start_date) << " -- " << add0(tempSemester->end_date) << ")";
	Textcolor(7);

	gotoXY(05, 12); cout << "ALL COURSE AVAILABLE IN SEMESTER " << g_selectSemester << ":";

	gotoXY(05, 14); cout << "Course name";
	gotoXY(45, 14); cout << "Course ID"; //25
	gotoXY(57, 14); cout << "Credits";  // 12
	gotoXY(67, 14); cout << "Teacher"; // 10
	gotoXY(85, 14); cout << "NoS"; // 18
	gotoXY(91, 14); cout << "Day"; // 6
	gotoXY(103, 14); cout << "Session"; // 12

	gotoXY(02, 16); cout << "===================================================="
		"=========================================================================";

	if (numberOfLine(path) == 1) {
		gotoXY(05, 18); cout << "N/A";
		gotoXY(45, 18); cout << "N/A";
		gotoXY(57, 18); cout << "N/A";
		gotoXY(67, 18); cout << "N/A";
		gotoXY(85, 18); cout << "N/A";
		gotoXY(91, 18); cout << "N/A";
		gotoXY(103, 18); cout << "N/A";
	}
	else {
		while (tempSemester->course) {
			gotoXY(05, y); cout << tempSemester->course->courseName;
			gotoXY(45, y); cout << tempSemester->course->courseID;
			gotoXY(57, y); cout << tempSemester->course->creditNum;
			gotoXY(67, y); cout << tempSemester->course->teacherName;
			gotoXY(85, y); cout << tempSemester->course->numOfStudents;
			gotoXY(91, y); cout << tempSemester->course->courseDate;
			gotoXY(103, y); cout << tempSemester->course->courseSession;
			y++; No++;
			tempSemester->course = tempSemester->course->pNext;
		}
	}

	gotoXY(45, y + 4); cout << "1. Enroll";
	gotoXY(45, y + 5); cout << "2. View list Course";
	gotoXY(45, y + 6); cout << "3. Remove course";
	gotoXY(45, y + 7); cout << "4. Exit";
	gotoXY(45, y + 8); cout << char(26) << " Enter your choice: ";
	char choice = getchar();
	string courseID;
	//int studentID;
	cin.ignore(100, '\n');
	switch (choice) {
	case '1': // Sonw
		gotoXY(75, y + 4); cout << char(26) << " Enter course ID: ";
		getline(cin, courseID, '\n');
		g_selectCourse = courseID;
		enroll();
		cout << "\n\n\t\t\t\t             Press any key to return...";
		_getch();
		system("cls");
		displayCourseForStudent(schoolyear);
		break;
	case '2': // Mountain
		system("cls");

		if (g_Time != "") {
			gotoXY(26, 4); cout << "Date: " << g_Time;
		}
		gotoXY(26, 5); cout << "==========================================================================================";
		Textcolor(Blue);
		gotoXY(63, 8); cout << "SEMESTER " << g_selectSemester;
		gotoXY(56, 9); cout << "(" << add0(tempSemester->start_date) << " -- " << add0(tempSemester->end_date) << ")";

		Textcolor(7);
		gotoXY(05, 10); cout << "YOUR COURSES: ";
		gotoXY(05, 12); cout << "Course name";
		gotoXY(45, 12); cout << "Course ID"; //25
		gotoXY(57, 12); cout << "Credits";  // 12
		gotoXY(67, 12); cout << "Teacher"; // 10
		gotoXY(85, 12); cout << "NoS"; // 18
		gotoXY(91, 12); cout << "Day"; // 6
		gotoXY(103, 12); cout << "Session"; // 12

		gotoXY(02, 14); cout << "===================================================="
			"=========================================================================";
		viewCourseEnrolled();
		cout << "\n\n\t\t\t\t             Press any key to return...";
		_getch();
		system("cls");
		displayCourseForStudent(schoolyear);
		break;
	case '3': // Som
		system("cls");
		if (g_Time != "") {
			gotoXY(26, 4); cout << "Date: " << g_Time;
		}
		gotoXY(26, 5); cout << "==========================================================================================";
		Textcolor(Blue);
		gotoXY(63, 8); cout << "SEMESTER " << g_selectSemester;
		gotoXY(56, 9); cout << "(" << add0(tempSemester->start_date) << " -- " << add0(tempSemester->end_date) << ")";
		Textcolor(7);

		gotoXY(05, 12); cout << "Course name";
		gotoXY(45, 12); cout << "Course ID"; //25
		gotoXY(57, 12); cout << "Credits";  // 12
		gotoXY(67, 12); cout << "Teacher"; // 10
		gotoXY(85, 12); cout << "NoS"; // 18
		gotoXY(91, 12); cout << "Day"; // 6
		gotoXY(103, 12); cout << "Session"; // 12

		gotoXY(02, 14); cout << "===================================================="
			"=========================================================================";
		viewCourseEnrolled();
		gotoXY(45, y + 6); cout << char(26) << " Enter course ID you want to remove: ";
		getline(cin, courseID, '\n');
		g_selectCourse = courseID;
		removeEnrolled();
		cout << "\n\n\t\t\t\t             Press any key to return...";
		_getch();
		system("cls");
		displayCourseForStudent(schoolyear);
		break;
	case '4':
		system("cls");
		displaySemesterForStudent(schoolyear->staff, schoolyear->student, schoolyear);
		break;
	default:
		gotoXY(31, y + 11); cout << "Try again in 2...";
		Sleep(1000);
		gotoXY(31, y + 11); cout << "Try again in 1...";
		Sleep(1000);
		system("cls");
		displaySemesterForStudent(schoolyear->staff, schoolyear->student, schoolyear);
		break;
	}

}

void displayCoursesStudentsExceed(SchoolYear* schoolyear) {
	setConsoleWindow(1000, 600);
	ofstream out;
	ifstream in;
	int y = 16, No = 0, check = 1;

	string title = { "Course name,Course ID,credits,teacher name,"
	"number of students,day,time" };

	string path = g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv";

	out.open(path, ios::app);
	if (numberOfLine(path) == 0) {
		out << title << endl;
	}
	out.close();
	getDataClass(schoolyear);
	SchoolYear* pCur = schoolyear;
	while (pCur && pCur->year != g_selectyear)
		pCur = pCur->pNext;
	getDataCoursesInSemester(schoolyear);
	Semester* tempSemester = schoolyear->semester;
	Class* tempClass = pCur->classes;
	while (tempSemester && tempSemester->no != g_selectSemester)
		tempSemester = tempSemester->pNext;

	Course* tempCourse = tempSemester->course, * tempCourse2 = tempSemester->course; // Will be used to add course later;
	string pathCase2, str;

	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "==========================================================================================";
	Textcolor(Blue);
	gotoXY(63, 8); cout << "SEMESTER " << g_selectSemester;
	gotoXY(56, 9); cout << "(" << add0(tempSemester->start_date) << " -- " << add0(tempSemester->end_date) << ")";
	Textcolor(7);

	gotoXY(05, 12); cout << "Course name";
	gotoXY(45, 12); cout << "Course ID"; //25
	gotoXY(57, 12); cout << "Credits";  // 12
	gotoXY(67, 12); cout << "Teacher"; // 10
	gotoXY(85, 12); cout << "NoS"; // 18
	gotoXY(91, 12); cout << "Day"; // 6
	gotoXY(103, 12); cout << "Session"; // 12

	gotoXY(02, 14); cout << "===================================================="
		"=========================================================================";

	if (numberOfLine(path) == 1) {
		gotoXY(05, 16); cout << "N/A";
		gotoXY(45, 16); cout << "N/A";
		gotoXY(57, 16); cout << "N/A";
		gotoXY(67, 16); cout << "N/A";
		gotoXY(85, 16); cout << "N/A";
		gotoXY(91, 16); cout << "N/A";
		gotoXY(103, 16); cout << "N/A";
	}
	else {
		while (tempSemester->course) {
			gotoXY(05, y); cout << tempSemester->course->courseName;
			gotoXY(45, y); cout << tempSemester->course->courseID;
			gotoXY(57, y); cout << tempSemester->course->creditNum;
			gotoXY(67, y); cout << tempSemester->course->teacherName;
			gotoXY(85, y); cout << tempSemester->course->numOfStudents;
			gotoXY(91, y); cout << tempSemester->course->courseDate;
			gotoXY(103, y); cout << tempSemester->course->courseSession;
			y++; No++;
			tempSemester->course = tempSemester->course->pNext;
		}
	}
	++y;
	gotoXY(05, ++y); cout << "Class list: ";
	if (tempClass) {
		gotoXY(18, y); cout << tempClass->className;
		tempClass = tempClass->pNext;
	}
	while (tempClass) {
		gotoXY(18, ++y); cout << tempClass->className;
		tempClass = tempClass->pNext;
	}

	gotoXY(45, y + 4); cout << "1. Your courses and marks";
	gotoXY(45, y + 5); cout << "2. View students in a certain course";
	gotoXY(45, y + 6); cout << "3. Exit";
	gotoXY(45, y + 7); cout << char(26) << " Enter your choice: ";
	char choice = getchar();
	string courseID;
	cin.ignore(100, '\n');
	switch (choice) {
	case '1':
		getDataCourseScore(schoolyear, schoolyear->student);
		displayCoursesStudentsExceed(schoolyear);
		break;
	case '2': // Khang
		gotoXY(45, y + 9); cout << "Enter course ID: ";
		getline(cin, courseID, '\n');
		while (tempCourse2 && tempCourse2->courseID != courseID)
			tempCourse2 = tempCourse2->pNext;

		if (!tempCourse2) {
			gotoXY(45, y + 10); cout << "Course ID " << courseID << " doesn't exist.";
			Sleep(2000);
			system("cls");
			displayCoursesStudentsExceed(schoolyear);
		}
		else {
			g_selectCourse = courseID;
			pathCase2 = g_selectyear + "_Semester" + to_string(g_selectSemester) +
				"_Course_" + courseID + "_student.csv";
			gotoXY(45, y + 10); cout << "Entering " << courseID << "...";
			Sleep(2000);
			system("cls");
			setConsoleWindow(800, 600);

			if (g_Time != "") {
				gotoXY(21, 4); cout << "Date: " << g_Time;
			}
			gotoXY(21, 5); cout << "==================================================================";
			Textcolor(Blue);
			gotoXY(47, 8); cout << "SEMESTER " << g_selectSemester;
			gotoXY(40, 9); cout << "(" << add0(tempSemester->start_date) << " -- " << add0(tempSemester->end_date) << ")";
			if (tempCourse2) {
				gotoXY(33, 10); cout << "COURSE: " << tempCourse2->courseName;
			}
			Textcolor(7);

			gotoXY(8, 14); cout << "No";
			gotoXY(13, 14); cout << "Student ID";
			gotoXY(27, 14); cout << "First name";
			gotoXY(41, 14); cout << "Last name";
			gotoXY(54, 14); cout << "Gender";
			gotoXY(64, 14); cout << "Date of birth";
			gotoXY(81, 14); cout << "Class";

			gotoXY(05, 16); cout << "============================================================="
				"=============================";

			y = 18, No = 1;

			in.open(pathCase2);
			if (!in.is_open()) {
				gotoXY(8, y); cout << "N/A";
				gotoXY(13, y); cout << "N/A";
				gotoXY(27, y); cout << "N/A";
				gotoXY(41, y); cout << "N/A";
				gotoXY(54, y); cout << "N/A";
				gotoXY(64, y); cout << "N/A";
				gotoXY(81, y); cout << "N/A";
				gotoXY(35, y + 4);  cout << "Press any key to exit...";
				_getch();
				system("cls");
				displayCoursesStudentsExceed(schoolyear);
				break;
			}
			else in.close();

			if (numberOfLine(pathCase2) < 2) {
				gotoXY(8, y); cout << "N/A";
				gotoXY(13, y); cout << "N/A";
				gotoXY(27, y); cout << "N/A";
				gotoXY(41, y); cout << "N/A";
				gotoXY(54, y); cout << "N/A";
				gotoXY(64, y); cout << "N/A";
				gotoXY(81, y); cout << "N/A";
			}
			else {
				in.open(pathCase2);
				if (in.is_open()) {
					getline(in, str, '\n');
					for (int i = 0; i < numberOfLine(pathCase2) - 1; ++i) {
						getline(in, str, ',');
						gotoXY(8, y); cout << No;
						gotoXY(13, y); cout << str; //id
						getline(in, str, ',');
						gotoXY(27, y); cout << str; //first name
						getline(in, str, ',');
						gotoXY(41, y); cout << str; //last name
						getline(in, str, ',');
						gotoXY(54, y); cout << str; //gender
						getline(in, str, ',');
						gotoXY(64, y); cout << str; //dob
						getline(in, str, ',');
						gotoXY(81, y); cout << str; //class
						getline(in, str, ',');
						getline(in, str, '\n');
						y++; No++;
					}
				}
				else cout << "\n\n\t\t\t\tCan not open file directory.";
			}
			gotoXY(35, y + 4);  cout << "Press any key to exit...";
			_getch();
			system("cls");
			displayCoursesStudentsExceed(schoolyear);
		}
		break;
	case '3':
		system("cls");
		displaySemesterForStudent(schoolyear->staff, schoolyear->student, schoolyear);
		break;
	default:
		gotoXY(31, y + 11); cout << "Try again in 2...";
		Sleep(1000);
		gotoXY(31, y + 11); cout << "Try again in 1...";
		Sleep(1000);
		system("cls");
		displayCoursesStudentsExceed(schoolyear);
		break;
	}
}

void viewCourseEnrolled() {
	ifstream in;
	ofstream out;
	string path = to_string(g_ID) + "_Semester" + to_string(g_selectSemester) + "_Course.csv";
	out.open(path, ios::app);
	if (numberOfLine(path) == 0) {
		out << "Course name, Course ID, credits, teacher name, number of students, day, time\n";
	}
	out.close();

	int y = 16, No = 1;

	if (numberOfLine(path) == 1) {
		gotoXY(05, 16); cout << "N/A";
		gotoXY(45, 16); cout << "N/A";
		gotoXY(57, 16); cout << "N/A";
		gotoXY(67, 16); cout << "N/A";
		gotoXY(85, 16); cout << "N/A";
		gotoXY(91, 16); cout << "N/A";
		gotoXY(103, 16); cout << "N/A";
	}
	else {
		in.open(path);
		string str;
		getline(in, str);
		for (int i = 1; i <= numberOfLine(to_string(g_ID) + "_Semester" + to_string(g_selectSemester) + "_Course.csv") - 1; i++) {
			getline(in, str, ',');
			gotoXY(05, y); cout << str; //name;
			getline(in, str, ',');
			gotoXY(45, y); cout << str; //id
			getline(in, str, ',');
			gotoXY(57, y); cout << str; //credit
			getline(in, str, ',');
			gotoXY(67, y); cout << str; //teacher
			getline(in, str, ',');
			gotoXY(85, y); cout << str; //numStudent
			getline(in, str, ',');
			gotoXY(91, y); cout << str; //Date
			getline(in, str, '\n');
			gotoXY(103, y); cout << str; //Session
			y++; No++;
		}
		in.close();
	}
}

void removeEnrolled() {
	ifstream in;
	ofstream out;
	in.open(to_string(g_ID) + "_Semester" + to_string(g_selectSemester) + "_Course.csv");
	out.open("tempenr.csv");
	string str;
	bool checkCourse = false;
	getline(in, str);
	out << str << endl;
	string s;
	for (int i = 1; i <= numberOfLine(to_string(g_ID) + "_Semester" + to_string(g_selectSemester) + "_Course.csv") - 1; i++) {
		getline(in, str, ',');
		s = str;
		getline(in, str, ',');
		if (str != g_selectCourse) {
			out << s << ",";
			out << str << ",";
			getline(in, str, ',');
			out << str << ",";
			getline(in, str, ',');
			out << str << ",";
			getline(in, str, ',');
			out << str << ",";
			getline(in, str, ',');
			out << str << ",";
			getline(in, str, '\n');
			out << str << "\n";
		}
		else {
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, '\n');
			checkCourse = true;
		}
	}

	out.close();
	in.close();
	remove((to_string(g_ID) + "_Semester" + to_string(g_selectSemester) + "_Course.csv").c_str());
	rename("tempenr.csv", (to_string(g_ID) + "_Semester" + to_string(g_selectSemester) + "_Course.csv").c_str());

	if (!checkCourse) {
		cout << "\n\n\t\t\t\t             Course " << g_selectCourse << " is not enrolled yet..";
		return;
	}

	in.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_student.csv");
	out.open("tempenr.csv");
	getline(in, str);
	out << str << endl;
	for (int i = 1; i <= numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_student.csv") - 1; i++) {
		getline(in, str, ',');
		if (str != to_string(g_ID)) {
			out << str << ",";
			getline(in, str, ',');
			out << str << ",";
			getline(in, str, ',');
			out << str << ",";
			getline(in, str, ',');
			out << str << ",";
			getline(in, str, ',');
			out << str << ",";
			getline(in, str, ',');
			out << str << ",";
			getline(in, str, ',');
			out << str << ",";
			getline(in, str, '\n');
			out << str << "\n";
		}
		else {
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, '\n');
		}
	}
	out.close();
	in.close();
	remove((g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_student.csv").c_str());
	rename("tempenr.csv", (g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_student.csv").c_str());
	cout << "\n\n\t\t\t\t             Unenroll " << g_selectCourse << " successfully!"; Sleep(2000);
}

void deleteCourse(SchoolYear*& schoolyear) {
	getDataCoursesInSemester(schoolyear);
	Course* temp = schoolyear->semester->course, * cur = temp, * cur2 = temp;
	while (temp && temp->courseID != g_selectCourse) {
		cur = temp;
		temp = temp->pNext;
	}

	if (temp) {
		cur->pNext = temp->pNext;
		delete temp;
	}

	string path = g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv";
	string courseName, courseID, teacherName, DoW, session1, session2, title;
	char comma;
	int credit, NoS;
	ifstream in;
	ofstream out;
	in.open(path);
	if (in) {
		out.open("tempSemester.csv");
		getline(in, title, '\n');
		out << title << endl;
		while (cur2) {
			getline(in, courseName, ',');
			out << cur2->courseName << ",";
			getline(in, courseID, ',');
			out << cur2->courseID << ",";
			in >> credit;
			in >> comma;
			out << cur2->creditNum << ",";
			getline(in, teacherName, ',');
			out << cur2->teacherName << ",";
			//Course name,Course ID,credits,teacher name,number of students,day,time
			in >> NoS;
			in >> comma;
			out << cur2->numOfStudents << ",";
			getline(in, DoW, ',');
			out << cur2->courseDate << ",";
			getline(in, session1, '\n');
			out << cur2->courseSession << "\n";
			cur2 = cur2->pNext;
		}
		out.close();
		in.close();
		remove(path.c_str());
		rename("tempSemester.csv", path.c_str());
	}
	else {
		cout << "\n\n\t\t\tCan not open file directory.";
	}
}