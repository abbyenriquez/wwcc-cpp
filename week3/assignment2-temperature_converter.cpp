#include <iostream>
#include <iomanip>
using namespace std;

// Function prototype
void convertTemperature(double input, char unit,
                        double &c, double &f, double &k);

int main() {
    double value;
    char unit;

    double celsius, fahrenheit, kelvin;

    cout << "Enter a temperature value: ";
    cin >> value;

    cout << "Enter the unit (C for Celsius, F for Fahrenheit, K for Kelvin): ";
    cin >> unit;

    // Convert lowercase to uppercase just in case
    unit = toupper(unit);

    // Validate input
    if (unit != 'C' && unit != 'F' && unit != 'K') {
        cout << "Invalid unit." << endl;
        return 1;
    }

    convertTemperature(value, unit, celsius, fahrenheit, kelvin);

    cout << fixed << setprecision(2);

    cout << "\nTemperature Conversions:" << endl;
    cout << "Celsius: " << celsius << " C" << endl;
    cout << "Fahrenheit: " << fahrenheit << " F" << endl;
    cout << "Kelvin: " << kelvin << " K" << endl;

    return 0;
}


// Function definition
void convertTemperature(double input, char unit,
                        double &c, double &f, double &k) {

    if (unit == 'C') {
        c = input;
        f = (input * 9.0/5.0) + 32;
        k = input + 273.15;
    }
    else if (unit == 'F') {
        c = (input - 32) * 5.0/9.0;
        f = input;
        k = c + 273.15;
    }
    else if (unit == 'K') {
        c = input - 273.15;
        f = (c * 9.0/5.0) + 32;
        k = input;
    }
}