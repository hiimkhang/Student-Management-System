#include "Header.h"

extern string g_account;
extern int g_ID;
extern string g_selectyear;
extern int g_selectSemester;
extern string g_selectClass;
extern string g_selectCourse;
extern int g_selectSemester;
extern string g_Time;

int numberOfLine(string filename) {
	ifstream in;
	in.open(filename);
	string s;
	int count = 0;
	while (!in.eof()) {
		getline(in, s, '\n');
		if (s != "") {
			count++;
		}
	}
	in.close();
	return count;
}


void getDataStaff(Staff*& pHead, string filename) {
	ifstream in;
	string t;
	in.open(filename);
	getline(in, t, '\n');
	if (in.is_open()) {
		string nameStaff, staffAccount, staffPassword = "staff";
		Staff* pCur = pHead;
		for (int i = 1; i <= numberOfLine(filename) - 1; i++) {
			if (pHead == nullptr) {
				pHead = new Staff;
				pCur = pHead;
			}
			else {
				pCur->pNext = new Staff;
				pCur = pCur->pNext;
			}
			getline(in, nameStaff, ',');
			getline(in, staffAccount, ',');
			getline(in, staffPassword, '\n');
			pCur->nameStaff = nameStaff;
			pCur->staffAccount = staffAccount;
			pCur->staffPassword = staffPassword;
			pCur->pNext = nullptr;
		}
		in.close();
	}
	else cout << "\n\n\t\t\tERROR \n";
}

void getDataStudent(Student*& pHead, string filename) {
	pHead = nullptr;
	ifstream in;
	string t;
	in.open(filename);
	getline(in, t, '\n');
	if (in.is_open()) {
		string Firstname, Lastname, Gender, studentPassword, studentClass, DoB;
		int StudentID;
		long SocialID;
		Student* pCur = pHead;
		for (int i = 1; i <= numberOfLine(filename) - 1; i++) {
			if (pHead == nullptr) {
				pHead = new Student;
				pCur = pHead;
			}
			else {
				pCur->pNext = new Student;
				pCur = pCur->pNext;
			}
			in >> StudentID;
			char z;
			in >> z;
			getline(in, Firstname, ',');
			getline(in, Lastname, ',');
			getline(in, Gender, ',');
			getline(in, DoB, ',');
			getline(in, studentClass, ',');
			in >> SocialID;
			in >> z;
			getline(in, studentPassword, '\n');

			pCur->StudentID = StudentID;
			pCur->Firstname = Firstname;
			pCur->Lastname = Lastname;
			pCur->Gender = Gender;
			pCur->DoB = DoB;
			pCur->studentClass = studentClass;
			pCur->SocialID = SocialID;
			pCur->studentPassword = studentPassword;
			pCur->pNext = nullptr;
		}
		in.close();
	}
	else cout << "\n\n\t\t\tERROR \n";
}

void getDataSchoolYear(SchoolYear*& pHead, string path) {
	ifstream in;
	string t;
	in.open(path);
	if (in.is_open()) {
		string year;
		SchoolYear* pCur = pHead;
		while (!in.eof()) {
			if (pHead == nullptr) {
				pHead = new SchoolYear;
				pCur = pHead;
			}
			else {
				pCur->pNext = new SchoolYear;
				pCur = pCur->pNext;
			}
			getline(in, year, '\n');
			pCur->year = year;
			pCur->pNext = nullptr;
		}
		in.close();
	}
	else cout << "\n";
}

void createNewYear(SchoolYear*& year_school) {
	ofstream out;
	out.open("school_year.txt", ios::app);

	cout << "\n\t\t\t\tEnter school year (2xxx_2xxx): ";
	string y;
	getline(cin, y, '\n');
	year_school = nullptr;
	getDataSchoolYear(year_school, "shool_year.txt");
	SchoolYear* pCur1 = year_school;
	while (pCur1 != nullptr) {
		if (pCur1->year == y) {
			cout << "\n\t\t\t\tThis year is already exsisted.";
			Sleep(2000);
			return;
		}
		pCur1 = pCur1->pNext;
	}
	cout << "\n\n\t\t\t\tLoading...\n";
	Sleep(2000);
	cout << "\n\t\t\t\tAdded.\n";
	cout << "\n\t\t\t\tPress any key to return to previous page...";
	_getch();
	out << y << endl;
}

void displayYear(SchoolYear* pHead) {
	int y = 10;
	pHead = nullptr;
	getDataSchoolYear(pHead, "school_year.txt");
	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(Blue);
	gotoXY(46, 8); cout << "SCHOOL YEAR";
	Textcolor(7);
	gotoXY(34, 10); cout << "List of school year: ";
	if (pHead) {
		gotoXY(56, y); cout << pHead->year;
		pHead = pHead->pNext;
		y++;
	}
	while (pHead) {
		gotoXY(56, y); cout << pHead->year;
		pHead = pHead->pNext;
		y++;
	}
	cout << endl;
}


void deleteList(Staff*& pHead) {
	Staff* pCur = pHead;
	while (pHead) {
		pHead = pHead->pNext;
		delete pCur;
		pCur = pHead;
	}
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
; bool loginStaff(Staff* staff) {
	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(11);
	gotoXY(50, 9); cout << "LOGIN";
	Textcolor(7);
	gotoXY(31, 12); cout << "Account: ";
	string acc;
	string password;
	fflush(stdin);
	getline(cin, acc);
	gotoXY(31, 14); cout << "Password: ";
	fflush(stdin);
	getline(cin, password);

	while (staff && staff->staffAccount != acc) {
		staff = staff->pNext;
	}
	if (staff) {
		g_account = acc;
		if (password == staff->staffPassword) return true;
		else return false;
	}
	return false;
}

bool loginStudent(Student* student) {
	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(11);
	gotoXY(50, 9); cout << "LOGIN";
	Textcolor(7);
	gotoXY(31, 12); cout << "Student ID: ";
	string password;
	int StudentID;
	cin >> StudentID;
	gotoXY(31, 14); cout << "Password: ";
	cin.ignore();
	getline(cin, password);
	while (student && student->StudentID != StudentID) {
		student = student->pNext;
	}
	if (student && password == student->studentPassword) {
		g_ID = StudentID;
		return true;
	}
	return false;
}


void changePassStaff(Staff*& staff, Student* student, SchoolYear* schoolyear, string path) {
	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(Blue);
	gotoXY(44, 9); cout << "PASSWORD CHANGING";
	Textcolor(7);
	gotoXY(32, 14); cout << "Enter your old password: ";
	string oldPass;
	getline(cin, oldPass, '\n');
	Staff* pCur = staff;
	while (pCur && pCur->staffAccount != g_account) {
		pCur = pCur->pNext;
	}
	while (pCur && oldPass == pCur->staffPassword) {
		cout << "\n\n\t\t\t\tEnter your new password: ";
		string tempPass, newPass;
		getline(cin, tempPass, '\n');

		cout << "\n\t\t\t\tEnter your new password again: ";
		getline(cin, newPass, '\n');

		if (tempPass == newPass) {
			cout << "\n\n\t\t\t\tLoading...";
			Sleep(3000);
			pCur->staffPassword = newPass;
			ifstream in;
			ofstream out;
			string title;
			string nameStaff, staffAccount, staffPassword;
			in.open(path);
			if (in) {
				out.open("temp.csv");
				getline(in, title, '\n');
				out << title << endl;
				for (int i = 1; i <= numberOfLine(path) - 1; i++) {
					getline(in, nameStaff, ',');
					out << nameStaff << ",";
					getline(in, staffAccount, ',');
					out << staffAccount << ",";
					getline(in, staffPassword, '\n');
					if (staffAccount == pCur->staffAccount) {
						out << newPass << endl;
					}
					else {
						out << staffPassword << endl;
					}
				}
				out.close();
				in.close();
				remove("Staff.csv");
				rename("temp.csv", "Staff.csv");
			}
			else {
				gotoXY(31, 22); cout << "ERROR";
			}
			cout << "\n\n\n\t\t\t\tYour password has been changed successfully!\n";
			cout << "\n\n\t\t\t\tPress any key to return back to the previous page...";
			_getch();
			system("cls");
			displayLoginStaff(staff, student, schoolyear);
			return;
		}
		cout << "\n\n\t\t\t\tYour two inputs are not the same.\n\t\t\t\tDo you want to insert again? (y/n): ";
		char choice; cin >> choice; cin.ignore();
		if (choice == 'n' || choice == 'N') {
			cout << "\n\n\t\t\t\tLoading...\n";
			Sleep(2000);
			system("cls");
			displayLoginStaff(staff, student, schoolyear);
			return;
		}
		else {
			system("cls");
			if (g_Time != "") {
				gotoXY(26, 4); cout << "Date: " << g_Time;
			}
			gotoXY(26, 5); cout << "=======================================================";
			Textcolor(Blue);
			gotoXY(44, 9); cout << "PASSWORD CHANGING";
			Textcolor(7);
			gotoXY(32, 14); cout << "Enter your old password: " << oldPass;
			continue;
		}
	}
	cout << "\n\t\t\t\tWrong old password!\n\t\t\t\tDo you want to insert again? (y/n): ";
	char choice; cin >> choice; cin.ignore();
	if (choice == 'n' || choice == 'N') {
		cout << "\n\t\t\t\tLoading...\n";
		Sleep(3000);
		system("cls");
		displayLoginStaff(staff, student, schoolyear);
		return;
	}
	else {
		system("cls");
		changePassStaff(staff, student, schoolyear, path);
	}
}



void changePassStudent(Staff* staff, Student*& student, SchoolYear* schoolyear, string path) {
	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(Blue);
	gotoXY(44, 9); cout << "PASSWORD CHANGING";
	Textcolor(7);
	gotoXY(32, 14); cout << "Enter your old password: ";
	string oldPass;
	string str;
	getline(cin, oldPass, '\n');

	Student* pCur = student;
	while (pCur && pCur->StudentID != g_ID) {
		pCur = pCur->pNext;
	}

	while (pCur && oldPass == pCur->studentPassword) {
		cout << "\n\n\t\t\t\tEnter your new password: ";
		string tempPass, newPass;
		getline(cin, tempPass, '\n');

		cout << "\n\n\t\t\t\tEnter your new password again: ";
		getline(cin, newPass, '\n');

		if (tempPass == newPass) {
			cout << "\n\n\t\t\t\tLoading...";
			Sleep(3000);
			pCur->studentPassword = newPass;
			ifstream in;
			ofstream out;
			in.open(path);
			if (in) {
				out.open("tempStudent.csv");
				getline(in, str, '\n');
				out << str << endl;
				for (int i = 1; i <= numberOfLine(path) - 1; i++) {
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
						out << newPass << "\n";
					}
				}
				out.close();
				in.close();
				remove("Student.csv");
				rename("tempStudent.csv", "Student.csv");
			}
			else {
				cout << "ERROR";
			}
			cout << "\n\n\n\t\t\t\tYour password has been changed successfully!\n";
			cout << "\n\n\t\t\t\tPress any key to return back to the previous page...";
			_getch();
			system("cls");
			displayLoginStudent(staff, student, schoolyear);
			return;
		}

		cout << "\n\n\t\t\t\tYour two inputs are not the same.\n\t\t\t\tDo you want to insert again? (y/n): ";
		char choice; cin >> choice; cin.ignore();
		if (choice == 'n' || choice == 'N') {
			cout << "\n\n\t\t\t\tLoading...\n";
			Sleep(2000);
			system("cls");
			displayLoginStudent(staff, student, schoolyear);
			return;
		}
		else {
			system("cls");
			if (g_Time != "") {
				gotoXY(26, 4); cout << "Date: " << g_Time;
			}
			gotoXY(26, 5); cout << "=======================================================";
			Textcolor(Blue);
			gotoXY(44, 9); cout << "PASSWORD CHANGING";
			Textcolor(7);
			gotoXY(32, 14); cout << "Enter your old password: " << oldPass;
			continue;
		}
	}
	cout << "\n\t\t\t\tWrong old password!\n\t\t\t\tDo you want to insert again? (y/n): ";
	char choice; cin >> choice; cin.ignore();
	if (choice == 'n' || choice == 'N') {
		cout << "\n\t\t\t\tLoading...\n";
		Sleep(3000);
		system("cls");
		displayLoginStudent(staff, student, schoolyear);
		return;
	}
	else {
		system("cls");
		changePassStudent(staff, student, schoolyear, path);
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

void createSemester(SchoolYear*& Schoolyear) {
	setConsoleWindow(800, 650);
	getDataSemester(Schoolyear);
	int no;
	string start_date, end_date, register_start_date, register_end_date;
	cout << "\n\t\t\t\t" << char(26) << " Enter semester (1/2/3): ";
	cin >> no; cin.ignore();
	while (!(no > 0 && no < 4)) {
		cout << "\n\t\t\t\tInvalid input\n\t\t\t" << char(26) << " Enter semester (1/2/3): ";
		cin >> no; cin.ignore();
	}

	Semester* pcur = Schoolyear->semester;
	while (pcur != nullptr && pcur->no != no) {
		pcur = pcur->pNext;
	}
	if (pcur == nullptr) {
		cout << "\n\t\t\t\tStart date: ";
		getline(cin, start_date);
		cout << "\n\t\t\t\tEnd date: ";
		getline(cin, end_date);
		register_start_date = addDays(start_date, -7);
		register_end_date = addDays(start_date, -1);
		cout << "\n\t\t\t\tCourses register is avaialable for 7 days before a semester begins.";
		Sleep(1500);
		cout << "\n\n\t\t\t\tRegister start date will be: " << register_start_date;
		cout << "\n\n\t\t\t\tRegister end date will be:  " << register_end_date;
		AnTroChuot();
		pcur = new Semester;
		pcur->no = no;
		pcur->pNext = nullptr;
		ofstream out;
		string path = g_selectyear + "_semester.txt";
		out.open(path, ios::app);
		if (out) {
			out << no << ",";
			out << start_date << ",";
			out << end_date << ",";
			out << register_start_date << ",";
			out << register_end_date << "\n";
			out.close();
		}
		Sleep(3000);
		cout << "\n\n\t\t\t\tAdd semester " << no << " successfully!";
		cout << "\n\n\t\t\t\tPress any key to return...";
		_getch();
	}
	else {
		cout << "\n\t\t\t\tSemester " << no << " has already existed!";
		Sleep(2000);
	}
}

void getDataSemester(SchoolYear*& Schoolyear) {
	Schoolyear->semester = nullptr;
	ifstream in;
	ofstream out;
	Semester* pCur = Schoolyear->semester;
	string filename = g_selectyear + "_semester.txt";
	out.open(filename, ios::app);
	if (out) {
		in.open(filename);
		if (in) {
			for (int i = 1; i <= numberOfLine(filename); i++) {
				if (Schoolyear->semester == nullptr) {
					Schoolyear->semester = new Semester;
					pCur = Schoolyear->semester;
				}
				else {
					pCur->pNext = new Semester;
					pCur = pCur->pNext;
				}
				in >> pCur->no;
				char c;
				in >> c;
				getline(in, pCur->start_date, ',');
				getline(in, pCur->end_date, ',');
				getline(in, pCur->register_start_date, ',');
				getline(in, pCur->register_end_date, '\n');
				pCur->pNext = nullptr;
			}
			in.close();
			out.close();
		}
		else cout << "\n\t\t\t\tERROR\n";
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


void inputStudent() {
	cout << "\n\n\t\tPlease input the link of your csv.file (Ex:C:\\DocumentsClass\\20CTT1.csv):\n\t\t";
	string s;
	getline(cin, s);
	ifstream in;
	ofstream out;
	string t;
	in.open(s);
	if (in) {
		getline(in, t);
		out.open("Student.csv", ios::app);
		for (int i = 1; i <= numberOfLine(s) - 1; i++) {
			getline(in, t);
			out << t << endl;
		}
		out.close();
		in.close();
	}
	else {
		cout << "\n\n\t\tCan not open " << s;
		Sleep(2000);
	}
	in.open(s);
	if (in) {
		getline(in, t);
		out.open(g_selectyear + "_" + g_selectClass + ".csv", ios::app);
		for (int i = 1; i <= numberOfLine(s) - 1; i++) {
			getline(in, t);
			out << t << endl;
		}
		out.close();
		in.close();
		cout << "\t\tUpdate students from csv file successfully!";
		Sleep(2000);
	}
	else {
		cout << "\n\n\t\tCan not open " << s;
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
		cout << "\n\n\t\t\t\t" << char(26) << "Enter the class you want to get access into: ";
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

string add0(string date) {
	int i = 0;
	string day, month, year;
	while (date[i] != '/') {
		day.push_back(date[i]);
		i++;
	}
	i++;
	while (date[i] != '/') {
		month.push_back(date[i]);
		i++;
	}
	i++;
	while (date[i]) {
		year.push_back(date[i]);
		i++;
	}
	if (day.size() < 2) {
		day = "0" + day;
	}
	if (month.size() < 2) {
		month = "0" + month;
	}
	return day + '/' + month + '/' + year;
}

int date_cmp(const char* d1, const char* d2)
{
	int rc;
	// compare years
	rc = strncmp(d1 + 6, d2 + 6, 4);
	if (rc != 0)
		return rc;

	// compare months
	rc = strncmp(d1 + 3, d2 + 3, 2);
	if (rc != 0)
		return rc;

	// compare days
	return strncmp(d1, d2, 2);
}

void DatePlusDays(struct tm* date, int days)
{
	const time_t ONE_DAY = 24 * 60 * 60;

	// Seconds since start of epoch
	time_t date_seconds = mktime(date) + (days * ONE_DAY);

	// Update caller's date
	// Use localtime because mktime converts to UTC so may change date
	*date = *localtime(&date_seconds); ;
}

string addDays(string date1, int days) {
	string realDate = add0(date1);
	int day = (realDate[0] - '0') * 10 + (realDate[1] - '0');
	int month = (realDate[3] - '0') * 10 + (realDate[4] - '0');
	int year = (realDate[6] - '0') * 1000 + (realDate[7] - '0') * 100 + (realDate[8] - '0') * 10 + (realDate[9] - '0');
	struct tm date = { 0, 0, 12 };
	date.tm_mday = day;
	date.tm_mon = month - 1;
	date.tm_year = year - 1900;
	DatePlusDays(&date, days);
	string time = asctime(&date);
	string dd = "10";
	if (time[8] != ' ') {
		dd[0] = time[8];
		dd[1] = time[9];
		dd[2] = '\0';
	}
	else {
		dd[0] = time[9];
		dd[1] = '\0';
	}
	string res = dd + "/" + to_string(date.tm_mon + 1) + "/" + to_string(date.tm_year + 1900);
	return add0(res);
}

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
		for (int i = 0; i < 7; i++) {
			getline(in, s, ',');
			out << s << ",";
			cout << s << "\t";
		}
		out << endl;
		cout << endl;
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
			cout << pCur->StudentID << "\t";
			cout << pCur->Firstname << "\t";
			cout << pCur->Lastname << "\t";
			cout << pCur->Gender << "\t";
			cout << pCur->DoB << "\t";
			cout << pCur->studentClass << "\t\t";
			cout << pCur->SocialID << "\n";
			pCur = pCur->pNext;
		}
		out.close();
	}
	else cout << "\n\t\t\t\tERROR. Can't open file...";
}

void importScoreboard(SchoolYear*& schoolyear) {
	system("cls");
	string choice;
	do {
		Textcolor(Blue);
		cout << "\n\n\t\t\t\tSCOREBOARD IMPORTING \n";
		Textcolor(7);
		cout << "\n\n\t\t\t\t1. Create template to import scoreboard \n";
		cout << "\n\t\t\t\t2. Import scoreboard \n";
		cout << "\n\t\t\t\t3. Exit \n";
		cout << "\n\n\t\t\t\t" << char(26) << " Please input your option: ";
		cin >> choice;
		cin.ignore();
		if (choice == "1") {
			cout << "\n\t\t\t Input link's location (in your computer) to export scoreboard template: ";
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
			cout << "\n\n\t\t\t\tPress any key to continue...";
			_getch();
			system("cls");
		}
		else if (choice == "2") {
			cout << "\n\t\t\t\t" << char(26) << " Import link that contents template: ";
			string s;
			getline(cin, s);
			ifstream in;
			in.open(s);
			ofstream out;
			out.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_score.csv");
			string str;
			for (int i = 1; i <= numberOfLine(s); i++) {
				getline(in, str);
				out << str << endl;
			}
			out.close();
			in.close();
			cout << "\n\t\t\t\tCompleted! \n";
			cout << "\n\n\t\t\t\tPress any key to continue...";
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
	string path = to_string(g_ID) + "_Course.csv";
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
	else cout << "\n\n\t\t\t\tCan not open file directory...";

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
		else cout << "\n\n\t\t\t\tCan not open directory file...";
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
	Textcolor(Blue);
	gotoXY(18, 5); cout << "\t\t\t" << char(3) << " VIEW SCOREBOARD " << char(3) << endl;
	Textcolor(7);
	gotoXY(8, 7); cout << "===========================================================================================" << endl;
	string str;
	ifstream in;
	in.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_score.csv");
	if (in.is_open()) {
		getline(in, str, ',');
		cout << str << "\t";
		getline(in, str, ',');
		cout << str << "\t";
		getline(in, str, ',');
		cout << str << "\t";
		getline(in, str, ',');
		cout << str << "\t";
		getline(in, str, ',');
		cout << str << "\t";
		getline(in, str, ',');
		cout << str << "\t";
		getline(in, str, '\n');
		cout << str << "\n";
		for (int i = 2; i <= numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_score.csv"); i++) {
			getline(in, str, ',');
			cout << str << "\t";
			getline(in, str, ',');
			cout << str << "\t";
			getline(in, str, ',');
			cout << str << "\t\t";
			getline(in, str, ',');
			cout << str << "\t\t";
			getline(in, str, ',');
			cout << str << "\t\t";
			getline(in, str, ',');
			cout << str << "\t\t";
			getline(in, str, '\n');
			cout << str << "\n";
		}
		in.close();
	}
	else cout << "\n\n\t\t\t\tFailed to open directory file (No imported board).";
}

void updateStudentResult(SchoolYear* schoolyear) {
	viewScore(schoolyear);
	cout << "\t\t\t\tInput student ID that need to be changed: ";
	string id;
	getline(cin, id);
	ifstream in; ofstream out;
	in.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_score.csv");
	string str;
	out.open("scoretemp.csv");
	getline(in, str);
	out << str << endl;
	for (int i = 1; i <= numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_score.csv") - 1; i++) {
		getline(in, str, ',');
		out << str << ",";
		getline(in, str, ',');
		if (str == id) {
			out << str << ',';
			getline(in, str, ',');
			out << str << ",";
			cout << str << ": \n";
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, '\n');
			string total, final, midterm, other;
			cout << "\n\t\t\t\tTotal mark: ";
			cin >> total;
			out << total << ",";
			cout << "\n\t\t\t\tFinal mark: ";
			cin >> final;
			out << final << ",";
			cout << "\n\t\t\t\tMidterm mark: ";
			cin >> midterm;
			out << midterm << ",";
			cout << "\n\t\t\t\tOther mark: ";
			cin >> other; cin.ignore();
			out << other << "\n";
		}
		else {
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
	}
	out.close();
	in.close();
	remove((g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_score.csv").c_str());
	rename("scoretemp.csv", (g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_score.csv").c_str());
	cout << "Updated \n";
	viewScore(schoolyear);
}
bool checkEnroll() {
	string str;
	string day, time;
	string Day[2], Time[2];
	ifstream in;
	in.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv");
	getline(in, str);
	for (int i = 1; i <= numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv") - 1; i++) {
		getline(in, str, ',');
		getline(in, str, ',');
		if (str == g_selectCourse) {
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, day, ',');
			getline(in, time, '\n');
			break;
		}
		else {
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, '\n');
		}
	}
	int temp = 0;
	for (int i = 0; i < day.size(); i++) {
		if (day[i] == ' ' || day[i] == '&') {
			temp = 1;
			while (day[i] == ' ' || day[i] == '&') {
				i++;
			}
		}
		if (temp == 0) Day[0].push_back(day[i]);
		else Day[1].push_back(day[i]);
	}
	temp = 0;
	for (int i = 0; i < time.size(); i++) {
		if (time[i] == ' ' || time[i] == '&') {
			temp = 1;
			while (time[i] == ' ' || time[i] == '&') {
				i++;
			}
		}
		if (temp == 0) Time[0].push_back(time[i]);
		else Time[1].push_back(time[i]);
	}
	in.close();
	string Day1[2], Time1[2];
	in.open(to_string(g_ID) + "_Course.csv");
	if (numberOfLine(to_string(g_ID) + "_Course.csv") == 6) return false;
	getline(in, str);
	for (int i = 1; i <= numberOfLine(to_string(g_ID) + "_Course.csv") - 1; i++) {
		getline(in, str, ',');
		getline(in, str, ',');
		getline(in, str, ',');
		getline(in, str, ',');
		getline(in, str, ',');
		getline(in, str, ',');
		temp = 0;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == ' ' || str[i] == '&') {
				temp = 1;
				while (str[i] == ' ' || str[i] == '&') {
					i++;
				}
			}
			if (temp == 0) Day1[0].push_back(str[i]);
			else Day1[1].push_back(str[i]);
		}
		getline(in, str);
		temp = 0;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == ' ' || str[i] == '&') {
				temp = 1;
				while (str[i] == ' ' || str[i] == '&') {
					i++;
				}
			}
			if (temp == 0) Time1[0].push_back(str[i]);
			else Time1[1].push_back(str[i]);
		}
	
		if (Day1[0] == Day[0] || Day1[1] == Day[1]) {
			if (Day1[0] == Day[0] && Day1[1] != Day[0]) {
				if (Time1[0] == Time[0]) return false;
			}
			else if (Day1[1] == Day[1] && Day1[0] != Day[0]) {
				if (Time1[1] == Time[1]) return false;
			}
			else {
				if (Time1[0] == Time[0]) return false;
				if (Time1[1] == Time[1]) return false;
			}
		}
		Day1[0] = "";
		Day1[1] = "";
		Time1[0] = "";
		Time1[1] = "";
	}
	in.close();
	return true;
}

void enroll() {
	Student* student = nullptr;
	ofstream out;
	ifstream in;
	out.open(to_string(g_ID) + "_Course.csv", ios::app);
	if (numberOfLine(to_string(g_ID) + "_Course.csv") == 0) {
		out << "Course name, Course ID, credits, teacher name, number of students, day, time\n";
	}
	out.close();
	if (checkEnroll() == true) {
		out.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_student.csv", ios::app);
		if (numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_student.csv") == 0) {
			out << "studentID, First Name, Last Name, Gender, Dob, studentClass, SocialID, studentPassword\n";
		}
		getDataStudent(student, "Student.csv");
		while (student != nullptr && student->StudentID != g_ID) {
			student = student->pNext;
		}
		out << student->StudentID << ",";
		out << student->Firstname << ",";
		out << student->Lastname << ",";
		out << student->Gender << ",";
		out << student->DoB << ",";
		out << student->studentClass << ",";
		out << student->SocialID << ",";
		out << student->studentPassword << "\n";
		out.close();
		string str;
		out.open(to_string(g_ID) + "_Course.csv", ios::app);
		in.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv");
		getline(in, str);
		string q, w;
		for (int i = 1; i <= numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv") - 1; i++) {
			getline(in, str, ',');
			q = str;
			getline(in, str, ',');
			w = str;
			if (str == g_selectCourse) {
				out << q << ",";
				out << w << ",";
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
				break;
			}
			else {
				getline(in, str, ',');
				getline(in, str, ',');
				getline(in, str, ',');
				getline(in, str, ',');
				getline(in, str, '\n');
			}
		}
		in.close();
		out.close();
		cout << "\n\t\t\t\t             Enroll successfully!";
	}
	else {
		cout << "\n\t\t\t\t             Unable to enroll!";
	}
}

void viewCourseEnrolled() {
	ifstream in;
	ofstream out;
	string path = to_string(g_ID) + "_Course.csv";
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
		for (int i = 1; i <= numberOfLine(to_string(g_ID) + "_Course.csv") - 1; i++) {
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
	in.open(to_string(g_ID) + "_Course.csv");
	out.open("tempenr.csv");
	string str;
	bool checkCourse = false;
	getline(in, str);
	out << str << endl;
	string s;
	for (int i = 1; i <= numberOfLine(to_string(g_ID) + "_Course.csv") - 1; i++) {
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
	remove((to_string(g_ID) + "_Course.csv").c_str());
	rename("tempenr.csv", (to_string(g_ID) + "_Course.csv").c_str());

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
			cout << "\n\n\t\t\t\tCan not open file directory...";
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
			cout << "\n\n\t\t\t\tCan not open file directory...";
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
			cout << "\n\n\t\t\t\tCan not open file directory...";
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
			cout << "\n\n\t\t\t\tCan not open file directory...";
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
			cout << "\n\n\t\t\t\tCan not open file directory...";
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
			cout << "\n\n\t\t\t\tCan not open file directory...";
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
			cout << "\n\n\t\t\t\tCan not open file directory...";
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
	else cout << "\n\t\t\t      Unable to open file..." << path;
}