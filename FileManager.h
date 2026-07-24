#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include "Transaction.h"
#include "User.h"

using namespace std;

class FileManager
{
public:
    // Transaction file operations
    static void saveTransactions(const vector<Transaction>& transactions);
    static vector<Transaction> loadTransactions();

    // User file operations
    static void saveUsers(const vector<User>& users);
    static vector<User> loadUsers();
};

#endif