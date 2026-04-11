#include <iostream>
using namespace std;

int main() {
    double temperature;
    char unit;

    cout << "Temperature Converter" << endl;

    // Prompt user input
    cout << "Enter temperature value: ";
    cin >> temperature;

    cout << "Enter unit (C for Celsius, F for Fahrenheit): ";
    cin >> unit;

    // Conversion logic
    if (unit == 'C' || unit == 'c') {
        double fahrenheit = (temperature * 9.0 / 5.0) + 32;
        cout << temperature << "°C is equal to " << fahrenheit << "°F" << endl;
    }
    else if (unit == 'F' || unit == 'f') {
        double celsius = (temperature - 32) * 5.0 / 9.0;
        cout << temperature << "°F is equal to " << celsius << "°C" << endl;
    }
    else {
        cout << "Invalid unit. Please enter C or F." << endl;
    }

    return 0;
}