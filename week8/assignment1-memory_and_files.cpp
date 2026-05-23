#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Swap values using references
void swapValues(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Find max value using pointer
int findMax(int* arr, int size) {
    int max = arr[0];

    for (int i = 1; i < size; i++) {
        if (*(arr + i) > max) {
            max = *(arr + i);
        }
    }

    return max;
}

// Write note to file
void writeNote(ofstream& file, const string& note) {
    file << note << endl;
}

// Display notes from file
void displayNotes(ifstream& file) {
    string line;
    int lineNumber = 1;

    while (getline(file, line)) {
        cout << lineNumber << ". "
             << line
             << endl;

        lineNumber++;
    }
}

// Bonus: Search notes
void searchNotes(ifstream& file, const string& keyword) {
    string line;

    cout << "\nMatching Notes:\n";

    while (getline(file, line)) {
        if (line.find(keyword) != string::npos) {
            cout << line << endl;
        }
    }
}

int main() {

    // ==============================
    // PART 1: MEMORY AND ADDRESSING
    // ==============================

    cout << "=== PART 1: MEMORY AND ADDRESSING ===\n\n";

    int age = 25;
    double gpa = 3.75;
    char grade = 'A';

    // Display values and memory addresses
    cout << "Variable values and addresses:\n";

    cout << "  int    age   = "
         << age
         << " at address "
         << &age
         << endl;

    cout << "  double gpa   = "
         << gpa
         << " at address "
         << &gpa
         << endl;

    cout << "  char   grade = "
         << grade
         << " at address "
         << static_cast<void*>(&grade)
         << endl;

    // ==============================
    // REFERENCES
    // ==============================

    cout << "\nReference demonstration:\n";

    int& ageRef = age;

    cout << "  Before: age = "
         << age
         << endl;

    ageRef = 26;

    cout << "  After modifying through reference: age = "
         << age
         << endl;

    // ==============================
    // POINTERS
    // ==============================

    cout << "\nPointer demonstration:\n";

    // Initialize pointer safely
    int* ptr = nullptr;

    ptr = &age;

    // nullptr check before dereferencing
    if (ptr != nullptr) {

        cout << "  Pointer stores address: "
             << ptr
             << endl;

        cout << "  Value at that address: "
             << *ptr
             << endl;

        // Modify original variable through pointer
        *ptr = 100;

        cout << "  After modifying through pointer: age = "
             << age
             << endl;
    }

    // ==============================
    // SWAP FUNCTION
    // ==============================

    cout << "\nSwap function (by reference):\n";

    int x = 10;
    int y = 20;

    cout << "  Before: x = "
         << x
         << ", y = "
         << y
         << endl;

    swapValues(x, y);

    cout << "  After swap: x = "
         << x
         << ", y = "
         << y
         << endl;

    // ==============================
    // ARRAY + POINTER RELATIONSHIP
    // ==============================

    int arr[] = {5, 12, 42, 8, 3};
    int size = 5;

    cout << "\nArray-pointer relationship:\n";

    cout << "  arr[0] = "
         << arr[0]
         << "    *(arr + 0) = "
         << *(arr + 0)
         << endl;

    cout << "  arr[1] = "
         << arr[1]
         << "   *(arr + 1) = "
         << *(arr + 1)
         << endl;

    cout << "  Maximum value (via pointer): "
         << findMax(arr, size)
         << endl;

    // ==============================
    // PART 2: FILE I/O
    // ==============================

    cout << "\n=== PART 2: FILE I/O ===\n";

    // Open file in append mode
    ofstream outFile("notes.txt", ios::app);

    // Error handling
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return 1;
    }

    // Enter 3 notes
    for (int i = 1; i <= 3; i++) {

        string note;

        cout << "\nEnter note "
             << i
             << ": ";

        getline(cin, note);

        writeNote(outFile, note);
    }

    outFile.close();

    cout << "\nNotes written to notes.txt successfully.\n";

    // Read notes back
    ifstream inFile("notes.txt");

    // Error handling
    if (!inFile) {
        cerr << "Error opening file for reading.\n";
        return 1;
    }

    cout << "\nReading notes back from file:\n";

    displayNotes(inFile);

    inFile.close();

    // BONUS SEARCH FEATURE
    ifstream searchFile("notes.txt");

    if (searchFile) {

        string keyword;

        cout << "\nEnter keyword to search notes: ";
        getline(cin, keyword);

        searchNotes(searchFile, keyword);

        searchFile.close();
    }

    return 0;
}