#include <iostream>       // for input/output operations 
#include <vector>         // to store dynamic arrays
#include <string>         // text-based data like usernames, passwords, and transaction descriptions.
#include <sstream>        // combine text and variables into a single string,
#include <limits>         // used to handle input validation (numeric limit)
#include <cstdlib>        // for system("cls") to clear the screen

using namespace std;

#define PHP "PHP "  // define the currency symbol for Philippine Peso

struct User {
    string username;
    string password;
    float balance;
    vector<string> transactionHistory;  // to keep track of all transactions for a user.

    // to initialize user with username, password, and balance set to 0
    User(string user, string pass) {
        username = user;
        password = pass;
        balance = 0.0f;
    }

    void addTransaction(const string& transaction) {
        transactionHistory.push_back(transaction);  // add a new transaction to the history
    }
};

class BankSystem {
private:
    User* currentUser;  // pointer to the currently logged-in user
    vector<User> users;  // list to store all user accounts

public:
    BankSystem() {
        currentUser = NULL;  // no user is logged in initially
    }

    // for the currently logged-in user.
    User* getCurrentUser() {
        return currentUser;
    }

    void createAccount() {
        string username, password;
        cout << "\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t[][][][][][][][][][][][][[][][][][][]\n";
        cout << "\t\t\t\t\t[][][]           Sign Up         [][]\n";
        cout << "\t\t\t\t\t[][][][][][][][][][][][][[][][][][][]\n";
        cout << "\n\t\t\t\t\tEnter username: ";
        cin >> username;
        cout << "\n\t\t\t\t\tEnter password: ";
        cin >> password;

        // add new user to the users list
        users.push_back(User(username, password));
        cout << "\t\t\t\t\tAccount created successfully!";
        system("cls");  // clear the screen
    }

    void login() {
        string username, password;
        cout << "\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t[][][][][][][][][][][][][[][][][][][]\n";
        cout << "\t\t\t\t\t[][][]           Log In          [][]\n";
        cout << "\t\t\t\t\t[][][][][][][][][][][][][[][][][][][]\n";
        cout << "\n\t\t\t\t\tEnter username: ";
        cin >> username;
        cout << "\n\t\t\t\t\tEnter password: ";
        cin >> password;

        for (size_t i = 0; i < users.size(); ++i) {
            User& user = users[i];  // accessing user by reference using index
            if (user.username == username && user.password == password) {
                currentUser = &user;  // if found, set the currentUser to the found user
                cout << "\t\t\t\t\tLogin successful!\n";
                system("cls");  // clear the screen
                return;
            }
        }

        // if no matching user is found, display an error message
        cout << "\t\t\t\t\tInvalid credentials. Try again.\n";
        system("cls");  // clear the screen
    }

    void checkBalance() {
    	system("cls");  // clear the screen
        if (currentUser != NULL) {
            cout << "\t\t\t\t\tYour balance: " << PHP << currentUser->balance << "\n";
        } else {
            cout << "\t\t\t\t\tYou need to log in first.\n";
        }
    }

    void deposit() {
        if (currentUser != NULL) {
            float amount;
            system("cls");  // clear the screen
            cout << "\t\t\t\t\tEnter deposit amount: " << PHP;

            // input validation for deposit amount
            while (!(cin >> amount) || amount <= 0) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
                cout << "\t\t\t\t\tInvalid input. Please enter a valid positive number: " << PHP;
            }

            currentUser->balance += amount;  // add the deposit amount to the user's balance
            stringstream ss;
            ss << "\n\t\t\t\t\tDeposited " << amount << " PHP";
            currentUser->addTransaction(ss.str());  // add transaction to history
            cout << "\t\t\t\t\tDeposit successful! New balance: " << PHP << currentUser->balance << "\n";
        } else {
            cout << "\t\t\t\t\tYou need to log in first.\n";
        }
    }

    void withdraw() {
        if (currentUser != NULL) {
            float amount;
            system("cls");  // clear the screen
            cout << "\t\t\t\t\tEnter withdrawal amount: " << PHP;

            // input validation for withdrawal amount
            while (!(cin >> amount) || amount <= 0) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
                cout << "\t\t\t\t\tInvalid input. Please enter a valid positive number: " << PHP;
            }

            // check if the user has sufficient balance
            if (amount <= currentUser->balance) {
                currentUser->balance -= amount;  // subtract the withdrawal amount from the user's balance
                stringstream ss;
                ss << "\n\t\t\t\t\tWithdrew " << amount << " PHP";
                currentUser->addTransaction(ss.str());  // add transaction to history
                cout << "\t\t\t\t\tWithdrawal successful! New balance: " << PHP << currentUser->balance << "\n";
            } else {
                cout << "\t\t\t\t\tInsufficient balance.\n";
            }
        } else {
            cout << "\t\t\t\t\tYou need to log in first.";
        }
    }

    void showTransactionHistory() {
        if (currentUser != NULL) {
        	system("cls");  // clear the screen
        	cout << "\n\n\n\n\n\n\n\n";
            cout << "\t\t\t\t\t[][][][][][][][][][][][][[][][][][][]\n";
            cout << "\t\t\t\t\t[][][]    Transaction History    [][]\n";
            cout << "\t\t\t\t\t[][][][][][][][][][][][][[][][][][][]\n";
            if (currentUser->transactionHistory.empty()) {
                cout << "\t\t\t\t\tNo transactions found.";
            } else {
                for (size_t i = 0; i < currentUser->transactionHistory.size(); ++i) {
                    cout << currentUser->transactionHistory[i] << endl;
                }
            }
        } else {
            cout << "\t\t\t\t\t\tYou need to log in first.";
        }
    }

    void transferMoney() {
        if (currentUser != NULL) {
            string recipientUsername;
            float amount;
            cout << "\n\n\n\n\n\n\n\n";
            cout << "\t\t\t\t\tEnter the recipient's username: ";
            cin >> recipientUsername;

            // find the recipient user
            User* recipientUser = NULL;
            for (size_t i = 0; i < users.size(); ++i) {
                if (users[i].username == recipientUsername) {
                    recipientUser = &users[i];
                    break;
                }
            }

            if (recipientUser == NULL) {
                cout << "\t\t\t\t\tRecipient not found.\n";
                return;
            }
            cout << "\t\t\t\t\tEnter the amount to transfer: " << PHP;

            // input validation for transfer amount
            while (!(cin >> amount) || amount <= 0) {
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
                cout << "\t\t\t\t\tInvalid input. Please enter a valid positive number: " << PHP;
            }

            // check if the current user has enough balance
            if (currentUser->balance < amount) {
                cout << "\t\t\t\t\tInsufficient balance.\n";
                return;
            }

            // transfer the amount
            currentUser->balance -= amount;
            recipientUser->balance += amount;

            // add transaction history for both users
            stringstream ss1, ss2;
            ss1 << "\n\t\t\t\t\tTransferred " << amount << " PHP to " << recipientUsername;
            ss2 << "\n\t\t\t\t\tReceived " << amount << " PHP from " << currentUser->username;
            currentUser->addTransaction(ss1.str());
            recipientUser->addTransaction(ss2.str());

            cout << "\n\t\t\t\t\tTransfer successful! \n New balance: " << PHP << currentUser->balance << "\n";
        } else {
            cout << "\t\t\t\t\tYou need to log in first.";
        }
        system("cls");  // clear the screen
    }

    void logout() {
        if (currentUser != NULL) {
            cout << "\t\t\t\t\tLogged out successfully.";
            currentUser = NULL;  // set currentUser to NULL (log out the user)
        } else {
            cout << "\t\t\t\t\tYou are not logged in.";
        }
        system("cls");  // clear the screen
    }

    void showLoggedInMenu() {
        int choice;
        while (true) {
            cout << "\n\n\n\n\n\n\n";
            cout << "\t\t\t\t\t[][][][][][][][][][][][][[][][][][][]\n";
            cout << "\t\t\t\t\t[][][]       Log In Menu       [][][]\n";
            cout << "\t\t\t\t\t[][][][][][][][][][][][][[][][][][][]\n";
            cout << "\t\t\t\t\t[][]                             [][]\n";
            cout << "\t\t\t\t\t[]           1. Deposit            []\n";
            cout << "\t\t\t\t\t[            2. Withdraw            ]\n";
            cout << "\t\t\t\t\t[            3. Check Balance       ]\n";
            cout << "\t\t\t\t\t[            4. Transaction         ]\n";
            cout << "\t\t\t\t\t[            5. Transfer            ]\n";
            cout << "\t\t\t\t\t[]           6. Logout             []\n";
            cout << "\t\t\t\t\t[][]                             [][]\n";
            cout << "\t\t\t\t\t[][][][][][][][][][][][][[][][][][][]\n";
            cout << "\n\t\t\t\t\tEnter your choice: ";

            // input validation for menu choice
            while (!(cin >> choice)) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
                cout << "\t\t\t\t\tInvalid input. Please enter a number (1-6): ";
            }
            system("cls");  // clear the screen

            switch (choice) {
                case 1:
                    deposit();  
                    break;
                case 2:
                    withdraw(); 
                    break;
                case 3:
                    checkBalance();  
                    break;
                case 4:
                    showTransactionHistory(); 
                    break;
                case 5:
                    transferMoney();  
                    break;
                case 6:
                    logout(); 
                    return;
                default:
                    cout << "\t\t\t\t\tInvalid choice. Try again.";
                    break;
            }
        }
    }
};

int main() {
    BankSystem bank;   // serves as the central controller for the entire banking application.
    int choice;

    while (true) {
        cout << "\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t[][][][][][][][][][][][][[][][][][][]\n";
        cout << "\t\t\t\t\t[][][]        Main Menu        [][][]\n";
        cout << "\t\t\t\t\t[][][][][][][][][][][][][[][][][][][]\n";
        cout << "\t\t\t\t\t[][]                             [][]\n";
        cout << "\t\t\t\t\t[]           1. Sign Up            []\n";
        cout << "\t\t\t\t\t[            2. Login               ]\n";
        cout << "\t\t\t\t\t[]           3. Exit               []\n";
        cout << "\t\t\t\t\t[][]                             [][]\n"; 
        cout << "\t\t\t\t\t[][][][][][][][][][][][][[][][][][][]\n";
        cout << "\n\t\t\t\t\tEnter your choice: ";

        // input validation for main menu choice
        while (!(cin >> choice)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
            cout << "\t\t\t\t\tInvalid input. Please enter a number (1-3): ";
        }
        system("cls");  // clear the screen

        switch (choice) {
            case 1:
                bank.createAccount();  
                break;
            case 2:
                bank.login();  
                if (bank.getCurrentUser() != NULL) {
                    bank.showLoggedInMenu();  // show logged-in user menu after login
                }
                break;
            case 3:
                cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tGoodbye!\n";
                return 0;  
            default:
                cout << "\t\t\t\t\tInvalid choice. Try again.";
                
        }
    }

    return 0;  
}
