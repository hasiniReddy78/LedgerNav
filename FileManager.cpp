#include "FileManager.h"
#include <fstream>
#include <sstream>

using namespace std;

// Save transactions to file
void FileManager::saveTransactions(Node *head)
{
    ofstream file("data/transactions.txt");

    Node *current = head;

    while (current != nullptr)
    {
        Transaction t = current->transaction;

        file << t.getId() << "|"
             << t.getDate() << "|"
             << t.getAmount() << "|"
             << t.getCategory() << "|"
             << t.getType() << "|"
             << t.getDescription() << endl;

        current = current->next;
    }

    file.close();
}

// Load transactions from file
void FileManager::loadTransactions(Ledger &ledger)
{
    ifstream file("data/transactions.txt");

    if (!file.is_open())
        return;

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

        Transaction transaction(
            stoi(id),
            date,
            stod(amount),
            category,
            type,
            description);

        ledger.addTransaction(transaction);
    }

    file.close();
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