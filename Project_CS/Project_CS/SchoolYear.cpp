#pragma once
#include "_SchoolYear.h"

extern string g_account;
extern int g_ID;
extern string g_selectyear;
extern int g_selectSemester;
extern string g_selectClass;
extern string g_selectCourse;
extern string g_Time;

void getDataSchoolYear(SchoolYear*& pHead, string path) {
    ifstream in;
    string t;
    in.open(path);
    if (in.is_open()) {
        string year;
        SchoolYear* pCur = pHead;
        while (!in.eof()) {
            if (pHead == nullptr) {
                pHead = new SchoolYear;
                pCur = pHead;
            }
            else {
                pCur->pNext = new SchoolYear;
                pCur = pCur->pNext;
            }
            getline(in, year, '\n');
            pCur->year = year;
            pCur->pNext = nullptr;
        }
        in.close();
    }
    else cout << "\n";
}

void createNewYear(SchoolYear*& year_school) {
    ofstream out;
    out.open("school_year.txt", ios::app);

    cout << "\n\t\t\t\tEnter school year (2xxx_2xxx): ";
    string y;
    getline(cin, y, '\n');

    bool checkYear = false;
    for (int i = 0; i < y.size(); ++i) {
        if (y[i] == '_') checkYear = true;
    }
    while (!checkYear) {
        cout << "\n\t\t\t\tInvalid, please enter school year again (2xxx_2xxx): ";
        getline(cin, y, '\n');
        for (int i = 0; i < y.size(); ++i) 
            if (y[i] == '_') checkYear = true;
    }
    year_school = nullptr;
    getDataSchoolYear(year_school, "school_year.txt");
    SchoolYear* pCur1 = year_school;
    while (pCur1 != nullptr) {
        if (pCur1->year == y) {
            cout << "\n\t\t\t\tThis year already exists.";
            Sleep(2000);
            return;
        }
        pCur1 = pCur1->pNext;
    }
    cout << "\n\n\t\t\t\tLoading...\n";
    Sleep(2000);
    cout << "\n\t\t\t\tAdded.\n";
    cout << "\n\t\t\t\tPress any key to return to previous page...";
    _getch();
    out << y << endl;
}

void displayYear(SchoolYear* pHead) {
    int y = 10;
    pHead = nullptr;
    getDataSchoolYear(pHead, "school_year.txt");
    if (g_Time != "") {
        gotoXY(26, 4); cout << "Date: " << g_Time;
    }
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(Blue);
    gotoXY(46, 8); cout << "SCHOOL YEAR";
    Textcolor(7);
    gotoXY(34, 10); cout << "List of school year: ";
    if (pHead) {
        gotoXY(56, y); cout << pHead->year;
        pHead = pHead->pNext;
        y++;
    }
    while (pHead) {
        gotoXY(56, y); cout << pHead->year;
        pHead = pHead->pNext;
        y++;
    }
    cout << endl;
}

void displaySchoolYearForStaff(Staff* staff, Student* student, SchoolYear*& schoolyear) {
    setConsoleWindow(800, 700);
    displayYear(schoolyear);
    cout << "\n\n\n\n\n\t\t\t\t1. Create new school year\n";
    cout << "\n\t\t\t\t2. Access into a school year\n";
    cout << "\n\t\t\t\t3. Exit\n";
    cout << "\n\n\t\t\t\t" << char(26) << " Enter your choice: ";
    string year;
    char choice = getchar();
    cin.ignore(100, '\n');
    schoolyear = nullptr;
    getDataSchoolYear(schoolyear, "school_year.txt");
    SchoolYear* pCur = schoolyear;
    switch (choice) {
    case '1':
        createNewYear(schoolyear);
        system("cls");
        displayYear(schoolyear);
        displaySchoolYearForStaff(staff, student, schoolyear);
        break;
    case '2':
        cout << "\n\t\t\t\t" << char(26) << " Enter the schoolyear (ex: 2020_2021): ";
        getline(cin, year, '\n');
        while (pCur && pCur->year != year) {
            pCur = pCur->pNext;
        }
        if (pCur != nullptr) {
            g_selectyear = year;
            system("cls");
            displaySelectedYearForStaff(staff, student, schoolyear);
        }
        else {
            cout << "\n\t\t\t\tSchool year " << year << " doesn't exist";
            Sleep(2000);
            system("cls");
            displaySchoolYearForStaff(staff, student, schoolyear);
        }
        break;
    case '3':
        system("cls");
        displayLoginStaff(staff, student, schoolyear);
        break;
    default:
        cout << "\n\t\t\t\tInvalid input, try again...";
        Sleep(1500);
        system("cls");
        displaySchoolYearForStaff(staff, student, schoolyear);
        break;
    }
}

void displaySchoolYearForStudent(Staff* staff, Student* student, SchoolYear*& schoolyear) {
    displayYear(schoolyear);
    cout << "\n\t\t\t\t1. Access into a school year\n";
    cout << "\n\t\t\t\t2. Exit\n";
    cout << "\n\n\t\t\t\t" << char(26) << " Enter your choice: ";
    string year;
    char choice = getchar();
    cin.ignore(100, '\n');
    SchoolYear* pCur = schoolyear;
    switch (choice) {
    case '1':
        cout << "\n\t\t\t\tEnter schoolyear (ex: 2020_2021): ";
        getline(cin, year, '\n');
        while (pCur && pCur->year != year) {
            pCur = pCur->pNext;
        }
        if (pCur != nullptr) {
            g_selectyear = year;
            system("cls");
            displaySelectedYearForStudent(staff, student, schoolyear);
        }
        else {
            cout << "\n\t\t\t\tSchool year " << year << " doesn't exist.";
            Sleep(2000);
            system("cls");
            displaySchoolYearForStudent(staff, student, schoolyear);
        }
        break;
    case '2':
        system("cls");
        displayLoginStudent(staff, student, schoolyear);
        break;
    default:
        cout << "\n\t\t\t\tInvalid input, try again...";
        Sleep(1500);
        system("cls");
        displaySchoolYearForStudent(staff, student, schoolyear);
        break;
    }
}

string displaySelectedYearForStaff(Staff* staff, Student* student, SchoolYear* schoolyear) {
    setConsoleWindow(800, 600);
    string choice1;
    if (g_Time != "") {
        gotoXY(26, 4); cout << "Date: " << g_Time;
    }
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(Blue);
    gotoXY(38, 8); cout << "SCHOOL YEAR: " << g_selectyear;
    Textcolor(7);
    gotoXY(31, 14); cout << "1. Semester";
    gotoXY(31, 16); cout << "2. Class";
    gotoXY(31, 18); cout << "3. Exit";
    gotoXY(31, 20); cout << char(26) << " Enter your choice: ";

    while (schoolyear && schoolyear->year != g_selectyear)
        schoolyear = schoolyear->pNext;

    cin >> choice1; cin.ignore();
    if (choice1 == "1") {
        system("cls");
        if (schoolyear)
            displaySemester(schoolyear->staff, student, schoolyear);
    }
    else if (choice1 == "2") {
        system("cls");
        if (schoolyear)
            displayMenuClass(schoolyear->staff, student, schoolyear);
    }
    else if (choice1 == "3") {
        gotoXY(40, 22); cout << "Loading...";
        Sleep(2000);
        system("cls");
        displayYear(schoolyear);
        displaySchoolYearForStaff(staff, student, schoolyear);
    }
    else {
        gotoXY(31, 22); cout << "Invalid input.";
        gotoXY(31, 23); cout << "Try again in 2...";
        Sleep(1000);
        gotoXY(31, 23); cout << "Try again in 1...";
        Sleep(1000);
        system("cls");
        displaySelectedYearForStaff(staff, student, schoolyear);
    }
    return choice1;
}

string displaySelectedYearForStudent(Staff* staff, Student* student, SchoolYear* schoolyear) {
    string choice1;
    if (g_Time != "") {
        gotoXY(26, 4); cout << "Date: " << g_Time;
    }
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(Blue);
    gotoXY(38, 8); cout << "SCHOOL YEAR: " << g_selectyear;
    Textcolor(7);
    gotoXY(31, 16); cout << "1. Semester";
    gotoXY(31, 18); cout << "2. Exit";
    gotoXY(31, 20); cout << char(26) << " Enter your choice: ";

    while (schoolyear && schoolyear->year != g_selectyear)
        schoolyear = schoolyear->pNext;

    cin >> choice1; cin.ignore();
    if (choice1 == "1") {
        system("cls");
        displaySemesterForStudent(staff, student, schoolyear);
    }
    else if (choice1 == "2") {
        gotoXY(40, 22); cout << "Loading...";
        Sleep(2000);
        system("cls");
        displayYear(schoolyear);
        displaySchoolYearForStudent(staff, student, schoolyear);
    }
    else {
        gotoXY(31, 22); cout << "Invalid input.";
        gotoXY(31, 23); cout << "Try again in 2...";
        Sleep(1000);
        gotoXY(31, 23); cout << "Try again in 1...";
        Sleep(1000);
        system("cls");
        displaySelectedYearForStudent(staff, student, schoolyear);
    }
    return choice1;
}