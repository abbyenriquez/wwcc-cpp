#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "Book.h"
using namespace std;

class Library {
private:
    string name;
    vector<Book> books;

public:
    Library(string n);

    void addBook(const Book& b);
    void displayAll() const;

    void searchByAuthor(string author) const;
    void searchByTitle(string keyword) const;

    void showStats() const;
};

#endif