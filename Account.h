#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

class Account
{
private:
    int userId;
    double balance;
    double totalIncome;
    double totalExpense;
    double totalInvested;

public:
    Account(int userId = 0, double initialBalance = 0.0);

    // Getters
    int getUserId() const;
    double getBalance() const;
    double getTotalIncome() const;
    double getTotalExpense() const;
    double getTotalInvested() const;

    // State Mutators
    void credit(double amount);
    void debit(double amount);
    void invest(double amount);

    // Rollback operations for Undo
    void revertCredit(double amount);
    void revertDebit(double amount);
    void revertInvest(double amount);

    // Reset account state
    void reset();

    // Display formatted account status
    void displayAccountSummary() const;
};

#endif // ACCOUNT_H
