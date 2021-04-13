#include "Header.h"

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
		string Firstname, Lastname, Gender, studentPassword = "student";
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
			getline(in, studentPassword, '\n');
			pCur->Firstname = Firstname;
			pCur->Lastname = Lastname;
			pCur->Gender = Gender;
			pCur->StudentID = StudentID;
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
	cout << "\n\t\t\tPlease input the School year you want to add (2xxx_2xxx): ";
	string y;
	getline(cin, y, '\n');
	SchoolYear* pCur = year_school;
	while (pCur->pNext != nullptr) {
		pCur = pCur->pNext;
	}
	pCur->pNext = new SchoolYear;
	pCur->pNext->year = y;
	pCur->pNext->pNext = nullptr;
}

void displayYear(SchoolYear* pHead) {
	cout << "\n\t\t\t\tList of school year: ";
	if (pHead) {
		cout << pHead->year;
		pHead = pHead->pNext;
	}
	while (pHead) {
		cout << "\n\t\t\t\t\t\t     " << pHead->year;
		pHead = pHead->pNext;
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
; bool loginStaff(Staff* staff, string &account) {
	cout << "\n\n\n\n\t\t\t\tAccount: ";
	string acc;
	string password;
	fflush(stdin);
	getline(cin, acc);
	cout << "\n\n\t\t\t\tPassword: ";
	fflush(stdin);
	getline(cin, password);

	while (staff && staff->staffAccount != acc) {
		staff = staff->pNext;
	}
	if (staff) {
		account = acc;
		if (password == staff->staffPassword) return true;
		else return false;
	}
	return false;
}

bool loginStudent(Student* student, int &ID) {
	cout << "\n\n\n\n\t\t\t\tStudent ID: ";
	string password;
	int StudentID;
	cin >> StudentID;
	cout << "\n\n\t\t\t\tPassword: ";
	cin.ignore();
	getline(cin, password);
	while (student && student->StudentID != StudentID) {
		student = student->pNext;
	}
	if (student && password == student->studentPassword) {
		ID = StudentID;
		return true;
	}
	return false;
}



void changePassStaff(Staff*& staff, Student* student, SchoolYear *schoolyear, string path, string account) {
	cout << "\n\t\t\t\t\tPASSWORD CHANGING\n";
	cout << "\n\t\t\t\tEnter your old password: ";
	string oldPass;
	getline(cin, oldPass, '\n');
	Staff* pCur = staff;
	while (pCur && pCur->staffAccount != account) {
		pCur = pCur->pNext;
	}
	while (oldPass == pCur->staffPassword) {
		cout << "\n\t\t\t\tEnter your new password: ";
		string tempPass, newPass;
		getline(cin, tempPass, '\n');

		cout << "\n\t\t\t\tEnter your new password again: ";
		getline(cin, newPass, '\n'); 

		if (tempPass == newPass) {
			cout << "\n\t\t\t\tLoading...\n";
			Sleep(3000);
			cout << "\n\t\t\t\tYour password has been changed successfully!\n";
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
				cout << "ERROR";
			}
			cout << "\n\t\t\t\tPress any key to return back to the previous page...";
			_getch();
			system("cls");
			displayLoginStaff(staff, student, schoolyear, account);
			return;
		}

		cout << "\n\t\t\t\tYour two inputs are not the same. Do you want to insert again?\n\t\t\t\t(y/n): ";
		char choice; cin >> choice; cin.ignore();
		if (choice == 'n' || choice == 'N') {
			cout << "\n\t\t\t\tLoading...\n";
			Sleep(2000);
			system("cls");
			displayLoginStaff(staff,student, schoolyear, account);
			return;
		}
		else continue;
	}
	cout << "\n\t\t\t\tWrong old password! Do you want to insert again?\n\t\t\t\t(y/n): ";
	char choice; cin >> choice; cin.ignore();
	if (choice == 'n' || choice == 'N') {
		cout << "\n\t\t\t\tLoading...\n";
		Sleep(3000);
		system("cls");
		displayLoginStaff(staff, student, schoolyear, account);
		return;
	}
	else {
		system("cls");
		changePassStaff(staff,student, schoolyear, path, account);
	}
}



void changePassStudent(Staff* staff, Student*& student, SchoolYear* schoolyear, string path, int ID) {
	cout << "\n\t\t\t\t\tPASSWORD CHANGING\n";
	cout << "\n\t\t\t\tEnter your old password: ";
	string oldPass;
	string title;
	string Firstname, Lastname, Gender, studentPassword;
	getline(cin, oldPass, '\n');

	Student* pCur = student;
	while (pCur && pCur->StudentID != ID) {
		pCur = pCur->pNext;
	}

	while (oldPass == pCur->studentPassword) {
		cout << "\n\t\t\t\tEnter your new password: ";
		string tempPass, newPass;
		getline(cin, tempPass, '\n');

		cout << "\n\t\t\t\tEnter your new password again: ";
		getline(cin, newPass, '\n');

		if (tempPass == newPass) {
			cout << "\n\t\t\t\tLoading...\n";
			Sleep(3000);
			cout << "\n\t\t\t\tYour password has been changed successfully!\n";
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
					getline(in, studentPassword, '\n');
					if (ID == pCur->StudentID) {
						out << newPass << endl;
					}
					else {
						out << studentPassword << endl;
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
			cout << "\n\t\t\t\tPress any key to return back to the previous page...";
			_getch();
			system("cls");
			displayLoginStudent(staff, student, schoolyear, ID);
			return;
		}

		cout << "\n\t\t\t\tYour two inputs are not the same. Do you want to insert again?\n\t\t\t\t(y/n): ";
		char choice; cin >> choice; cin.ignore();
		if (choice == 'n' || choice == 'N') {
			cout << "\n\t\t\t\tLoading...\n";
			Sleep(3000);
			system("cls");
			displayLoginStudent(staff, student, schoolyear, ID);
			return;
		}
		else continue;
	}
	cout << "\n\t\t\t\tWrong old password! Do you want to insert again?\n\t\t\t\t(y/n): ";
	char choice; cin >> choice; cin.ignore();
	if (choice == 'n' || choice == 'N') {
		cout << "\n\t\t\t\tLoading...\n";
		Sleep(3000);
		system("cls");
		displayLoginStudent(staff, student, schoolyear, ID);
		return;
	}
	else {
		system("cls");
		changePassStudent(staff, student, schoolyear, path, ID);
	}

}