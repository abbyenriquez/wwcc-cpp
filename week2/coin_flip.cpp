#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
using namespace std;

int main() {
    srand(time(0));

    int flips;
    int heads = 0;
    int tails = 0;

    cout << "Coin Flip Simulator" << endl;
    cout << "How many flips would you like to simulate? ";
    cin >> flips;

    cout << "Simulating " << flips << " coin flips..." << endl;

    for (int i = 0; i < flips; i++) {
        int result = rand() % 2;

        if (result == 0) {
            heads++;
        } else {
            tails++;
        }
    }

    double headsPercent = (double)heads / flips * 100;
    double tailsPercent = (double)tails / flips * 100;

    cout << "\nResults:" << endl;
    cout << "Heads: " << heads << " (" << headsPercent << "%)" << endl;
    cout << "Tails: " << tails << " (" << tailsPercent << "%)" << endl;

    return 0;
}