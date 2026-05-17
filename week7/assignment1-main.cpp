#include <iostream>
#include "Library.h"
#include "Author.h"
#include "Book.h"

using namespace std;

int main() {
    Library lib("Central City Library");

    int choice;

    do {
        cout << "\nLIBRARY MANAGEMENT SYSTEM\n";
        cout << "--------------------------\n";
        cout << "Library: Central City Library\n\n";

        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search by Author\n";
        cout << "4. Search by Title\n";
        cout << "5. Show Stats\n";
        cout << "6. Exit\n\n";

        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title, authorName, isbn;
            int year, birthYear;

            cout << "Title: ";
            getline(cin, title);

            cout << "Author name: ";
            getline(cin, authorName);

            cout << "Author birth year: ";
            cin >> birthYear;

            cout << "Publication year: ";
            cin >> year;
            cin.ignore();

            cout << "ISBN: ";
            getline(cin, isbn);

            Author a(authorName, birthYear);
            Book b(title, year, isbn, a);

            lib.addBook(b);
        }

        else if (choice == 2) {
            lib.displayAll();
        }

        else if (choice == 3) {
            string author;
            cout << "Search by author: ";
            getline(cin, author);
            lib.searchByAuthor(author);
        }

        else if (choice == 4) {
            string keyword;
            cout << "Search by title: ";
            getline(cin, keyword);
            lib.searchByTitle(keyword);
        }

        else if (choice == 5) {
            lib.showStats();
        }

    } while (choice != 6);

    cout << "Goodbye!\n";

    return 0;
}