#pragma once
#include "Header.h"

extern string g_account;
extern int g_ID;
extern string g_selectyear;
extern int g_selectSemester;
extern string g_selectClass;
extern string g_selectCourse;
extern string g_Time;

void displayLogin(Staff* staff, Student* student, SchoolYear* schoolYear) {
    setConsoleWindow(800, 600);
    if (g_Time != "") {
        gotoXY(26, 4); cout << "Date: " << g_Time;
    }
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(rand() % 16);
    gotoXY(39, 9); cout << "COURSE REGISTRATION SYSTEM";
    Textcolor(7);
    gotoXY(31, 12); cout << "1. Academic staff login";
    gotoXY(31, 14); cout << "2. Student login";
    gotoXY(31, 16); cout << "3. Set date";
    gotoXY(31, 18); cout << "4. Exit";
    if (g_Time == "") {
        gotoXY(31, 25); cout << "You should set date first!";
    }
    gotoXY(31, 20); cout << char(26) << " Enter your choice: ";
    string date;
    char choice = getchar();
    cin.ignore(100, '\n');
    switch (choice) {
    case '1':
        system("cls");
        if (loginStaff(staff)) {
            loadingSuccess();
            system("cls");
            displayLoginStaff(staff, student, schoolYear);
        }
        else {
            gotoXY(35, 16); cout << "Your account or password is incorrect.";
            gotoXY(35, 18); cout << "Try again in 3...";
            Sleep(1000);
            gotoXY(35, 18); cout << "Try again in 2...";
            Sleep(1000);
            gotoXY(35, 18); cout << "Try again in 1...";
            Sleep(1000);
            system("cls");
            displayLogin(staff, student, schoolYear);
        }
        break;
    case '2':
        system("cls");
        getDataStudent(student, "student.csv");
        if (loginStudent(student)) {
            loadingSuccess();
            system("cls");
            displayLoginStudent(staff, student, schoolYear);
        }
        else {
            gotoXY(35, 16); cout << "Your account or password is incorrect.";
            gotoXY(35, 18); cout << "Try again in 3...";
            Sleep(1000);
            gotoXY(35, 18); cout << "Try again in 2...";
            Sleep(1000);
            gotoXY(35, 18); cout << "Try again in 1...";
            Sleep(1000);
            system("cls");
            displayLogin(staff, student, schoolYear);
        }
        break;
    case '3':
        system("cls");
        gotoXY(26, 5); cout << "=======================================================";
        Textcolor(rand() % 15 + 1);
        gotoXY(48, 9); cout << "SET DATE";
        Textcolor(7);
        gotoXY(29, 13); cout << "This date will be considered as the time at the present.";
        gotoXY(29, 15); cout << "Which will determine whether:";
        gotoXY(29, 17); cout << char(5);
        gotoXY(31, 17); cout << "A student can be able to get access into a semester or not;";
        gotoXY(29, 19); cout << char(5);
        gotoXY(31, 19); cout << "A student can be able to enroll a course or not;";
        gotoXY(29, 21); cout << char(5);
        gotoXY(31, 21); cout << "A staff can be able to get access into a semester or not;";
        gotoXY(29, 23); cout << char(5);
        gotoXY(31, 23); cout << "A staff can be able to add courses in a semester or not;";
        gotoXY(29, 25); cout << "Enter date (dd/mm/yyyy): ";
        getline(cin, date, '\n');
        g_Time = add0(date);
        gotoXY(29, 28); cout << "Set date successfully!";
        gotoXY(29, 30); cout << "Press any key to return...";
        _getch();
        system("cls");
        displayLogin(staff, student, schoolYear);
        break;
    case '4':
        system("cls");
        gotoXY(31, 15); cout << "THANK YOU FOR USING OUR SYSTEM!\n\t\t\t\t";
        exit(0);
        break;
    default:
        gotoXY(31, 23); cout << "Try again in 2...";
        Sleep(1000);
        gotoXY(31, 23); cout << "Try again in 1...";
        Sleep(1000);
        system("cls");
        displayLogin(staff, student, schoolYear);
        break;
    }
}

void loadingSuccess() {
    system("cls");
    gotoXY(40, 15); cout << "Login successfully!! " << char(1) << endl;
    gotoXY(44, 18); cout << "Loading...";
    Sleep(3000);
}

int numberOfLine(string filename) {
    ifstream in;
    in.open(filename);
    string s;
    int count = 0;
    while (!in.eof()) {
        getline(in, s, '\n');
        if (s != "") {
            count++;
        }
    }
    in.close();
    return count;
}

void deleteList(Staff*& pHead) {
    Staff* pCur = pHead;
    while (pHead) {
        pHead = pHead->pNext;
        delete pCur;
        pCur = pHead;
    }
}

string add0(string date) {
    int i = 0;
    string day, month, year;
    while (date[i] != '/') {
        day.push_back(date[i]);
        i++;
    }
    i++;
    while (date[i] != '/') {
        month.push_back(date[i]);
        i++;
    }
    i++;
    while (date[i]) {
        year.push_back(date[i]);
        i++;
    }
    if (day.size() < 2) {
        day = "0" + day;
    }
    if (month.size() < 2) {
        month = "0" + month;
    }
    return day + '/' + month + '/' + year;
}

int date_cmp(const char* d1, const char* d2)
{
    int rc;
    // compare years
    rc = strncmp(d1 + 6, d2 + 6, 4);
    if (rc != 0)
        return rc;

    // compare months
    rc = strncmp(d1 + 3, d2 + 3, 2);
    if (rc != 0)
        return rc;

    // compare days
    return strncmp(d1, d2, 2);
}

void DatePlusDays(struct tm* date, int days)
{
    const time_t ONE_DAY = 24 * 60 * 60;

    // Seconds since start of epoch
    time_t date_seconds = mktime(date) + (days * ONE_DAY);

    // Update caller's date
    // Use localtime because mktime converts to UTC so may change date
    *date = *localtime(&date_seconds); ;
}

string addDays(string date1, int days) {
    string realDate = add0(date1);
    int day = (realDate[0] - '0') * 10 + (realDate[1] - '0');
    int month = (realDate[3] - '0') * 10 + (realDate[4] - '0');
    int year = (realDate[6] - '0') * 1000 + (realDate[7] - '0') * 100 + (realDate[8] - '0') * 10 + (realDate[9] - '0');
    struct tm date = { 0, 0, 12 };
    date.tm_mday = day;
    date.tm_mon = month - 1;
    date.tm_year = year - 1900;
    DatePlusDays(&date, days);
    string time = asctime(&date);
    string dd = "10";
    if (time[8] != ' ') {
        dd[0] = time[8];
        dd[1] = time[9];
        dd[2] = ' ';
    }
    else {
        dd[0] = time[9];
        dd[1] = ' ';
    }
    string res = dd + "/" + to_string(date.tm_mon + 1) + "/" + to_string(date.tm_year + 1900);
    if (res[1] == ' ') res.erase(1, 1);
    if (res[4] == ' ') res.erase(4, 1);
    return add0(res);
}

void welcome() {
    Textcolor(Blue);
    gotoXY(45, 14);
    cout << char(3) << " WELCOME TO OUR MOODLES " << char(3);
    Sleep(1000);
    Textcolor(Red);
    gotoXY(45, 14); cout << char(3) << " WELCOME TO OUR MOODLES " << char(3);
    Sleep(1000);
    Textcolor(Yellow);
    gotoXY(45, 14); cout << char(3) << " WELCOME TO OUR MOODLES " << char(3);
    Textcolor(7);
    Sleep(1500);
    system("cls");
}