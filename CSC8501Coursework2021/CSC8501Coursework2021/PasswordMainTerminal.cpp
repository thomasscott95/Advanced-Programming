#include "PasswordMainTerminal.h"
#include "Manager.h"


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;


Manager manager = Manager();

void menu() {
    cout << "Choose Following Opions \n\n"
        << "1. Create Username & Password\n"
        << "2. Check Username & Password\n"
        << "3. Generate Password Strength Anaysis\n"
        << "4. Analys Password Strength File\n"
        << "Enter your choice: ";
}

void runCreatePassword() {
    manager.createUsernamePassword();
}

void runLogIn() {
    manager.logIn();
}

void runPasswordGenerator() {
    manager.randomPasswordGenerator10000();
    manager.randomPasswordGenerator20000();
}

int main()
{
    int menuChoice;
    bool reset = true;

    do {
        menu();
        cin >> menuChoice;

        switch (menuChoice)

        {
        case 1:

            cout << "Create Username & Password Selected" << endl;
            runCreatePassword();
            cout << "Complete!\n";

            break;

        case 2:
            cout << "Check Username & Password Selected" << endl;
            runLogIn();
            cout << "Complete!\n";

            break;



        case 3:
            cout << "Generate Password Strength Anaysis Selected" << endl;
            runPasswordGenerator();
            cout << "Complete!\n";
            break;


        case 4:
            cout << "Analys Password Strength File Selected" << endl;
            manager.readCrack();
            cout << "Complete!\n";
            break;

        default:
        {
            reset = true;
            break;
        }

        }

    } while (reset);
}