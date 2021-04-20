#include "Header.h"

extern string g_account;
extern int g_ID;
extern string g_selectyear;
extern string g_class;



void displayLogin(Staff *staff, Student* student, SchoolYear *schoolYear) {
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(rand() % 16);
    gotoXY(39, 9); cout << "COURSE REGISTRATION SYSTEM";
    Textcolor(7);
    gotoXY(31, 12); cout << "1. Academic staff login";
    gotoXY(31, 14); cout << "2. Student login";
    gotoXY(31, 16); cout << "3. Exit";
    gotoXY(31, 18); cout << "Enter your choice: "; 
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
        displaySchoolYear(staff, student, schoolyear);
        choice = getchar();
        cin.ignore(100, '\n');
        switch (choice) {
        case '1':
            createNewYear(schoolyear);
            Sleep(2000);
            cout << "\n\n\t\t\t\tAdded.";
            cout << "\n\n\t\t\t\tPress any key to return to previous page...";
            _getch();
            system("cls");
            displaySchoolYear(staff, student, schoolyear);
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
    int choice;
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
        displaySchoolYear(staff, student, schoolyear);
      /*  cin >> choice; cin.ignore();
        switch (choice) {
        case 1:
            createNewYear(schoolyear);
            Sleep(2000);
            cout << "\n\n\t\t\t\tAdded.";
            cout << "\n\n\t\t\t\tPress any key to return to previous page...";
            _getch();
            system("cls");   
            displaySchoolYear(staff, student, schoolyear);
            cin >> choice;
            break;
        case 2:
            system("cls");
            displayLoginStaff(staff, student, schoolyear);
            break;
        }*/
    case '2':
        system("cls");
        displayStaffProfile(staff);
        cout << "\n\n\t\t\t   Press any key to return to previous page...";
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


void displaySchoolYear(Staff* staff, Student* student, SchoolYear* schoolyear) {
    displayYear(schoolyear);
    cout << "\n\n\n\n\n\t\t\t\t1. Create new year\n";
    cout << "\n\t\t\t\t2. Exit\n";
    cout << "\n\n\t\t\t\tEnter your choice\n\t\t\t\tOr year (2xxx_2xxx): ";
    string choice;
    getline(cin, choice);
    g_selectyear = choice;
    string k;
    SchoolYear* pCur = schoolyear;

    if (choice == "1") {
        createNewYear(schoolyear);
        /*cout << "\n\n\t\t\t\tLoading...\n";
        Sleep(2000);
        cout << "\n\t\t\t\tAdded.\n";
        cout << "\n\t\t\tPress any key to return to previous page...";
        _getch();*/
        system("cls");
        displayYear(schoolyear);
        displaySchoolYear(staff, student, schoolyear);
    }
    else if (choice == "2") {
        system("cls");
        //displayLoginStaff(staff, student, schoolyear);
        displayLoginStaff(staff, student, schoolyear);
    }
    else {
        while (pCur && pCur->year != g_selectyear) {
            pCur = pCur->pNext;
        }
        if (pCur != nullptr) {
            system("cls");
            displaySelectedYear(staff, student, schoolyear);
        }
        else {
            system("cls");
            displaySchoolYear(staff, student, schoolyear);
        }
    }
}

void displayStaffProfile(Staff* staff) {
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(rand() % 15 + 1);
    gotoXY(47, 9); cout << "PROFILE";
    Textcolor(7);

    /*while (staff && staff->staffAccount != account)
        staff = staff->pNext;*/

    while (staff && staff->staffAccount != g_account)
        staff = staff->pNext;
           
    gotoXY(31, 12); cout << "Name: " << staff->nameStaff;
    gotoXY(31, 14); cout << "Account: " << staff->staffAccount;
    gotoXY(31, 16); cout << "Password: " << staff->staffPassword;

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

    gotoXY(31, 25); cout << "U: Update Date of birth";
    gotoXY(31, 26); cout << "ESC: Exit";

    string title;
    string Firstname, Lastname, Gender, studentPassword, DoB, tempDoB;
    int ID, check = 1;
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
                    cout << "\n\nCan't not open " << path << ", return after 3 seconds..";
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

string displaySelectedYear(Staff* staff, Student* student, SchoolYear* schoolyear) {
    string choice, choice1;
    gotoXY(26, 5); cout << "=======================================================";
    Textcolor(Blue);
    gotoXY(38, 9); cout << "SCHOOL YEAR: " << g_selectyear;
    Textcolor(7);
    gotoXY(31, 14); cout << "1.Semester";
    gotoXY(31, 16); cout << "2.Class";
    gotoXY(31, 18); cout << "3.Exit";
    gotoXY(31, 20); cout << "Enter your choice: ";

    while (schoolyear && schoolyear->year != g_selectyear)
        schoolyear = schoolyear->pNext;

    cin >> choice1; cin.ignore();
    if (choice1 == "1") {

    }
    else if (choice1 == "2") {
        system("cls");
        displayMenuClass(staff, student, schoolyear);
    }
    else if (choice1 == "3") {
        gotoXY(40, 22); cout << "Loading...";
        Sleep(2000);
        system("cls");
        displayYear(schoolyear);
        displaySchoolYear(staff, student, schoolyear);
    }
    else {
        displaySelectedYear(staff, student, schoolyear);
    }
    return choice1;
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


