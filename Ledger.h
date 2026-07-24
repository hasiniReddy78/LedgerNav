#ifndef LEDGER_H
#define LEDGER_H

#include <vector>
#include "Transaction.h"

using namespace std;

class Ledger
{
private:
    vector<Transaction> transactions;

public:
    // Add a transaction
    void addTransaction(const Transaction &transaction);

    // Display all transactions
    void displayTransactions() const;

    // Get all transactions
    vector<Transaction>& getTransactions();
};

#endif