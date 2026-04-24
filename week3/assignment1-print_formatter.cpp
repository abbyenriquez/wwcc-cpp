#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

// Prototypes
string format(int num);
string format(double num);
string format(double num, int precision);
string format(string text);

int main() {

    cout << "Integer formatting:" << endl;
    cout << "Original: 1234567" << endl;
    cout << "Formatted: " << format(1234567) << endl << endl;

    cout << "Double formatting (default 2 decimal places):" << endl;
    cout << "Original: 45.6789" << endl;
    cout << "Formatted: " << format(45.6789) << endl << endl;

    cout << "Double formatting (custom decimal places):" << endl;
    cout << "Original: 45.6789 with precision 3" << endl;
    cout << "Formatted: " << format(45.6789, 3) << endl << endl;

    string text = "hello world of c++ programming";
    cout << "String formatting:" << endl;
    cout << "Original: \"" << text << "\"" << endl;
    cout << "Formatted: \"" << format(text) << "\"" << endl;

    return 0;
}


// Integer with commas
string format(int num) {
    string s = to_string(num);
    string result = "";
    int count = 0;

    for (int i = s.length() - 1; i >= 0; i--) {
        result = s[i] + result;
        count++;
        if (count == 3 && i != 0) {
            result = "," + result;
            count = 0;
        }
    }
    return result;
}


// Double (2 decimal places)
string format(double num) {
    stringstream ss;
    ss << fixed << setprecision(2) << num;
    return ss.str();
}


// Double (custom precision)
string format(double num, int precision) {
    stringstream ss;
    ss << fixed << setprecision(precision) << num;
    return ss.str();
}


// Capitalize words
string format(string text) {
    if (text.length() == 0) return text;

    text[0] = toupper(text[0]);

    for (int i = 1; i < text.length(); i++) {
        if (text[i - 1] == ' ') {
            text[i] = toupper(text[i]);
        }
    }

    return text;
}