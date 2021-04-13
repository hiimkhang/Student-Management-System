#include "Header.h"
void getDataClass(SchoolYear*& Schoolyear) {
	ifstream in;
	Class* pCur = Schoolyear->classes;
	string filename = Schoolyear->year + "_classes.txt";
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
	}
	else cout << "ERROR\n";
}
