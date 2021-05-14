#pragma once
#include "_Class.h"
#include "Console.h"

extern string g_account;
extern int g_ID;
extern string g_selectyear;
extern int g_selectSemester;
extern string g_selectClass;
extern string g_selectCourse;
extern string g_Time;

void getDataStudentinClass(SchoolYear*& schoolyear) {
	ifstream in;
	SchoolYear* pCur1 = schoolyear;
	while (pCur1->classes && pCur1->classes->className != g_selectClass) {
		pCur1->classes = pCur1->classes->pNext;
	}
	if (pCur1->classes) pCur1->classes->student = nullptr;
	Student* pCur = nullptr;
	in.open(g_selectyear + "_" + g_selectClass + ".csv");
	if (in) {
		string str;
		int a;
		char c;
		getline(in, str);
		for (int i = 1; i <= numberOfLine(g_selectyear + "_" + g_selectClass + ".csv") - 1; i++) {
			if (pCur1->classes->student == nullptr) {
				pCur1->classes->student = new Student;
				pCur = schoolyear->classes->student;
			}
			else {
				pCur->pNext = new Student;
				pCur = pCur->pNext;
			}
			in >> a;
			in >> c;
			pCur->StudentID = a;
			getline(in, pCur->Firstname, ',');
			getline(in, pCur->Lastname, ',');
			getline(in, pCur->Gender, ',');
			getline(in, pCur->DoB, ',');
			getline(in, pCur->studentClass, ',');
			in >> a;
			pCur->SocialID = a;
			getline(in, pCur->studentPassword, '\n');
			pCur->studentClass = g_selectClass;
			pCur->pNext = nullptr;
		}
		in.close();
	}
	else {
		cout << "\t\t\t\t\nERROR\n";
	}
}

void getDataClass(SchoolYear*& Schoolyear) {
	Schoolyear->classes = nullptr;
	ifstream in;
	ofstream out;
	Class* pCur = Schoolyear->classes;
	string filename = g_selectyear + "_classes.txt";
	out.open(filename, ios::app);
	if (out) {
		in.open(filename);
		if (in) {
			for (int i = 1; i <= numberOfLine(filename); i++) {
				if (Schoolyear->classes == nullptr) {
					Schoolyear->classes = new Class;
					pCur = Schoolyear->classes;
				}
				else {
					pCur->pNext = new Class;
					pCur = pCur->pNext;
				}
				getline(in, pCur->className);
				pCur->pNext = nullptr;
			}
			in.close();
			out.close();
		}
		else cout << "\n\n\t\t\t\tERROR\n";
	}
}

void displayClass(SchoolYear* schoolyear) {
	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(Blue);
	gotoXY(38, 8); cout << "SCHOOL YEAR: " << g_selectyear;
	Textcolor(7);
	cout << "\n\n\t\t\t\tThe list of class: ";
	if (schoolyear->classes) {
		cout << schoolyear->classes->className;
		schoolyear->classes = schoolyear->classes->pNext;
	}

	while (schoolyear->classes != nullptr) {
		cout << "\n\t\t\t\t\t\t   " << schoolyear->classes->className;
		schoolyear->classes = schoolyear->classes->pNext;
	}
}

void createClassForYear(SchoolYear*& Schoolyear) {
	getDataClass(Schoolyear);
	string class_name;
	cout << "\n\t\t\t\tPlease input class name: ";
	getline(cin, class_name);
	Class* pcur = Schoolyear->classes;
	while (pcur != nullptr && pcur->className != class_name) {
		pcur = pcur->pNext;
	}
	if (pcur == nullptr) {
		pcur = new Class;
		pcur->className = class_name;
		pcur->pNext = nullptr;
		ofstream out;
		string path = g_selectyear + "_classes.txt";
		out.open(path, ios::app);
		if (out) {
			out << class_name << endl;
			out.close();
		}
		cout << "\n\t\t\t\tAdd class " << class_name << " successfully!";
		Sleep(2000);
	}
	else {
		cout << "\n\t\t\t\tClass " << class_name << " has already existed";
		Sleep(2000);
	}
}

void displayMenuClass(Staff* staff, Student* student, SchoolYear*& schoolyear) {

	string choice;
	getDataClass(schoolyear);
	displayClass(schoolyear);
	cout << "\n\n\t\t\t\t1. Create class \n";
	cout << "\n\n\t\t\t\t2. Get access into class \n";
	cout << "\n\n\t\t\t\t3. Exit \n";
	cout << "\n\n\t\t\t\t" << char(26) << " Enter your choice: ";
	cin >> choice; cin.ignore();
	if (choice == "1") {
		createClassForYear(schoolyear);
		system("cls");
		displayMenuClass(staff, student, schoolyear);
	}
	else if (choice == "2") {
		cout << "\n\n\t\t\t\t" << char(26) << " Enter the class you want to get access into: ";
		string class_name;
		getline(cin, class_name, '\n');
		getDataClass(schoolyear);
		Class* pCur = schoolyear->classes;
		while (pCur && pCur->className != class_name) {
			pCur = pCur->pNext;
		}
		if (pCur) {
			g_selectClass = class_name;
			cout << "\n\n\t\t\t\tEntering class " << class_name << "...";
			Sleep(2000);
			system("cls");
			displayStudentInClass(schoolyear, student);
			//displaySelectedYear(staff, student, schoolyear);
		}
		else {
			cout << "\n\n\t\t\t\tClass " << class_name << " doesn't exist";
			Sleep(2000);
			system("cls");
			displayMenuClass(staff, student, schoolyear);
		}
	}
	else if (choice == "3") {
		cout << "\n\n\t\t\t\tLoading...";
		Sleep(2000);
		system("cls");
		displaySelectedYearForStaff(staff, student, schoolyear);
	}
	else {
		cout << "\n\n\t\t\t\tInvalid input. Try again..";
		Sleep(1800);
		system("cls");
		displayMenuClass(staff, student, schoolyear);
	}
}

void displayStudentInClass(SchoolYear*& schoolyear, Student* student) {
	ofstream out;
	ifstream in;
	int y = 14, No = 1, check = 1;
	in.open("student.csv");
	string str;
	getline(in, str);
	in.close();
	out.open(g_selectyear + "_" + g_selectClass + ".csv", ios::app);
	if (numberOfLine(g_selectyear + "_" + g_selectClass + ".csv") == 0) {
		out << str << endl;
	}
	out.close();
	getDataStudentinClass(schoolyear);
	Class* tempClass = schoolyear->classes;
	while (tempClass && tempClass->className != g_selectClass)
		tempClass = tempClass->pNext;


	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(Blue);
	gotoXY(38, 8); cout << "CLASS: " << g_selectClass;
	Textcolor(7);
	gotoXY(31, 14); cout << "1. View student";
	gotoXY(31, 16); cout << "2. Exit";
	gotoXY(31, 18); cout << "Enter your choice: ";
	char choice = getchar();
	cin.ignore(100, '\n');
	switch (choice) {
	case '1':
		system("cls");
		if (g_Time != "") {
			gotoXY(26, 4); cout << "Date: " << g_Time;
		}
		gotoXY(26, 5); cout << "=======================================================";
		Textcolor(Blue);
		gotoXY(46, 8); cout << "CLASS: " << g_selectClass;
		Textcolor(7);

		gotoXY(5 + 5, y - 2); cout << "No";
		gotoXY(10 + 5, y - 2); cout << "Student ID";
		gotoXY(24 + 5, y - 2); cout << "Last name";
		gotoXY(38 + 5, y - 2); cout << "First name";
		gotoXY(51 + 5, y - 2); cout << "Gender";
		gotoXY(61 + 5, y - 2); cout << "Date of birth";
		gotoXY(78 + 5, y - 2); cout << "Social ID";

		gotoXY(02, y); cout << "===================================================="
			"===============================================";
		y += 2;

		if (numberOfLine(g_selectyear + "_" + g_selectClass + ".csv") == 1) {
			gotoXY(05 + 5, y); cout << "N/A";
			gotoXY(10 + 5, y); cout << "N/A";
			gotoXY(24 + 5, y); cout << "N/A";
			gotoXY(38 + 5, y); cout << "N/A";
			gotoXY(51 + 5, y); cout << "N/A";
			gotoXY(61 + 5, y); cout << "N/A";
			gotoXY(78 + 5, y); cout << "N/A";

		}
		else {
			while (tempClass && tempClass->student && tempClass->student->studentClass == g_selectClass) {
				gotoXY(05 + 5, y); cout << No;
				gotoXY(10 + 5, y); cout << tempClass->student->StudentID;
				gotoXY(24 + 5, y); cout << tempClass->student->Firstname;
				gotoXY(38 + 5, y); cout << tempClass->student->Lastname;
				gotoXY(51 + 5, y); cout << tempClass->student->Gender;
				gotoXY(61 + 5, y); cout << tempClass->student->DoB;
				gotoXY(78 + 5, y); cout << tempClass->student->SocialID;
				y++; No++;
				tempClass->student = tempClass->student->pNext;
			}
		}

		gotoXY(31, y + 4); cout << "T: Add a student by typing";
		gotoXY(31, y + 5); cout << "F: Add student/Change student list using csv file";
		gotoXY(31, y + 6); cout << "ESC: Exit";

		AnTroChuot();

		while (check) {
			if (_kbhit())
			{
				switch (_getch()) {
				case 't':
					if (No > 49) {
						gotoXY(31, y + 8); cout << "Number of student in " << g_selectClass << " has exceed the limit!!";
					}
					else {
						addStudent(schoolyear);
						displayStudentInClass(schoolyear, student);
					}
					break;
				case 'f':
					inputStudent();
					system("cls");
					displayStudentInClass(schoolyear, student);
					break;
				case 27:
					check = 0;
					system("cls");
					displayStudentInClass(schoolyear, student);
					break;
				}
			}
		}
		break;
	case '2':
		system("cls");
		gotoXY(40, 16); cout << "Loading...";
		Sleep(2000);
		system("cls");
		displayMenuClass(schoolyear->staff, student, schoolyear);
		break;
	default:
		gotoXY(31, 20); cout << "Try again in 2...";
		Sleep(1000);
		gotoXY(31, 20); cout << "Try again in 1...";
		Sleep(1000);
		system("cls");
		displayStudentInClass(schoolyear, student);
		break;
	}
}