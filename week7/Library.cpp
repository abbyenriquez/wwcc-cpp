#include "Library.h"
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

Library::Library(string n) {
    name = n;
}

void Library::addBook(const Book& b) {
    books.push_back(b);
}

void Library::displayAll() const {
    cout << "\nCATALOG:\n";
    for (int i = 0; i < books.size(); i++) {
        cout << i + 1 << ". ";
        books[i].display();
        cout << endl;
    }
}

string toLowerStr(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

void Library::searchByAuthor(string author) const {
    string search = toLowerStr(author);
    bool found = false;

    cout << "\nBooks by " << author << ":\n";

    for (const auto& b : books) {
        if (toLowerStr(b.getAuthor().getName()) == search) {
            cout << "  - \"" << b.getTitle() << "\" ("
                 << b.getPublicationYear() << ")\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No books found for that author.\n";
    }
}

void Library::searchByTitle(string keyword) const {
    string search = toLowerStr(keyword);
    bool found = false;

    cout << "\nSearch results:\n";

    for (const auto& b : books) {
        if (toLowerStr(b.getTitle()).find(search) != string::npos) {
            cout << "  - \"" << b.getTitle() << "\" ("
                 << b.getPublicationYear() << ")\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No books found matching that title.\n";
    }
}

void Library::showStats() const {
    cout << "\nSTATS:\n";
    cout << "Total books in catalog: " << books.size() << endl;
}