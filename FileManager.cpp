#include "FileManager.h"
#include <fstream>
#include <sstream>

using namespace std;

// Save transactions to file
void FileManager::saveTransactions(const vector<Transaction>& transactions)
{
    ofstream file("data/transactions.txt");

    for (const auto &transaction : transactions)
    {
        file << transaction.getId() << "|"
             << transaction.getDate() << "|"
             << transaction.getAmount() << "|"
             << transaction.getCategory() << "|"
             << transaction.getType() << "|"
             << transaction.getDescription() << endl;
    }

    file.close();
}

// Load transactions from file
vector<Transaction> FileManager::loadTransactions()
{
    vector<Transaction> transactions;
    ifstream file("data/transactions.txt");

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string id, date, amount, category, type, description;

        getline(ss, id, '|');
        getline(ss, date, '|');
        getline(ss, amount, '|');
        getline(ss, category, '|');
        getline(ss, type, '|');
        getline(ss, description);

        transactions.push_back(
            Transaction(
                stoi(id),
                date,
                stod(amount),
                category,
                type,
                description
            )
        );
    }

    file.close();
    return transactions;
}

// Save users
void FileManager::saveUsers(const vector<User>& users)
{
    ofstream file("data/users.txt");

    for (const auto &user : users)
    {
        file << user.getUsername() << "|"
             << user.getPassword() << endl;
    }

    file.close();
}

// Load users
vector<User> FileManager::loadUsers()
{
    vector<User> users;
    ifstream file("data/users.txt");

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string username, password;

        getline(ss, username, '|');
        getline(ss, password);

        users.push_back(User(username, password));
    }

    file.close();

    return users;
}