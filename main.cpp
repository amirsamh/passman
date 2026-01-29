#include <iostream>
#include <string>
#include "manager.h"

using namespace std;

int main() {
    string choice;
    clearTerminal();
    
    do {
        //Viewing menu
        cout << "====================================\n"
             << "========= Password Manager =========\n"
             << "==== by amirsamh at github.com =====\n"
             << "====================================\n\n"
             << "1. View all\n"
             << "2. Add a password\n"
             << "3. Delete a password\n"
             << "4. Quit\n\n"
        ;

        //Asking for user's choice
        cout << "Choose one of the above options (1 - 4): ";
        cin >> choice;
        if (choice == "1") {
            viewAll();
        } else if (choice == "2") {
            addPass();
        } else if (choice == "3") {
            deletePass();
        } else if (choice == "4") {
            break;
        } else {
            clearTerminal();
        }
    } while (choice != "4"); //looping until choosing to quit

    clearTerminal();
    return 0;
}