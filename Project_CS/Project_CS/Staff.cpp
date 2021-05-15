#pragma once
#include "_Staff.h"

extern string g_account;
extern int g_ID;
extern string g_selectyear;
extern int g_selectSemester;
extern string g_selectClass;
extern string g_selectCourse;
extern string g_Time;

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
	else {
		gotoXY(31, 23);
		cout << "Unable to open file staff.csv directory, can not get data.";
	}
}

bool loginStaff(Staff* staff) {
	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(11);
	gotoXY(50, 9); cout << "LOGIN";
	Textcolor(7);
	gotoXY(35, 20); cout << "Default account of staffs:";
	gotoXY(35, 22); cout << "Account:  staffNVA (or staffNVB/C/D)";
	gotoXY(35, 24); cout << "Password: staff";
	gotoXY(35, 12); cout << "Account: ";
	string acc;
	string password;
	fflush(stdin);
	getline(cin, acc);
	gotoXY(35, 14); cout << "Password: ";
	fflush(stdin);
	getline(cin, password);
	staff = nullptr;
	getDataStaff(staff, "Staff.csv");
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
	staff = nullptr;
	getDataStaff(staff, "Staff.csv");
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

void displayLoginStaff(Staff* staff, Student* student, SchoolYear* schoolyear) {
	setConsoleWindow(800, 600);
	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(Blue);
	gotoXY(39, 9); cout << "COURSE REGISTRATION SYSTEM";
	Textcolor(7);
	gotoXY(31, 12); cout << "1. School year";
	gotoXY(31, 14); cout << "2. View profile";
	gotoXY(31, 16); cout << "3. Change password";
	gotoXY(31, 18); cout << "4. Log out";
	gotoXY(31, 20); cout << char(26) << " Enter your choice: ";
	char choice = getchar();
	cin.ignore(100, '\n');
	switch (choice) {
	case '1':
		system("cls");
		displayYear(schoolyear);
		displaySchoolYearForStaff(staff, student, schoolyear);
		break;
	case '2':
		system("cls");
		displayStaffProfile(staff);
		_getch();
		system("cls");
		displayLoginStaff(staff, student, schoolyear);
		break;
	case '3':
		system("cls");
		changePassStaff(staff, student, schoolyear, "Staff.csv");
		break;
	case '4':
		gotoXY(31, 23); cout << "Logging out...";
		Sleep(3000);
		system("cls");
		displayLogin(staff, student, schoolyear);
		break;
	default:
		gotoXY(31, 22); cout << "Invalid input.";
		gotoXY(31, 23); cout << "Try again in 3...";
		Sleep(1000);
		gotoXY(31, 23); cout << "Try again in 2...";
		Sleep(1000);
		gotoXY(31, 23); cout << "Try again in 1...";
		Sleep(1000);
		system("cls");
		displayLoginStaff(staff, student, schoolyear);
		break;
	}
}

void displayStaffProfile(Staff* staff) {
	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(rand() % 15 + 1);
	gotoXY(47, 9); cout << "PROFILE";
	Textcolor(7);
	staff = nullptr;
	getDataStaff(staff, "Staff.csv");
	while (staff && staff->staffAccount != g_account)
		staff = staff->pNext;
	if (staff) {
		gotoXY(31, 12); cout << "Name: " << staff->nameStaff;
		gotoXY(31, 14); cout << "Account: " << staff->staffAccount;
		gotoXY(31, 16); cout << "Password: " << staff->staffPassword;
		gotoXY(31, 20); cout << "Press any key to return...";
	}
	else {
		gotoXY(31, 12); cout << "Staff not found!";
	}
}

