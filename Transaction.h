#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>

using namespace std;

class Transaction
{
private:
    int id;
    string date;
    double amount;
    string category;
    string type;
    string description;

public:
    // Constructors
    Transaction();
    Transaction(int id, string date, double amount,
                string category, string type,
                string description);

    // Getters
    int getId() const;
    string getDate() const;
    double getAmount() const;
    string getCategory() const;
    string getType() const;
    string getDescription() const;

    // Setters
    void setId(int id);
    void setDate(string date);
    void setAmount(double amount);
    void setCategory(string category);
    void setType(string type);
    void setDescription(string description);

    // Display transaction
    void display() const;
};

#endif