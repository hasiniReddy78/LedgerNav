#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <map>
#include "Transaction.h"
#include "User.h"
#include "Node.h"
#include "Ledger.h"

using namespace std;

class FileManager
{
public:
    // Save transactions from Doubly Linked List for a specific user
    static void saveTransactions(Node *head, int userId);

    // Load transactions from file for a specific user
    static void loadTransactions(Ledger &ledger, int userId);

    // User operations
    static void saveUsers(const vector<User> &users);
    static vector<User> loadUsers();

    // Helper for absolute highest transaction ID
    static int getHighestTransactionIdInFile();

    // Budget operations
    static void saveBudget(int userId, const string &category, double amount);
    static map<string, double> loadBudgets(int userId);
};

#endif