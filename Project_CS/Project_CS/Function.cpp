#include "Header.h"


void getDataStaff(Staff* &pHead, string filename) {
	ifstream in;
	string t;
	in.open(filename);
	getline(in, t, '\n');
	if (in) {
		string nameStaff, staffAccount, staffPassword = "staff";
		char tmp;
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

void getDataYearSchool(YearSchool*& pHead, string path) {
	ifstream in;
	string t;
	in.open(path);
	if (in) {
		string year;
		YearSchool* pCur = pHead;
		while (!in.eof()) {
			if (pHead == nullptr) {
				pHead = new YearSchool;
				pCur = pHead;
			}
			else {
				pCur->pNext = new YearSchool;
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

void createNewYear(YearSchool*& year_school) {
	cout << "Please input name of year: ";
	string y;
	getline(cin, y);
	YearSchool* pCur = year_school;
	while (pCur->pNext != nullptr) {
		pCur = pCur->pNext;
	}
	pCur->pNext = new YearSchool;
	pCur->pNext->year = y;
	pCur->pNext->pNext = nullptr;

}

void displayYear(YearSchool* pHead) {
	while (pHead) {
		cout << pHead->year << endl;
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
bool loginStaff(Staff*& staff) {
	cout << "Your account: ";
	string account, password;
	getline(cin, account);
	cout << "Your password: ";
	getline(cin, password);
	while (staff != nullptr && staff->staffAccount != account) {
		staff = staff->pNext;
	}
	if (staff != nullptr) {
		if (password == staff->staffPassword) return true;
		else return false;
	}
	else return false;
}


