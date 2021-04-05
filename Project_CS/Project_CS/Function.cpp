#include "Header.h"


	void getData(Staff* &pHead, string filename) {
	ifstream in;
	char t;
	in.open(filename);
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
			getline(in, nameStaff, '_');
			getline(in, staffAccount, '_');
			getline(in, staffPassword, '_');
			pCur->nameStaff = nameStaff;
			pCur->staffAccount = staffAccount;
			pCur->staffPassword = staffPassword;
			pCur->pNext = nullptr;
		}
		in.close();
	}
	else cout << "ERROR \n";
}
void display(Staff* pHead) {
	while (pHead) {
		cout << "Name: " << pHead->nameStaff << endl;
		cout << "Account " << pHead->staffAccount << endl;
		cout << "Password " << pHead->staffPassword << endl;
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


