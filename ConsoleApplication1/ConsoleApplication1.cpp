/**
* Solution to course project #9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Bogomil Pankov
* @idnumber 6MI0600428 @compiler VCC
* <main file>
* */


#include <iostream>
#include <vector>
#include "UserManagement.h"

using namespace std;

void mainMenu() {
    vector<User> users;
    int choice;

    do {
        cout << "\n=== Welcome to MyFitnessPal ===\n";
        cout << "1. Sign Up\n";
        cout << "2. Log In\n";
        cout << "3. Close Application\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 3) {
            cout << "Invalid choice. Select a number between 1 and 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1:
            signUp(users);
            break;
        case 2:
            logIn(users);

            break;
        case 3:
            closeApp();
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

int main() {
    mainMenu();
    return 0;
}
