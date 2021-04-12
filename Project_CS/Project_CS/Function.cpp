#include "Header.h"

void getDataStaff(Staff* &pHead, string filename) {
	ifstream in;
	string t;
	in.open(filename);
	getline(in, t, '\n');
	if (in.is_open()) {
		string nameStaff, staffAccount, staffPassword = "staff";
		/*char tmp;*/
		Staff* pCur = pHead;
		while (!in.eof()) {
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
	cout << "\n\t\t\t\tPlease input the School year you want to add (2xxx_2xxx): ";
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
bool loginStaff(Staff* staff, string& account) {
	cout << "\n\n\n\n\t\t\t\tAccount: ";
	string password;
	fflush(stdin);
	getline(cin, account);
	cout << "\n\n\t\t\t\tPassword: ";
	fflush(stdin);
	getline(cin, password);
	while (staff && staff->staffAccount != account) {
		staff = staff->pNext;
	}
	if (staff) {
		if (password == staff->staffPassword) return true;
		else return false;
	}
	return false;
}


void changePassStaff(Staff*& staff, SchoolYear *schoolyear, string account) {
	cout << "\n\t\t\t\t\tPASSWORD CHANGING\n";
	cout << "\n\t\t\t\tEnter your old password: ";
	string oldPass;
	getline(cin, oldPass, '\n');

	Staff* temp = staff;
	while (temp && temp->staffAccount != account)
		temp = temp->pNext;

	while (oldPass == temp->staffPassword) {
		cout << "\n\t\t\t\tEnter your new password: ";
		string tempPass, newPass;
		getline(cin, tempPass, '\n');

		cout << "\n\t\t\t\tEnter your new password again: ";
		getline(cin, newPass, '\n'); 

		if (tempPass == newPass) {
			cout << "\n\t\t\t\tLoading...\n";
			Sleep(3000);
			cout << "\n\t\t\t\tYour password has been changed successfully!\n";
			temp->staffPassword = newPass;
			cout << "\n\t\t\t\tPress any key to return back to the previous page...";
			_getch();
			system("cls");
			displayLoginStaff(staff, schoolyear, account);
			return;
		}

		cout << "\n\t\t\t\tYour two inputs are not the same. Do you want to insert again?\n\t\t\t\t(y/n): ";
		char choice; cin >> choice; cin.ignore();
		if (choice == 'n' || choice == 'N') {
			cout << "\n\t\t\t\tLoading...\n";
			Sleep(2000);
			system("cls");
			displayLoginStaff(staff, schoolyear, account);
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
		displayLoginStaff(staff, schoolyear, account);
		return;
	}
	else {
		system("cls");
		changePassStaff(staff, schoolyear, account);
	}
}


