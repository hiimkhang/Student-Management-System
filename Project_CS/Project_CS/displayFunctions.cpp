#include "Header.h"

extern string g_account;
extern int g_ID;


void displayLogin(Staff *staff, Student* student, SchoolYear *schoolYear) {
    int choice;
    cout << "\n\t\t\t   =======================================================\n\n";
    Textcolor(rand() % 16);
    cout << "\n\n\t\t\t\t\tCOURSE REGISTRATION SYSTEM\n\n\n";
    Textcolor(7);
    cout << "\n\t\t\t\t1. Academic staff login\n";
    cout << "\n\t\t\t\t2. Student login\n";
    cout << "\n\t\t\t\t3. Exit\n";
    cout << "\n\t\t\t\tEnter your choice: "; cin >> choice;
    switch (choice) {
    case 1:
        system("cls");
        cin.ignore();
        if (loginStaff(staff)) {
            loadingSuccess();
            system("cls");
            displayLoginStaff(staff, student, schoolYear);
            /*switch (choice) {
            case 1:
                system("cls");
                displayYear(schoolYear);
                displaySchoolYear(staff, student, schoolYear, account);
                cin >> choice;
                switch (choice) {
                case 1:
                    createNewYear(schoolYear);
                    Sleep(2000);
                    cout << "\n\t\t\t\t Added.";
                    cout << "\n\t\t\t\tPress any key to return to previous page...";
                    _getch();
                    system("cls");
                    displaySchoolYear(staff, student, schoolYear, account);
                    cin >> choice;
                case 2:
                    system("cls");
                    displayLoginStaff(staff, student, schoolYear, account);
                }
            case 2:
                system("cls");
                displayStaffProfile(staff);
                cout << "\n\t\t\t\tPress any key to return to previous page...";
                _getch();
                system("cls");
                displayLoginStaff(staff, student, schoolYear, account);
            case 3:
                system("cls");
                changePassStaff(staff, student, schoolYear, "Staff.csv", account);
            default:
                displayLogin(staff, student, schoolYear);
            }*/
        }
        else {
            cout << "\n\n\t\t\tYour account or password is incorrect.\n\n\t\t\tTry again after 3 seconds...";
            Sleep(3000);
            system("cls");
            displayLogin(staff, student, schoolYear);
        }
        break;
    case 2:
        system("cls");
        cin.ignore();
        if (loginStudent(student)) {
            loadingSuccess();
            system("cls");
            displayLoginStudent(staff, student, schoolYear);
            switch (choice) {
            case 1:
                system("cls");
                displayYear(schoolYear);
                /*displaySchoolYear(staff, student, schoolYear, ID);*/
                cin >> choice;
                switch (choice) {
                case 1:
                    createNewYear(schoolYear);
                    Sleep(2000);
                    cout << "\n\t\t\t\tAdded.";
                    cout << "\n\t\t\t\tPress any key to return to previous page...";
                    _getch();
                    system("cls");
                    //displaySchoolYear(staff, student, schoolYear, ID);
                    cin >> choice;
                case 2:
                    system("cls");
                    displayLoginStudent(staff, student, schoolYear);
                }
            case 2:
                system("cls");
                displayStudentProfile(student,"Student.csv");
                cout << "\n\t\t\t\tPress any key to return to previous page...";
                _getch();
                system("cls");
                displayLoginStudent(staff, student, schoolYear);
            case 3:
                system("cls");
                changePassStudent(staff, student, schoolYear, "Student.csv");
            case 4:
                system("cls");
                displayLogin(staff, student, schoolYear);
            default:
                cout << "\n\t\t\t\tError.";
            }
        }
        else {
            cout << "\n\n\t\t\tYour account or password is incorrect.\n\n\t\t\tTry again after 3 seconds...";
            Sleep(3000);
            system("cls");
            displayLogin(staff, student, schoolYear);
        }
        break;
    case 3:
        system("cls");
        cout << "\n\n\n\n\n\t\t\t\t\t\tSEE YOU AGAIN!\n\n\n\n\n";
        break;
    default:
        cout << "\n\n\t\t\t\tInvalid input. Please try again...";
        Sleep(2000);
        system("cls");
        displayLogin(staff, student, schoolYear);
        break;
    }
}

void displayLoginStudent(Staff* staff, Student* student, SchoolYear* schoolyear) {
    cout << "\n\t\t\t   =======================================================\n\n";
    Textcolor(rand() % 15 + 1);
    cout << "\n\n\t\t\t\t\tCOURSE REGISTRATION SYSTEM\n\n\n";
    Textcolor(7);
    cout << "\n\t\t\t\t1. School year\n";
    cout << "\n\t\t\t\t2. View and edit profile\n";
    cout << "\n\t\t\t\t3. Change password\n";
    cout << "\n\t\t\t\t4. Log out\n";
    cout << "\n\t\t\t\tEnter your choice: ";
    int choice; cin >> choice; cin.ignore();
    switch (choice) {
    case 1:
        system("cls");
        displayYear(schoolyear);
        //displaySchoolYear(staff, student, schoolyear, ID);
        cin >> choice;
        switch (choice) {
        case 1:
            createNewYear(schoolyear);
            Sleep(2000);
            cout << "\n\t\t\t\t Added.";
            cout << "\n\t\t\t\tPress any key to return to previous page...";
            _getch();
            system("cls");
            //displaySchoolYear(staff, student, schoolyear, ID);
            cin >> choice;
            break;
        case 2:
            system("cls");
            displayLoginStudent(staff, student, schoolyear);
            break;
        }
    case 2:
        system("cls");
        displayStudentProfile(student, "Student.csv");
        cout << "\n\t\t\t\tPress any key to return to previous page...";
        _getch();
        system("cls");
        displayLoginStudent(staff, student, schoolyear);
        break;
    case 3:
        system("cls");
        changePassStudent(staff, student, schoolyear, "Student.csv");
        break;
    case 4:
        cout << "\n\n\t\t\t\tLogging out...";
        Sleep(3000);
        system("cls");
        displayLogin(staff, student, schoolyear);
        break;
    default:
        cout << "\n\t\t\t\tError.";
        cout << "\n\t\t\t\tReturn to main menu...";
        Sleep(2000);
        system("cls");
        displayLogin(staff, student, schoolyear);
        break;
    }
}
void loadingSuccess() {
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t  Login successfully!!\n\n";
    cout << "\t\t\t\t\tLoading...";
    Sleep(3000);
}

void displayLoginStaff(Staff* staff, Student* student, SchoolYear* schoolyear) {
    cout << "\n\t\t\t   =======================================================\n\n";
    Textcolor(rand() % 15 + 1);
    cout << "\n\n\t\t\t\t\tCOURSE REGISTRATION SYSTEM\n\n\n";
    Textcolor(7);
    cout << "\n\t\t\t\t1. School year\n";
    cout << "\n\t\t\t\t2. View and edit profile\n";
    cout << "\n\t\t\t\t3. Change password\n";
    cout << "\n\t\t\t\t4. Log out\n";
    cout << "\n\t\t\t\tEnter your choice: ";
    int choice; cin >> choice; cin.ignore();
    switch (choice) {
    case 1:
        system("cls");
        displayYear(schoolyear);
        displaySchoolYear(staff, student, schoolyear);
        cin >> choice; cin.ignore();
        switch (choice) {
        case 1:
            createNewYear(schoolyear);
            Sleep(2000);
            cout << "\n\t\t\t\tAdded.\n";
            cout << "\n\t\t\t\tPress any key to return to previous page...";
            _getch();
            system("cls");
            displaySchoolYear(staff, student, schoolyear);
            cin >> choice;
            break;
        case 2:
            system("cls");
            displayLoginStaff(staff, student, schoolyear);
            break;
        }
    case 2:
        system("cls");
        displayStaffProfile(staff);
        cout << "\n\t\t\t\tPress any key to return to previous page...";
        _getch();
        system("cls");
        displayLoginStaff(staff, student, schoolyear);
        break;
    case 3:
        system("cls");
        changePassStaff(staff, student, schoolyear, "Staff.csv");
        break;
    case 4:
        cout << "\n\n\t\t\t\tLogging out...";
        Sleep(3000);
        system("cls");
        displayLogin(staff, student, schoolyear);
        break;
    default:
        cout << "\n\t\t\t\tError.";
        cout << "\n\t\t\t\tReturn to main menu...";
        Sleep(2000);
        system("cls");
        displayLogin(staff, student, schoolyear);
        break;
    }
}

//void displaySemester(Staff* staff, Student* student, SchoolYear* schoolyear, string& year) {
//    cout << ""
//}


void displaySchoolYear(Staff* staff, Student* student, SchoolYear* schoolyear) {
    cout << "\n\n\n\n\n\t\t\t\t1. Create new year\n";
    cout << "\n\t\t\t\t2. Exit\n";
    cout << "\n\t\t\t\tEnter your choice\n\t\t\t\tOr enter the year you want to access into (2xxx_2xxx): ";
    string choice; 
    getline(cin, choice);
    string k;
    SchoolYear* pCur = schoolyear;
    while (pCur) {
        if (choice == pCur->year) {
            system("cls");
            cout <<"\n\n\n\n\n\t\t\t\t"<< pCur->year;
            Sleep(3000);
            // Viet ham gi do de return, end vong lap.s
            cout << "1.Semester: \n";
            cout << "2.Class: \n";
            cout << "3.Exit \n";
            cout << "Please input: ";
            cin >> choice;
            if (choice == "1") {

            }
            else if (choice == "2") {
                getDataClass(pCur);
                displayClass(schoolyear);
                cout << "1.Create class \n";
                cout << "2.Exit \n";
                cout << "Please input: "
                    
                    ;
                cin >> choice;
                if (choice == "1") {
                    createClassForYear(schoolyear);
                }
                else if (choice == "2") {

                }
            }
            else if (choice == "3") {
                displayYear(schoolyear);
                displaySchoolYear(staff, student, schoolyear);
            }
            break;
        }
        pCur = pCur->pNext;
    }
    if (choice == "1") {
        createNewYear(schoolyear);
        cout << "\n\n\t\t\t\tLoading...\n";
        Sleep(2000);
        cout << "\n\t\t\t\tAdded.\n";
        cout << "\n\t\t\t\tPress any key to return to previous page...";
        _getch();
        system("cls");
        displayYear(schoolyear);
        displaySchoolYear(staff, student, schoolyear);
    }
    else if (choice == "2") {
        system("cls");
        displayLoginStaff(staff, student, schoolyear);
    }
    else{
        cout << "\n\t\t\t\tInvalid input, please try again...";
        Sleep(2000);
        system("cls");
        displayYear(schoolyear);
        displaySchoolYear(staff, student, schoolyear);
    }
}

void displayStaffProfile(Staff* staff) {
    cout << "\n\t\t\t   =======================================================\n\n";
    Textcolor(rand() % 15 + 1);
    cout << "\n\n\t\t\t\t\ttPROFILE\n\n\n";
    Textcolor(7);

    /*while (staff && staff->staffAccount != account)
        staff = staff->pNext;*/

    while (staff && staff->staffAccount != g_account)
        staff = staff->pNext;
           
    cout << "\n\t\t\t\tName: " << staff->nameStaff;
    cout << "\n\t\t\t\tAccount: " << staff->staffAccount;
    cout << "\n\t\t\t\tPassword: " << staff->staffPassword;

    if (staff->teacherCourse == "N/A") {
        cout << "\n\t\t\t\tWhat courses are you incharge of? ";
        getline(cin, staff->teacherCourse, '\n');
    }
    else if (staff->teacherCourse != "N/A")
        cout << "\n\t\t\t\tCourse incharge: " << staff->teacherCourse;

    if (staff->teacherClass == "N/A") {
        cout << "\n\t\t\t\tWhat classes are you incharge of? ";
        getline(cin, staff->teacherClass, '\n');
    }
    else if (staff->teacherClass != "N/A")
        cout << "\n\t\t\t\tClass incharge: " << staff->teacherClass;

}

void displayStudentProfile(Student*& student, string path) {
    cout << "\n\t\t\t   =======================================================\n\n";
    Textcolor(rand() % 15 + 1);
    cout << "\n\n\t\t\t\t\tPROFILE\n\n\n";
    Textcolor(7);

    Student* pCur = student;

    while (pCur && pCur->StudentID != g_ID)
        pCur = pCur->pNext;

    cout << "\n\t\t\t\tFirst name: " << pCur->Firstname;
    cout << "\n\n\t\t\t\tLast name: " << pCur->Lastname;
    cout << "\n\n\t\t\t\tGender: " << pCur->Gender;
    cout << "\n\n\t\t\t\tStudent ID: " << pCur->StudentID;
    cout << "\n\n\t\t\t\tPassword: " << pCur->studentPassword;
    cout << "\n\n\t\t\t\tDate of birth: " << pCur->DoB;

    if (pCur->DoB == "N/A") {
        cout << "\n\n\t\t\t\tDo you want to update your date of birth?\n\t\t\t\t(y/n): ";
        string choice; cin >> choice; cin.ignore();
        if (choice == "y" || choice == "Y") {
            string title;
            string Firstname, Lastname, Gender, studentPassword, DoB, tempDoB;
            int ID;
            cout << "\n\n\t\t\t\tEnter your Date of birth (dd/mm/yyyy): ";
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
                    }
                    else {
                        out << DoB << endl;
                    }
                }
                out.close();
                in.close();
                remove("Student.csv");
                rename("tempStudent.csv", "Student.csv");
            }
            else {
                cout << "\n\n\t\t\t\tCan't not open " << path << ", return after 3 seconds..";
                Sleep(3000);
                displayStudentProfile(pCur, path);
            }
        }
    }        
}

