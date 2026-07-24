#include "Ledger.h"
#include <iostream>

using namespace std;

// Constructor
Ledger::Ledger()
{
    head = nullptr;
    tail = nullptr;
}

// Destructor
Ledger::~Ledger()
{
    Node *current = head;

    while (current != nullptr)
    {
        Node *nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
    tail = nullptr;
}

// Add transaction at the end
void Ledger::addTransaction(const Transaction &transaction)
{
    Node *newNode = new Node(transaction);

    // Empty list
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
        return;
    }

    // Insert at the end
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
}

// Display all transactions
void Ledger::displayTransactions() const
{
    if (head == nullptr)
    {
        cout << "No transactions found.\n";
        return;
    }

    Node *current = head;

    while (current != nullptr)
    {
        current->transaction.display();
        current = current->next;
    }
}

// Display financial summary
void Ledger::displayFinancialSummary() const
{
    double totalIncome = 0.0;
    double totalExpense = 0.0;
    double totalInvestment = 0.0;

    Node *current = head;

    while (current != nullptr)
    {
        if (current->transaction.getType() == "Income")
        {
            totalIncome += current->transaction.getAmount();
        }
        else if (current->transaction.getType() == "Expense")
        {
            totalExpense += current->transaction.getAmount();
        }
        else if (current->transaction.getType() == "Investment")
        {
            totalInvestment += current->transaction.getAmount();
        }

        current = current->next;
    }

    cout << "\n========== Financial Summary ==========\n";
    cout << "Total Income      : Rs. " << totalIncome << endl;
    cout << "Total Expense     : Rs. " << totalExpense << endl;
    cout << "Total Investment  : Rs. " << totalInvestment << endl;
    cout << "Net Cash Balance  : Rs. "
         << (totalIncome - totalExpense - totalInvestment) << endl;
    cout << "=======================================\n";
}

int Ledger::getHighestTransactionId() const
{
    if (head == nullptr)
        return 1000;

    int highestId = 1000;
    Node *current = head;

    while (current != nullptr)
    {
        if (current->transaction.getId() > highestId)
        {
            highestId = current->transaction.getId();
        }

        current = current->next;
    }

    return highestId;
}

// Return head pointer
Node *Ledger::getHead() const
{
    return head;
}

// Return tail pointer
Node *Ledger::getTail() const
{
    return tail;
}