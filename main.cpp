#include "FileManager.h"
#include "Exceptions.h"
#include "Ledger.h"
#include "Transaction.h"
#include "User.h"
#include "Utils.h"
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// Coordinate User Registration with input validation and exception handling
void handleRegistration(vector<User> &users)
{
    try
    {
        string username, password;
        cout << "\n--- Register ---\n";
        cout << "Enter username: ";
        getline(cin, username);

        Utils::validateString(username, "Username");

        for (const auto &user : users)
        {
            if (user.getUsername() == username)
            {
                throw UserAuthException("Username '" + username + "' already exists!");
            }
        }

        cout << "Enter password: ";
        getline(cin, password);
        Utils::validateString(password, "Password");

        // Auto-generate unique user ID starting at 100
        int highestUserId = 99;
        for (const auto &user : users)
        {
            if (user.getUserId() > highestUserId)
            {
                highestUserId = user.getUserId();
            }
        }
        int newUserId = highestUserId + 1;

        User newUser(newUserId, username, password);
        users.push_back(newUser);
        FileManager::saveUsers(users);

        cout << "\nRegistration successful! User ID assigned: " << newUserId << "\n";
    }
    catch (const LedgerException &e)
    {
        cout << "\nRegistration Failed: " << e.what() << "\n";
    }
}

// Coordinate User Login
int handleLogin(const vector<User> &users, string &outUsername)
{
    try
    {
        string username, password;
        cout << "\n--- Login ---\n";
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);

        for (const auto &user : users)
        {
            if (user.getUsername() == username && user.authenticate(password))
            {
                cout << "\nLogin successful! Welcome back, " << username << ".\n";
                outUsername = username;
                return user.getUserId();
            }
        }

        throw UserAuthException("Invalid username or password!");
    }
    catch (const LedgerException &e)
    {
        cout << "\nLogin Failed: " << e.what() << "\n";
        return -1;
    }
}

int main()
{
    vector<User> users = FileManager::loadUsers();
    int currentUserId = -1;
    string currentUsername = "";

    int choice;
    do
    {
        Utils::printHeader();
        if (currentUserId == -1)
        {
            cout << "1. Login\n";
            cout << "2. Register\n";
            cout << "3. Exit\n\n";
            cout << "Enter choice: ";
            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid input. Please enter a number.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice)
            {
            case 1:
                currentUserId = handleLogin(users, currentUsername);
                break;
            case 2:
                handleRegistration(users);
                users = FileManager::loadUsers(); // Refresh list of users
                break;
            case 3:
                cout << "\nThank you for using LedgerNav!\n";
                break;
            default:
                cout << "\nInvalid Choice! Please choose 1, 2, or 3.\n";
            }
        }
        else
        {
            // Logged in user dashboard
            Ledger ledger(currentUserId);
            FileManager::loadTransactions(ledger, currentUserId);
            Utils::setCurrentId(FileManager::getHighestTransactionIdInFile());

            int userChoice;
            do
            {
                cout << "\n============================================================\n";
                cout << "  Main Menu [User: " << currentUsername << " | ID: " << currentUserId << "]\n";
                cout << "  Live Balance: Rs. " << ledger.getAccount().getBalance() << "\n";
                cout << "  History Status: "
                     << (ledger.canUndo() ? "[<- Undo Available] " : "[<- Undo Disabled] ")
                     << (ledger.canRedo() ? "[Redo Available ->]" : "[Redo Disabled ->]") << "\n";
                cout << "============================================================\n";
                cout << "1.  Add Transaction (Linear History Forking)\n";
                cout << "2.  View All Transactions & History Status\n";
                cout << "3.  Browser-Style Undo (Navigate Backward)\n";
                cout << "4.  Browser-Style Redo (Navigate Forward)\n";
                cout << "5.  Interactive Transaction Navigator (Browser Mode)\n";
                cout << "6.  View History Timeline & Account State\n";
                cout << "7.  Update Transaction\n";
                cout << "8.  Delete Transaction\n";
                cout << "9.  Search Transactions\n";
                cout << "10. Sort Transactions (In-Place Merge Sort)\n";
                cout << "11. Generate Financial Reports\n";
                cout << "12. Budget Tracking Dashboard\n";
                cout << "13. Logout\n\n";
                cout << "Enter choice: ";

                if (!(cin >> userChoice))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nInvalid input! Please enter a valid number.\n";
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                try
                {
                    switch (userChoice)
                    {
                    case 1: // Add Transaction
                    {
                        string date, category, type, description;
                        double amount;
                        int typeChoice;

                        cout << "\nEnter Date (DD-MM-YYYY): ";
                        getline(cin, date);
                        Utils::validateDate(date);

                        cout << "Enter Amount: ";
                        if (!(cin >> amount))
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            throw InvalidAmountException("Non-numeric amount entered.");
                        }
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        Utils::validateAmount(amount);

                        cout << "\nSelect Transaction Type:\n";
                        cout << "1. Income\n";
                        cout << "2. Expense\n";
                        cout << "3. Investment\n";
                        cout << "Enter choice (1-3): ";
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
                            throw InvalidTransactionException("Invalid transaction type option selected.");
                        }

                        cout << "Enter Category: ";
                        getline(cin, category);
                        Utils::validateString(category, "Category");

                        cout << "Enter Description: ";
                        getline(cin, description);
                        Utils::validateString(description, "Description");

                        int newId = Utils::generateTransactionId();
                        Transaction *newTx = TransactionFactory::createTransaction(
                            newId, currentUserId, date, amount, category, type, description);

                        // Adding transaction will discard forward history if currently undid
                        ledger.addTransaction(newTx);
                        FileManager::saveTransactions(ledger.getHead(), currentUserId);

                        cout << "\nTransaction #" << newId << " added successfully!\n";
                        cout << "Account balance updated to: Rs. " << ledger.getAccount().getBalance() << "\n";
                        break;
                    }

                    case 2: // View Transactions
                        ledger.displayTransactions();
                        break;

                    case 3: // Browser Undo
                    {
                        Transaction *undone = ledger.undo();
                        cout << "\n<<< [UNDO SUCCESSFUL]\n";
                        cout << "Rolled back Transaction #" << undone->getId()
                             << " (" << undone->getType() << " of Rs. " << undone->getAmount() << ")\n";
                        cout << "Current Account Balance: Rs. " << ledger.getAccount().getBalance() << "\n";
                        if (ledger.canRedo())
                        {
                            cout << "Note: Forward history is retained for Redo. Adding a new transaction will discard it.\n";
                        }
                        break;
                    }

                    case 4: // Browser Redo
                    {
                        Transaction *redone = ledger.redo();
                        cout << "\n>>> [REDO SUCCESSFUL]\n";
                        cout << "Re-applied Transaction #" << redone->getId()
                             << " (" << redone->getType() << " of Rs. " << redone->getAmount() << ")\n";
                        cout << "Current Account Balance: Rs. " << ledger.getAccount().getBalance() << "\n";
                        break;
                    }

                    case 5: // Interactive Browser Navigator
                        ledger.navigateHistory();
                        break;

                    case 6: // Timeline & Account State
                        ledger.displayHistoryTimeline();
                        ledger.getAccount().displayAccountSummary();
                        break;

                    case 7: // Update Transaction
                    {
                        int id;
                        cout << "\nEnter Transaction ID to update: ";
                        cin >> id;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        string date, category, type, description;
                        double amount;
                        int typeChoice;

                        cout << "Enter New Date (DD-MM-YYYY): ";
                        getline(cin, date);
                        Utils::validateDate(date);

                        cout << "Enter New Amount: ";
                        cin >> amount;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        Utils::validateAmount(amount);

                        cout << "Select New Transaction Type\n";
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
                            throw InvalidTransactionException("Invalid transaction type option.");
                        }

                        cout << "Enter New Category: ";
                        getline(cin, category);
                        Utils::validateString(category, "Category");

                        cout << "Enter New Description: ";
                        getline(cin, description);
                        Utils::validateString(description, "Description");

                        if (ledger.updateTransaction(id, date, amount, category, type, description))
                        {
                            FileManager::saveTransactions(ledger.getHead(), currentUserId);
                            cout << "\nTransaction updated successfully! Account state recalculated.\n";
                        }
                        else
                        {
                            cout << "\nTransaction ID #" << id << " not found!\n";
                        }
                        break;
                    }

                    case 8: // Delete Transaction
                    {
                        int id;
                        cout << "\nEnter Transaction ID to delete: ";
                        cin >> id;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if (ledger.deleteTransaction(id))
                        {
                            FileManager::saveTransactions(ledger.getHead(), currentUserId);
                            cout << "\nTransaction deleted successfully! Account state recalculated.\n";
                        }
                        else
                        {
                            cout << "\nTransaction ID #" << id << " not found!\n";
                        }
                        break;
                    }

                    case 9: // Search Transactions
                    {
                        int searchChoice;
                        cout << "\nSearch By:\n";
                        cout << "1. Transaction ID\n";
                        cout << "2. Category\n";
                        cout << "3. Date (DD-MM-YYYY)\n";
                        cout << "4. Type\n";
                        cout << "Enter choice (1-4): ";
                        cin >> searchChoice;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if (searchChoice < 1 || searchChoice > 4)
                        {
                            throw InvalidTransactionException("Invalid search option selected.");
                        }

                        string query;
                        cout << "Enter search query: ";
                        getline(cin, query);

                        ledger.searchTransactions(searchChoice, query);
                        break;
                    }

                    case 10: // Sort Transactions
                    {
                        int sortChoice;
                        cout << "\nSort By:\n";
                        cout << "1. Date\n";
                        cout << "2. Amount\n";
                        cout << "3. Category\n";
                        cout << "Enter choice (1-3): ";
                        cin >> sortChoice;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if (sortChoice < 1 || sortChoice > 3)
                        {
                            throw InvalidTransactionException("Invalid sort option selected.");
                        }

                        ledger.sortTransactions(sortChoice);
                        FileManager::saveTransactions(ledger.getHead(), currentUserId);
                        cout << "\nTransactions sorted via in-place Merge Sort and saved successfully!\n";
                        break;
                    }

                    case 11: // Reports
                    {
                        int rChoice;
                        cout << "\n--- Reports Sub-Menu ---\n";
                        cout << "1. Financial Summary & Account State\n";
                        cout << "2. Category-wise Expense Report\n";
                        cout << "3. Investment Report\n";
                        cout << "4. Monthly Report\n";
                        cout << "Enter choice: ";
                        cin >> rChoice;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        switch (rChoice)
                        {
                        case 1:
                            ledger.displayFinancialSummary();
                            break;
                        case 2:
                            ledger.displayCategoryExpenseReport();
                            break;
                        case 3:
                            ledger.displayInvestmentReport();
                            break;
                        case 4:
                        {
                            int month, year;
                            cout << "Enter Month (1-12): ";
                            cin >> month;
                            cout << "Enter Year (YYYY): ";
                            cin >> year;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            if (month < 1 || month > 12 || year < 1)
                            {
                                throw InvalidDateException("Invalid month or year entered for report.");
                            }
                            ledger.displayMonthlyReport(month, year);
                            break;
                        }
                        default:
                            cout << "Invalid Option!\n";
                        }
                        break;
                    }

                    case 12: // Budget Tracking
                    {
                        int bChoice;
                        cout << "\n--- Budget Tracking Sub-Menu ---\n";
                        cout << "1. View Budget Status Dashboard\n";
                        cout << "2. Set/Update Category Budget\n";
                        cout << "Enter choice: ";
                        cin >> bChoice;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if (bChoice == 1)
                        {
                            map<string, double> budgets = FileManager::loadBudgets(currentUserId);
                            ledger.displayBudgetStatus(budgets);
                        }
                        else if (bChoice == 2)
                        {
                            string category;
                            double amount;
                            cout << "Enter Category Name: ";
                            getline(cin, category);
                            Utils::validateString(category, "Category");

                            cout << "Enter Budget Amount: ";
                            cin >> amount;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            Utils::validateAmount(amount);

                            FileManager::saveBudget(currentUserId, category, amount);
                            cout << "\nBudget for '" << category << "' saved successfully!\n";
                        }
                        else
                        {
                            cout << "Invalid Option!\n";
                        }
                        break;
                    }

                    case 13: // Logout
                        cout << "\nLogging out...\n";
                        currentUserId = -1;
                        currentUsername = "";
                        break;

                    default:
                        cout << "\nInvalid Choice! Please enter a number from 1 to 13.\n";
                    }
                }
                catch (const LedgerException &e)
                {
                    cout << "\n[Domain Exception Caught] " << e.what() << "\n";
                }
                catch (const exception &e)
                {
                    cout << "\n[System Exception Caught] " << e.what() << "\n";
                }

                if (userChoice != 13)
                {
                    cout << "\nPress Enter to continue...";
                    cin.get();
                }

            } while (userChoice != 13);
        }

        if (currentUserId == -1 && choice != 3)
        {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 3 || currentUserId != -1);

    return 0;
}