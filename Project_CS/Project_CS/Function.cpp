#include "Header.h"
//extern string z;

extern string g_account;
extern int g_ID;
extern string g_selectyear;
extern string g_class;
extern string g_selectClass;

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


void getDataStaff(Staff* &pHead, string filename) {
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
	else cout << "ERROR \n";
}

void getDataStudent(Student*& pHead, string filename) {
	ifstream in;
	string t;
	in.open(filename);
	getline(in, t, '\n');
	if (in.is_open()) {
		string Firstname, Lastname, Gender ,studentPassword, studentClass, DoB;
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
	else cout << "ERROR \n";
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
	out << endl;
	out << y;
	SchoolYear* pCur = year_school;
	while (pCur->pNext != nullptr) {
		pCur = pCur->pNext;
	}
	pCur->pNext = new SchoolYear;
	pCur->pNext->year = y;
	pCur->pNext->pNext = nullptr;
	out.close();
}

void displayYear(SchoolYear* pHead) {
	int y = 10;
	pHead = nullptr;
	getDataSchoolYear(pHead, "school_year.txt");
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
	Staff *pCur = pHead;
	while (pHead) {
		pHead = pHead->pNext;
		delete pCur;
		pCur = pHead;
	}
}
; bool loginStaff(Staff* staff) {
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


void changePassStaff(Staff*& staff, Student* student, SchoolYear *schoolyear, string path) {
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
	while (oldPass == pCur->staffPassword) {
		cout << "\n\n\t\t\t\tEnter your new password: "; 
		string tempPass, newPass;
		getline(cin, tempPass, '\n');

		cout << "\n\n\t\t\t\tEnter your new password again: ";
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
				for (int i = 1; i <= numberOfLine(path) - 1 ; i++) {
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
			displayLoginStaff(staff,student, schoolyear);
			return;
		}
		else {
			system("cls");
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
		changePassStaff(staff,student, schoolyear, path);
	}
}



void changePassStudent(Staff* staff, Student*& student, SchoolYear* schoolyear, string path) {
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(Blue);
	gotoXY(44, 9); cout << "PASSWORD CHANGING";
	Textcolor(7);
	gotoXY(32, 14); cout << "Enter your old password: ";
	string oldPass;
	string title;
	string Firstname, Lastname, Gender, studentPassword, DoB;
	int ID;
	long SocialID;
	getline(cin, oldPass, '\n');

	Student* pCur = student;
	while (pCur && pCur->StudentID != g_ID) {
		pCur = pCur->pNext;
	}

	while (oldPass == pCur->studentPassword) {
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
				getline(in, title, '\n');
				out << title << endl;
				for (int i = 1; i <= numberOfLine(path) - 1; i++) {
					getline(in, Firstname, ',');
					out << Firstname << ",";
					getline(in, Lastname, ',');
					out << Lastname << ",";
					getline(in, Gender, ',');
					out << Gender << ",";
					in >> ID;
					out << ID << ",";
					char z;
					in >> z;		
					getline(in, studentPassword, ',');
					if (ID == pCur->StudentID) {
						out << newPass << ",";
						pCur->studentPassword = newPass;
					}
					else {
						out << studentPassword << ",";
					}
					getline(in, DoB, ',');
					out << DoB << ",";
					in >> SocialID;
					out << SocialID << "\n";
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
void createClassForYear(SchoolYear*& Schoolyear){
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
		cout << "\n\t\t\t\tClass " << class_name << " is already exist";
		Sleep(2000);
	}
}

void createSemester(SchoolYear* &Schoolyear) {
	ofstream out;
	int no;
		string start_date, end_date, register_start_date, register_end_date, teacher_name;
		cout << "\nThis is for 1st, 2nd or 3rd semester? (Enter 1/2 or 3):";
		cin >> no;
		string path = Schoolyear->year + "_semester.txt";
		out.open(path, ios::app);
		while (no < 1 && no > 3) {
			out << "\nError. Please input again: ";
			cin >> no;
		}
		cin.ignore();
		Semester* pcur = Schoolyear->semester;
		while (pcur != nullptr) {
			pcur = pcur->pNext;
		}
		pcur = new Semester;
		string t = "Semester";
		t.push_back(char(no + 48));
		out << t << ",";
		cout << "\nStart date: ";
		getline(cin, start_date);
		out << start_date << ",";
		pcur->start_date = start_date;
		cout << "\nEnd date: ";
		getline(cin, end_date);
		out << end_date << ",";
		pcur->end_date = end_date;
		cout << "\nRegister start date: ";
		getline(cin, register_start_date);
		out << register_start_date << ",";
		pcur->register_start_date = register_start_date;
		cout << "\nRegister end date: ";
		getline(cin, register_end_date);
		out << register_end_date << ",";
		pcur->register_end_date = register_end_date;
		cout << "Teacher in charge: ";
		getline(cin, teacher_name);
		out << teacher_name << endl;
		pcur->teacher_name = teacher_name;
		out.close();
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
		else cout << "ERROR\n";
	}
}

void displayClass(SchoolYear* schoolyear) {
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
	cout << "Please input the link of your file csv: ";
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
		cout << "Can not open " << s;
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
	}
	else {
		cout << "Can not open " << s;
	}
}

void displayMenuClass(Staff* staff, Student* student, SchoolYear* &schoolyear) {

	string choice;
	getDataClass(schoolyear);
	displayClass(schoolyear);
	cout << "\n\n\t\t\t\t1.Create class \n";
	cout << "\n\n\t\t\t\t2.Get access in class \n";
	cout << "\n\n\t\t\t\t3.Exit \n";
	cout << "\n\n\t\t\t\tEnter your choice: ";
	cin >> choice; cin.ignore();
	if (choice == "1") {
		createClassForYear(schoolyear);
		system("cls");
		displayMenuClass(staff, student, schoolyear);
	}
	else if (choice == "2") {
		cout << "\n\n\t\t\t\tEnter the class you want to get access to: ";
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
			cout << "\n\n\t\t\t\tClass " << class_name << " not found..";
			if (pCur)
				cout << "\n\n\t\t\t\tpCur->className at the moment is: " << pCur->className;
			else cout << "\n\n\t\pCur = nullptr. Tai vi luc gan pCur = schoolyear->classes o dong 618 function.cpp"
				" thi pCur da bang null roi, schoolyear->classes cung bang null luon.";
			cout << "\n\n\t\t\t\tPress any key to return...";
			_getch();
			system("cls");
			displaySchoolYearForStaff(staff, student, schoolyear);
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
	pCur1->classes->student = nullptr;
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
		cout << "ERROR\n";
	}
}

char* getTime() {
	time_t now = time(0);
	char* dt = ctime(&now);
	return dt;
}
void studentInCourse(Course* course) {
	Course* pCur = course;
	ofstream out;
	string filename = course->courseName + "_course.csv";
	out.open(filename, ios::app);
	if (out) {
		while (pCur != nullptr) {
			out << pCur->studentInCourse->StudentID << ",";
			out << pCur->studentInCourse->Firstname << ",";
			out << pCur->studentInCourse->Lastname << ",";
			out << pCur->studentInCourse->Gender << ",";
			out << pCur->studentInCourse->studentClass << ",";
			out << pCur->studentInCourse->SocialID << ",";
			out << pCur->studentInCourse->DoB << endl;
		}
		out.close();
	}
	else cout << "\n\n\t\t\t\tERROR. Can't open file...";
}


//void getDataCourse(Course* course, string path) {
//	ifstream in;
//	string t;
//	in.open(path);
//	if (in.is_open()) {
//		Course* pCur = pHead;
//		while (!in.eof()) {
//			if (pHead == nullptr) {
//				pHead = new SchoolYear;
//				pCur = pHead;
//			}
//			else {
//				pCur->pNext = new SchoolYear;
//				pCur = pCur->pNext;
//			}
//			getline(in, year, '\n');
//			pCur->year = year;
//			pCur->pNext = nullptr;
//		}
//		in.close();
//	}
//	else cout << "\n";
//}
//
//void displayStudent(string path) {
//	ifstream in;
//	in.open(path);
//	string a;
//	if (in) {
//		for (int i = 0; i < numberOfLine(path); i++) {
//			getline(in, a);
//			cout << a;
//		}
//	}
//}
// void displayCourse(string path) {
//	fstream fin;
//	string a;
//	fin.open();
//	if (fin) {
//		for (int i = 0; i < numberOfLine(path); i++) {
//			getline(fin, a);
//			cout << a;
//		}
//	}
//}
