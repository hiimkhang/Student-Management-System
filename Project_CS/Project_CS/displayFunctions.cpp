#include "Header.h"

void displayLogin(Staff *staff, SchoolYear *schoolYear) {
    int choice;
    cout << "\n\t=======================================================\n";
    cout << "\n\t\t\tCOURSE REGISTRATION SYSTEM\n";
    cout << "\n\t1. Academic staff login";
    cout << "\n\t2. Student login";
    cout << "\n\t3. Exit";
    cout << "\n\tEnter your choice: "; cin >> choice;

    switch (choice) {
    case 1:
        system("cls");
        if (loginStaff(staff)) {
            loadingSuccess();
            cout << "\n\t=======================================================\n";
            cout << "\n\t\t\tCOURSE REGISTRATION SYSTEM\n";
            cout << "\n\t\t1. School year\n";
            cout << "\n\t\t2. View profile\n";
            cout << "\n\t\t3. Change password\n";
            cout << "\n\t\t4. Log out\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
            case 1: 
                displayYear(schoolYear);
                cout << "\n\t\t1. Create new year\n";
                cout << "2. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice) {
                case 1:
                    createNewYear(schoolYear);
                    getch();
                }
            }
        }
    }
}

void loadingSuccess() {
    system("cls");
    cout << "\n\n\t\tLogin successful!!";
    for (int i = 5; i >= 0; --i) {
        printf("\n\tRedirect to the base menu after %d seconds.\n", i);
        Sleep(1000);
    }
}