#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));

    int secretNumber = rand() % 100 + 1;
    int guess;
    int attempts = 0;

    cout << "Number Guessing Game" << endl;
    cout << "I'm thinking of a number between 1 and 100." << endl << endl;

    while (true) {
        cout << "Enter your guess: ";
        cin >> guess;

        attempts++;

        if (guess > secretNumber) {
            cout << "Too high! Try again.\n" << endl;
        } 
        else if (guess < secretNumber) {
            cout << "Too low! Try again.\n" << endl;
        } 
        else {
            cout << "Congratulations! You guessed the number " 
                 << secretNumber << " correctly!" << endl;
            cout << "It took you " << attempts << " guesses." << endl;
            break;
        }
    }

    return 0;
}