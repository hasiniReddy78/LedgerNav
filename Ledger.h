#ifndef LEDGER_H
#define LEDGER_H

<<<<<<< HEAD
#include <map>
#include <string>
#include "Node.h"
#include "Account.h"

using namespace std;
=======
#include "Node.h"
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74

class Ledger
{
private:
    Node *head;
    Node *tail;
<<<<<<< HEAD
    Node *current;    // Browser-style navigation history cursor
    Account account;  // Encapsulated financial account state

    // Private Merge Sort helpers for custom Doubly Linked List
    Node *mergeSort(Node *h, int sortChoice);
    Node *split(Node *h);
    Node *merge(Node *first, Node *second, int sortChoice);
    static int compareDates(const string &d1, const string &d2);

public:
    // Constructor & Destructor
    explicit Ledger(int userId = 0);
    ~Ledger();

    // Memory management
    void clear();

    // Core CRUD Operations
    void addTransaction(Transaction *transaction);
    void displayTransactions() const;
    void displayFinancialSummary() const;
    bool updateTransaction(int id, const string &date, double amount,
                           const string &category, const string &type,
                           const string &description);
    bool deleteTransaction(int id);
    void searchTransactions(int searchChoice, const string &query) const;
    void sortTransactions(int sortChoice);

    // Browser-Style Navigation & History State Management
    bool canUndo() const;
    bool canRedo() const;
    Transaction *undo();
    Transaction *redo();
    void navigateHistory();
    void displayHistoryTimeline() const;
    void discardForwardHistory();
    void recalculateAccountState();

    // Financial Reports
    void displayCategoryExpenseReport() const;
    void displayInvestmentReport() const;
    void displayMonthlyReport(int month, int year) const;
    void displayBudgetStatus(const map<string, double> &budgets) const;

    // Utility & State Accessors
    int getHighestTransactionId() const;
    Node *getHead() const;
    Node *getTail() const;
    Node *getCurrent() const;
    const Account &getAccount() const;
    void setUserId(int userId);
};

#endif // LEDGER_H
=======

public:
    // Constructor & Destructor
    Ledger();
    ~Ledger();

    // Core Operations
    void addTransaction(const Transaction &transaction);
    void displayTransactions() const;
    void displayFinancialSummary() const;

    // Utility Functions
    int getHighestTransactionId() const;

    // Getters
    Node *getHead() const;
    Node *getTail() const;
};

#endif
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
