#pragma once
#include "_Student.h"

extern string g_account;
extern int g_ID;
extern string g_selectyear;
extern int g_selectSemester;
extern string g_selectClass;
extern string g_selectCourse;
extern string g_Time;

void getDataStudent(Student*& pHead, string filename) {
	pHead = nullptr;
	ifstream in;
	string t;
	in.open(filename);
	getline(in, t, '\n');
	if (in.is_open()) {
		string Firstname, Lastname, Gender, studentPassword, studentClass, DoB;
		int StudentID;
		long SocialID;
		Student* pCur = pHead;
		for (int i = 1; i <= numberOfLine(filename) - 1; i++) {
			if (pHead == nullptr) {
				pHead = new Student;
				pCur = pHead;
			}
			else {
				pCur->pNext = new Student;
				pCur = pCur->pNext;
			}
			in >> StudentID;
			char z;
			in >> z;
			getline(in, Firstname, ',');
			getline(in, Lastname, ',');
			getline(in, Gender, ',');
			getline(in, DoB, ',');
			getline(in, studentClass, ',');
			in >> SocialID;
			in >> z;
			getline(in, studentPassword, '\n');

			pCur->StudentID = StudentID;
			pCur->Firstname = Firstname;
			pCur->Lastname = Lastname;
			pCur->Gender = Gender;
			pCur->DoB = DoB;
			pCur->studentClass = studentClass;
			pCur->SocialID = SocialID;
			pCur->studentPassword = studentPassword;
			pCur->pNext = nullptr;
		}
		in.close();
	}
	else {
		gotoXY(31, 25);
		cout << "Unable to open file student.csv directory, can not get data.";
	}
}

void inputStudent() {
	cout << "\n\n\t\tPlease input the link of your csv.file (Ex:C:\\DocumentsClass\\20CTT1.csv):\n\t\t";
	string s;
	getline(cin, s);
	ifstream in;
	ofstream out;
	string t;
	in.open(s);
	if (in) {
		getline(in, t);
		out.open("Student.csv", ios::app);
		for (int i = 1; i <= numberOfLine(s) - 1; i++) {
			getline(in, t);
			out << t << endl;
		}
		out.close();
		in.close();
	}
	else {
		cout << "\n\n\t\tCan not open " << s;
		Sleep(2000);
	}
	in.open(s);
	if (in) {
		getline(in, t);
		out.open(g_selectyear + "_" + g_selectClass + ".csv", ios::app);
		for (int i = 1; i <= numberOfLine(s) - 1; i++) {
			getline(in, t);
			out << t << endl;
		}
		out.close();
		in.close();
		cout << "\t\tUpdate students from csv file successfully!";
		Sleep(2000);
	}
	else {
		cout << "\n\n\t\tCan not open " << s;
		Sleep(2000);
	}
}

void updateStudentResult(SchoolYear* schoolyear) {
	viewScore(schoolyear);
	cout << "\t\t\t\tInput student ID that need to be changed: ";
	string id;
	getline(cin, id);
	ifstream in; ofstream out;
	in.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_score.csv");
	string str;
	out.open("scoretemp.csv");
	getline(in, str);
	out << str << endl;
	for (int i = 1; i <= numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_score.csv") - 1; i++) {
		getline(in, str, ',');
		out << str << ",";
		getline(in, str, ',');
		if (str == id) {
			out << str << ',';
			getline(in, str, ',');
			out << str << ",";
			cout << str << ": \n";
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, '\n');
			string total, final, midterm, other;
			cout << "\n\t\t\t\tTotal mark: ";
			cin >> total;
			out << total << ",";
			cout << "\n\t\t\t\tFinal mark: ";
			cin >> final;
			out << final << ",";
			cout << "\n\t\t\t\tMidterm mark: ";
			cin >> midterm;
			out << midterm << ",";
			cout << "\n\t\t\t\tOther mark: ";
			cin >> other; cin.ignore();
			out << other << "\n";
		}
		else {
			out << str << ",";
			getline(in, str, ',');
			out << str << ",";
			getline(in, str, ',');
			out << str << ",";
			getline(in, str, ',');
			out << str << ",";
			getline(in, str, ',');
			out << str << ",";
			getline(in, str, '\n');
			out << str << "\n";
		}
	}
	out.close();
	in.close();
	remove((g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_score.csv").c_str());
	rename("scoretemp.csv", (g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_score.csv").c_str());
	cout << "da update \n";
	viewScore(schoolyear);
}

bool checkEnroll() {
	string str;
	string day, time;
	string Day[2], Time[2];
	ifstream in;
	in.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv");
	getline(in, str);
	for (int i = 1; i <= numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv") - 1; i++) {
		getline(in, str, ',');
		getline(in, str, ',');
		if (str == g_selectCourse) {
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, day, ',');
			getline(in, time, '\n');
			break;
		}
		else {
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, ',');
			getline(in, str, '\n');
		}
	}
	int temp = 0;
	for (unsigned int i = 0; i < day.size(); i++) {
		if (day[i] == ' ' || day[i] == '&') {
			temp = 1;
			while (day[i] == ' ' || day[i] == '&') {
				i++;
			}
		}
		if (temp == 0) Day[0].push_back(day[i]);
		else Day[1].push_back(day[i]);
	}
	temp = 0;
	for (unsigned int i = 0; i < time.size(); i++) {
		if (time[i] == ' ' || time[i] == '&') {
			temp = 1;
			while (time[i] == ' ' || time[i] == '&') {
				i++;
			}
		}
		if (temp == 0) Time[0].push_back(time[i]);
		else Time[1].push_back(time[i]);
	}
	in.close();
	string Day1[2], Time1[2];
	in.open(to_string(g_ID) + "_Course.csv");
	if (numberOfLine(to_string(g_ID) + "_Course.csv") == 6) return false;
	getline(in, str);
	for (int i = 1; i <= numberOfLine(to_string(g_ID) + "_Course.csv") - 1; i++) {
		getline(in, str, ',');
		getline(in, str, ',');
		getline(in, str, ',');
		getline(in, str, ',');
		getline(in, str, ',');
		getline(in, str, ',');
		temp = 0;
		for (unsigned int i = 0; i < str.size(); i++) {
			if (str[i] == ' ' || str[i] == '&') {
				temp = 1;
				while (str[i] == ' ' || str[i] == '&') {
					i++;
				}
			}
			if (temp == 0) Day1[0].push_back(str[i]);
			else Day1[1].push_back(str[i]);
		}
		getline(in, str);
		temp = 0;
		for (unsigned int i = 0; i < str.size(); i++) {
			if (str[i] == ' ' || str[i] == '&') {
				temp = 1;
				while (str[i] == ' ' || str[i] == '&') {
					i++;
				}
			}
			if (temp == 0) Time1[0].push_back(str[i]);
			else Time1[1].push_back(str[i]);
		}

		if (Day1[0] == Day[0] || Day1[1] == Day[1]) {
			if (Day1[0] == Day[0] && Day1[1] != Day[0]) {
				if (Time1[0] == Time[0]) return false;
			}
			else if (Day1[1] == Day[1] && Day1[0] != Day[0]) {
				if (Time1[1] == Time[1]) return false;
			}
			else {
				if (Time1[0] == Time[0]) return false;
				if (Time1[1] == Time[1]) return false;
			}
		}
		Day1[0] = "";
		Day1[1] = "";
		Time1[0] = "";
		Time1[1] = "";
	}
	in.close();
	return true;
}

void enroll() {
	Student* student = nullptr;
	ofstream out;
	ifstream in;
	out.open(to_string(g_ID) + "_Course.csv", ios::app);
	if (numberOfLine(to_string(g_ID) + "_Course.csv") == 0) {
		out << "Course name, Course ID, credits, teacher name, number of students, day, time\n";
	}
	out.close();
	if (checkEnroll() == true) {
		out.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_student.csv", ios::app);
		if (numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + "_Course_" + g_selectCourse + "_student.csv") == 0) {
			out << "studentID, First Name, Last Name, Gender, Dob, studentClass, SocialID, studentPassword\n";
		}
		getDataStudent(student, "Student.csv");
		while (student != nullptr && student->StudentID != g_ID) {
			student = student->pNext;
		}
		out << student->StudentID << ",";
		out << student->Firstname << ",";
		out << student->Lastname << ",";
		out << student->Gender << ",";
		out << student->DoB << ",";
		out << student->studentClass << ",";
		out << student->SocialID << ",";
		out << student->studentPassword << "\n";
		out.close();
		string str;
		out.open(to_string(g_ID) + "_Course.csv", ios::app);
		in.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv");
		getline(in, str);
		string q, w;
		for (int i = 1; i <= numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv") - 1; i++) {
			getline(in, str, ',');
			q = str;
			getline(in, str, ',');
			w = str;
			if (str == g_selectCourse) {
				out << q << ",";
				out << w << ",";
				getline(in, str, ',');
				out << str << ",";
				getline(in, str, ',');
				out << str << ",";
				getline(in, str, ',');
				out << str << ",";
				getline(in, str, ',');
				out << str << ",";
				getline(in, str, '\n');
				out << str << "\n";
				break;
			}
			else {
				getline(in, str, ',');
				getline(in, str, ',');
				getline(in, str, ',');
				getline(in, str, ',');
				getline(in, str, '\n');
			}
		}
		in.close();
		out.close();
		cout << "\n\n\n\n\n\t\t\t\t             Enroll successfully!";
	}
	else {
		cout << "\n\n\n\n\n\t\t\t\t             Unable to enroll!";
	}
}

void changePassStudent(Staff* staff, Student*& student, SchoolYear* schoolyear, string path) {
	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(Blue);
	gotoXY(44, 9); cout << "PASSWORD CHANGING";
	Textcolor(7);
	gotoXY(32, 14); cout << "Enter your old password: ";
	string oldPass;
	string str;
	getline(cin, oldPass, '\n');

	Student* pCur = student;
	while (pCur && pCur->StudentID != g_ID) {
		pCur = pCur->pNext;
	}

	while (pCur && oldPass == pCur->studentPassword) {
		cout << "\n\n\t\t\t\tEnter your new password: ";
		string tempPass, newPass;
		getline(cin, tempPass, '\n');

		cout << "\n\n\t\t\t\tEnter your new password again: ";
		getline(cin, newPass, '\n');

		if (tempPass == newPass) {
			cout << "\n\n\t\t\t\tLoading...";
			Sleep(3000);
			pCur->studentPassword = newPass;
			ifstream in;
			ofstream out;
			in.open(path);
			if (in) {
				out.open("tempStudent.csv");
				getline(in, str, '\n');
				out << str << endl;
				for (int i = 1; i <= numberOfLine(path) - 1; i++) {
					getline(in, str, ',');
					if (str != to_string(g_ID)) {
						out << str << ",";
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, '\n');
						out << str << "\n";
					}
					else {
						out << str << ",";
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, ',');
						out << str << ",";
						getline(in, str, '\n');
						out << newPass << "\n";
					}
				}
				out.close();
				in.close();
				remove("Student.csv");
				rename("tempStudent.csv", "Student.csv");
			}
			else {
				cout << "ERROR";
			}
			cout << "\n\n\n\t\t\t\tYour password has been changed successfully!\n";
			cout << "\n\n\t\t\t\tPress any key to return back to the previous page...";
			_getch();
			system("cls");
			displayLoginStudent(staff, student, schoolyear);
			return;
		}

		cout << "\n\n\t\t\t\tYour two inputs are not the same.\n\t\t\t\tDo you want to insert again? (y/n): ";
		char choice; cin >> choice; cin.ignore();
		if (choice == 'n' || choice == 'N') {
			cout << "\n\n\t\t\t\tLoading...\n";
			Sleep(2000);
			system("cls");
			displayLoginStudent(staff, student, schoolyear);
			return;
		}
		else {
			system("cls");
			if (g_Time != "") {
				gotoXY(26, 4); cout << "Date: " << g_Time;
			}
			gotoXY(26, 5); cout << "=======================================================";
			Textcolor(Blue);
			gotoXY(44, 9); cout << "PASSWORD CHANGING";
			Textcolor(7);
			gotoXY(32, 14); cout << "Enter your old password: " << oldPass;
			continue;
		}
	}
	cout << "\n\t\t\t\tWrong old password!\n\t\t\t\tDo you want to insert again? (y/n): ";
	char choice; cin >> choice; cin.ignore();
	if (choice == 'n' || choice == 'N') {
		cout << "\n\t\t\t\tLoading...\n";
		Sleep(3000);
		system("cls");
		displayLoginStudent(staff, student, schoolyear);
		return;
	}
	else {
		system("cls");
		changePassStudent(staff, student, schoolyear, path);
	}
}

bool loginStudent(Student* student) {
	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(11);
	gotoXY(50, 9); cout << "LOGIN";
	Textcolor(7);
	gotoXY(31, 12); cout << "Student ID: ";
	int y = 14;
	string password;
	string StudentID;
	bool checkLogin = true;
	getline(cin, StudentID, '\n');
	while (checkLogin) {
		checkLogin = false;
		for (unsigned int i = 0; i < StudentID.size(); ++i) {
			if (StudentID[i] >= 'A' && StudentID[i] <= 'Z'
				&& StudentID[i] >= 'a' && StudentID[i] <= 'z') {
				gotoXY(31, y);  cout << "Student ID must contains only number, try again..";
				Sleep(1500);
				gotoXY(31, y);  cout << "Student ID: ";
				getline(cin, StudentID, '\n');
				y += 2;
				checkLogin = true;
				break;
			}
		}
	}
	gotoXY(31, 14); cout << "Password: ";
	/*cin.ignore();*/
	getline(cin, password);
	while (student && to_string(student->StudentID) != StudentID) {
		student = student->pNext;
	}
	if (student && password == student->studentPassword) {
		g_ID = stoi(StudentID);
		return true;
	}
	return false;
}

void displayLoginStudent(Staff* staff, Student* student, SchoolYear* schoolyear) {
	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(rand() % 15 + 1);
	gotoXY(39, 9); cout << "COURSE REGISTRATION SYSTEM";
	Textcolor(7);
	gotoXY(31, 12); cout << "1. School year";
	gotoXY(31, 14); cout << "2. View and edit profile";
	gotoXY(31, 16); cout << "3. Change password";
	gotoXY(31, 18); cout << "4. Log out";
	gotoXY(31, 20); cout << char(26) << " Enter your choice: ";
	char choice = getchar();
	cin.ignore(100, '\n');
	switch (choice) {
	case '1':
		system("cls");
		displaySchoolYearForStudent(staff, student, schoolyear);
		choice = getchar();
		cin.ignore(100, '\n');
		switch (choice) {
		case '1':
			createNewYear(schoolyear);
			Sleep(2000);
			system("cls");
			displaySchoolYearForStudent(staff, student, schoolyear);
			cin >> choice;
			break;
		case '2':
			system("cls");
			displayLoginStudent(staff, student, schoolyear);
			break;
		}
		break;
	case '2':
		system("cls");
		displayStudentProfile(student, "Student.csv");
		system("cls");
		displayLoginStudent(staff, student, schoolyear);
		break;
	case '3':
		system("cls");
		changePassStudent(staff, student, schoolyear, "Student.csv");
		break;
	case '4':
		gotoXY(31, 23); cout << "Logging out...";
		Sleep(3000);
		system("cls");
		displayLogin(staff, student, schoolyear);
		break;
	default:
		gotoXY(31, 22); cout << "Invalid input.";
		gotoXY(31, 23); cout << "Try again in 3...";
		Sleep(1000);
		gotoXY(31, 23); cout << "Try again in 2...";
		Sleep(1000);
		gotoXY(31, 23); cout << "Try again in 1...";
		Sleep(1000);
		system("cls");
		displayLoginStudent(staff, student, schoolyear);
		break;
	}
}

void displayStudentProfile(Student*& student, string path) {
	if (g_Time != "") {
		gotoXY(26, 4); cout << "Date: " << g_Time;
	}
	gotoXY(26, 5); cout << "=======================================================";
	Textcolor(rand() % 15 + 1);
	gotoXY(47, 9); cout << "PROFILE";
	Textcolor(7);
	student = nullptr;
	getDataStudent(student, "Student.csv");
	Student* pCur = student;

	while (pCur && pCur->StudentID != g_ID)
		pCur = pCur->pNext;
	if (pCur) {
		gotoXY(31, 12); cout << "First name: " << pCur->Firstname;
		gotoXY(31, 14); cout << "Last name: " << pCur->Lastname;
		gotoXY(31, 16); cout << "Gender: " << pCur->Gender;
		gotoXY(31, 18); cout << "Student ID: " << pCur->StudentID;
		gotoXY(31, 20); cout << "Password: " << pCur->studentPassword;
		gotoXY(31, 22); cout << "Date of birth: " << pCur->DoB;
		gotoXY(31, 24); cout << "Social ID: " << pCur->SocialID;

		gotoXY(31, 26); cout << "ESC: Exit";
	}
	else {
		gotoXY(31, 12); cout << "Student not found!";
	}
	string title;
	string Firstname, Lastname, Gender, studentPassword, DoB, studentClass, tempDoB;
	//long SocialID;
	int check = 1;
	ifstream in;
	ofstream out;

	AnTroChuot();

	while (check) {
		if (_kbhit())
		{
			switch (_getch())
			{
			case 27:
				check = 0;
				break;
			}
		}
	}

}
