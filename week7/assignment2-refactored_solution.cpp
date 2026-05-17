#include <iostream>
#include <string>

using namespace std;

class BankAccount {
private:
    // FIX: Encapsulation issue — data members were public in original code
    // Now all data is private to protect object integrity
    string customerName;
    double balance;
    bool isOpen;
    int accountNumber;
    string accountType;

    // FIX: Magic numbers removed — interest rates are now constants
    static constexpr double SAVINGS_RATE = 1.03;
    static constexpr double CHECKING_RATE = 1.01;
    static constexpr double BUSINESS_RATE = 1.005;

public:
    // FIX: Replaced setup() method with a constructor
    // Original issue: object could exist in invalid/uninitialized state
    BankAccount(string name, int num, string type) {
        customerName = name;
        accountNumber = num;
        accountType = type;
        balance = 0.0;
        isOpen = true;
    }

    // FIX: Validation added (no negative deposits)
    void deposit(double amount) {
        if (!isOpen) {
            cout << "Account is closed.\n";
            return;
        }

        if (amount <= 0) {
            cout << "Invalid deposit amount.\n";
            return;
        }

        balance += amount;
    }

    // FIX: Validation added (no overdraft unless allowed)
    void withdraw(double amount) {
        if (!isOpen) {
            cout << "Account is closed.\n";
            return;
        }

        if (amount <= 0) {
            cout << "Invalid withdrawal amount.\n";
            return;
        }

        if (amount > balance) {
            cout << "Insufficient funds.\n";
            return;
        }

        balance -= amount;
    }

    // FIX: Replaced magic numbers with named constants
    void applyInterest() {
        if (!isOpen) return;

        if (accountType == "savings") {
            balance *= SAVINGS_RATE;
        }
        else if (accountType == "checking") {
            balance *= CHECKING_RATE;
        }
        else if (accountType == "business") {
            balance *= BUSINESS_RATE;
        }
        else {
            cout << "Unknown account type. No interest applied.\n";
        }
    }

    // FIX: const correctness — method does not modify object
    void print() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Customer Name: " << customerName << endl;
        cout << "Balance: $" << balance << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Status: " << (isOpen ? "Open" : "Closed") << endl;
    }

    // FIX: const correctness applied where needed
    double getBalance() const {
        return balance;
    }

    string getAccountType() const {
        return accountType;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    string getCustomerName() const {
        return customerName;
    }

    // FIX: Better naming convention (closeAccount instead of close)
    void closeAccount() {
        isOpen = false;
    }
};

// ---------------- TESTING ----------------
int main() {
    // FIX: Replaced setup() with constructor usage
    BankAccount acc1("John Smith", 12345, "savings");

    acc1.deposit(1000);
    acc1.withdraw(250);
    acc1.applyInterest();

    acc1.print();
    acc1.closeAccount();

    return 0;
}