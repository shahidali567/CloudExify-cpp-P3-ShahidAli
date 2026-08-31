## Banking Management System

## Description

The Banking Management System is a C++ console-based application designed to manage basic banking operations. It allows users to create bank accounts, 
deposit and withdraw money, check balances, view transaction history, and calculate interest for savings accounts.
The project uses file handling to save and load account and transaction records, so the data remains available when the program is restarted.



## Developer Info

Developer: Shahid Ali

Roll Number: CX-INT-2026-CPP-0361


## Features

- Create new bank accounts
- Savings and Checking account types
- Automatic account numbers
- Deposit money
- Withdraw money
- Insufficient balance validation
- Check current balance
- View last 10 transactions
- Calculate 5% interest for Savings accounts
- Save account information to a file
- Save transaction information to a file
- Load saved data when the program starts

## Project Structure

Banking-Management-System/
│
├── main.cpp
├── accounts.dat
├── transactions.dat
└── README.md

## File Description

- main.cpp — Contains the complete C++ source code.
- accounts.dat — Stores bank account information.
- transactions.dat — Stores transaction records.
- README.md — Contains project documentation.

## How to Run

1. Download or clone the project.
2. Open "main.cpp" in a C++ compiler or IDE.
3. Compile the program.
4. Run the executable.
5. Select an option from the banking menu.
6. Account and transaction data can be saved using the Save Data option.

The project can be run using:

- Visual Studio
- VS Code
- Code::Blocks
- Dev-C++
- Any standard C++ compiler

## Program Workflow

Start
  ↓
Load Saved Data
  ↓
Display Banking Menu
  ↓
Select Operation
  ↓
Create Account / Deposit / Withdraw
  ↓
Check Balance / Transactions / Interest
  ↓
Save Data
  ↓
Exit

## Account Workflow

1. User selects Create Account.
2. User enters customer name.
3. User selects Savings or Checking.
4. User enters the opening balance.
5. A unique account number is generated.
6. The account is stored in the program.

## Transaction Workflow

1. User enters the account number.
2. The system searches for the account.
3. User enters the transaction amount.
4. The balance is updated.
5. The transaction is recorded.
6. Updated data can be saved to files.

## Screenshots

Main Menu

<img width="732" height="399" alt="image" src="https://github.com/user-attachments/assets/c0ed5c70-7498-4604-8fcd-a86651f3060c" />

Create Account

<img width="652" height="296" alt="image" src="https://github.com/user-attachments/assets/c0d9086c-d6d8-4afc-89a8-d87eedae9a0f" />

Transaction History

<img width="788" height="311" alt="image" src="https://github.com/user-attachments/assets/68783c9b-815d-49ad-a490-c73d9a9d86ea" />

Account List

<img width="796" height="195" alt="image" src="https://github.com/user-attachments/assets/88c8d686-4d33-4200-90fc-d9148b38dd67" />



## Concepts Used

The project demonstrates the following C++ concepts:
- Structures
- Variables and data types
- Functions
- Pointers
- Vectors
- Loops
- Conditional statements
- Switch statements
- String handling
- File input/output
- "ifstream"
- "ofstream"
- "stringstream"
- Searching records
- Data persistence
- Basic validation
- Formatted output using "iomanip"

## Author

Shahid Ali

Roll Number: CX-INT-2026-CPP-0361

Project: Banking Management System

Language: C++
