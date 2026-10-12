<<<<<<< HEAD
# LedgerNav - Transaction History Navigator

> **C++, OOPs, Data Structures | July 2026**

LedgerNav is a high-performance, object-oriented financial transaction management and history navigation engine written in C++. It features a custom **Doubly Linked List** implementation that powers **browser-style linear history navigation (Undo/Redo)**, strict **forward history management**, polymorphic **transaction type modeling**, encapsulated **account state tracking**, and a custom **exception hierarchy** with rigorous input validation.

---

## Core Highlights

- **Browser-Style Undo / Redo Navigation**:
  - Implements a bidirectional navigation cursor over a custom Doubly Linked List (`prev` and `next` pointers).
  - Step backward (**Undo**) to revert financial transactions from live account state.
  - Step forward (**Redo**) to re-apply transactions.
  - Interactive **Transaction Navigator Console** allowing real-time timeline inspection and step-by-step traversal.

- **OOP Modeling for Transaction Types & Account State**:
  - **Polymorphic Transaction Hierarchy**: Abstract base `Transaction` class with specialized derived classes:
    - `IncomeTransaction` (credits liquid balance & tracks income)
    - `ExpenseTransaction` (debits balance & tracks expenditures)
    - `InvestmentTransaction` (allocates balance to investment portfolio)
  - **TransactionFactory**: Enforces the GoF Factory Pattern for validated object creation.
  - **Encapsulated Account State**: `Account` models dynamic liquid cash, accumulated income, expenses, and portfolio totals with full rollback capabilities.

- **History State Management (Branch Fork Pruning)**:
  - Preserves linear history integrity just like modern web browser URL navigation.
  - If a user performs an **Undo** (navigating backward in history) and subsequently records a **New Transaction**, all forward history (`current->next` to `tail`) is discarded and deallocated, establishing a new active branch from the current point.

- **Custom Exception Handling & Strict Input Validation**:
  - Domain-specific exception hierarchy derived from `std::exception`:
    - `LedgerException` (base)
    - `InvalidDateException` (calendar validation, leap-year checks, day/month bounds)
    - `InvalidAmountException` (strictly positive amount enforcement)
    - `InsufficientFundsException`
    - `HistoryNavigationException` (boundary condition detection during undo/redo)
    - `InvalidTransactionException`
    - `UserAuthException`

- **In-Place Merge Sort on Doubly Linked List**:
  - Sort transactions by Date, Amount, or Category directly on DLL pointer links ($O(N \log N)$ time, $O(1)$ auxiliary space) without STL containers or node copying.

- **Persistence & User Isolation**:
  - Multi-user authentication with isolated transaction query-mimicry stored in clean pipe-delimited text files (`data/users.txt`, `data/transactions.txt`, `data/budgets.txt`).

---

## Architecture Overview

```text
d:\LedgerNav1/
├── data/
│   ├── users.txt         # Format: userId|username|password
│   ├── transactions.txt  # Format: transactionId|userId|date|amount|category|type|description
│   └── budgets.txt       # Format: userId|category|amount
│
├── Exceptions.h          # Domain exception hierarchy (LedgerException, etc.)
├── Account.h / .cpp      # Financial account state modeling & state transitions
├── Transaction.h / .cpp  # Polymorphic Transaction base & derived types + Factory
├── Node.h / .cpp         # Doubly linked list node with RAII transaction ownership
├── Ledger.h / .cpp       # DLL engine, history cursor, undo/redo, reports & merge sort
├── FileManager.h / .cpp  # File storage, multi-user isolation & record serialization
├── User.h / .cpp         # User entity & authentication helpers
├── Utils.h / .cpp        # Date validation (leap-years), amount validation, UI helpers
├── main.cpp              # Controller, interactive navigator, and menu loop
└── Readme.md             # Project documentation
```

---

## Doubly Linked List History Navigation Model

```text
[Genesis: 0 TX] <---> [TX #101: Salary +$50,000] <---> [TX #102: Food -$3,000] <---> [TX #103: Stocks -$7,000]
                                                            ^                               ^
                                                            |                               |
                                                      (Undo Cursor)                  (Forward / Redo)
```

1. **Undo Operation**:
   $$\text{Cursor} \leftarrow \text{Cursor} \to \text{prev}$$
   Rolls back `TX #103` from `Account` balance.
2. **Redo Operation**:
   $$\text{Cursor} \leftarrow \text{Cursor} \to \text{next}$$
   Re-applies `TX #103` to `Account` balance.
3. **New Transaction after Undo**:
   Forward nodes (`TX #103` onwards) are pruned and freed from memory.
   New transaction `TX #104` is appended directly after `TX #102`.

---

## Build Instructions

Compile with any standard C++ compiler (C++14 or newer):

### Using GCC / G++:
```bash
g++ -std=c++17 -o LedgerNav main.cpp Transaction.cpp Account.cpp User.cpp Ledger.cpp Node.cpp FileManager.cpp Utils.cpp
```

### Using MSVC (`cl.exe`):
```cmd
cl /EHsc /std:c++17 /Fe:LedgerNav.exe main.cpp Transaction.cpp Account.cpp User.cpp Ledger.cpp Node.cpp FileManager.cpp Utils.cpp
```

### Run the Application:
```bash
./LedgerNav
```

---

## Interactive Menu Structure

```text
============================================================
  Main Menu [User: alice | ID: 1]
  Live Balance: Rs. 47000.00
  History Status: [<- Undo Available] [Redo Available ->]
============================================================
1.  Add Transaction (Linear History Forking)
2.  View All Transactions & History Status
3.  Browser-Style Undo (Navigate Backward)
4.  Browser-Style Redo (Navigate Forward)
5.  Interactive Transaction Navigator (Browser Mode)
6.  View History Timeline & Account State
7.  Update Transaction
8.  Delete Transaction
9.  Search Transactions
10. Sort Transactions (In-Place Merge Sort)
11. Generate Financial Reports
12. Budget Tracking Dashboard
13. Logout
```
=======
# LedgerNav

LedgerNav is a C++ console-based transaction history navigator designed using Object-Oriented Programming principles.

## Features (In Progress)

- Transaction Management
- User Management
- File Handling
- Search & Sort Transactions
- Monthly Reports

## Technologies Used

- C++
- Doubly LInked LIst
- File Handling
- Object-Oriented Programming

## Project Status

🚧 Under Development
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
