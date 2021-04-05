#include "Header.h"

int main() {
	// load data
	char choice;
	string str;
	do {
		cout << "a. Staff \n";
		cout << "b. Student \n";
		cout << "c. Exit \n";
		cout << "Please input: ";
		cin >> choice;
		switch (choice) {
		case 'c':
			cout << "See you later! \n";
			break;

		case'a':
			do {
				cout << "a. Login\n";
				cout << "b. Exit\n";
				cout << "Please input your option: ";
				cin >> choice;
				switch (choice) {
				case 'a':
					// Implement function here;
					loginStaff(staff);
					break;
				case 'b':
					cout << "See you later!\n";
				default:
					cout << "Invalid input, please input again";
					break;
				}
				do {
					cout << "a. School year \n";
					cout << "b. View profile \n";
					cout << "c. Change password \n";
					cout << "d. Log out \n";
					cout << "Please input: ";
					cin >> choice;
					if (choice == 'd') break;
					else if (choice == 'a') {
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
											cin >> choice;
										if (choice == 'c') break;
										else if (choice == 'a') {

										}
										else if (choice == 'b') {

										}
										else {
											cout << "Please input a or b or c! \n";
											cout << "Please input: ";
											cin >> choice;
										}
									} while (choice != 'a' && choice != 'b' && choice != 'c');
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
					else if (choice == 'b') {

					}
					else if (choice == 'c') {

					}
					else {
						cout << "Please input a or b or c or d! \n";
						cout << "Please input: ";
						cin >> choice;
					}
					} while (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd');
				}
		else if (choice == 'b') {

		}
		else {
		cout << "Please input a or b or c! \n";
		cout << "Please input: ";
		cin >> choice;
		}
			}
		} while (choice != 'a' && choice != 'b' && choice != 'c');
	}