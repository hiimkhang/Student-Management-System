#include "Header.h"

void displayLogin(Staff *staff, SchoolYear *schoolYear) {
    int choice;
    cout << "\n\t\t\t\t=======================================================\n";
    cout << "\n\t\t\t\t\tCOURSE REGISTRATION SYSTEM\n";
    cout << "\n\t\t\t\t1. Academic staff login";
    cout << "\n\t\t\t\t2. Student login";
    cout << "\n\t\t\t\t3. Exit";
    cout << "\n\t\t\t\tEnter your choice: "; cin >> choice;

    switch (choice) {
    case 1:
        system("cls");
        cin.ignore();
        if (loginStaff(staff)) {
            loadingSuccess();
            system("cls");
            displayLoginStaff(staff, schoolYear);
            switch (choice) {
            case 1: 
                system("cls");
                displayYear(schoolYear);
                displaySchoolYear();
                cin >> choice;
                switch (choice) {
                case 1:
                    createNewYear(schoolYear);
                    Sleep(2000);
                    cout << "\n\t\t\t\t Added.";
                    cout << "\n\t\t\t\tPress any key to return to previous page...";
                    _getch();
                    system("cls");
                    displaySchoolYear();
                    cin >> choice;
                case 2:
                    system("cls");
                    displayLoginStaff(staff, schoolYear);
                }
            case 2:
                system("cls");
                displayStaffProfile(staff);
                cout << "\n\t\t\t\tPress any key to return to previous page...";
                _getch();
                system("cls");
                displayLoginStaff(staff, schoolYear);
            case 3:
                system("cls");
                changePassStaff(staff, schoolYear);
            default:
                cout << "\n\t\t\t\tError.";
            }
        }
    }
}

void loadingSuccess() {
    system("cls");
    cout << "\n\n\t\t\t\t\t  Login successfully!!\n\n";
    cout << "\t\t\t\t\tLoading...";
    Sleep(3000);
}

void displayLoginStaff(Staff* staff, SchoolYear* schoolyear) {
    cout << "\n\t\t\t\t=======================================================\n";
    cout << "\n\t\t\t\t\tCOURSE REGISTRATION SYSTEM\n";
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
        displaySchoolYear();
        cin >> choice;
        switch (choice) {
        case 1:
            createNewYear(schoolyear);
            Sleep(2000);
            cout << "\n\t\t\t\t Added.";
            cout << "\n\t\t\t\tPress any key to return to previous page...";
            _getch();
            system("cls");
            displaySchoolYear();
            cin >> choice;
        case 2:
            system("cls");
            displayLoginStaff(staff, schoolyear);
        }
    case 2:
        system("cls");
        displayStaffProfile(staff);
        cout << "\n\t\t\t\tPress any key to return to previous page...";
        _getch();
        system("cls");
        displayLoginStaff(staff, schoolyear);
    case 3:
        system("cls");
        changePassStaff(staff, schoolyear);
    default:
        cout << "\n\t\t\t\tError.";
    }
}

void displaySchoolYear() {
    cout << "\n\t\t\t\t1. Create new year\n";
    cout << "\n\t\t\t\t2. Exit\n";
    cout << "\n\t\t\t\tEnter your choice: ";
}

void displayStaffProfile(Staff* staff) {
    cout << "\n\t\t\t\t\tPROFILE\n";
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

