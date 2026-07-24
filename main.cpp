#include <iostream>
#include "Utils.h"
#include "Ledger.h"
#include "Transaction.h"

using namespace std;

int main()
{
    Utils::printHeader();

    Ledger ledger;

    // Sample transactions
    Transaction t1(
        Utils::generateTransactionId(),
        "24-07-2026",
        250.50,
        "Food",
        "Expense",
        "Burger and Fries"
    );

    Transaction t2(
        Utils::generateTransactionId(),
        "24-07-2026",
        5000,
        "Salary",
        "Income",
        "Monthly Salary"
    );

    ledger.addTransaction(t1);
    ledger.addTransaction(t2);

    ledger.displayTransactions();

    cout << "\nThank you for using LedgerNav!\n";

    return 0;
}