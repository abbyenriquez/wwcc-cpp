#include <iostream>
#include <iomanip>
using namespace std;

// Shared static variable
static int conversionCount = 0;

// Function prototypes
double dollarToEuro(double amount);
double dollarToPound(double amount);
double dollarToYen(double amount);
int getConversionCount();

int main() {
    int choice;
    double amount;
    char again = 'y';

    cout << fixed << setprecision(2);

    while (again == 'y' || again == 'Y') {

        cout << "\nCURRENCY CONVERTER" << endl;
        cout << "------------------" << endl;
        cout << "1. Convert USD to Euro (EUR)" << endl;
        cout << "2. Convert USD to British Pound (GBP)" << endl;
        cout << "3. Convert USD to Japanese Yen (JPY)" << endl;
        cout << "4. Exit" << endl;

        cout << "\nEnter your choice (1-4): ";
        cin >> choice;

        if (choice == 4) {
            break;
        }

        if (choice < 1 || choice > 4) {
            cout << "Invalid choice." << endl;
            continue;
        }

        cout << "Enter amount in USD: ";
        cin >> amount;

        double result;

        switch (choice) {
            case 1:
                result = dollarToEuro(amount);
                cout << amount << " USD = " << result << " EUR" << endl;
                break;
            case 2:
                result = dollarToPound(amount);
                cout << amount << " USD = " << result << " GBP" << endl;
                break;
            case 3:
                result = dollarToYen(amount);
                cout << amount << " USD = " << result << " JPY" << endl;
                break;
        }

        cout << "\nNumber of conversions performed: "
             << getConversionCount() << endl;

        cout << "\nWould you like to perform another conversion? (y/n): ";
        cin >> again;
    }

    cout << "\nThank you for using the Currency Converter!" << endl;

    return 0;
}


// Conversion functions (each increments the SAME counter)
double dollarToEuro(double amount) {
    conversionCount++;
    return amount * 0.85;
}

double dollarToPound(double amount) {
    conversionCount++;
    return amount * 0.74;
}

double dollarToYen(double amount) {
    conversionCount++;
    return amount * 110.33;
}

// Return total conversions
int getConversionCount() {
    return conversionCount;
}