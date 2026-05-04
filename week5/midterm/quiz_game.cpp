
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Struct
struct Question {
    string questionText;
    string options[4];
    char correctAnswer;
    int points;
};

// Function prototypes
void displayQuestion(Question q);
bool checkAnswer(Question q, char userAnswer);
void swapQuestions(Question &a, Question &b);
void runQuiz(Question quiz[], int totalQuestions);

int main() {
    const int TOTAL_QUESTIONS = 10;
    Question quiz[TOTAL_QUESTIONS];

    // Animal Questions
    quiz[0] = {"What is the largest land animal?",
        {"A. Elephant", "B. Giraffe", "C. Rhino", "D. Hippo"},
        'A', 10};

    quiz[1] = {"Which animal is known as the King of the Jungle?",
        {"A. Tiger", "B. Lion", "C. Bear", "D. Wolf"},
        'B', 10};

    quiz[2] = {"What do pandas mainly eat?",
        {"A. Meat", "B. Fish", "C. Bamboo", "D. Fruit"},
        'C', 10};

    quiz[3] = {"Which animal can fly?",
        {"A. Penguin", "B. Ostrich", "C. Eagle", "D. Kangaroo"},
        'C', 10};

    quiz[4] = {"What is the fastest land animal?",
        {"A. Lion", "B. Horse", "C. Cheetah", "D. Dog"},
        'C', 10};

    quiz[5] = {"Which animal lives in water?",
        {"A. Shark", "B. Tiger", "C. Elephant", "D. Cat"},
        'A', 10};

    quiz[6] = {"Which animal is known for changing colors?",
        {"A. Snake", "B. Chameleon", "C. Frog", "D. Lizard"},
        'B', 10};

    quiz[7] = {"Which animal has a long neck?",
        {"A. Zebra", "B. Horse", "C. Giraffe", "D. Deer"},
        'C', 10};

    quiz[8] = {"What animal is known for hopping?",
        {"A. Kangaroo", "B. Dog", "C. Cat", "D. Cow"},
        'A', 10};

    quiz[9] = {"Which animal is a mammal?",
        {"A. Snake", "B. Frog", "C. Whale", "D. Turtle"},
        'C', 10};

    int choice;

    do {
        cout << "\n===== QUIZ MENU =====\n";
        cout << "1. Start Animal Quiz\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                runQuiz(quiz, TOTAL_QUESTIONS);
                break;

            case 2:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 2);

    return 0;
}

// Runs the quiz
void runQuiz(Question quiz[], int totalQuestions) {
    srand(time(0));

    // Shuffle questions
    for (int i = 0; i < totalQuestions; i++) {
        int randomIndex = rand() % totalQuestions;
        swapQuestions(quiz[i], quiz[randomIndex]);
    }

    int score = 0;
    char userAnswer;
    string name;

    cin.ignore(); // fix getline after cin
    cout << "\nEnter your name: ";
    getline(cin, name);

    cout << "\nWelcome, " << name << "! Starting quiz...\n";

    for (int i = 0; i < totalQuestions; i++) {
        displayQuestion(quiz[i]);

        cout << "Your answer (A/B/C/D): ";
        cin >> userAnswer;

        // convert to uppercase
        if (userAnswer >= 'a' && userAnswer <= 'z') {
            userAnswer = userAnswer - 32;
        }

        if (checkAnswer(quiz[i], userAnswer)) {
            cout << "Correct!\n";
            score += quiz[i].points;
        } else {
            cout << "Wrong! Correct answer: " << quiz[i].correctAnswer << endl;
        }

        cout << "------------------------\n";
    }

    cout << "\nFinal Score: " << score << endl;

    // Performance summary
    if (score == totalQuestions * 10) {
        cout << "Perfect score! Amazing!\n";
    } else if (score >= 70) {
        cout << "Great job!\n";
    } else if (score >= 40) {
        cout << "Not bad!\n";
    } else {
        cout << "Keep practicing!\n";
    }
}

// Display question
void displayQuestion(Question q) {
    cout << "\n" << q.questionText << endl;
    for (int i = 0; i < 4; i++) {
        cout << q.options[i] << endl;
    }
}

// Check answer
bool checkAnswer(Question q, char userAnswer) {
    return userAnswer == q.correctAnswer;
}

// Swap for shuffling
void swapQuestions(Question &a, Question &b) {
    Question temp = a;
    a = b;
    b = temp;
}