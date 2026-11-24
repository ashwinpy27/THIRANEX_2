# Bank Management Application (C++)

A beginner-friendly, console-based banking application demonstrating object-oriented programming and file handling.

## Features
- Create a customer account
- Deposit money
- Withdraw money (prevents withdrawals above the available balance)
- Check an account balance
- Display all accounts
- Save account records in `accounts.txt` so they remain after the program closes

## OOP concepts used
- **Class:** `BankAccount` and `Bank`
- **Encapsulation:** account number, customer name, and balance are private
- **Objects:** the `Bank` class manages `BankAccount` objects
- **Member functions:** deposit, withdraw, display, and account-management operations

## Requirements
- C++ compiler (GCC / MinGW / Clang)
- C++11 or later

## Compile and run on Windows (MinGW)
Open a terminal in this folder:

```bash
g++ main.cpp -o BankManagement
.\BankManagement.exe
```

## Compile and run on Linux / macOS
```bash
g++ main.cpp -o BankManagement
./BankManagement
```

## Data file
The program creates `accounts.txt` in the current working directory when an account is saved.
Each line stores:

`AccountNumber|CustomerName|Balance`

Keep this file in the same working directory when you run the program again. Back it up to preserve the sample records.

## Important security note
This is an educational internship project, not production banking software. The text file is plain text and is **not encrypted**. It does not include authentication, PIN/password protection, audit logs, transaction rollback, or protection against concurrent access. Do not enter real customer details or use it to store real money/account information. A real banking system needs secure authentication, encryption, access controls, tamper-resistant audit logging, and a properly secured database.
