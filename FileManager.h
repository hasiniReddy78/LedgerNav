#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
<<<<<<< HEAD
#include <map>
=======
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
#include "Transaction.h"
#include "User.h"
#include "Node.h"
#include "Ledger.h"

using namespace std;

class FileManager
{
public:
<<<<<<< HEAD
    // Save transactions from Doubly Linked List for a specific user
    static void saveTransactions(Node *head, int userId);

    // Load transactions from file for a specific user
    static void loadTransactions(Ledger &ledger, int userId);
=======
    // Save transactions from Doubly Linked List
    static void saveTransactions(Node *head);

    // Load transactions from file
    static void loadTransactions(Ledger &ledger);;
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74

    // User operations
    static void saveUsers(const vector<User> &users);
    static vector<User> loadUsers();
<<<<<<< HEAD

    // Helper for absolute highest transaction ID
    static int getHighestTransactionIdInFile();

    // Budget operations
    static void saveBudget(int userId, const string &category, double amount);
    static map<string, double> loadBudgets(int userId);
=======
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
};

#endif