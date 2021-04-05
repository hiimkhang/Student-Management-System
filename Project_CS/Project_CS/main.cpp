#include "Header.h"

int main() {
	// load data
	char choose;
	string str;
	do {
		cout << "a. Staff \n";
		cout << "b. Student \n";
		cout << "c. Exit \n";
		cout << "Please input: ";
		cin >> choose;
		if (choose == 'c') {
			cout << "See you later! \n";
			break;
		}
		else if (choose == 'a') {
			do {
				cout << "a. School year \n";
				cout << "b. View profile \n";
				cout << "c. Change password \n";
				cout << "d. Log out \n";
				cout << "Please input: ";
				cin >> choose;
				if (choose == 'd') break;
				else if (choose == 'a') {
					do {
						//cout << danh sach cac nam;
						cout << "a. Create new year \n";
						cout << "b. Exit \n";
						cout << "Please input the year (or press a/b): ";
						cin >> str;
						if (str == "b") break;
						else if (str == "a") {
							do {
								cout << "a. Semester \n";
								cout << "b. Student \n";
								cout << "c. Exit \n";
								cout << "Please input: ";
								cin >> choose;
								if (choose == 'c') break;
								else if (choose == 'a') {
									//cout << danh sach cac hoc ki
									cout << "a. Create new semester \n";
									cout << "b. Exit \n";
									cout << "Please input the semester (or press a/b): ";
									cin >> str;
									if (str == "")
								}
								else if (choose == 'b') {

								}
								else {
									cout << "Please input a or b or c! \n";
									cout << "Please input: ";
									cin >> choose;
								}
							} while (choose != 'a' && choose != 'b' && choose != 'c');
						}
						else if (str == "year.name") {

						}
						else {
							cout << "Error input \n";
							cout << "Please input again: ";
							cin >> str;
						}
					} while (str != "a" && str != "b" && nam ko co trong list);
				}
				else if (choose == 'b') {

				}
				else if (choose == 'c') {

				}
				else {
					cout << "Please input a or b or c or d! \n";
					cout << "Please input: ";
					cin >> choose;
				}
			} while (choose != 'a' && choose != 'b' && choose != 'c' && choose != 'd');
		}
		else if (choose == 'b') {

		}
		else {
			cout << "Please input a or b or c! \n";
			cout << "Please input: ";
			cin >> choose;
		}
	} while (choose != 'a' && choose != 'b' && choose != 'c');
}