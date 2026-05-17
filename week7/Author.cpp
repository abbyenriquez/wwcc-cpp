#include "Author.h"
#include <iostream>

using namespace std;

Author::Author(string n, int by) {
    name = n;
    birthYear = by;
}

string Author::getName() const {
    return name;
}

int Author::getBirthYear() const {
    return birthYear;
}

void Author::display() const {
    cout << name << " (born " << birthYear << ")";
}