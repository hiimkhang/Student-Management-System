#include "Header.h"
//extern string z;

extern string g_account;
extern int g_ID;
extern string g_selectyear;
extern int g_selectSemester;
extern string g_selectClass;
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
	Staff *pCur = pHead;
	while (pHead) {
		pHead = pHead->pNext;
		delete pCur;
		pCur = pHead;
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


void changePassStaff(Staff*& staff, Student* student, SchoolYear *schoolyear, string path) {
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
	while (oldPass == pCur->staffPassword) {
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
		changePassStaff(staff,student, schoolyear, path);
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
	string title;
	string Firstname, Lastname, Gender, studentPassword, DoB, studentClass;
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
					in >> ID;
					out << ID << ",";
					char z;
					in >> z;
					getline(in, Firstname, ',');
					out << Firstname << ",";
					getline(in, Lastname, ',');
					out << Lastname << ",";
					getline(in, Gender, ',');
					out << Gender << ",";
					getline(in, DoB, ',');
					out << DoB << ",";
					getline(in, studentClass, ',');
					out << studentClass;
					in >> SocialID;
					out << SocialID << ",";
					in >> z;
					getline(in, studentPassword, '\n');
					if (ID == pCur->StudentID) {
						out << newPass << "\n";
						pCur->studentPassword = newPass;
					}
					else {
						out << studentPassword << "\n";
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

void createSemester(SchoolYear*& Schoolyear) {
	getDataSemester(Schoolyear);
	int no;
	string start_date, end_date, register_start_date, register_end_date;
	cout << "\n\t\t\t\tEnter no of semester (1/2/3): ";
	cin >> no; cin.ignore();
	/*cout << "\n\t\t\t\tStart date: ";
	getline(cin, start_date);
	cout << "\n\t\t\t\tEnd date: ";
	getline(cin, end_date);

	cout << "\n\t\t\t\tRegister start date: ";
	getline(cin, register_start_date);
	
	cout << "\n\t\t\t\tRegister end date: ";
	getline(cin, register_end_date, '\n');
	*/

	Semester* pcur = Schoolyear->semester;
	while (pcur != nullptr && pcur->no != no) {
		pcur = pcur->pNext;
	}
	if (pcur == nullptr) {
		cout << "\n\t\t\t\tStart date: ";
		getline(cin, start_date);
		cout << "\n\t\t\t\tEnd date: ";
		getline(cin, end_date);
		cout << "\n\t\t\t\tRegister start date: ";
		getline(cin, register_start_date);
		cout << "\n\t\t\t\tRegister end date: ";
		getline(cin, register_end_date, '\n');
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
		cout << "\n\t\t\t\tAdd semester " << no << " successfully!";
		Sleep(2000);
	}
	else {
		cout << "\n\t\t\t\tSemester " << no << " is already exist";
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
		else cout << "ERROR\n";
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
		else cout << "ERROR\n";
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
		cout << "\n\n\t\t\t\tEnter the class you want to get access into: ";
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

void getDataCourseInSemester(SchoolYear*& schoolyear) {
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
			/*in >> a;
			in >> c;
			pCur->StudentID = a;
			string title = { "Course name,Course ID,credits,teacher name,"
			"number of students,day,time " };*/
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
			/*in >> a;
			pCur->SocialID = a;
			getline(in, str, '\n');
			pCur->studentClass = g_selectClass;*/
			pCur->pNext = nullptr;
		}
		in.close();
	}
	else {
		cout << "ERROR\n";
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
void exportListStudentInCourse(SchoolYear* schoolyear, string name_course) {
	while (schoolyear->year != g_selectyear) {
		schoolyear = schoolyear->pNext;
	}
	while (schoolyear->semester->no != g_selectSemester) {
		schoolyear->semester = schoolyear->semester->pNext;
	}
	while (schoolyear->semester->course->courseName != name_course) {
		schoolyear->semester->course = schoolyear->semester->course->pNext;
	}
	ofstream out;
	string filename = schoolyear->semester->course->courseName + "_course.csv";
	out.open(filename, ios::app);
	if (out) {
		while (schoolyear->semester->course->studentInCourse) {
			out << schoolyear->semester->course->studentInCourse->StudentID << ",";
			out << schoolyear->semester->course->studentInCourse->Firstname << ",";
			out << schoolyear->semester->course->studentInCourse->Lastname << ",";
			out << schoolyear->semester->course->studentInCourse->Gender << ",";
			out << schoolyear->semester->course->studentInCourse->studentClass << ",";
			out << schoolyear->semester->course->studentInCourse->SocialID << ",";
			out << schoolyear->semester->course->studentInCourse->DoB << endl;
			cout << schoolyear->semester->course->studentInCourse->StudentID << ",";
			cout << schoolyear->semester->course->studentInCourse->Firstname << ",";
			cout << schoolyear->semester->course->studentInCourse->Lastname << ",";
			cout << schoolyear->semester->course->studentInCourse->Gender << ",";
			cout << schoolyear->semester->course->studentInCourse->studentClass << ",";
			cout << schoolyear->semester->course->studentInCourse->SocialID << ",";
			cout << schoolyear->semester->course->studentInCourse->DoB << endl;
		}
		out.close();
	}
	else cout << "\n\n\t\t\t\tERROR. Can't open file...";
}
//void createTemplateScoreboard(string path) {
//	ofstream out;
//	out.open(path);
//	if (out) {
//		out << "No" << "," << "student ID" << "," << "Student full name" << "," << "Total mark" << "," << "Final mark" << "," << "Midterm mark" << "," << "Other mark" << endl;
//	else cout << "ERROR";
//}
void importScoreboard(string name_course){
	cout << "Please input the link of your file csv: ";
	string s;
	getline(cin, s);
	ifstream in;
	ofstream out;
	string t;
	in.open(s);
	if (in) {
		getline(in, t);
		out.open(g_selectyear + "_Semester" + to_string(g_selectSemester)+ name_course + ".csv", ios::app);
		for (int i = 1; i <= numberOfLine(s) - 1; i++) {
			getline(in, t);
			out << t << endl;
		}
		out.close();
		in.close();
	}
	else {
		cout << "\n\n\t\t\t\tCan not open " << s;
	}
}

void getDataScore(SchoolYear*& schoolyear, string path) {
	int no, studentID;
	float total_mark, final_mark, midterm_mark, other_mark;
	string Student_full_name;
	ifstream in;
	SchoolYear* pCur = new SchoolYear;
	in.open(path);
	if(in){
		for (int i = 1; i <= numberOfLine(path) - 1; i++) {
			if (schoolyear == nullptr) {
				schoolyear = new SchoolYear;
				pCur = schoolyear;
			}
			else {
				pCur->pNext = new SchoolYear;
				pCur = pCur->pNext;
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
			while (schoolyear->semester->course->studentInCourse->StudentID != studentID) {
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

void viewScore(SchoolYear *schoolyear) {
	gotoXY(26, 5); cout << "\n\n\t\t\t\tVIEW SCOREBOARD";
	if (schoolyear == nullptr) cout << "\n\n\t\tThere are currently no student in the course";
	else {
		cout << schoolyear->semester->course->studentInCourse->Firstname << " ";
		cout << schoolyear->semester->course->studentInCourse->Lastname << "\t";
		cout << schoolyear->semester->course->studentInCourse->StudentID << "\t";
		cout << schoolyear->semester->course->studentInCourse->Gender << "\t";
		cout << schoolyear->semester->course->studentInCourse->totalMark << "\t";
		cout << schoolyear->semester->course->studentInCourse->finalMark << "\t";
		cout << schoolyear->semester->course->studentInCourse->midtermMark << "\t";
		cout << schoolyear->semester->course->studentInCourse->otherMark << "\n";
	}
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
