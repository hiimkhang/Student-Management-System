#include "Header.h"

int main() {
	// load data
	Staff* staff = nullptr;
	SchoolYear* schoolYear = nullptr;
	getDataStaff(staff, "Staff.csv");
	getDataSchoolYear(schoolYear, "school_year.txt");

	displayLogin(staff, schoolYear);

	return 0;
}

//	int choose;
//	string str;
//	do {
//		cout << "1. Staff \n";
//		cout << "2. Student \n";
//		cout << "3. Exit \n";
//		cout << "Input your choice: ";
//		cin >> choose;
//		if (choose == 3) {
//			system("cls");
//			cout << "See you later! \n"; 
//			break;
//		}
//		else if (choose == 1) {
//			system("cls");
//			do {
//				cout << "1. Login \n";
//				cout << "2. Exit \n";
//				cout << "Input your choice: ";
//				cin >> choose;
//				system("cls");
//				if (choose == 2) break;
//				else if (choose == 1) {
//					cin.ignore();
//					if (loginStaff(staff) == true) {
//						do {
//							cout << "1. School year \n";
//							cout << "2. View profile \n";
//							cout << "3. Change password \n";
//							cout << "4. Log out \n";
//							cout << "Please input: ";
//							cin >> choose;
//							system("cls");
//							if (choose == 4) break;
//							else if (choose == 1) {
//								do {
//									displayYear(schoolYear);
//									cout << "1. Create new year \n";
//									cout << "2. Exit \n";
//									cout << "Please input the year (xxxx_xxxx or input your choice): ";
//									cin >> str;
//									if (str == "2") break;
//									else if (str == "1") {
//										/*cout << "Input the schoolyear you want to add (xxxx_xxxx): ";
//										cin >> str;
//										if (str == "year.name")*/
//									}
//									else if (str == "year.name") {
//										do {
//											cout << "1. Semester \n";
//											cout << "2. Student \n";
//											cout << "3. Exit \n";
//											cout << "Please input: ";
//											cin >> choose;
//											if (choose == '3') break;
//											else if (choose == '1') {
//
//											}
//											else if (choose == '2') {
//
//											}
//											else {
//												cout << "Please input 1, 2 or 3! \n";
//												cout << "Please input your choice: ";
//												cin >> choose;
//											}
//										} while (choose != '1' && choose != '2' && choose != '3');
//									}
//									else {
//										cout << "Error input \n";
//										cout << "Please input your choice again: ";
//										cin >> str;
//									}
//								} while (str != "1" && str != "2" ); // nam ko co trong danh sach
//							}
//							else if (choose == '2') {
//
//							}
//							else if (choose == '3') {
//
//							}
//							else {
//								cout << "Please input 1, 2, 3 or 4! \n";
//								cout << "Please input your choice: ";
//								cin >> choose;
//							}
//						} while (choose != '1' && choose != '2' && choose != '3' && choose != '4');
//					}
//					else {
//						//dang nhap lai
//					}
//				}
//				else {
//					cout << "Please input 1 or 2: \n";
//				}
//			} while (choose != '2');
//		}
//		else if (choose == '2') {
//
//		}
//		else {
//			cout << "Please input 1, 2 or 3! \n";
//		}
//	} while (choose != '3');
//}
	/*Staff* pHead=nullptr;
	getData(pHead, "Staff.csv");
	display(pHead);
	cout << loginStaff(pHead);
	deleteList(pHead);*/
