#pragma once
#include "_Semester.h"

extern string g_account;
extern int g_ID;
extern string g_selectyear;
extern int g_selectSemester;
extern string g_selectClass;
extern string g_selectCourse;
extern string g_Time;

void getDataSemester(SchoolYear*& Schoolyear) {
    Schoolyear->semester = nullptr;
    ifstream in;
    ofstream out;
    Semester* pCur = Schoolyear->semester;
    string filename = g_selectyear + "_semester.txt";
    out.open(filename, ios::app);
    if (out) {
        in.open(filename);
        if (in) {
            for (int i = 1; i <= numberOfLine(filename); i++) {
                if (Schoolyear->semester == nullptr) {
                    Schoolyear->semester = new Semester;
                    pCur = Schoolyear->semester;
                }
                else {
                    pCur->pNext = new Semester;
                    pCur = pCur->pNext;
                }
                in >> pCur->no;
                char c;
                in >> c;
                getline(in, pCur->start_date, ',');
                getline(in, pCur->end_date, ',');
                getline(in, pCur->register_start_date, ',');
                getline(in, pCur->register_end_date, '\n');
                pCur->pNext = nullptr;
            }
            in.close();
            out.close();
        }
        else cout << "\n\t\t\t\tERROR\n";
    }
}

void createSemester(SchoolYear*& Schoolyear) {
    setConsoleWindow(800, 650);
    getDataSemester(Schoolyear);
    int no;
    string start_date, end_date, register_start_date, register_end_date;
    cout << "\n\t\t\t\t" << char(26) << " Enter semester (1/2/3): ";
    cin >> no; cin.ignore();
    while (!(no > 0 && no < 4)) {
        cout << "\n\t\t\t\tInvalid input\n\t\t\t" << char(26) << " Enter semester (1/2/3): ";
        cin >> no; cin.ignore();
    }

    Semester* pcur = Schoolyear->semester;
    while (pcur != nullptr && pcur->no != no) {
        pcur = pcur->pNext;
    }
    if (pcur == nullptr) {
        cout << "\n\t\t\t\tStart date: ";
        getline(cin, start_date);
        cout << "\n\t\t\t\tEnd date: ";
        getline(cin, end_date);
        register_start_date = addDays(start_date, -7);
        register_end_date = addDays(start_date, -1);
        cout << "\n\t\t\t\tCourses register is avaialable for 7 days before a semester begins.";
        Sleep(1500);
        cout << "\n\n\t\t\t\tRegister start date will be: " << register_start_date;
        cout << "\n\n\t\t\t\tRegister end date will be:  " << register_end_date;
        AnTroChuot();
        pcur = new Semester;
        pcur->no = no;
        pcur->pNext = nullptr;
        ofstream out;
        string path = g_selectyear + "_semester.txt";
        out.open(path, ios::app);
        if (out) {
            out << no << ",";
            out << start_date << ",";
            out << end_date << ",";
            out << register_start_date << ",";
            out << register_end_date << "\n";
            out.close();
        }
        Sleep(3000);
        cout << "\n\n\t\t\t\tAdd semester " << no << " successfully!";
        cout << "\n\n\t\t\t\tPress any key to return...";
        _getch();
    }
    else {
        cout << "\n\t\t\t\tSemester " << no << " has already existed!";
        Sleep(2000);
    }
}

void displaySemester(Staff* staff, Student* student, SchoolYear* schoolyear) {
    setConsoleWindow(800, 600);
    getDataSemester(schoolyear);
    Semester* temp = schoolyear->semester;
    bool check1 = false, check2 = false, check3 = false;
    while (temp) {
        if (temp->no == 1) {
            check1 = true;
            Textcolor(11);
            gotoXY(62, 10); cout << "(" << add0(temp->start_date) << " -- " << add0(temp->end_date) << ")";
            Textcolor(7);
        }
        else if (temp->no == 2) {
            check2 = true;
            Textcolor(11);
            gotoXY(62, 11); cout << "(" << add0(temp->start_date) << " -- " << add0(temp->end_date) << ")";
            Textcolor(7);
        }
        else if (temp->no == 3) {
            check3 = true;
            Textcolor(11);
            gotoXY(62, 12); cout << "(" << add0(temp->start_date) << " -- " << add0(temp->end_date) << ")";
            Textcolor(7);
        }
        temp = temp->pNext;
    }
    if (g_Time != "") {
        gotoXY(26, 4); cout << "Date: " << g_Time;
    }
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(Blue);
    gotoXY(38, 8); cout << "SCHOOL YEAR: " << g_selectyear;
    Textcolor(7);
    cout << "\n\n\t\t\t\tList of semester: Semester 1";
    if (!check1) cout << " (Not created)";
    cout << "\n\t\t\t\t\t\t  Semester 2";
    if (!check2) cout << " (Not created)";
    cout << "\n\t\t\t\t\t\t  Semester 3";
    if (!check3) cout << " (Not created)";

    int no;
    Semester* pCur;
    cout << "\n\n\n\t\t\t\t1. Create semester (maximum 3) \n";
    cout << "\n\n\t\t\t\t2. Get access in semester \n";
    cout << "\n\n\t\t\t\t3. Exit \n";
    cout << "\n\n\t\t\t\t" << char(26) << " Enter your choice: ";
    char choice = getchar();
    cin.ignore(100, '\n');
    switch (choice) {
    case '1':
        createSemester(schoolyear);
        system("cls");
        setConsoleWindow(800, 600);
        displaySemester(staff, student, schoolyear);
        break;
    case '2':
        cout << "\n\n\t\t\t\t" << char(26) << " Enter the semester you want to get access into (number): ";
        cin >> no; cin.ignore();
        getDataSemester(schoolyear);
        pCur = schoolyear->semester;
        while (pCur && pCur->no != no) {
            pCur = pCur->pNext;
        }
        if (pCur) {
            g_selectSemester = no;
            cout << "\n\n\t\t\t\tEntering semester " << no << "...";
            Sleep(2000);
            system("cls");
            if ((date_cmp(add0(pCur->start_date).c_str(), add0(g_Time).c_str()) < 0 // hien tai > bat dau va
                && date_cmp(addDays(add0(pCur->end_date), -5).c_str(), add0(g_Time).c_str()) > 0) || //hien tai <= ket thuc -5
                date_cmp(add0(pCur->start_date).c_str(), add0(g_Time).c_str()) > 0) // hien tai < bat dau
                displayCourseInSemester(schoolyear);
            else {
                system("cls");
                displayCourseWhenDayExceed(schoolyear);
            }
        }
        else {
            cout << "\n\n\t\t\t\tSemester " << no << " doesn't exist.";
            Sleep(2000);
            system("cls");
            displaySemester(staff, student, schoolyear);
        }
        break;
    case '3':
        cout << "\n\n\t\t\t\tLoading...";
        Sleep(2000);
        system("cls");
        displaySchoolYearForStaff(staff, student, schoolyear);
        break;
    default:
        cout << "\n\n\t\t\t\tInvalid input. Try again..";
        Sleep(1800);
        system("cls");
        displayMenuClass(staff, student, schoolyear);
        break;
    }
}

void displaySemesterForStudent(Staff* staff, Student* student, SchoolYear* schoolyear) {
    setConsoleWindow(800, 600);
    getDataSemester(schoolyear);
    Semester* temp = schoolyear->semester;
    bool check1 = false, check2 = false, check3 = false;
    while (temp) {
        if (temp->no == 1) {
            check1 = true;
            Textcolor(11);
            gotoXY(62, 10); cout << "(" << add0(temp->start_date) << " -- " << add0(temp->end_date) << ")";
            Textcolor(7);
        }
        else if (temp->no == 2) {
            check2 = true;
            Textcolor(11);
            gotoXY(62, 11); cout << "(" << add0(temp->start_date) << " -- " << add0(temp->end_date) << ")";
            Textcolor(7);
        }
        else if (temp->no == 3) {
            check3 = true;
            Textcolor(11);
            gotoXY(62, 12); cout << "(" << add0(temp->start_date) << " -- " << add0(temp->end_date) << ")";
            Textcolor(7);
        }
        temp = temp->pNext;
    }
    if (g_Time != "") {
        gotoXY(26, 4); cout << "Date: " << g_Time;
    }
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(Blue);
    gotoXY(38, 8); cout << "SCHOOL YEAR: " << g_selectyear;
    Textcolor(7);
    cout << "\n\n\t\t\t\tList of semester: Semester 1";
    if (!check1) cout << " (Not created)";
    cout << "\n\t\t\t\t\t\t  Semester 2";
    if (!check2) cout << " (Not created)";
    cout << "\n\t\t\t\t\t\t  Semester 3";
    if (!check3) cout << " (Not created)";

    gotoXY(11, 12); cout << "Note: ";
    gotoXY(2, 13); cout << "If you get access into";
    gotoXY(2, 14); cout << "a semester during its";
    gotoXY(2, 15); cout << "session, you can only";
    gotoXY(2, 16); cout << "able to view data.";
    gotoXY(2, 18); cout << "To enroll courses, you";
    gotoXY(2, 19); cout << "need to set date back";
    gotoXY(2, 20); cout << "during register date";
    gotoXY(2, 21); cout << "(7 days before begin)";

    int no;
    Semester* pCur;
    gotoXY(32, 16); cout << "1. Get access into semester \n";
    gotoXY(32, 18); cout << "2. Exit \n";
    gotoXY(32, 20); cout << char(26);
    gotoXY(33, 20); cout << " Enter your choice: ";
    char choice = getchar();
    cin.ignore(100, '\n');
    switch (choice) {
    case '1':
        cout << "\n\n\t\t\t\tEnter the semester you want to get access into (number): ";
        cin >> no; cin.ignore();
        getDataSemester(schoolyear);
        pCur = schoolyear->semester;
        while (pCur && pCur->no != no) {
            pCur = pCur->pNext;
        }
        if (pCur) {
            if (date_cmp(add0(pCur->register_start_date).c_str(), add0(g_Time).c_str()) > 0) {
                cout << "\n\n\t\t\t\tYou can not get access into semester " << no << "yet!";
                cout << "\n\n\t\t\t\t(Access available for 7 days before a semester begins.)";
                Sleep(2000);
                system("cls");
                displaySemesterForStudent(staff, student, schoolyear);
            }
            else {
                g_selectSemester = no;
                cout << "\n\n\t\t\t\tEntering semester " << no << "...";
                Sleep(2000);
                system("cls");
                if (date_cmp(add0(pCur->register_start_date).c_str(), add0(g_Time).c_str()) <= 0
                    && date_cmp(add0(pCur->register_end_date).c_str(), add0(g_Time).c_str()) >= 0)
                    displayCourseForStudent(schoolyear);
                else {
                    system("cls");
                    displayCoursesStudentsExceed(schoolyear);
                }
            }
        }
        else {
            cout << "\n\n\t\t\t\tSemester " << no << " doesn't exist.";
            Sleep(2000);
            system("cls");
            displaySemesterForStudent(staff, student, schoolyear);
        }
        break;
    case '2':
        cout << "\n\n\t\t\t\tLoading...";
        Sleep(2000);
        system("cls");
        displaySchoolYearForStudent(staff, student, schoolyear);
        break;
    default:
        cout << "\n\n\t\t\t\tInvalid input. Try again..";
        Sleep(1800);
        system("cls");
        displayMenuClass(staff, student, schoolyear);
        break;
    }
}