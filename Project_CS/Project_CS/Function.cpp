#include "Header.h"


	void getData(Staff * &pHead, string filename) {
	ifstream in;
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
		cout << "Account" << pHead->staffAccount << endl;
		cout << "Password" << pHead->staffPassword << endl;

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


