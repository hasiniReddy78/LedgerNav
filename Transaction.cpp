#include "Transaction.h"

Transaction::Transaction()
{
    id = 0;
    date = "";
    amount = 0.0;
    category = "";
    type = "";
    description = "";
}

Transaction::Transaction(int id, string date, double amount,
                         string category, string type,
                         string description)
{
    this->id = id;
    this->date = date;
    this->amount = amount;
    this->category = category;
    this->type = type;
    this->description = description;
}

// Getters

int Transaction::getId() const
{
    return id;
}

string Transaction::getDate() const
{
    return date;
}

double Transaction::getAmount() const
{
    return amount;
}

string Transaction::getCategory() const
{
    return category;
}

string Transaction::getType() const
{
    return type;
}

string Transaction::getDescription() const
{
    return description;
}

// Setters

void Transaction::setId(int id)
{
    this->id = id;
}

void Transaction::setDate(string date)
{
    this->date = date;
}

void Transaction::setAmount(double amount)
{
    this->amount = amount;
}

void Transaction::setCategory(string category)
{
    this->category = category;
}

void Transaction::setType(string type)
{
    this->type = type;
}

void Transaction::setDescription(string description)
{
    this->description = description;
}

// Display

void Transaction::display() const
{
    cout << "----------------------------------\n";
    cout << "Transaction ID : " << id << endl;
    cout << "Date           : " << date << endl;
    cout << "Amount         : " << amount << endl;
    cout << "Category       : " << category << endl;
    cout << "Type           : " << type << endl;
    cout << "Description    : " << description << endl;
    cout << "----------------------------------\n";
}