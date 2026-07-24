#include "FileManager.h"
#include <iostream>
#include <limits>
#include "Utils.h"
#include "Ledger.h"
#include "Transaction.h"

using namespace std;

int main()
{
    Ledger ledger;

    // Load previously saved transactions directly into the linked list
    FileManager::loadTransactions(ledger);

    // Initialize the transaction ID generator
    Utils::setCurrentId(ledger.getHighestTransactionId());

    int choice;

    do
    {
        Utils::printHeader();

        cout << "1. Add Transaction\n";
        cout << "2. View Transactions\n";
        cout << "3. Financial Summary\n";
        cout << "4. Exit\n\n";

        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            string date, category, type, description;
            double amount;
            int typeChoice;

            cout << "\nEnter Date (DD-MM-YYYY): ";
            getline(cin, date);

            cout << "Enter Amount: ";
            cin >> amount;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Select Transaction Type\n";
            cout << "1. Income\n";
            cout << "2. Expense\n";
            cout << "3. Investment\n";
            cout << "Enter choice: ";
            cin >> typeChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (typeChoice)
            {
            case 1:
                type = "Income";
                break;

            case 2:
                type = "Expense";
                break;

            case 3:
                type = "Investment";
                break;

            default:
                cout << "\nInvalid transaction type!\n";
                continue;
            }

            cout << "Enter Category: ";
            getline(cin, category);

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

            // Save all transactions to file
            FileManager::saveTransactions(ledger.getHead());

            cout << "\nTransaction added successfully!\n";
            break;
        }

        case 2:
            ledger.displayTransactions();
            break;

        case 3:
            ledger.displayFinancialSummary();
            break;

        case 4:
            cout << "\nThank you for using LedgerNav!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

        if (choice != 4)
        {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 4);

    return 0;
}