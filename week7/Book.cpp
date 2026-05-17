#include "Book.h"
#include <iostream>

using namespace std;

Book::Book(string t, int py, string i, Author a)
    : author(a) {
    title = t;
    publicationYear = py;
    isbn = i;
}

string Book::getTitle() const {
    return title;
}

int Book::getPublicationYear() const {
    return publicationYear;
}

string Book::getISBN() const {
    return isbn;
}

Author Book::getAuthor() const {
    return author;
}

void Book::setPublicationYear(int py) {
    if (py > 0) {
        publicationYear = py;
    }
}

void Book::display() const {
    cout << "\"" << title << "\" (" << publicationYear << ")\n";
    cout << "   Author: ";
    author.display();
    cout << "\n   ISBN: " << isbn << "\n";
}