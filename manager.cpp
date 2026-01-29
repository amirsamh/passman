#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "manager.h"

using namespace std;

constexpr const char* YELLOW = "\033[33m";
constexpr const char* GREEN = "\033[1;32m";
constexpr const char* WHITE = "\033[0m";
constexpr const char* RED = "\033[1;31m";

struct Entry {
    string site;
    string username;
    string password;
};

vector <Entry> entries;

void clearTerminal() {
    //Clearing the terminal screen before going into a new menu
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForEnter() {
    //Waiting for user to hit ENTER key and go back to main menu
    cout << "\nPress ENTER to return to main menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

string removeWhiteSpace(string &s) {
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    return s;
}

bool load() {
    //Clearing the previous load
    entries.clear();

    //Opening the file
    ifstream f("data.txt");
    if (!f) {
        cout << RED
             << "File was not found!\n"
             << "Add a new password to create a new database.\n"
             << WHITE;
        return 1;
    }
    
    //Passing file data into vector
    string line;
    string site, username, password;
    Entry e;
    while (getline(f, line)) {
        stringstream parser(line);
        getline(parser, site, '|');
        getline(parser, username, '|');
        getline(parser, password, '|');

        e.site = site;
        e.username = username;
        e.password = password;
        entries.push_back(e);
    }
    f.close();
    return 0;
}

bool printEntries() {
    clearTerminal();

    //Printing loaded data into terminal
    if (load() == 0) {
        cout << "========= All Passwords =========\n";
        for (int i = 0; i < entries.size(); i++) {
            cout << "[" << i+1 << "]: " << "Site URL: " << entries[i].site << endl;
            cout << "     Username: " << removeWhiteSpace(entries[i].username) << endl;
            cout << "     Password: " << removeWhiteSpace(entries[i].password) << endl;
            cout << "---------------------------------\n";
        }
        return 0;
    } else {
        return 1;
    }
}

void viewAll() {
    printEntries();
    waitForEnter();
    clearTerminal();
    return;
}

void addPass() {
    clearTerminal();

    string site, username, password;
    cout << "========= Add a Password =========\n";
    cout << "Site name: ";
    cin >> site;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    //Opening the file in append mode
    ofstream f("data.txt", std::ios::app);

    //appending new password to the file
    f << site << " | " << username << " | " << password << "\n";
    f.close();

    clearTerminal();
    cout << GREEN
         << "New password was added successfully.\n"
         << WHITE; 
    return;
}

void deletePass() {
    if (printEntries() == 1) {
        return;
    }

    if (entries.size() == 0) {
        clearTerminal();
        cout << RED
             << "No password to delete! create one first.\n"
             << WHITE;
        return;
    }
    
    int choice;
    cout << "\n======= Delete a Password =======\n";
    while (true) {
        cout << "Choose the password to delete: ";
        if (cin >> choice && choice <= entries.size()) {
            break;
        } 

        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    string response;
    cout << YELLOW
         << "Are you sure you want to delete password number " << choice << "? (Y/n): "
         << WHITE;
    cin >> response;
    if (response != "Y" && response != "y") {
        clearTerminal();
        return;
    }

    entries.erase(entries.begin() + (choice - 1));

    ofstream f("data.txt", std::ios::trunc);

    string site, username, password;
    for (int i = 0; i < entries.size(); i++) {
        site = removeWhiteSpace(entries[i].site);
        username = removeWhiteSpace(entries[i].username);
        password = removeWhiteSpace(entries[i].password);
        f << site << " | " << username << " | " << password << "\n";
    }

    f.close();

    clearTerminal();
    cout << GREEN
         << "Password was deleted successfully.\n"
         << WHITE;
    return;
}