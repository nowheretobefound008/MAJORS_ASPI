#include <iostream>
#include <string.h>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <sstream>

using namespace std;

void displayHeader() {
    cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t\t[][]                                          [][]\n";
    cout << "\t\t\t\t[]               STRING.H FUNCTIONS             []\n";
    cout << "\t\t\t\t[][]                                          [][]\n";
    cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n\n";
}

void displayLoginHeader() {
    cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t\t[][]                                          [][]\n";
    cout << "\t\t\t\t[]                   LOG IN FORM                []\n";
    cout << "\t\t\t\t[][]                                          [][]\n";
    cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n\n";
}

void displaySignUpHeader() {
    cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t\t[][]                                          [][]\n";
    cout << "\t\t\t\t[]                  SIGN UP FORM                []\n";
    cout << "\t\t\t\t[][]                                          [][]\n";
    cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n\n";
}

void getInput(const char* prompt, char* buffer, int size) {
    while (true) {
        cout << "\t\t\t\t" << prompt;
        cin.getline(buffer, size);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "\t\t\t\tInvalid input. Please try again.\n";
        } else {
            bool valid = true;
            for (int i = 0; buffer[i] != '\0'; i++) {
                if (!isalpha(buffer[i])) {
                    valid = false;
                    break;
                }
            }
            if (valid) break;
            cout << "\t\t\t\tInvalid input. Please enter letters only.\n";
        }
    }
}

void getInputGeneral(const char* prompt, char* buffer, int size) {
    while (true) {
        cout << "\t\t\t\t" << prompt;
        cin.getline(buffer, size);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "\t\t\t\tInvalid input. Please try again.\n";
        } else {
            bool valid = true;
            for (int i = 0; buffer[i] != '\0'; i++) {
                if (buffer[i] == '|') {
                    valid = false;
                    break;
                }
            }
            if (valid) break;
            cout << "\t\t\t\tInput cannot contain pipes (|). Please try again.\n";
        }
    }
}

void signUp() {
    system("cls");
    displaySignUpHeader();
    
    char firstname[10], lastname[10], username[10], password[10];
    
    getInput("Enter first name: ", firstname, 10);
    getInput("Enter last name: ", lastname, 10);
    getInputGeneral("Enter username: ", username, 10);
    getInputGeneral("Enter password: ", password, 10);

    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << username << "|" << password << "|" << firstname << "|" << lastname << endl;
        cout << "\t\t\t\tRegistration successful!\n";
    } else {
        cout << "\t\t\t\tError saving user data!\n";
    }
    file.close();
}

bool login(char* firstname, char* lastname) {
    system("cls");
    displayLoginHeader();
    
    char username[10], password[10];
    getInputGeneral("Enter username: ", username, 10);
    getInputGeneral("Enter password: ", password, 10);

    ifstream file("users.txt");
    if (!file.is_open()) {
        cout << "\t\t\t\tNo users registered!\n";
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string storedUsername, storedPassword, storedFirstname, storedLastname;
        
        getline(ss, storedUsername, '|');
        getline(ss, storedPassword, '|');
        getline(ss, storedFirstname, '|');
        getline(ss, storedLastname, '|');

        if (strcmp(username, storedUsername.c_str()) == 0 && 
            strcmp(password, storedPassword.c_str()) == 0) {
            strcpy(firstname, storedFirstname.c_str());
            strcpy(lastname, storedLastname.c_str());
            file.close();
            return true;
        }
    }
    
    file.close();
    cout << "\t\t\t\tInvalid username or password!\n";
    return false;
}

void stringOperations(char* text1, char* text2) {
    char text3[20];
    system("cls");
    displayHeader();

    cout << "\t\t\t\tAfter strlen, Length of text1: " << strlen(text1) << endl;
    cout << "\n\t\t\t\tAfter strlen, Length of text2: " << strlen(text2) << endl;

    strcpy(text3, text1);
    cout << "\n\t\t\t\tAfter strcpy, text3: " << text3 << endl;

    strcat(text1, " ");
    strcat(text1, text2);
    cout << "\n\t\t\t\tAfter strcat, text1: " << text1 << endl;

    int result = strcmp(text3, text2);
    if (result == 0) {
        cout << "\n\t\t\t\tAfter strcmp, text1 and text2 are equal" << endl;
    } else if (result < 0) {
        cout << "\n\t\t\t\tAfter strcmp, text1 is less than text2" << endl;
    } else {
        cout << "\n\t\t\t\tAfter strcmp, text1 is greater than text2" << endl;
    }

    for (int i = 0; text1[i]; i++) text1[i] = tolower(text1[i]);
    cout << "\n\t\t\t\tAfter strlwr, text1: " << text1 << endl;

    for (int i = 0; text1[i]; i++) text1[i] = toupper(text1[i]);
    cout << "\n\t\t\t\tAfter strupr, text1: " << text1 << endl;

    int length = strlen(text1);
    for (int i = 0; i < length / 2; i++) {
        swap(text1[i], text1[length - i - 1]);
    }
    cout << "\n\t\t\t\tAfter strrev, text1: " << text1 << endl;
}

int main() {
    int choice;
    char firstname[10], lastname[10];

    while (true) {
        system("cls");
        displayLoginHeader();
        cout << "\t\t\t\t1. Sign Up\n\t\t\t\t2. Log In\n\t\t\t\t3. Exit\n";
        cout << "\t\t\t\tEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                if (login(firstname, lastname)) {
                    char text1[10], text2[10];
                    strcpy(text1, firstname);
                    strcpy(text2, lastname);
                    stringOperations(text1, text2);
                    cout << "\n\t\t\t\tPress enter to exit...";
                    cin.ignore();
                    return 0;
                }
                break;
            case 3:
                return 0;
            default:
                cout << "\t\t\t\tInvalid choice!\n";
                break;
        }
        cout << "\t\t\t\tPress enter to continue...";
        cin.ignore();
    }
}
