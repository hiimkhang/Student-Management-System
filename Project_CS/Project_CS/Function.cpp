#include "Header.h"


void getDataStaff(Staff* &pHead, string filename) {
	ifstream in;
	string t;
	in.open(filename);
	getline(in, t, '\n');
	if (in) {
		string nameStaff, staffAccount, staffPassword = "staff";
		//char tmp;
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
	if (in) {
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
	else cout << "ERROR \n";
}

void createNewYear(SchoolYear*& year_school) {
	cout << "\n\t\tPlease input the School year you want to add (2xxx_2xxx): ";
	string y;
	getline(cin, y);
	SchoolYear* pCur = year_school;
	while (pCur->pNext != nullptr) {
		pCur = pCur->pNext;
	}
	pCur->pNext = new SchoolYear;
	pCur->pNext->year = y;
	pCur->pNext->pNext = nullptr;

}

void displayYear(SchoolYear* pHead) {
	cout << "\n\t\t List of school year:\n";
	while (pHead) {
		cout << "\t\t" << pHead->year << endl;
		pHead = pHead->pNext;
	}
}
void deleteList(Staff*& pHead) {
	Staff *pCur = pHead;
	while (pHead) {
		pHead = pHead->pNext;
		delete pCur;
		pCur = pHead;
	}
}
bool loginStaff(Staff* staff) {
	cout << "Your account: ";
	string account, password;
	getline(cin, account);
	cout << "Your password: ";
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


