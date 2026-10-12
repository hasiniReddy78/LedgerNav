#include "FileManager.h"
#include "Exceptions.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Save transactions to file for a specific user, preserving other users' transactions
void FileManager::saveTransactions(Node *head, int userId)
{
    vector<string> otherUsersLines;
    ifstream infile("data/transactions.txt");

    if (infile.is_open())
    {
        string line;
        while (getline(infile, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            string tid_str, uid_str;

            if (getline(ss, tid_str, '|') && getline(ss, uid_str, '|'))
            {
                try
                {
                    int uid = stoi(uid_str);
                    if (uid != userId)
                    {
                        otherUsersLines.push_back(line);
                    }
                }
                catch (...)
                {
                    // Skip malformed record, do not preserve it
                }
            }
        }
        infile.close();
    }

    // Now write back other users' transactions + current user's active transactions
    ofstream outfile("data/transactions.txt");
    if (!outfile.is_open())
    {
        cerr << "Error: Could not open transactions file for writing.\n";
        return;
    }

    for (const auto &line : otherUsersLines)
    {
        outfile << line << endl;
    }

    Node *current = head;
    while (current != nullptr)
    {
        if (current->transaction != nullptr)
        {
            outfile << current->transaction->serialize() << endl;
        }
        current = current->next;
    }

    outfile.close();
}

// Load transactions from file for a specific user
void FileManager::loadTransactions(Ledger &ledger, int userId)
{
    ledger.setUserId(userId);
    ifstream file("data/transactions.txt");

    if (!file.is_open())
        return;

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string id_str, uid_str, date, amt_str, category, type, description;

        if (getline(ss, id_str, '|') &&
            getline(ss, uid_str, '|') &&
            getline(ss, date, '|') &&
            getline(ss, amt_str, '|') &&
            getline(ss, category, '|') &&
            getline(ss, type, '|') &&
            getline(ss, description))
        {
            try
            {
                int id = stoi(id_str);
                int uid = stoi(uid_str);
                double amount = stod(amt_str);

                if (uid == userId)
                {
                    Transaction *transaction = TransactionFactory::createTransaction(
                        id, uid, date, amount, category, type, description);

                    ledger.addTransaction(transaction);
                }
            }
            catch (const LedgerException &e)
            {
                // Robustness: skip invalid record and log warning
                cerr << "Warning loading record: " << e.what() << "\n";
            }
            catch (...)
            {
                // Robustness: skip malformed record and continue loading
            }
        }
    }

    file.close();
}

// Save users to file in format: userId|username|password
void FileManager::saveUsers(const vector<User> &users)
{
    ofstream file("data/users.txt");
    if (!file.is_open())
    {
        cerr << "Error: Could not open users file for writing.\n";
        return;
    }

    for (const auto &user : users)
    {
        file << user.getUserId() << "|"
             << user.getUsername() << "|"
             << user.getPassword() << endl;
    }

    file.close();
}

// Load users from file in format: userId|username|password
vector<User> FileManager::loadUsers()
{
    vector<User> users;
    ifstream file("data/users.txt");

    if (!file.is_open())
        return users;

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string uid_str, username, password;

        if (getline(ss, uid_str, '|') &&
            getline(ss, username, '|') &&
            getline(ss, password))
        {
            try
            {
                int uid = stoi(uid_str);
                users.push_back(User(uid, username, password));
            }
            catch (...)
            {
                // Robustness: skip malformed line
            }
        }
    }

    file.close();
    return users;
}

// Helper to scan transactions.txt and find the highest transaction ID
int FileManager::getHighestTransactionIdInFile()
{
    int highestId = 1000;
    ifstream file("data/transactions.txt");

    if (!file.is_open())
        return highestId;

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string id_str;

        if (getline(ss, id_str, '|'))
        {
            try
            {
                int id = stoi(id_str);
                if (id > highestId)
                {
                    highestId = id;
                }
            }
            catch (...)
            {
                // Skip malformed record ID
            }
        }
    }

    file.close();
    return highestId;
}

// Save or update a specific category budget for a user
void FileManager::saveBudget(int userId, const string &category, double amount)
{
    vector<string> otherBudgets;
    ifstream infile("data/budgets.txt");
    if (infile.is_open())
    {
        string line;
        while (getline(infile, line))
        {
            if (line.empty())
                continue;
            stringstream ss(line);
            string uid_str, cat, amt_str;
            if (getline(ss, uid_str, '|') && getline(ss, cat, '|') && getline(ss, amt_str))
            {
                try
                {
                    int uid = stoi(uid_str);
                    if (uid != userId || cat != category)
                    {
                        otherBudgets.push_back(line);
                    }
                }
                catch (...)
                {
                    // Skip malformed record
                }
            }
        }
        infile.close();
    }

    ofstream outfile("data/budgets.txt");
    if (!outfile.is_open())
    {
        cerr << "Error: Could not open budgets file for writing.\n";
        return;
    }

    for (const auto &line : otherBudgets)
    {
        outfile << line << endl;
    }
    outfile << userId << "|" << category << "|" << amount << endl;
    outfile.close();
}

// Load all budgets for a user
map<string, double> FileManager::loadBudgets(int userId)
{
    map<string, double> budgets;
    ifstream file("data/budgets.txt");
    if (!file.is_open())
        return budgets;

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string uid_str, cat, amt_str;
        if (getline(ss, uid_str, '|') && getline(ss, cat, '|') && getline(ss, amt_str))
        {
            try
            {
                int uid = stoi(uid_str);
                double amt = stod(amt_str);
                if (uid == userId)
                {
                    budgets[cat] = amt;
                }
            }
            catch (...)
            {
                // Skip malformed budget records
            }
        }
    }
    file.close();
    return budgets;
}