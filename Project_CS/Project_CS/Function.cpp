#include "Header.h"
//extern string z;

extern string g_account;
extern int g_ID;
extern string g_selectyear;
extern string g_class;

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
		string Firstname, Lastname, Gender, studentPassword = "student", DoB = "N/A";
		int StudentID;
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
			getline(in, Firstname, ',');
			getline(in, Lastname, ',');
			getline(in, Gender, ',');
			in >> StudentID;
			char z;
			in >> z;
			getline(in, studentPassword, ',');
			getline(in, DoB, '\n');
			pCur->Firstname = Firstname;
			pCur->Lastname = Lastname;
			pCur->Gender = Gender;
			pCur->StudentID = StudentID;
			pCur->studentPassword = studentPassword;
			pCur->DoB = DoB;
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
			cout << "This year is exist \n";
			return;
		}
		pCur1 = pCur1->pNext;
	}
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
					getline(in, DoB, '\n');
					out << DoB << "\n";
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
    string class_name;
	cout << "\n\n\t\t\t\tPlease input class name: ";
	getline(cin, class_name);
	Schoolyear->classes = nullptr;
	Class* pcur = Schoolyear->classes;
	while (pcur != nullptr) {
		pcur = pcur->pNext;
	}
	pcur = new Class;
	pcur->className= class_name;
	pcur->pNext = nullptr;
	cout << "\n\n\t\t\t\tCreate successfully!";
	Sleep(2000);
	ofstream out;
	string path = g_selectyear + "_classes.txt";
	out.open(path, ios::app);
	if (out) {
		out << class_name << endl;
		out.close();
	}
}

void createSemester(SchoolYear* &Schoolyear) {
	ofstream out;
	int no;
		string start_date, end_date, register_start_date, register_end_date, teacher_name;
		cout << "\nThis is for 1st, 2nd or 3rd semester? ";
		cin >> no;
		string path = g_selectyear + "_semester.txt";
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
		out << no << ",";
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
	int y = 14;
	gotoXY(31, 14); cout << "List of classes: ";
	while (schoolyear->classes != nullptr) {
		gotoXY(49, y++); cout << schoolyear->classes->className;
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
	in.open(s);
	if (in) {
		getline(in, t);
		g_class = "test.csv";
		out.open(g_class, ios::app);
		for (int i = 1; i <= numberOfLine(s) - 1; i++) {
			getline(in, t);
			out << t << endl;
		}
		out.close();
		in.close();
	}
}

void getDataSemester(SchoolYear*& Schoolyear) {
	ifstream in;
	Semester* pCur = Schoolyear->semester;
	string filename = g_selectyear + "_semesters.txt";
	int no;
	in.open(filename, ios::app);
	if (in) {
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
				in >> no;
				char z;
				in >> z;
				getline(in, pCur->start_date);
				getline(in, pCur->end_date);
				getline(in, pCur->register_start_date);
				getline(in, pCur->register_end_date);
				getline(in, pCur->teacher_name);
				pCur->pNext = nullptr;
			}
			in.close();
		}
		else cout << "\n\n\t\t\t\tERROR\n";
	}
}

void displaySemester(SchoolYear* schoolyear) {
	ifstream in;
	string no, start_date, end_date, register_start_date, register_end_date, teacher_name;
	string path = g_selectyear + "_semester.txt";
	in.open(path);
	if (in) {
		getline(in, no, ',');
		cout << "Semester "<< no << " ";
		getline(in, start_date, ',');
		cout << "Start date: " << start_date << " ";
		getline(in, end_date, ',');
		cout << "End date: " << end_date << " ";
		getline(in, register_start_date, ',');
		cout << "Register start date: " << register_start_date << " ";
		getline(in, register_end_date, ',');
		cout << "Register end date: " << register_end_date << " ";
		getline(in, teacher_name, ',');
		cout << "Teacher name: " << teacher_name << " ";
		in.close();
	}
}

