#include "header.h"
//extern string z;

void createSemester(ifstream in, ofstream out, Semester* semester, string path) {
	out.open(path);
	if (out) {
		//int no;
		string start_date, end_date, name, register_start_date, register_end_date;
		out << "\n\t\t\t\tThis is for 1st, 2nd or 3rd semester? ";
		cin >> semester->no;
		while (semester->no > 0 && semester->no < 4) {
			out << "\n\t\t\t\tError. Please input again: ";
			in >> semester->no;
		}
		getline(cin, name);
		out << name << endl;
		getline(cin, start_date);
		out << start_date << endl;
		getline(cin, end_date);
		out << end_date << endl;
		getline(cin, register_start_date);
		out << register_start_date << endl;
		getline(cin, register_end_date);
		out << register_end_date << endl;
		out.close();
	}
	else cout << "\n\t\t\t\tERROR";
}