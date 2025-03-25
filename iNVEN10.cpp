#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <limits>
#include <cctype>
#include <sstream>
#include <algorithm>

using namespace std;

struct Component {
    string status;
    int quantity;
};

struct Computer {
    string pcNumber;
    Component mouse;
    Component keyboard;
    Component monitor;
    Component lanCable;
    Component systemUnit;
    Component powerSupply;
    string status;
    bool exists;
};

// Function prototypes
void displayMainMenu();
void displayComputerManagementMenu();
void displayComponentManagementMenu();
void displayDisplayOptionsMenu();
void addComputer(vector<Computer>& computers);
void editComputer(vector<Computer>& computers);
void deleteComputer(vector<Computer>& computers);
void searchComputer(const vector<Computer>& computers);
void managePCComponents(vector<Computer>& computers);
void displayLabMap(vector<Computer>& computers);
void displayComponentStatus(const vector<Computer>& computers);
void displayComputerStatus(const vector<Computer>& computers);
void displayAllComputers(const vector<Computer>& computers);
string getComponentStatusChoice();
string getComputerStatusChoice();
int getValidQuantity();
void clearInputBuffer();
void waitForKeyPress();
void initializeComputers(vector<Computer>& computers);
string intToString(int value);

struct ComputerFinder {
    string pcNum;
    ComputerFinder(const string& num) : pcNum(num) {}
    bool operator()(const Computer& c) {
        return (c.pcNumber == pcNum) && c.exists;
    }
};

struct PCNumberFinder {
    string pcNum;
    PCNumberFinder(const string& num) : pcNum(num) {}
    bool operator()(const Computer& c) {
        return c.pcNumber == pcNum;
    }
};

int main() {
    vector<Computer> computers;
    initializeComputers(computers);
    int choice = 0;

    while(true) {
        system("cls");
        displayMainMenu();
        cout << "\n\t\t\tEnter your choice (1-4): ";
        
        if(!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\t\t\tInvalid input. Please enter a number.\n";
            waitForKeyPress();
            continue;
        }

        switch(choice) {
            case 1: {
                system("cls");
                displayComputerManagementMenu();
                int subChoice;
                cout << "\n\t\t\tEnter your choice (1-5): ";
                
                if(!(cin >> subChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n\t\t\tInvalid input. Please enter a number.\n";
                    waitForKeyPress();
                    break;
                }

                switch(subChoice) {
                    case 1: addComputer(computers); break;
                    case 2: editComputer(computers); break;
                    case 3: deleteComputer(computers); break;
                    case 4: searchComputer(computers); break;
                    case 5: break;
                    default:
                        cout << "\n\t\t\tInvalid choice. Please try again.\n";
                        waitForKeyPress();
                }
                break;
            }
            
            case 2: {
                system("cls");
                displayComponentManagementMenu();
                int subChoice;
                cout << "\n\t\t\tEnter your choice (1-5): ";
                
                if(!(cin >> subChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n\t\t\tInvalid input. Please enter a number.\n";
                    waitForKeyPress();
                    break;
                }

                switch(subChoice) {
                    case 1: case 2: case 3: case 4: 
                        managePCComponents(computers); 
                        break;
                    case 5: break;
                    default:
                        cout << "\n\t\t\tInvalid choice. Please try again.\n";
                        waitForKeyPress();
                }
                break;
            }
            
            case 3: {
                system("cls");
                displayDisplayOptionsMenu();
                int subChoice;
                cout << "\n\t\t\tEnter your choice (1-5): ";
                
                if(!(cin >> subChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n\t\t\tInvalid input. Please enter a number.\n";
                    waitForKeyPress();
                    break;
                }

                switch(subChoice) {
                    case 1: displayLabMap(computers); break;
                    case 2: displayComponentStatus(computers); break;
                    case 3: displayComputerStatus(computers); break;
                    case 4: displayAllComputers(computers); break;
                    case 5: break;
                    default:
                        cout << "\n\t\t\tInvalid choice. Please try again.\n";
                        waitForKeyPress();
                }
                break;
            }
            
            case 4:
                cout << "\n\t\t\tExiting Computer Laboratory Inventory System. Thank you!\n";
                return 0;
            
            default:
                cout << "\n\t\t\tInvalid choice. Please try again.\n";
                waitForKeyPress();
        }
    }
    return 0;
}

string intToString(int value) {
    stringstream ss;
    ss << value;
    return ss.str();
}

void initializeComputers(vector<Computer>& computers) {
    computers.clear();
    for(int i = 1; i <= 20; i++) {
        Computer comp;
        comp.pcNumber = "PC" + string(i < 10 ? "0" : "") + intToString(i);
        
        comp.mouse.status = "WORKING";
        comp.mouse.quantity = 1;
        comp.keyboard.status = "WORKING";
        comp.keyboard.quantity = 1;
        comp.monitor.status = "WORKING";
        comp.monitor.quantity = 1;
        comp.lanCable.status = "WORKING";
        comp.lanCable.quantity = 1;
        comp.systemUnit.status = "WORKING";
        comp.systemUnit.quantity = 1;
        comp.powerSupply.status = "WORKING";
        comp.powerSupply.quantity = 1;
        
        comp.status = "GOOD";
        comp.exists = true;
        computers.push_back(comp);
    }
}

string getComponentStatusChoice() {
    int choice;
    while(true) {
        cout << "\t\t\t1. WORKING\n\t\t\t2. NOT WORKING\n\t\t\tEnter choice (1-2): ";
        if(cin >> choice && (choice == 1 || choice == 2)) {
            return (choice == 1) ? "WORKING" : "NOT WORKING";
        }
        cout << "\t\t\tInvalid choice! ";
        clearInputBuffer();
    }
}

string getComputerStatusChoice() {
    int choice;
    while(true) {
        cout << "\t\t\t1. GOOD\n\t\t\t2. BAD\n\t\t\tEnter choice (1-2): ";
        if(cin >> choice && (choice == 1 || choice == 2)) {
            return (choice == 1) ? "GOOD" : "BAD";
        }
        cout << "\t\t\tInvalid choice! ";
        clearInputBuffer();
    }
}

int getValidQuantity() {
    int quantity;
    while(true) {
        if(!(cin >> quantity) || quantity < 0) {
            cout << "\t\t\tInvalid quantity. Please enter a non-negative number: ";
            clearInputBuffer();
        } else {
            clearInputBuffer();
            return quantity;
        }
    }
}

void addComputer(vector<Computer>& computers) {
    vector<Computer>::iterator it;
    for(it = computers.begin(); it != computers.end(); ++it) {
        if(!it->exists) break;
    }

    if(it != computers.end()) {
        it->exists = true;
        cout << "\n\t\t\tComputer " << it->pcNumber << " added successfully!\n";
    } else {
        cout << "\n\t\t\tMaximum capacity reached (20 computers). Cannot add more.\n";
    }
    waitForKeyPress();
}

void editComputer(vector<Computer>& computers) {
    string pcNum;
    cout << "\n\t\t\tEnter PC number to edit: ";
    cin >> pcNum;
    transform(pcNum.begin(), pcNum.end(), pcNum.begin(), ::toupper);

    vector<Computer>::iterator it = find_if(computers.begin(), computers.end(), ComputerFinder(pcNum));

    if(it == computers.end()) {
        cout << "\n\t\t\tComputer not found!\n";
        waitForKeyPress();
        return;
    }

    cout << "\n\t\t\tSet overall status:\n";
    it->status = getComputerStatusChoice();
    cout << "\n\t\t\tComputer status updated successfully!\n";
    waitForKeyPress();
}

void deleteComputer(vector<Computer>& computers) {
    string pcNum;
    cout << "\n\t\t\tEnter PC number to delete: ";
    cin >> pcNum;
    transform(pcNum.begin(), pcNum.end(), pcNum.begin(), ::toupper);

    vector<Computer>::iterator it = find_if(computers.begin(), computers.end(), ComputerFinder(pcNum));

    if(it != computers.end()) {
        it->exists = false;
        cout << "\n\t\t\tComputer " << pcNum << " deleted successfully!\n";
    } else {
        cout << "\n\t\t\tComputer not found!\n";
    }
    waitForKeyPress();
}

void searchComputer(const vector<Computer>& computers) {
    string pcNum;
    cout << "\n\t\t\tEnter PC number to search: ";
    cin >> pcNum;
    transform(pcNum.begin(), pcNum.end(), pcNum.begin(), ::toupper);

    vector<Computer>::const_iterator it = find_if(computers.begin(), computers.end(), ComputerFinder(pcNum));

    if(it == computers.end()) {
        cout << "\n\t\t\tComputer not found!\n";
        waitForKeyPress();
        return;
    }

    cout << "\n\t\t\tComputer " << pcNum << " Status:\n";
    cout << "\t\t\t--------------------------------\n";
    cout << "\t\t\tOverall Status: " << it->status << endl;
    cout << "\t\t\tMouse: " << it->mouse.status << " (Qty: " << it->mouse.quantity << ")\n";
    cout << "\t\t\tKeyboard: " << it->keyboard.status << " (Qty: " << it->keyboard.quantity << ")\n";
    cout << "\t\t\tMonitor: " << it->monitor.status << " (Qty: " << it->monitor.quantity << ")\n";
    cout << "\t\t\tLAN Cable: " << it->lanCable.status << " (Qty: " << it->lanCable.quantity << ")\n";
    cout << "\t\t\tSystem Unit: " << it->systemUnit.status << " (Qty: " << it->systemUnit.quantity << ")\n";
    cout << "\t\t\tPower Supply: " << it->powerSupply.status << " (Qty: " << it->powerSupply.quantity << ")\n";
    waitForKeyPress();
}

void managePCComponents(vector<Computer>& computers) {
    string pcNum;
    cout << "\n\t\t\tEnter PC number to manage components: ";
    cin >> pcNum;
    transform(pcNum.begin(), pcNum.end(), pcNum.begin(), ::toupper);

    vector<Computer>::iterator it = find_if(computers.begin(), computers.end(), ComputerFinder(pcNum));

    if(it == computers.end()) {
        cout << "\n\t\t\tComputer not found!\n";
        waitForKeyPress();
        return;
    }

    cout << "\n\t\t\tSelect component to manage:\n"
    	 << "\t\t\t1. Mouse\n"
    	 << "\t\t\t2. Keyboard\n"
    	 << "\t\t\t3. Monitor\n"
    	 << "\t\t\t4. LAN Cable\n"
    	 << "\t\t\t5. System Unit\n"
    	 << "\t\t\t6. Power Supply\n"
         << "\t\t\tEnter your choice: ";

    int choice;
    if(!(cin >> choice) || choice < 1 || choice > 6) {
        cout << "\n\t\t\tInvalid selection!\n";
        clearInputBuffer();
        waitForKeyPress();
        return;
    }

    Component* comp = NULL;
    string componentName;
    switch(choice) {
        case 1: comp = &it->mouse; componentName = "Mouse"; break;
        case 2: comp = &it->keyboard; componentName = "Keyboard"; break;
        case 3: comp = &it->monitor; componentName = "Monitor"; break;
        case 4: comp = &it->lanCable; componentName = "LAN Cable"; break;
        case 5: comp = &it->systemUnit; componentName = "System Unit"; break;
        case 6: comp = &it->powerSupply; componentName = "Power Supply"; break;
    }

    cout << "\n\t\t\tCurrent " << componentName << " Status: " << comp->status << endl;
    cout << "\t\t\tCurrent Quantity: " << comp->quantity << endl;
    
    cout << "\t\t\tEnter new status:\n";
    comp->status = getComponentStatusChoice();
    
    cout << "\t\t\tEnter new quantity: ";
    comp->quantity = getValidQuantity();

    cout << "\n\t\t\t" << componentName << " updated successfully!\n";
    waitForKeyPress();
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void waitForKeyPress() {
    cout << "\n\t\t\tPress any key to continue...";
    _getch();
}

void displayMainMenu() {
    cout << "\n\n\n";
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t[][][]                                                            [][][]\n";
    cout << "\t\t\t[][]            COMPUTER LABORATORY INVENTORY SYSTEM                [][]\n";
    cout << "\t\t\t[][][]                                                            [][][]\n";
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t[][]                                                                [][]\n";
    cout << "\t\t\t[]                   [1] COMPUTER MANAGEMENT                          []\n";
    cout << "\t\t\t[]                   [2] COMPONENT MANAGEMENT                         []\n";
    cout << "\t\t\t[]                   [3] DISPLAY OPTION                               []\n";
    cout << "\t\t\t[]                   [4] EXIT INVENTORY                               []\n";
    cout << "\t\t\t[][]                                                                [][]\n";
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n\n";
}

void displayComputerManagementMenu() {
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t[][][]                                [][][]\n";
    cout << "\t\t\t[][]        COMPUTER MANAGEMENT         [][]\n";
    cout << "\t\t\t[][][]                                [][][]\n";
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t[][]                                    [][]\n";
    cout << "\t\t\t[]           [1] ADD COMPUTER             []\n";
    cout << "\t\t\t[]           [2] EDIT COMPUTER            []\n";
    cout << "\t\t\t[]           [3] DELETE COMPUTER          []\n";
    cout << "\t\t\t[]           [4] SEARCH COMPUTER          []\n";
    cout << "\t\t\t[]           [5] BACK OPTION              []\n";
    cout << "\t\t\t[][]                                    [][]\n";
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][]\n\n";
}

void displayComponentManagementMenu() {
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t[][][]                                [][][]\n";
    cout << "\t\t\t[][]        COMPONENT MANAGEMENT        [][]\n";
    cout << "\t\t\t[][][]                                [][][]\n";
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t[][]                                    [][]\n";
    cout << "\t\t\t[]           [1] ADD COMPONENT            []\n";
    cout << "\t\t\t[]           [2] EDIT COMPONENT           []\n";
    cout << "\t\t\t[]           [3] DELETE COMPONENT         []\n";
    cout << "\t\t\t[]           [4] SEARCH COMPONENT         []\n";
    cout << "\t\t\t[]           [5] BACK OPTION              []\n";
    cout << "\t\t\t[][]                                    [][]\n";
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][]\n\n";
}

void displayDisplayOptionsMenu() {
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t[][][]                                [][][]\n";
    cout << "\t\t\t[][]           DISPLAY OPTIONS          [][]\n";
    cout << "\t\t\t[][][]                                [][][]\n";
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t[][]                                    [][]\n";
    cout << "\t\t\t[]           [1] COMPLAB MAP              []\n";
    cout << "\t\t\t[]           [2] COMPONENT STATUS         []\n";
    cout << "\t\t\t[]           [3] COMPUTER STATUS          []\n";
    cout << "\t\t\t[]           [4] FULL SYSTEM STATUS       []\n";
    cout << "\t\t\t[]           [5] BACK OPTION              []\n";
    cout << "\t\t\t[][]                                    [][]\n";
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][]\n\n";
}

void displayLabMap(vector<Computer>& computers) {
    char choice;
    do {
        system("cls");
        cout << "\n\n\n";
        cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n";
        cout << "\t\t\t[][][]                                                            [][][]\n";
        cout << "\t\t\t[][]                      COMPUTER LABORATORY                       [][]\n";
        cout << "\t\t\t[][][]                                                            [][][]\n";
        cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n";

        for(int i = 0; i < 20; i += 5) {
            cout << "\t\t\t[]            []            []            []            []            []\n";
            cout << "\t\t\t[]    " << (computers[i].exists ? computers[i].pcNumber : "  DEL  ") 
                 << "    []    " << (computers[i+1].exists ? computers[i+1].pcNumber : "  DEL  ")
                 << "    []    " << (computers[i+2].exists ? computers[i+2].pcNumber : "  DEL  ")
                 << "    []    " << (computers[i+3].exists ? computers[i+3].pcNumber : "  DEL  ")
                 << "    []    " << (computers[i+4].exists ? computers[i+4].pcNumber : "  DEL  ") << "    []\n";
            cout << "\t\t\t[]            []            []            []            []            []\n";
            cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n";
        }

        cout << "\n\t\t\t[1] Select PC\t[2] Return to Menu\n";
        cout << "\t\t\tEnter choice: ";
        cin >> choice;

        if(choice == '1') {
            string pcNum;
            cout << "\t\t\tEnter PC number (e.g., PC01): ";
            cin >> pcNum;
            transform(pcNum.begin(), pcNum.end(), pcNum.begin(), ::toupper);

            vector<Computer>::iterator it = find_if(computers.begin(), computers.end(), PCNumberFinder(pcNum));

            if(it != computers.end()) {
                system("cls");
                cout << "\n\t\t\tSelected Computer: " << pcNum << endl;
                cout << "\t\t\tCurrent Status: " << (it->exists ? "ACTIVE" : "DELETED") << endl;
                cout << "\n\t\t\t[1] " << (it->exists ? "Edit" : "Add") 
                     << "\t[2] " << (it->exists ? "Delete" : "Cancel") 
                     << "\t[3] Cancel\n";
                cout << "\t\t\tEnter action: ";
                char action;
                cin >> action;

                switch(action) {
                    case '1':
                        if(it->exists) {
                            editComputer(computers);
                        } else {
                            it->exists = true;
                            cout << "\n\t\t\tComputer " << pcNum << " added successfully!\n";
                        }
                        break;
                    case '2':
                        if(it->exists) {
                            it->exists = false;
                            cout << "\n\t\t\tComputer " << pcNum << " deleted successfully!\n";
                        }
                        break;
                }
                waitForKeyPress();
            } else {
                cout << "\t\t\tInvalid PC number!\n";
                waitForKeyPress();
            }
        }
    } while(choice != '2');
}

void displayComponentStatus(const vector<Computer>& computers) {
    system("cls");
    cout << "\n\n\n";
    cout << "[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "[][][]                                                                                                                                        [][][]\n";
    cout << "[][]                                                            LABORATORY STATUS                                                               [][]\n";
    cout << "[][][]                                                                                                                                        [][][]\n";
    cout << "[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "[]  NO OF PC  []        MOUSE       []      KEYBOARD      []       MONITOR      []      LAN CABLE     []     SYSTEM UNIT    []    POWER SUPPLY    []\n";
    cout << "[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n";

    for(vector<Computer>::const_iterator it = computers.begin(); it != computers.end(); ++it) {
        if(it->exists) {
            cout << "[]            []                    []                    []                    []                    []                    []                    []\n";
            cout << "[]    " << left << setw(6) << it->pcNumber 
                 << "  []  " << setw(16) << (it->mouse.status + " (Qty: " + intToString(it->mouse.quantity) + ")")
                 << "  []  " << setw(16) << (it->keyboard.status + " (Qty: " + intToString(it->keyboard.quantity) + ")")
                 << "  []  " << setw(16) << (it->monitor.status + " (Qty: " + intToString(it->monitor.quantity) + ")")
                 << "  []  " << setw(16) << (it->lanCable.status + " (Qty: " + intToString(it->lanCable.quantity) + ")")
                 << "  []  " << setw(16) << (it->systemUnit.status + " (Qty: " + intToString(it->systemUnit.quantity) + ")")
                 << "  []  " << setw(16) << (it->powerSupply.status + " (Qty: " + intToString(it->powerSupply.quantity) + ")")
                 << "  []\n";
        }
    }
    
    cout << "[]            []                    []                    []                    []                    []                    []                    []\n";
    cout << "[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n\n";
    waitForKeyPress();
}

void displayComputerStatus(const vector<Computer>& computers) {
    system("cls");
    cout << "\n\n\n";
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t[][][]                                              [][][]\n";
    cout << "\t\t\t[][]                  COMPUTER STATUS                 [][]\n";
    cout << "\t\t\t[][][]                                              [][][]\n";
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t[]       NUMBER OF PC       []          STATUS          []\n";
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t[]                          []                          []\n";
    
    for(vector<Computer>::const_iterator it = computers.begin(); it != computers.end(); ++it) {
        if(it->exists) {
            cout << "\t\t\t[]           " << left << setw(9) << it->pcNumber 
                 << "      []           " << setw(8) << it->status << "       []\n";
        }
    }
    
    cout << "\t\t\t[]                          []                          []\n";
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    waitForKeyPress();
}

void displayAllComputers(const vector<Computer>& computers) {
    system("cls");
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t[][][]                                                                                                    [][][]\n";
    cout << "\t\t\t[][]                                             FULL SYSTEM STATUS                                         [][]\n";
    cout << "\t\t\t[][][]                                                                                                    [][][]\n";
    cout << "\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    
    cout << "\t\t" << left 
         << setw(10) << "PC NUMBER" 
         << setw(10) << "STATUS"
         << setw(18) << "MOUSE (Qty/Status)"
         << setw(20) << "KEYBOARD (Qty/Status)"
         << setw(18) << "MONITOR (Qty/Status)"
         << setw(18) << "LAN CABLE (Qty/Status)"
         << setw(20) << "SYSTEM UNIT (Qty/Status)"
         << setw(20) << "POWER SUPPLY (Qty/Status)"
         << endl;
    
    cout << "\t\t" << string(130, '_') << endl;

    for(vector<Computer>::const_iterator it = computers.begin(); it != computers.end(); ++it) {
        const Computer& pc = *it;
        cout << "\t\t"
             << setw(10) << pc.pcNumber
             << setw(10) << (pc.exists ? pc.status : "DELETED");
        
        if(pc.exists) {
            cout << setw(18) << (intToString(pc.mouse.quantity) + "/" + pc.mouse.status)
                 << setw(20) << (intToString(pc.keyboard.quantity) + "/" + pc.keyboard.status)
                 << setw(18) << (intToString(pc.monitor.quantity) + "/" + pc.monitor.status)
                 << setw(18) << (intToString(pc.lanCable.quantity) + "/" + pc.lanCable.status)
                 << setw(20) << (intToString(pc.systemUnit.quantity) + "/" + pc.systemUnit.status)
                 << setw(20) << (intToString(pc.powerSupply.quantity) + "/" + pc.powerSupply.status);
        } else {
            cout << setw(18) << "N/A"
                 << setw(20) << "N/A"
                 << setw(18) << "N/A"
                 << setw(18) << "N/A"
                 << setw(20) << "N/A"
                 << setw(20) << "N/A";
        }
        
        cout << endl << "\t\t" << string(130, '_') << endl;
    }
    
    waitForKeyPress();
}
