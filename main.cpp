#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>

using namespace std;

const string DATA_FILE = "accounts.txt";

class BankAccount {
private:
    int accountNumber;
    string customerName;
    double balance;

public:
    BankAccount() : accountNumber(0), balance(0.0) {}

    BankAccount(int number, const string& name, double amount)
        : accountNumber(number), customerName(name), balance(amount) {}

    int getAccountNumber() const { return accountNumber; }
    string getCustomerName() const { return customerName; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        return true;
    }

    void display() const {
        cout << "\nAccount Number : " << accountNumber
             << "\nCustomer Name  : " << customerName
             << "\nBalance        : Rs. " << fixed << setprecision(2)
             << balance << '\n';
    }
};

class Bank {
private:
    vector<BankAccount> accounts;

    int findAccountIndex(int accountNumber) const {
        for (int i = 0; i < static_cast<int>(accounts.size()); ++i) {
            if (accounts[i].getAccountNumber() == accountNumber)
                return i;
        }
        return -1;
    }

    void loadAccounts() {
        accounts.clear();
        ifstream file(DATA_FILE);
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string numberText, name, balanceText;

            if (getline(ss, numberText, '|') &&
                getline(ss, name, '|') &&
                getline(ss, balanceText)) {
                try {
                    int number = stoi(numberText);
                    double balance = stod(balanceText);
                    if (number > 0 && !name.empty() && balance >= 0)
                        accounts.emplace_back(number, name, balance);
                } catch (...) {
                    // Ignore invalid records.
                }
            }
        }
    }

    bool saveAccounts() const {
        ofstream file(DATA_FILE);
        if (!file) return false;

        for (const auto& account : accounts) {
            file << account.getAccountNumber() << '|'
                 << account.getCustomerName() << '|'
                 << fixed << setprecision(2) << account.getBalance()
                 << '\n';
        }
        return file.good();
    }

    bool readPositiveAmount(double& amount) const {
        if (!(cin >> amount) || amount <= 0) {
            cout << "Please enter a valid amount greater than zero.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }
        return true;
    }

public:
    Bank() {
        loadAccounts();
    }

    void createAccount() {
        int number;
        string name;

        cout << "\nEnter a new account number: ";
        if (!(cin >> number) || number <= 0) {
            cout << "Invalid account number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        if (findAccountIndex(number) != -1) {
            cout << "An account with this number already exists.\n";
            return;
        }

        cout << "Enter customer name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);

        if (name.empty() || name.find('|') != string::npos) {
            cout << "Name cannot be empty or contain the | character.\n";
            return;
        }

        accounts.emplace_back(number, name, 0.0);

        if (saveAccounts())
            cout << "Account created successfully!\n";
        else
            cout << "Error saving account. Please check file permissions.\n";
    }

    void depositMoney() {
        int number;
        double amount;

        cout << "\nEnter account number: ";
        if (!(cin >> number)) {
            cout << "Invalid account number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        int index = findAccountIndex(number);
        if (index == -1) {
            cout << "Account not found.\n";
            return;
        }

        cout << "Enter amount to deposit: Rs. ";
        if (!readPositiveAmount(amount)) return;

        accounts[index].deposit(amount);
        if (saveAccounts())
            cout << "Deposit successful. New balance: Rs. "
                 << fixed << setprecision(2)
                 << accounts[index].getBalance() << '\n';
        else
            cout << "Error saving transaction.\n";
    }

    void withdrawMoney() {
        int number;
        double amount;

        cout << "\nEnter account number: ";
        if (!(cin >> number)) {
            cout << "Invalid account number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        int index = findAccountIndex(number);
        if (index == -1) {
            cout << "Account not found.\n";
            return;
        }

        cout << "Enter amount to withdraw: Rs. ";
        if (!readPositiveAmount(amount)) return;

        if (!accounts[index].withdraw(amount)) {
            cout << "Withdrawal failed. Check the amount and available balance.\n";
            return;
        }

        if (saveAccounts())
            cout << "Withdrawal successful. Remaining balance: Rs. "
                 << fixed << setprecision(2)
                 << accounts[index].getBalance() << '\n';
        else
            cout << "Error saving transaction.\n";
    }

    void checkBalance() const {
        int number;

        cout << "\nEnter account number: ";
        if (!(cin >> number)) {
            cout << "Invalid account number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        int index = findAccountIndex(number);
        if (index == -1) {
            cout << "Account not found.\n";
            return;
        }

        accounts[index].display();
    }

    void displayAllAccounts() const {
        if (accounts.empty()) {
            cout << "\nNo accounts are available.\n";
            return;
        }

        cout << "\n---------------- BANK ACCOUNTS ----------------\n";
        cout << left << setw(16) << "Account No."
             << setw(26) << "Customer Name" << "Balance (Rs.)\n";
        cout << string(58, '-') << '\n';

        for (const auto& account : accounts) {
            cout << left << setw(16) << account.getAccountNumber()
                 << setw(26) << account.getCustomerName()
                 << fixed << setprecision(2)
                 << account.getBalance() << '\n';
        }
    }
};

int main() {
    Bank bank;
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "        BANK MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Exit\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a valid menu number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.depositMoney(); break;
            case 3: bank.withdrawMoney(); break;
            case 4: bank.checkBalance(); break;
            case 5: bank.displayAllAccounts(); break;
            case 6: cout << "Thank you for using the Bank Management System!\n"; break;
            default: cout << "Invalid choice. Select 1 to 6.\n";
        }
    } while (choice != 6);

    return 0;
}
