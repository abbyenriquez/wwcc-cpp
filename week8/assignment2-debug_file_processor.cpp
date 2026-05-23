#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Student {
    string lastName;
    string firstName;
    int g1, g2, g3;
    double average;
    int high;
    int low;
};

int main() {

    // --- Read input file ---
    ifstream inFile("grades.txt");

    // BUG: File was never checked to see if it opened successfully
    // FIX: Added file validation
    if (!inFile) {
        cerr << "Error opening grades.txt" << endl;
        return 1;
    }

    cout << "Reading records from grades.txt..." << endl;

    vector<Student> students;
    string line;

    // BUG: while (!inFile.eof()) can process data incorrectly
    // FIX: Use getline() directly as loop condition
    while (getline(inFile, line)) {

        if (line.empty() || line[0] == '#') {
            continue;
        }

        // BUG: stringstream was outside loop and never reset
        // FIX: Create a new stringstream inside loop
        stringstream ss(line);

        Student s;

        ss >> s.lastName
           >> s.firstName
           >> s.g1
           >> s.g2
           >> s.g3;

        s.high = max({s.g1, s.g2, s.g3});
        s.low = min({s.g1, s.g2, s.g3});

        int total = s.g1 + s.g2 + s.g3;

        // BUG: Integer division removed decimal precision
        // FIX: Cast total to double before division
        s.average = static_cast<double>(total) / 3;

        students.push_back(s);
    }

    inFile.close();

    cout << students.size()
         << " students loaded."
         << endl << endl;

    // --- Write report ---

    // BUG: Output file overwrote previous reports
    // FIX: Open file in append mode
    ofstream outFile("grade_report.txt", ios::app);

    if (!outFile) {
        cerr << "Error opening grade_report.txt" << endl;
        return 1;
    }

    // --- Display to console and write to file ---
    auto printReport = [&](ostream& out) {

        out << "GRADE REPORT" << endl;
        out << string(20, '-') << endl;

        out << left
            << setw(20) << "Name"
            << right
            << setw(7) << "Avg"
            << setw(7) << "High"
            << setw(7) << "Low"
            << endl;

        out << string(20, '-') << endl;

        double classTotal = 0;

        int topIdx = 0;
        int lowIdx = 0;

        for (int i = 0; i < students.size(); i++) {

            Student& s = students[i];

            string name =
                s.lastName + ", " + s.firstName;

            // BUG: setw() was outside loop
            // FIX: Apply setw() to every row

            // BUG: Numbers were left-aligned
            // FIX: Use right alignment for numeric columns
            out << left
                << setw(20) << name
                << right
                << setw(7) << fixed
                << setprecision(1)
                << s.average
                << setw(7)
                << s.high
                << setw(7)
                << s.low
                << endl;

            classTotal += s.average;

            if (s.average >
                students[topIdx].average) {

                topIdx = i;
            }

            if (s.average <
                students[lowIdx].average) {

                lowIdx = i;
            }
        }

        double classAvg =
            classTotal / students.size();

        out << endl;

        out << "CLASS STATISTICS" << endl;

        out << string(20, '-') << endl;

        out << fixed << setprecision(1);

        out << "Class average: "
            << classAvg
            << endl;

        out << "Top student:   "
            << students[topIdx].lastName
            << ", "
            << students[topIdx].firstName
            << " ("
            << students[topIdx].average
            << ")"
            << endl;

        out << "Low student:   "
            << students[lowIdx].lastName
            << ", "
            << students[lowIdx].firstName
            << " ("
            << students[lowIdx].average
            << ")"
            << endl;
    };

    printReport(cout);
    printReport(outFile);

    outFile.close();

    cout << endl
         << "Report written to grade_report.txt"
         << endl;

    return 0;
}