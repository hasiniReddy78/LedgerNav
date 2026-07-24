#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include "Transaction.h"
#include "User.h"
#include "Node.h"
#include "Ledger.h"

using namespace std;

class FileManager
{
public:
    // Save transactions from Doubly Linked List
    static void saveTransactions(Node *head);

    // Load transactions from file
    static void loadTransactions(Ledger &ledger);;

    // User operations
    static void saveUsers(const vector<User> &users);
    static vector<User> loadUsers();
};

#endif