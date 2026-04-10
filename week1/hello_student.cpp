#include <iostream>
#include <string>
using namespace std;

int main() {
    string name;
    string answer;

    cout << "Enter your name: ";
    cin >> name;

    cout << "Hello, " << name << "! Welcome to C++!" << endl;

    cout << "Please enter your favorite food: ";
    cin >> answer;

    cout << name << "! Wow, I love " << answer << " too!" << endl;

    return 0;
}