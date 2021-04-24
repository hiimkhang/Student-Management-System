#include "Header.h"

extern string g_account;
extern int g_ID;
extern string g_selectyear;
extern string g_selectClass;
extern int g_selectSemester;
extern string g_Time;


void displayLogin(Staff *staff, Student* student, SchoolYear *schoolYear) {
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
    gotoXY(31, 20); cout << "Enter your choice: "; 
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
            gotoXY(31, 16); cout << "Your account or password is incorrect.";
            gotoXY(31, 18); cout << "Try again in 3...";
            Sleep(1000);
            gotoXY(31, 18); cout << "Try again in 2...";
            Sleep(1000);
            gotoXY(31, 18); cout << "Try again in 1...";
            Sleep(1000);
            system("cls");
            displayLogin(staff, student, schoolYear);
        }
        break;
    case '2':
        system("cls");
        if (loginStudent(student)) {
            loadingSuccess();
            system("cls");
            displayLoginStudent(staff, student, schoolYear);
        }
        else {
            gotoXY(31, 16); cout << "Your account or password is incorrect.";
            gotoXY(31, 18); cout << "Try again in 3...";
            Sleep(1000);
            gotoXY(31, 18); cout << "Try again in 2...";
            Sleep(1000);
            gotoXY(31, 18); cout << "Try again in 1...";
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
        gotoXY(29, 13); cout << "This date will be consider as the time at present.";
        gotoXY(7, 15); cout << "Which will determine whether the student can be able to get access into a semester or not.";
        gotoXY(29, 19); cout << "Enter date (dd/mm/yyyy): ";
        getline(cin, date, '\n');
        g_Time = add0(date);
        gotoXY(29, 21); cout << "Set date successfully!";
        gotoXY(35, 24); cout << "Press any key to return...";
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
    gotoXY(31, 20); cout << "Enter your choice: ";
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
void loadingSuccess() {
    system("cls");
    gotoXY(40, 15);cout << "Login successfully!!";
    gotoXY(44, 18);cout << "Loading...";
    Sleep(3000);
}

void displayLoginStaff(Staff* staff, Student* student, SchoolYear* schoolyear) {
    if (g_Time != "") {
        gotoXY(26, 4); cout << "Date: " << g_Time;
    }
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(Blue);
    gotoXY(39, 9); cout << "COURSE REGISTRATION SYSTEM";
    Textcolor(7);
    gotoXY(31, 12); cout << "1. School year";
    gotoXY(31, 14); cout << "2. View and edit profile";
    gotoXY(31, 16); cout << "3. Change password";
    gotoXY(31, 18); cout << "4. Log out";
    gotoXY(31, 20); cout << "Enter your choice: ";
    char choice = getchar();
    cin.ignore(100, '\n');
    switch (choice) {
    case '1':
        system("cls");
        displayYear(schoolyear);
        displaySchoolYearForStaff(staff, student, schoolyear);
    case '2':
        system("cls");
        displayStaffProfile(staff);
        _getch();
        system("cls");
        displayLoginStaff(staff, student, schoolyear);
        break;
    case '3':
        system("cls");
        changePassStaff(staff, student, schoolyear, "Staff.csv");
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
        displayLoginStaff(staff, student, schoolyear);
        break;
    }
}

//void displaySemester(Staff* staff, Student* student, SchoolYear* schoolyear, string& year) {
//    cout << ""
//}


void displaySchoolYearForStaff(Staff* staff, Student* student, SchoolYear*& schoolyear) {
    displayYear(schoolyear);
    cout << "\n\n\n\n\n\t\t\t\t1. Create new year\n";
    cout << "\n\t\t\t\t2. Exit\n";
    cout << "\n\n\t\t\t\tEnter your choice\n\t\t\t\tOr year (2xxx_2xxx): ";
    string choice;
    getline(cin, choice);
    g_selectyear = choice;
    SchoolYear* pCur = schoolyear;

    if (choice == "1") {
        createNewYear(schoolyear);
        system("cls");
        displayYear(schoolyear);
        displaySchoolYearForStaff(staff, student, schoolyear);
    }
    else if (choice == "2") {
        system("cls");
        displayLoginStaff(staff, student, schoolyear);
    }
    else {
        while (pCur && pCur->year != g_selectyear) {
            pCur = pCur->pNext;
        }
        if (pCur != nullptr) {
            system("cls");
            displaySelectedYearForStaff(staff, student, schoolyear);
        }
        else {
            system("cls");
            displaySchoolYearForStaff(staff, student, schoolyear);
        }
    }
}

void displaySchoolYearForStudent(Staff* staff, Student* student, SchoolYear*& schoolyear) {
    displayYear(schoolyear);
    cout << "\n\t\t\t\t1. Exit\n";
    cout << "\n\n\t\t\t\tEnter your choice\n\t\t\t\tOr year (2xxx_2xxx): ";
    string choice;
    getline(cin, choice);
    g_selectyear = choice;
    SchoolYear* pCur = schoolyear;

    if (choice == "1") {
        system("cls");
        displayLoginStudent(staff, student, schoolyear);
    }
    else {
        while (pCur && pCur->year != g_selectyear) {
            pCur = pCur->pNext;
        }
        if (pCur != nullptr) {
            system("cls");
            displaySelectedYearForStudent(staff, student, schoolyear);
        }
        else {
            system("cls");
            displaySchoolYearForStudent(staff, student, schoolyear);
        }
    }
}

void displayStaffProfile(Staff* staff) {
    if (g_Time != "") {
        gotoXY(26, 4); cout << "Date: " << g_Time;
    }
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(rand() % 15 + 1);
    gotoXY(47, 9); cout << "PROFILE";
    Textcolor(7);

    while (staff && staff->staffAccount != g_account)
        staff = staff->pNext;
           
    gotoXY(31, 12); cout << "Name: " << staff->nameStaff;
    gotoXY(31, 14); cout << "Account: " << staff->staffAccount;
    gotoXY(31, 16); cout << "Password: " << staff->staffPassword;
    gotoXY(31, 20); cout << "Press any key to return...";

    /*if (staff->teacherCourse == "N/A") {
        cout << "\nWhat courses are you incharge of? ";
        getline(cin, staff->teacherCourse, '\n');
    }
    else if (staff->teacherCourse != "N/A")
        cout << "\nCourse incharge: " << staff->teacherCourse;

    if (staff->teacherClass == "N/A") {
        cout << "\nWhat classes are you incharge of? ";
        getline(cin, staff->teacherClass, '\n');
    }
    else if (staff->teacherClass != "N/A")
        cout << "\nClass incharge: " << staff->teacherClass;*/

}

void displayStudentProfile(Student*& student, string path) {
    if (g_Time != "") {
        gotoXY(26, 4); cout << "Date: " << g_Time;
    }
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(rand() % 15 + 1);
    gotoXY(47, 9); cout << "PROFILE";
    Textcolor(7);

    Student* pCur = student;

    while (pCur && pCur->StudentID != g_ID)
        pCur = pCur->pNext;

    gotoXY(31, 12); cout << "First name: " << pCur->Firstname;
    gotoXY(31, 14); cout << "Last name: " << pCur->Lastname;
    gotoXY(31, 16); cout << "Gender: " << pCur->Gender;
    gotoXY(31, 18); cout << "Student ID: " << pCur->StudentID;
    gotoXY(31, 20); cout << "Password: " << pCur->studentPassword;
    gotoXY(31, 22); cout << "Date of birth: " << pCur->DoB;
    gotoXY(31, 24); cout << "Social ID: " << pCur->SocialID;

    gotoXY(31, 26); cout << "U: Update Date of birth";
    gotoXY(31, 27); cout << "ESC: Exit";

    string title;
    string Firstname, Lastname, Gender, studentPassword, DoB, studentClass, tempDoB;
    //long SocialID;
    int ID, SocialID, check = 1;
    ifstream in;
    ofstream out;

    AnTroChuot();

    while (check) {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'u':

                gotoXY(55, 25); cout << ": ";
                gotoXY(57, 25); getline(cin, tempDoB, '\n');

                in.open(path);
                if (in) {
                    out.open("tempStudent.csv");
                    getline(in, title, '\n');
                    out << title << endl;
                    for (int i = 1; i <= numberOfLine(path) - 1; i++) {
                        in >> ID;
                        out << ID << ",";
                        char z;
                        in >> z;
                        getline(in, Firstname, ',');
                        out << Firstname << ",";
                        getline(in, Lastname, ',');
                        out << Lastname << ",";
                        getline(in, Gender, ',');
                        out << Gender << ",";
                        getline(in, DoB, ',');
                        if (ID == pCur->StudentID) {
                            out << tempDoB << ",";
                            pCur->DoB = tempDoB;
                        }
                        else {
                            out << DoB << ",";
                        }
                        getline(in, studentClass, ',');
                        out << studentClass << ",";
                        in >> SocialID;
                        out << SocialID << "\n";
                        getline(in, studentPassword, ',');
                        out << studentPassword << "," << endl;
                    }
                    out.close();
                    in.close();
                    remove("Student.csv");
                    rename("tempStudent.csv", "Student.csv");
                    system("cls");
                    gotoXY(31, 16); cout << "Date of birth updated successfully!";
                    gotoXY(31, 18); cout << "Return in 2 ...";
                    Sleep(1000);
                    gotoXY(31, 18); cout << "Return in 1 ...";
                    Sleep(1000);
                    system("cls");
                    displayStudentProfile(student, path);
                }
                else {
                    cout << "\n\n\t\t\t\tCan't not open " << path << ", return after 3 seconds..";
                    Sleep(3000);
                    displayStudentProfile(pCur, path);
                }
                break;
            case 27:
                check = 0;
                break;
            }
        }
    }

}

string displaySelectedYearForStaff(Staff* staff, Student* student, SchoolYear* schoolyear) {
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
    gotoXY(31, 20); cout << "Enter your choice: ";

    while (schoolyear && schoolyear->year != g_selectyear)
        schoolyear = schoolyear->pNext;

    cin >> choice1; cin.ignore();
    if (choice1 == "1") {
        system("cls");
        displaySemester(schoolyear->staff, student, schoolyear);
    }
    else if (choice1 == "2") {
        system("cls");
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
    gotoXY(31, 14); cout << "1. Semester";
    gotoXY(31, 18); cout << "2. Exit";
    gotoXY(31, 20); cout << "Enter your choice: ";

    while (schoolyear && schoolyear->year != g_selectyear)
        schoolyear = schoolyear->pNext;

    cin >> choice1; cin.ignore();
    if (choice1 == "1") {

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

void displayStudentInClass(SchoolYear*& schoolyear, Student* student) {
    ofstream out;
    ifstream in;
    int y = 16, No = 0, check = 1;
    in.open("student.csv");
    string str;
    getline(in, str);
    in.close();
    out.open(g_selectyear + "_" + g_selectClass + ".csv", ios::app);
    if (numberOfLine(g_selectyear + "_" + g_selectClass + ".csv") == 0) {
        out << str << endl;
    }
    out.close();
    getDataStudentinClass(schoolyear);
    Class* tempClass = schoolyear->classes;
    while (tempClass && tempClass->className != g_selectClass)
        tempClass = tempClass->pNext;


    if (g_Time != "") {
        gotoXY(26, 4); cout << "Date: " << g_Time;
    }
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(Blue);
    gotoXY(38, 8); cout << "CLASS: " << g_selectClass;
    Textcolor(7);
    gotoXY(31, 14); cout << "1. View lecturer";
    gotoXY(31, 16); cout << "2. View student";
    gotoXY(31, 18); cout << "3. Exit";
    gotoXY(31, 20); cout << "Enter your choice: ";
    char choice = getchar();
    cin.ignore(100, '\n');
    switch (choice) {
    case '1':
        /*system("cls");
        gotoXY(26, 5); cout << "=======================================================";
        Textcolor(Blue);
        gotoXY(38, 8); cout << "CLASS: " << g_selectClass;
        Textcolor(7);
        gotoXY(31, 14); cout << "Lecturer's name";
        gotoXY(61, 14); cout << "Course incharge";
        int y = 16;
        if (!tempClass->staff) {
            gotoXY(31, 16); cout << "Not available.";
            gotoXY(61, 16); cout << "Not available.";
        }
        while (tempClass->staff && tempClass->staff->nameStaff == g_selectClass) {
            gotoXY(31, y); cout << tempClass->staff->nameStaff;
            gotoXY(61, y); cout << tempClass->staff->staffCourse->courseName;
            y += 2;
            tempClass->staff = tempClass->staff->pNext;
        }
        gotoXY(31, y); cout << "Press any key to return...";
        _getch();
        gotoXY(31, y += 2); cout << "Loading..";
        system("cls");
        displayStudentInClass(schoolyear, student);*/
        break;
    case '2':
        system("cls");
        if (g_Time != "") {
            gotoXY(26, 4); cout << "Date: " << g_Time;
        }
        gotoXY(26, 5); cout << "=======================================================";
        Textcolor(Blue);
        gotoXY(46, 8); cout << "CLASS: " << g_selectClass;
        Textcolor(7);

        gotoXY(05, 14); cout << "No";
        gotoXY(10, 14); cout << "Student ID";
        gotoXY(24, 14); cout << "First name";
        gotoXY(38, 14); cout << "Last name";
        gotoXY(51, 14); cout << "Gender";
        gotoXY(61, 14); cout << "Date of birth";
        gotoXY(78, 14); cout << "Social ID";

        
        if (numberOfLine(g_selectyear + "_" + g_selectClass + ".csv") == 1) {
            gotoXY(05, 16); cout << "N/A";
            gotoXY(10, 16); cout << "N/A";
            gotoXY(24, 16); cout << "N/A";
            gotoXY(38, 16); cout << "N/A";
            gotoXY(51, 16); cout << "N/A";
            gotoXY(61, 16); cout << "N/A";
            gotoXY(78, 16); cout << "N/A";

        }
        else {
            while (tempClass->student && tempClass->student->studentClass == g_selectClass) {
                gotoXY(05, y); cout << No;
                gotoXY(10, y); cout << tempClass->student->StudentID;
                gotoXY(24, y); cout << tempClass->student->Firstname;
                gotoXY(38, y); cout << tempClass->student->Lastname;
                gotoXY(51, y); cout << tempClass->student->Gender;
                gotoXY(61, y); cout << tempClass->student->DoB;
                gotoXY(78, y); cout << tempClass->student->SocialID;
                y++; No++;
                tempClass->student = tempClass->student->pNext;
            }
        }

        gotoXY(31, y += 2); cout << "T: Add student by typing";
        gotoXY(31, ++y); cout << "F: Add student using csv file";
        gotoXY(31, ++y); cout << "ESC: Exit";

        AnTroChuot();

        while (check) {
            if (_kbhit())
            {
                switch (_getch()) {
                case 't':
                    system("cls");
                    AddStudentIntoClass(schoolyear, student, g_selectyear + "_" + g_selectClass + ".csv");
                    break;
                case 'f':
                    inputStudent();
                    system("cls");
                    displayStudentInClass(schoolyear, student);
                    break;
                case 27:
                    check = 0;
                    system("cls");
                    displayStudentInClass(schoolyear, student);
                    break;
                }
            }
        }
        break;
    case '3':
        system("cls");
        gotoXY(40, 16); cout << "Loading...";
        Sleep(2000);
        system("cls");
        displayMenuClass(schoolyear->staff, student, schoolyear);
    }
}


void AddStudentIntoClass(SchoolYear*& schoolyear, Student*& student, string path) { // path o day la chi toi lop, vd: 2020_2021_20CTT2.csv/txt
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(Blue);
    gotoXY(38, 8); cout << "CLASS: " << g_selectClass;
    gotoXY(40, 9); cout << "ADDING STUDENT";
    Textcolor(7);
    string Firstname, Lastname, Gender, DoB;
    int StudentID;
    long SocialID;
    gotoXY(31, 12); cout << "Student ID: ";
    cin >> StudentID;
    cin.ignore();
    Student* tempStudent = schoolyear->classes->student;
    while (tempStudent && tempStudent->studentClass != g_selectClass)
        tempStudent = tempStudent->pNext;
    if (tempStudent) {
        gotoXY(31, 14); cout << "Student whose ID is " << tempStudent->StudentID
            << " is already existed in this class.";
        Sleep(1500);
        system("cls");
        gotoXY(26, 5); cout << "=======================================================";
        Textcolor(Blue);
        gotoXY(38, 8); cout << "CLASS: " << g_selectClass;
        gotoXY(40, 9); cout << "ADDING STUDENT";
        Textcolor(7);
        gotoXY(31, 12); cout << "Student ID: ";
        cin >> StudentID;
    }
    gotoXY(31, 14); cout << "First name: ";
    getline(cin, Firstname, '\n');
    gotoXY(31, 16); cout << "Last name: ";
    getline(cin, Lastname, '\n');
    gotoXY(31, 18); cout << "Gender: ";
    getline(cin, Gender, '\n');
    gotoXY(31, 20); cout << "Date of birth: ";
    getline(cin, DoB, '\n');
    gotoXY(31, 22); cout << "Social ID: ";
    cin >> SocialID;
    string title;
    string Firstname1, Lastname1, Gender1, studentPassword1, DoB1;
    int ID1;
    long SocialID1;

    Student* pCur = schoolyear->classes->student;

    while (pCur) pCur = pCur->pNext;

    ifstream in;
    ofstream out;
    string path2 = g_selectyear + g_selectClass + "temp.csv";
    in.open(path);
    if (in) {
        out.open(path2);
        getline(in, title, '\n');
        out << title << endl;
        for (int i = 1; i <= numberOfLine(path) - 1; i++) {
            getline(in, Firstname1, ',');
            out << Firstname1 << ",";
            getline(in, Lastname1, ',');
            out << Lastname1 << ",";
            getline(in, Gender1, ',');
            out << Gender1 << ",";
            in >> ID1;
            out << ID1 << ",";
            char z;
            in >> z;
            getline(in, studentPassword1, ',');
            out << studentPassword1 << ",";
            getline(in, DoB1, ',');
            out << DoB1 << ",";
            in >> SocialID1;
            out << SocialID1 << "\n";
        }
        getline(in, Firstname, ',');
        out << Firstname << ",";
        pCur->Firstname = Firstname;
        getline(in, Lastname, ',');
        out << Lastname << ","; pCur->Lastname = Lastname;
        getline(in, Gender, ',');
        out << Gender << ","; pCur->Gender = Gender;
        in >> StudentID;
        out << StudentID << ","; pCur->StudentID = StudentID;
        char z;
        in >> z;
        string pass = "student";
        getline(in, pass, ',');
        out << "student,"; pCur->studentPassword = "student";
        getline(in, DoB, ',');
        out << DoB << ","; pCur->DoB = DoB;
        in >> SocialID;
        out << SocialID << "\n"; pCur->SocialID = SocialID;
        out.close();
        in.close();
        remove(path.c_str());
        rename(path2.c_str(), path.c_str());
    }
    else {
        cout << "Can't not open file " << path;
    }
    gotoXY(31, 24); cout << "Student has been add successfully!\n";
    gotoXY(31, 26); cout << "Press any key to return back to the previous page...";
    _getch();
    system("cls");
}

void displaySemester(Staff* staff, Student* student, SchoolYear* schoolyear) {
    string choice;
    getDataSemester(schoolyear);
    if (g_Time != "") {
        gotoXY(26, 4); cout << "Date: " << g_Time;
    }
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(Blue);
    gotoXY(38, 8); cout << "SCHOOL YEAR: " << g_selectyear;
    Textcolor(7);
    cout << "\n\n\t\t\t\tList of semester: ";
    if (schoolyear->semester) {
        cout << "Semester " << schoolyear->semester->no;
        schoolyear->semester = schoolyear->semester->pNext;
    }

    while (schoolyear->semester) {
        cout << "\n\t\t\t\t\t\t  Semester " << schoolyear->semester->no;
        schoolyear->semester = schoolyear->semester->pNext;
    }

    cout << "\n\n\n\t\t\t\t1.Create semester (maximum 3) \n";
    cout << "\n\n\t\t\t\t2.Get access in semester \n";
    cout << "\n\n\t\t\t\t3.Exit \n";
    cout << "\n\n\t\t\t\tEnter your choice: ";
    cin >> choice; cin.ignore();
    if (choice == "1") {
        createSemester(schoolyear);
        system("cls");
        displaySemester(staff, student, schoolyear);
    }
    else if (choice == "2") {
        cout << "\n\n\t\t\t\tEnter the semester you want to get access into (number): ";
        int no;
        cin >> no; cin.ignore();
        getDataSemester(schoolyear);
        Semester* pCur = schoolyear->semester;
        while (pCur && pCur->no != no) {
            pCur = pCur->pNext;
        }
        if (pCur) {
            g_selectSemester = no;
            cout << "\n\n\t\t\t\tEntering semester " << no << "...";
            Sleep(2000);
            system("cls");
            displayCourseInSemester(schoolyear);
            //displaySelectedYear(staff, student, schoolyear);
        }
        else {
            cout << "\n\n\t\t\tSemester " << no << " doesn't exist.";
            Sleep(2000);
            system("cls");
            displaySemester(staff, student, schoolyear);
        }
    }
    else if (choice == "3") {
        cout << "\n\n\t\t\t\tLoading...";
        Sleep(2000);
        system("cls");
        displaySchoolYearForStudent(staff, student, schoolyear);
    }
    else {
        cout << "\n\n\t\t\t\tInvalid input. Try again..";
        Sleep(1800);
        system("cls");
        displayMenuClass(staff, student, schoolyear);
    }
}

void displayCourseInSemester(SchoolYear*& schoolyear) {
    ofstream out;
    ifstream in;
    int y = 16, No = 0, check = 1;
    /*in.open("student.csv");
    string str;
    getline(in, str);
    in.close();*/
    string title = { "Course name,Course ID,teacher name,credits,"
    "number of students,day,time " };
    out.open(g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv", ios::app);
    if (numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv") == 0) {
        out << title << endl;
    }
    out.close();
    getDataCourseInSemester(schoolyear);
    Semester* tempSemester = schoolyear->semester;
    while (tempSemester && tempSemester->no != g_selectSemester)
        tempSemester = tempSemester->pNext;

    if (g_Time != "") {
        gotoXY(26, 4); cout << "Date: " << g_Time;
    }
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(Blue);
    gotoXY(48, 8); cout << "SEMESTER " << g_selectSemester;
    Textcolor(7);

    gotoXY(05, 12); cout << "Course name";
    gotoXY(30, 12); cout << "Course ID";
    gotoXY(42, 12); cout << "Credits"; 
    gotoXY(52, 12); cout << "Teacher";
    gotoXY(70, 12); cout << "NoS";
    gotoXY(76, 12); cout << "Day";
    gotoXY(88, 12); cout << "Session";


    if (numberOfLine(g_selectyear + "_Semester" + to_string(g_selectSemester) + ".csv") == 1) {
        gotoXY(05, 14); cout << "N/A";
        gotoXY(30, 14); cout << "N/A";
        gotoXY(42, 14); cout << "N/A";
        gotoXY(52, 14); cout << "N/A";
        gotoXY(70, 14); cout << "N/A";
        gotoXY(76, 14); cout << "N/A";
        gotoXY(88, 14); cout << "N/A";
    }
    else {
        while (tempSemester->course) {
            gotoXY(05, y); cout << tempSemester->course->courseName;
            gotoXY(30, y); cout << tempSemester->course->courseID;
            gotoXY(42, y); cout << tempSemester->course->creditNum;
            gotoXY(52, y); cout << tempSemester->course->teacherName;
            gotoXY(70, y); cout << tempSemester->course->numOfStudents;
            gotoXY(76, y); cout << tempSemester->course->courseDate;
            gotoXY(88, y); cout << tempSemester->course->courseSession;
            y++; No++; 
            tempSemester->course = tempSemester->course->pNext;
        }
    }
  
    gotoXY(31, y + 4); cout << "1. Add course";
    gotoXY(31, y + 5); cout << "2. Update course information";
    gotoXY(31, y + 6); cout << "3. Delete course";
    gotoXY(31, y + 7); cout << "4. Exit";
    gotoXY(31, y + 8); cout << "Enter your choice: ";
    char choice = getchar();
    cin.ignore(100, '\n');
    switch (choice) {
    case '1':
        // Add course;
        break;
    case '2':
        // Update course info;
        break;
    case '3':
        // Delete course;
        break;
    }
}

    


    /*if (pCur->DoB == "N/A") { 
        gotoXY(31, 24); cout << "Do you want to update your date of birth?\n(y/n): ";

        string choice; cin >> choice; cin.ignore();
        if (choice == "y" || choice == "Y") {
            string title;
            string Firstname, Lastname, Gender, studentPassword, DoB, tempDoB;
            int ID;
            cout << "\n\nEnter your Date of birth (dd/mm/yyyy): ";
            getline(cin, tempDoB, '\n');
            ifstream in;
            ofstream out;
            in.open(path);
            if (in) {
                out.open("tempStudent.csv");
                getline(in, title, '\n');
                out << title << endl;
                for (int i = 1; i <= numberOfLine(path) - 1; i++) {
                    getline(in, Firstname, ',');
                    out << Firstname << ",";
                    getline(in, Lastname, ',');
                    out << Lastname << ",";
                    getline(in, Gender, ',');
                    out << Gender << ",";
                    in >> ID;
                    out << ID << ",";
                    char z;
                    in >> z;
                    getline(in, studentPassword, ',');
                    out << studentPassword << ",";
                    getline(in, DoB, '\n');
                    if (ID == pCur->StudentID) {
                        out << tempDoB << endl;
                        pCur->DoB = tempDoB;
                    }
                    else {
                        out << DoB << endl;
                    }
                }
                out.close();
                in.close();
                remove("Student.csv");
                rename("tempStudent.csv", "Student.csv");
                cout << "\n\nDate of birth updated successfully!";
            }
            else {
                cout << "\n\nCan't not open " << path << ", return after 3 seconds..";
                Sleep(3000);
                displayStudentProfile(pCur, path);
            }
        }
    }    */    


