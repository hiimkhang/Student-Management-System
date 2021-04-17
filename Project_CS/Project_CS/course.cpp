#include "header.h"

void getDataCourse(Course*& head, string path) {
	ifstream in;
	string t;
	in.open(path);
	getline(in, t, '\n');
	if (in.is_open()) {
		string courseName, teacherName, courseID;
		int creditNum;
		Course* pCur = head;
		for (int i = 1; i <= numberOfLine(path) - 1; i++) {
			if (head == nullptr) {
				head = new Course;
				pCur = head;
			}
			else {
				pCur->pNext = new Course;
				pCur = pCur->pNext;
			}
			getline(in, courseID, ',');
			getline(in, courseName, ',');
			getline(in, teacherName, ',');
			in >> creditNum;

			pCur->courseID = courseID;
			pCur->courseName = courseName;
			pCur->teacherName = teacherName;
			pCur->creditNum = creditNum;
			pCur->pNext = nullptr;
		}
		in.close();
	}
	else cout << "\n\t\t\t\tERROR \n";
}

void displayCourse(Course* head) {
	cout << "\n\n\n\n\n\t\t\t\t1. View all courses\n";
	cout << "\n\n\n\n\n\t\t\t\t2. Enroll a course/ courses: \n";
	cout << "\n\n\n\n\n\t\t\t\t3. Exit\n";
	cout << "\n\n\n\n\n\t\t\t\t1. Please enter an option you want to choose: \n";
	string choice, courseID;
	Course* pCur = head;
	cin >> choice;
	if (choice == "1") {
		while (head != nullptr) {
			cout << pCur->courseID;
			cout << pCur->courseName;
			cout << pCur->teacherName;
			cout << pCur->creditNum << "\n\n\n";
		}
		cout << "Press any key to exit";
		system("pause");
		system("cls");
		displayCourse(head);
	}
	//if (choice == "2") {
	//	pCur = head;
	//	cout << "\n\n\n\n\n\t\t\t\tPlease enter the course ID that you want to enroll: ";
	//	getline(cin, courseID);
	//	while (pCur->courseID != courseID && pCur!=nullptr) {
	//		pCur = pCur->pNext;
	//	}
	//	if (pCur != nullptr && pCur->courseID = courseID) {

	//	}
	//}
}
//void updateCourse(Course*& head) {
//
//	Course* pCur = head;
//	while (pCur != nullptr) {
//		pCur = pCur->pNext;
//	}
//	pCur = new Course;
//	out.open("course.csv")
//		if (out) {
//
//		}
//}