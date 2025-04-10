#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdlib> 

using namespace std;

#define MAX_USERS 100
#define MAX_LENGTH 50

struct User {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    bool isActive;
};

User users[MAX_USERS];
int userCount = 0;

void loadUsers();
void saveUsers();
void displayMenu();
void registerUser();
bool loginUser();
void reverseString(char* str);  
void convertToUppercase(char* str);  
void convertToLowercase(char* str);  
void encryptPassword(char* password);
void decryptPassword(char* password);

int main() {
   
    loadUsers();
    
    int choice;
    bool loggedIn = false;
    
    do {
        if (!loggedIn) {
            displayMenu();
            cout << "\t\t\t\tEnter your choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1: 
                    registerUser();
                    break;
                case 2:
                    loggedIn = loginUser();
                    if (loggedIn) {
                        cout << "\t\t\t\tLogin successful! Welcome to the system.\n";
                    } else {
                        cout << "\t\t\t\tLogin failed. Please try again.\n";
                    }
                    break;
                case 3:
                    system("cls"); 
                    cout << "\n\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n";
                    cout << "\t\t\t\t[][]                                          [][]\n";
                    cout << "\t\t\t\t[]              GOODBYE! THANK YOU              []\n";
                    cout << "\t\t\t\t[][]                                          [][]\n";
                    cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n\n";
                    break;
                default:
                    cout << "\t\t\t\tInvalid choice. Please try again.\n";
            }
        } else {
            system("cls"); 
            cout << "\n\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n";
            cout << "\t\t\t\t[][]                                          [][]\n";
            cout << "\t\t\t\t[]                  USER MENU                   []\n";
            cout << "\t\t\t\t[][]                                          [][]\n";
            cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n\n";
            cout << "\t\t\t\t1. Logout\n";
            cout << "\t\t\t\t2. Exit\n";
            cout << "\t\t\t\tEnter your choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1:
                    loggedIn = false;
                    cout << "\t\t\t\tLogged out successfully!\n";
                    break;
                case 2:
                    system("cls");
                    cout << "\n\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n";
                    cout << "\t\t\t\t[][]                                          [][]\n";
                    cout << "\t\t\t\t[]              GOODBYE! THANK YOU              []\n";
                    cout << "\t\t\t\t[][]                                          [][]\n";
                    cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n\n";
                    choice = 3; 
                    break;
                default:
                    cout << "\t\t\t\tInvalid choice. Please try again.\n";
            }
        }
    } while (choice != 3);
    
    saveUsers();
    
    return 0;
}

void loadUsers() {
    ifstream file("users.dat", ios::binary);
    if (!file) {
        cout << "\t\t\t\tNo existing user data found. Starting with empty database.\n";
        return;
    }
    
    file.read(reinterpret_cast<char*>(&userCount), sizeof(userCount));
    file.read(reinterpret_cast<char*>(users), sizeof(User) * userCount);
    
    for (int i = 0; i < userCount; i++) {
        decryptPassword(users[i].password);
    }
    
    file.close();
    cout << "\t\t\t\tLoaded " << userCount << " users from database.\n";
}

void saveUsers() {
    
    for (int i = 0; i < userCount; i++) {
        encryptPassword(users[i].password);
    }
    
    ofstream file("users.dat", ios::binary);
    if (!file) {
        cout << "\t\t\t\tError: Unable to save user data.\n";
        return;
    }
    
    file.write(reinterpret_cast<char*>(&userCount), sizeof(userCount));
    file.write(reinterpret_cast<char*>(users), sizeof(User) * userCount);
    
    file.close();

    for (int i = 0; i < userCount; i++) {
        decryptPassword(users[i].password);
    }
    
    cout << "\t\t\t\tSaved " << userCount << " users to database.\n";
}

void displayMenu() {
    cout << "\n\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t\t[][]                                          [][]\n";
    cout << "\t\t\t\t[]            AUTHENTICATION SYSTEM             []\n";
    cout << "\t\t\t\t[][]                                          [][]\n";
    cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n\n";
    cout << "\t\t\t\t1. Register\n";
    cout << "\t\t\t\t2. Login\n";
    cout << "\t\t\t\t3. Exit\n";
}

void registerUser() {
    if (userCount >= MAX_USERS) {
        cout << "\t\t\t\tError: Maximum number of users reached.\n";
        return;
    }
    system("cls");
    cout << "\n\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t\t[][]                                          [][]\n";
    cout << "\t\t\t\t[]               REGISTRATION FORM              []\n";
    cout << "\t\t\t\t[][]                                          [][]\n";
    cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n\n";
    
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char confirmPassword[MAX_LENGTH];
    
    cin.ignore();
    cout << "\t\t\t\tEnter username: ";
    cin.getline(username, MAX_LENGTH);
    
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            cout << "\t\t\t\tSTRCMP: Username already exists. Please choose another.\n";
            return;
        }
    }
    
    cout << "\t\t\t\tEnter password: ";
    cin.getline(password, MAX_LENGTH);

    if (strlen(password) > 8) {
        cout << "\t\t\t\tSTRLEN: Password must be 8 characters or less. Registration failed.\n";
        return;
    }
    
    cout << "\t\t\t\tConfirm password: ";
    cin.getline(confirmPassword, MAX_LENGTH);
    
    if (strcmp(password, confirmPassword) != 0) {
        cout << "\t\t\t\tSTRCMP: Passwords do not match. Registration failed.\n";
        return;
    }
    
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    users[userCount].isActive = true;

    char displayName[MAX_LENGTH];
    strcpy(displayName, username);
    convertToUppercase(displayName); 
    
    char welcomeMsg[100] = "STRCAT: Welcome, STRUPR: ";
    strcat(welcomeMsg, displayName);
    strcat(welcomeMsg, "! Registration successful!");
    
    userCount++;
    
    cout << "\t\t\t\t" << welcomeMsg << " You can now login.\n";

    saveUsers();
}

bool loginUser() {
	system("cls");
    cout << "\n\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t\t[][]                                          [][]\n";
    cout << "\t\t\t\t[]                   LOGIN FORM                 []\n";
    cout << "\t\t\t\t[][]                                          [][]\n";
    cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n\n";
    
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    
    cin.ignore();
    cout << "\t\t\t\tEnter username: STRLWR: ";
    cin.getline(username, MAX_LENGTH);
    
    convertToLowercase(username);
    
    cout << "\t\t\t\tEnter password: STRLWR: ";
    cin.getline(password, MAX_LENGTH);
    
   char tempUsername[MAX_LENGTH], tempPassword[MAX_LENGTH];
    strcpy(tempUsername, username);
    strcpy(tempPassword, password);
    
    convertToLowercase(tempUsername);
    convertToLowercase(tempPassword);
    
    for (int i = 0; i < userCount; i++) {
        char storedUsername[MAX_LENGTH], storedPassword[MAX_LENGTH];
        strcpy(storedUsername, users[i].username);
        strcpy(storedPassword, users[i].password);

        convertToLowercase(storedUsername);
        convertToLowercase(storedPassword);

        if (strcmp(tempUsername, storedUsername) == 0 && strcmp(tempPassword, storedPassword) == 0) {
            return true;
        }
    }
    
    return false;
}

void reverseString(char* str) {
    
    int length = strlen(str);
    char temp;
    
    for (int i = 0; i < length / 2; i++) {
        temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

void convertToUppercase(char* str) {
    int i = 0;
    while (str[i]) {
        str[i] = toupper(str[i]);
        i++;
    }
}

void convertToLowercase(char* str) {
    int i = 0;
    while (str[i]) {
        str[i] = tolower(str[i]);
        i++;
    }
}

void encryptPassword(char* password) {
    char originalPassword[MAX_LENGTH];
    strcpy(originalPassword, password);
    
    reverseString(password);
    
    int len = strlen(password);
    for (int i = 0; i < len; i++) {
        password[i] = password[i] + 3;
    }
    
    strcat(password, "_enc");
}

void decryptPassword(char* password) {
	
    int len = strlen(password);
    int signatureLen = strlen("_enc");
    
    if (len > signatureLen) {

        if (strcmp(password + len - signatureLen, "_enc") == 0) {
            password[len - signatureLen] = '\0';
        }
    }
    
    len = strlen(password);
    for (int i = 0; i < len; i++) {
        password[i] = password[i] - 3;
    }
    
    reverseString(password);
}
