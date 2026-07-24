#include "Ledger.h"
#include <iostream>

using namespace std;

// Add a transaction
void Ledger::addTransaction(const Transaction &transaction)
{
    transactions.push_back(transaction);
}

// Display all transactions
void Ledger::displayTransactions() const
{
    if (transactions.empty())
    {
        cout << "\nNo transactions found.\n";
        return;
    }

    cout << "\n========== Transaction History ==========\n";

    for (const auto &transaction : transactions)
    {
        transaction.display();
    }
}

// Return reference to transaction vector
vector<Transaction>& Ledger::getTransactions()
{
    return transactions;
}