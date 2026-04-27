#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Function prototypes
int countVowels(string word);
int countConsonants(string word);
bool isPalindrome(string word);
char firstLetter(string word);
string reverseWord(string word);

int main() {
    string word;
    char again = 'y';

    while (again == 'y' || again == 'Y') {

        cout << "Enter a word: ";
        cin >> word;

        cout << "\nWord Analysis:" << endl;
        cout << "-------------" << endl;
        cout << "Original word: " << word << endl;
        cout << "Number of vowels: " << countVowels(word) << endl;
        cout << "Number of consonants: " << countConsonants(word) << endl;
        cout << "First letter: " << firstLetter(word) << endl;
        cout << "Reversed: " << reverseWord(word) << endl;

        if (isPalindrome(word)) {
            cout << "Is palindrome: Yes" << endl;
        } else {
            cout << "Is palindrome: No" << endl;
        }

        cout << "\nWould you like to analyze another word? (y/n): ";
        cin >> again;
        cout << endl;
    }

    return 0;
}


// Count vowels
int countVowels(string word) {
    int count = 0;

    for (int i = 0; i < word.length(); i++) {
        char c = tolower(word[i]);

        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }

    return count;
}


// Count consonants
int countConsonants(string word) {
    int count = 0;

    for (int i = 0; i < word.length(); i++) {
        char c = tolower(word[i]);

        if (isalpha(c) && !(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')) {
            count++;
        }
    }

    return count;
}


// Check palindrome
bool isPalindrome(string word) {
    int left = 0;
    int right = word.length() - 1;

    while (left < right) {
        if (tolower(word[left]) != tolower(word[right])) {
            return false;
        }
        left++;
        right--;
    }

    return true;
}


// Get first letter
char firstLetter(string word) {
    if (word.length() == 0) {
        return '?'; // handles empty case
    }
    return word[0];
}


// Reverse word
string reverseWord(string word) {
    string reversed = "";

    for (int i = word.length() - 1; i >= 0; i--) {
        reversed += word[i];
    }

    return reversed;
}