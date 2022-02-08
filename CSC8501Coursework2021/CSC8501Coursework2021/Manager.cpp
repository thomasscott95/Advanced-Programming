#include "Manager.h"


using namespace std;

Manager::Manager() {

}

string Manager::encyrpt(string password) {
    int encryption;
    int offset = 0;
    string output;

    for (int i = 0; (unsigned)i < password.length(); i++) {
        auto count = 0;
        unsigned char character = password[i];
        encryption = static_cast <int> (character) + offset;
        while (encryption != 1) {
            if (encryption % 2 == 0) {
                encryption /= 2;
            }
            else {
                encryption = 3 * encryption + 1;
            }

            count++;
        }
        offset = count;
        output = output + to_string(count);

    }

    return output;
}

void Manager::createUsernamePassword() {
    string username;
    string password;

    fstream myfile("password.txt", ios::out | ios::binary | ios::app);
    try {
        if (myfile.is_open())
        {
            cout << "Enter New Username: ";
            cin >> username;
            cout << "Enter New Password: ";
            cin >> password;
            myfile << username << " ";
            string output = encyrpt(password);
            myfile << output;

            myfile << endl;

            myfile.close();
        }
    }
    catch (...) { "Access Denined"; }

}

void Manager::logIn() {

    string line = " ";
    ifstream readFile("password.txt");
    string username;
    string password;
    string _userName;
    string _password;
    int attemps = 3;

    bool found = false;
    readFile.clear();
    readFile.seekg(0, ios::beg);


    while (!found && attemps > 0) {


        cout << "Attempts Left - : " << attemps << endl;

        cout << "Enter UserName: ";
        cin >> username;

        cout << "Enter Password: ";
        cin >> password;
        password = encyrpt(password);

        readFile.clear();
        readFile.seekg(0, ios::beg);
        while (getline(readFile, line) && !found) {
            stringstream iss(line);
            iss >> _userName >> _password;
            found = username == _userName && password == _password;
        }

        if (found) { cout << "Login Successfully!" << endl; }
        else { cout << "Invalid UserName And Password: " << endl; }
        --attemps;
    }
}

char Manager::randomChar(int start, int size) {
    return start + rand() % size;
}

void Manager::randomPasswordGenerator10000() {

    fstream myfile("passwordtest.txt", ios::out | ios::binary | ios::app);
    int randPassword = 100;
    int passwordLength = 1;

    srand((unsigned)time(0));

    if (myfile.is_open()) {


        for (int a = 1; a <= 100; a++) {
            for (int i = 0; i < randPassword; i++) {
                string password;
                for (int j = 0; j < passwordLength; j++) {

                    password += randomChar(97, 10);
                }

                string(*enPass)(string) = &encyrpt; // Points to encyrpt function.
                myfile << (*enPass)(password) << endl;

                //password = encyrpt(password);
                //myfile << password << endl;
            }
            passwordLength++;
        }
        myfile.close();
    }
}

void Manager::randomPasswordGenerator20000() {

    fstream myfile("passwordtest.txt", ios::out | ios::binary | ios::app);
    int randPassword = 100;
    int passwordLength = 1;

    srand((unsigned)time(0));

    if (myfile.is_open()) {


        for (int a = 1; a <= 100; a++) {
            for (int i = 0; i < randPassword; i++) {
                string password;
                unsigned char previousChar = 256;
                for (int j = 0; j < passwordLength; j++) {
                    unsigned char currentChar;
                    do {
                        currentChar = randomChar(0, 256);
                    } while (currentChar == previousChar);
                    previousChar = currentChar;
                    password += currentChar;
                }

                string(*enPass)(string) = &encyrpt;
                myfile << (*enPass)(password) << endl;

                //password = encyrpt(password);
                //myfile << password << endl;
            }
            passwordLength++;
        }

        myfile.close();
    }
}


void  Manager::readCrack() {
    ifstream readFile("passwordtest.txt");
    string password;
    string decyrptedPassword;
    string temp;
    int cracked = 0;
    int notCracked = 0;

    auto start = chrono::steady_clock::now();

    auto end = chrono::steady_clock::now();
    auto diff = end - start;

    //cout << chrono::duration<double, milli>(diff).count << "ms" << endl;

    try {
        if (readFile.is_open()) {
            while (getline(readFile, password)) {
                decyrptedPassword = Cracked(password);
                if (temp == password) {
                    temp = encyrpt(decyrptedPassword);
                    cout << "cracked " << cracked++ << endl;



                }
                else {
                    temp = encyrpt(decyrptedPassword);
                    cout << "not cracked " << notCracked++ << endl;

                }


            }
            cout << chrono::duration<double, milli>(diff).count();
            cout << " millisecounds\n";

        }


    }
    catch (...) { cout << "File Didnt Open or Doesnt exitist"; }

}

int collatz(int value) {
    int count = 0;
    while (value != 1) {
        if (value % 2 == 0) {
            value /= 2;
        }
        else {
            value = 3 * value + 1;
        }
        count++;

    }
    return count;
}

string  Manager::Cracked(string& encrypted_password, int startIndex, int offset) {
    int newPassword;
    string password;
    int len = 0;
    for (int size = 0; size < 3 && size + startIndex < encrypted_password.size(); size++) {

        len = len * 10 + (encrypted_password[startIndex + size] - 48);
        for (int start = 1; start < 256; start++) {
            newPassword = collatz(start + offset);




            if (newPassword == len) {
                if (startIndex + size == encrypted_password.size() - 1) {
                    return  "" + static_cast<char>(start);

                }
                else {
                    password = Cracked(encrypted_password, startIndex + size + 1, newPassword);
                    if (password.length() != newPassword) {
                        return static_cast<char>(start) + password;
                    }
                }
            }
        }

    }
    return "";
} // was trying to optimiise and make more effient