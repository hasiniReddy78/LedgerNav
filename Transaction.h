#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include "Account.h"

using namespace std;

// Base Abstract Class modeling common transaction properties and lifecycle
class Transaction
{
protected:
    int id;
    int userId;
    string date;
    double amount;
    string category;
    string description;

public:
    // Constructors & Virtual Destructor
    Transaction();
    Transaction(int id, int userId, const string &date, double amount,
                const string &category, const string &description);
    virtual ~Transaction() = default;

    // Getters
    int getId() const;
    int getUserId() const;
    string getDate() const;
    double getAmount() const;
    string getCategory() const;
    string getDescription() const;

    // Setters
    void setId(int id);
    void setUserId(int userId);
    void setDate(const string &date);
    void setAmount(double amount);
    void setCategory(const string &category);
    void setDescription(const string &description);

    // Pure Virtual Methods (Polymorphism)
    virtual string getType() const = 0;
    virtual void applyToAccount(Account &account) const = 0;
    virtual void rollbackFromAccount(Account &account) const = 0;
    virtual Transaction *clone() const = 0;

    // Concrete Methods
    virtual void display() const;
    virtual string serialize() const;
};

// Derived Class: Income Transaction
class IncomeTransaction : public Transaction
{
public:
    IncomeTransaction(int id, int userId, const string &date, double amount,
                      const string &category, const string &description);

    string getType() const override;
    void applyToAccount(Account &account) const override;
    void rollbackFromAccount(Account &account) const override;
    Transaction *clone() const override;
};

// Derived Class: Expense Transaction
class ExpenseTransaction : public Transaction
{
public:
    ExpenseTransaction(int id, int userId, const string &date, double amount,
                       const string &category, const string &description);

    string getType() const override;
    void applyToAccount(Account &account) const override;
    void rollbackFromAccount(Account &account) const override;
    Transaction *clone() const override;
};

// Derived Class: Investment Transaction
class InvestmentTransaction : public Transaction
{
public:
    InvestmentTransaction(int id, int userId, const string &date, double amount,
                          const string &category, const string &description);

    string getType() const override;
    void applyToAccount(Account &account) const override;
    void rollbackFromAccount(Account &account) const override;
    Transaction *clone() const override;
};

// Factory to instantiate polymorphic transaction objects with validation
class TransactionFactory
{
public:
    static Transaction *createTransaction(int id, int userId, const string &date,
                                          double amount, const string &category,
                                          const string &type, const string &description);
};

#endif // TRANSACTION_H
