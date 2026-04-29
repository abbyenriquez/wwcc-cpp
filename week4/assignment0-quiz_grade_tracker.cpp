#include <iostream>
#include <iomanip>
using namespace std;

const int NUM_QUIZZES = 5;

// Helper function to determine letter grade
char getLetterGrade(double score) {
    if (score >= 90) return 'A';
    else if (score >= 80) return 'B';
    else if (score >= 70) return 'C';
    else if (score >= 60) return 'D';
    else return 'F';
}

int main() {
    double scores[NUM_QUIZZES];
    double sum = 0;

    cout << "QUIZ GRADE TRACKER\n";
    cout << "------------------\n";

    // Input scores
    for (int i = 0; i < NUM_QUIZZES; i++) {
        cout << "Enter score for Quiz " << i + 1 << " (0-100): ";
        cin >> scores[i];
        sum += scores[i];
    }

    // Initialize min/max
    double highest = scores[0];
    double lowest = scores[0];
    int highestIndex = 0;
    int lowestIndex = 0;

    // Grade distribution counters
    int countA = 0, countB = 0, countC = 0, countD = 0, countF = 0;

    // Analyze scores
    for (int i = 0; i < NUM_QUIZZES; i++) {
        if (scores[i] > highest) {
            highest = scores[i];
            highestIndex = i;
        }
        if (scores[i] < lowest) {
            lowest = scores[i];
            lowestIndex = i;
        }

        char grade = getLetterGrade(scores[i]);
        if (grade == 'A') countA++;
        else if (grade == 'B') countB++;
        else if (grade == 'C') countC++;
        else if (grade == 'D') countD++;
        else countF++;
    }

    double average = sum / NUM_QUIZZES;
    char overallGrade = getLetterGrade(average);

    // Display results
    cout << "\nQuiz Results:\n";
    for (int i = 0; i < NUM_QUIZZES; i++) {
        cout << "  Quiz " << i + 1 << ":  "
             << setw(3) << scores[i]
             << "  (" << getLetterGrade(scores[i]) << ")\n";
    }

    cout << fixed << setprecision(1);
    cout << "\nStatistics:\n";
    cout << "  Average score:  " << average << endl;
    cout << "  Highest score:  " << highest << "  (Quiz " << highestIndex + 1 << ")\n";
    cout << "  Lowest score:   " << lowest << "  (Quiz " << lowestIndex + 1 << ")\n";
    cout << "  Overall grade:  " << overallGrade << endl;

    cout << "\nGrade Distribution:\n";
    cout << "  A: " << countA << endl;
    cout << "  B: " << countB << endl;
    cout << "  C: " << countC << endl;
    cout << "  D: " << countD << endl;
    cout << "  F: " << countF << endl;

    // Bonus: Score chart
    cout << "\nScore Chart:\n";
    for (int i = 0; i < NUM_QUIZZES; i++) {
        cout << "  Quiz " << i + 1 << " (" << scores[i] << "): ";
        
        int filledBlocks = scores[i] / 10;
        int emptyBlocks = 10 - filledBlocks;

        for (int j = 0; j < filledBlocks; j++) cout << "█";
        for (int j = 0; j < emptyBlocks; j++) cout << "░";

        cout << endl;
    }

    return 0;
}