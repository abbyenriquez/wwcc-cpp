#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

// Helper function to remove punctuation from a word
string cleanWord(string word) {
    word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
    return word;
}

// Helper to convert string to lowercase (for frequency comparison)
string toLowerString(string str) {
    for (char &c : str) {
        c = tolower(c);
    }
    return str;
}

// Check if word is a common word to ignore
bool isCommonWord(const string& word) {
    return (word == "a" || word == "is" || word == "it" || word == "the" || word == "at");
}

int main() {
    string text;

    cout << "TEXT ANALYZER\n";
    cout << "-------------\n";
    cout << "Enter a sentence or paragraph:\n";
    getline(cin, text);

    // Character count
    int charCount = text.length();

    // Sentence count
    int sentenceCount = 0;
    for (char c : text) {
        if (c == '.' || c == '!' || c == '?') {
            sentenceCount++;
        }
    }

    // Word processing
    stringstream ss(text);
    string word;

    int wordCount = 0;
    int totalWordLength = 0;
    string longestWord = "";

    // For bonus frequency tracking (simple arrays)
    const int MAX_WORDS = 100;
    string words[MAX_WORDS];
    int counts[MAX_WORDS] = {0};
    int uniqueCount = 0;

    while (ss >> word) {
        string cleaned = cleanWord(word);
        if (cleaned.empty()) continue;

        wordCount++;
        totalWordLength += cleaned.length();

        // Longest word
        if (cleaned.length() > longestWord.length()) {
            longestWord = cleaned;
        }

        // Bonus: frequency tracking
        string lower = toLowerString(cleaned);

        if (!isCommonWord(lower)) {
            bool found = false;
            for (int i = 0; i < uniqueCount; i++) {
                if (words[i] == lower) {
                    counts[i]++;
                    found = true;
                    break;
                }
            }
            if (!found && uniqueCount < MAX_WORDS) {
                words[uniqueCount] = lower;
                counts[uniqueCount] = 1;
                uniqueCount++;
            }
        }
    }

    double avgLength = (wordCount > 0) ? (double)totalWordLength / wordCount : 0;

    // Uppercase and lowercase versions
    string upperText = text;
    string lowerText = text;

    for (char &c : upperText) {
        c = toupper(c);
    }
    for (char &c : lowerText) {
        c = tolower(c);
    }

    // Output
    cout << "\nAnalysis:\n";
    cout << "  Characters (with spaces): " << charCount << endl;
    cout << "  Word count:               " << wordCount << endl;
    cout << "  Sentence count:           " << sentenceCount << endl;
    cout << "  Longest word:             " << longestWord << endl;
    cout << fixed << setprecision(1);
    cout << "  Average word length:      " << avgLength << " characters\n";

    cout << "\nUppercase:\n  " << upperText << endl;
    cout << "\nLowercase:\n  " << lowerText << endl;

    // Bonus: Top 3 frequent words
    cout << "\nMost frequent words:\n";

    for (int k = 0; k < 3; k++) {
        int maxIndex = -1;
        for (int i = 0; i < uniqueCount; i++) {
            if (counts[i] > 0 && (maxIndex == -1 || counts[i] > counts[maxIndex])) {
                maxIndex = i;
            }
        }

        if (maxIndex != -1) {
            cout << "  " << k + 1 << ". \"" << words[maxIndex]
                 << "\" - " << counts[maxIndex] << " time";
            if (counts[maxIndex] > 1) cout << "s";
            cout << endl;

            counts[maxIndex] = -1; // mark as used
        }
    }

    return 0;
}