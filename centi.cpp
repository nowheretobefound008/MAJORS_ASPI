#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;


double cm_to_mm(double cm);
double cm_to_m(double cm);
void conversion(double cm);

int main() {
    double centimeters;
    char choice;

    do {
    	system("cls");
        cout << "\n\n\n\n";
        cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n";
        cout << "\t\t\t\t[][]                                          [][]\n";
        cout << "\t\t\t\t[]              CENTIMETER CONVERTER            []\n";
        cout << "\t\t\t\t[][]                                          [][]\n";
        cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n\n";

        cout << "\t\t\t\tEnter length in centimeters: ";
        
        while (!(cin >> centimeters)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\t\t\t\tInvalid input. Please enter a number: ";
        }

        conversion(centimeters);

        cout << "\n\t\t\t\tConvert another measurement? (y/n): ";
        cin >> choice;
        cin.ignore(1000, '\n');

    } while (tolower(choice) == 'y');

    cout << "\n\t\t\t\tThank you for using the converter!\n";
    return 0;
}

double cm_to_mm(double cm) {
    return cm * 10;
}

double cm_to_m(double cm) {
    return cm / 100;
}

void conversion(double cm) {
    cout << fixed << setprecision(2);
    system("cls");
    cout << "\n\n\n";
    cout << "\n\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n";
    cout << "\t\t\t\t[][]                                          [][]\n";
    cout << "\t\t\t\t[]                CONVERSION RESULTS            []\n";
    cout << "\t\t\t\t[][]                                          [][]\n";
    cout << "\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n\n";
    cout << "\t\t\t\t";
    cout << cm << " cm = " << cm_to_mm(cm) << " mm\n";
    cout << "\t\t\t\t";
    cout << cm << " cm = " << cm_to_m(cm) << " m\n";
    cout << "\n\t\t\t\t[][][][][][][][][][][][][][][][][][][][][][][][][]\n";
}
