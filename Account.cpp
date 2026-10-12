#include "Account.h"
#include "Exceptions.h"
#include <iomanip>

using namespace std;

Account::Account(int userId, double initialBalance)
    : userId(userId),
      balance(initialBalance),
      totalIncome(0.0),
      totalExpense(0.0),
      totalInvested(0.0)
{
}

int Account::getUserId() const
{
    return userId;
}

double Account::getBalance() const
{
    return balance;
}

double Account::getTotalIncome() const
{
    return totalIncome;
}

double Account::getTotalExpense() const
{
    return totalExpense;
}

double Account::getTotalInvested() const
{
    return totalInvested;
}

void Account::credit(double amount)
{
    if (amount <= 0.0)
    {
        throw InvalidAmountException("Credit amount must be strictly positive.");
    }
    balance += amount;
    totalIncome += amount;
}

void Account::debit(double amount)
{
    if (amount <= 0.0)
    {
        throw InvalidAmountException("Debit amount must be strictly positive.");
    }
    balance -= amount;
    totalExpense += amount;
}

void Account::invest(double amount)
{
    if (amount <= 0.0)
    {
        throw InvalidAmountException("Investment amount must be strictly positive.");
    }
    balance -= amount;
    totalInvested += amount;
}

void Account::revertCredit(double amount)
{
    if (amount <= 0.0)
    {
        throw InvalidAmountException("Revert credit amount must be positive.");
    }
    balance -= amount;
    totalIncome -= amount;
}

void Account::revertDebit(double amount)
{
    if (amount <= 0.0)
    {
        throw InvalidAmountException("Revert debit amount must be positive.");
    }
    balance += amount;
    totalExpense -= amount;
}

void Account::revertInvest(double amount)
{
    if (amount <= 0.0)
    {
        throw InvalidAmountException("Revert investment amount must be positive.");
    }
    balance += amount;
    totalInvested -= amount;
}

void Account::reset()
{
    balance = 0.0;
    totalIncome = 0.0;
    totalExpense = 0.0;
    totalInvested = 0.0;
}

void Account::displayAccountSummary() const
{
    cout << "\n+-----------------------------------------------+\n";
    cout << "|              ACCOUNT STATE SUMMARY            |\n";
    cout << "+-----------------------------------------------+\n";
    cout << "  User ID           : " << userId << "\n";
    cout << "  Total Income      : Rs. " << fixed << setprecision(2) << totalIncome << "\n";
    cout << "  Total Expense     : Rs. " << totalExpense << "\n";
    cout << "  Total Invested    : Rs. " << totalInvested << "\n";
    cout << "  Net Liquid Cash   : Rs. " << balance << "\n";
    cout << "+-----------------------------------------------+\n";
}
