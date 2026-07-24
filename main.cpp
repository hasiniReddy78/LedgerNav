#include <iostream>
#include <limits>
#include "Utils.h"
#include "Ledger.h"
#include "Transaction.h"

using namespace std;

int main()
{
    Ledger ledger;
    int choice;

    do
    {
        Utils::printHeader();

        cout << "1. Add Transaction\n";
        cout << "2. View Transactions\n";
        cout << "3. Exit\n\n";

        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            string date, category, type, description;
            double amount;

            cout << "\nEnter Date (DD-MM-YYYY): ";
            getline(cin, date);

            cout << "Enter Amount: ";
            cin >> amount;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Category: ";
            getline(cin, category);

            cout << "Enter Type (Income/Expense): ";
            getline(cin, type);

            cout << "Enter Description: ";
            getline(cin, description);

            Transaction transaction(
                Utils::generateTransactionId(),
                date,
                amount,
                category,
                type,
                description);

            ledger.addTransaction(transaction);

            cout << "\nTransaction added successfully!\n\n";

            break;
        }

        case 2:

            ledger.displayTransactions();
            break;

        case 3:

            cout << "\nThank you for using LedgerNav!\n";
            break;

        default:

            cout << "\nInvalid Choice!\n";
        }

        if (choice != 3)
        {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 3);

    return 0;
}