#include "Header.h"

int main() {
	// load data
	Staff* staff = nullptr;
	YearSchool* yearSchool = nullptr;
	getDataStaff(staff, "Staff.csv");
	getDataYearSchool(yearSchool, "year_school.txt");
	char choose;
	string str;
	do {
		cout << "a. Staff \n";
		cout << "b. Student \n";
		cout << "c. Exit \n";
		cout << "Please input: ";
		cin >> choose;
		if (choose == 'c') {
			system("cls");
			cout << "See you later! \n"; 
			break;
		}
		else if (choose == 'a') {
			system("cls");
			do {
				cout << "a. Login \n";
				cout << "b. Exit \n";
				cout << "Please input: ";
				cin >> choose;
				system("cls");
				if (choose == 'b') break;
				else if (choose == 'a') {
					cin.ignore();
					if (loginStaff(staff) == true) {
						do {
							cout << "a. School year \n";
							cout << "b. View profile \n";
							cout << "c. Change password \n";
							cout << "d. Log out \n";
							cout << "Please input: ";
							cin >> choose;
							system("cls");
							if (choose == 'd') break;
							else if (choose == 'a') {
								do {
									displayYear(yearSchool);
									cout << "a. Create new year \n";
									cout << "b. Exit \n";
									cout << "Please input the year (or press a/b): ";
									cin >> str;
									if (str == "b") break;
									else if (str == "a") {
										
									}
									else if (str == "year.name") {
										do {
											cout << "a. Semester \n";
											cout << "b. Student \n";
											cout << "c. Exit \n";
											cout << "Please input: ";
											cin >> choose;
											if (choose == 'c') break;
											else if (choose == 'a') {

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
									else {
										cout << "Error input \n";
										cout << "Please input again: ";
										cin >> str;
									}
								} while (str != "a" && str != "b" ); // nam ko co trong danh sach
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
					else {
						//dang nhap lai
					}
				}
				else {
					cout << "Please input a or b: \n";
				}
			} while (choose != 'b');
		}
		else if (choose == 'b') {

		}
		else {
			cout << "Please input a or b or c! \n";
		}
	} while (choose != 'c');
}
	/*Staff* pHead=nullptr;
	getData(pHead, "Staff.csv");
	display(pHead);
	cout << loginStaff(pHead);
	deleteList(pHead);*/
