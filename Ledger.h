#ifndef LEDGER_H
#define LEDGER_H

#include "Node.h"

class Ledger
{
private:
    Node *head;
    Node *tail;

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