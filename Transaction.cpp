#include "Transaction.h"
#include "Exceptions.h"
#include <iomanip>
#include <sstream>

// Base Transaction Constructors
Transaction::Transaction()
    : id(0), userId(0), date(""), amount(0.0), category(""), description("")
{
}

Transaction::Transaction(int id, int userId, const string &date, double amount,
                         const string &category, const string &description)
    : id(id), userId(userId), date(date), amount(amount),
      category(category), description(description)
{
}

// Getters
int Transaction::getId() const
{
    return id;
}

int Transaction::getUserId() const
{
    return userId;
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

string Transaction::getDescription() const
{
    return description;
}

// Setters
void Transaction::setId(int id)
{
    this->id = id;
}

void Transaction::setUserId(int userId)
{
    this->userId = userId;
}

void Transaction::setDate(const string &date)
{
    this->date = date;
}

void Transaction::setAmount(double amount)
{
    if (amount <= 0.0)
    {
        throw InvalidAmountException("Transaction amount must be strictly positive.");
    }
    this->amount = amount;
}

void Transaction::setCategory(const string &category)
{
    if (category.empty())
    {
        throw InvalidTransactionException("Category cannot be empty.");
    }
    this->category = category;
}

void Transaction::setDescription(const string &description)
{
    this->description = description;
}

// Display
void Transaction::display() const
{
    cout << "----------------------------------\n";
    cout << "Transaction ID : " << id << "\n";
    cout << "User ID        : " << userId << "\n";
    cout << "Date           : " << date << "\n";
    cout << "Amount         : Rs. " << fixed << setprecision(2) << amount << "\n";
    cout << "Category       : " << category << "\n";
    cout << "Type           : " << getType() << "\n";
    cout << "Description    : " << description << "\n";
    cout << "----------------------------------\n";
}

// Serialization format: id|userId|date|amount|category|type|description
string Transaction::serialize() const
{
    stringstream ss;
    ss << id << "|"
       << userId << "|"
       << date << "|"
       << fixed << setprecision(2) << amount << "|"
       << category << "|"
       << getType() << "|"
       << description;
    return ss.str();
}

// ========================================================
// IncomeTransaction Implementation
// ========================================================
IncomeTransaction::IncomeTransaction(int id, int userId, const string &date,
                                     double amount, const string &category,
                                     const string &description)
    : Transaction(id, userId, date, amount, category, description)
{
}

string IncomeTransaction::getType() const
{
    return "Income";
}

void IncomeTransaction::applyToAccount(Account &account) const
{
    account.credit(amount);
}

void IncomeTransaction::rollbackFromAccount(Account &account) const
{
    account.revertCredit(amount);
}

Transaction *IncomeTransaction::clone() const
{
    return new IncomeTransaction(*this);
}

// ========================================================
// ExpenseTransaction Implementation
// ========================================================
ExpenseTransaction::ExpenseTransaction(int id, int userId, const string &date,
                                       double amount, const string &category,
                                       const string &description)
    : Transaction(id, userId, date, amount, category, description)
{
}

string ExpenseTransaction::getType() const
{
    return "Expense";
}

void ExpenseTransaction::applyToAccount(Account &account) const
{
    account.debit(amount);
}

void ExpenseTransaction::rollbackFromAccount(Account &account) const
{
    account.revertDebit(amount);
}

Transaction *ExpenseTransaction::clone() const
{
    return new ExpenseTransaction(*this);
}

// ========================================================
// InvestmentTransaction Implementation
// ========================================================
InvestmentTransaction::InvestmentTransaction(int id, int userId, const string &date,
                                             double amount, const string &category,
                                             const string &description)
    : Transaction(id, userId, date, amount, category, description)
{
}

string InvestmentTransaction::getType() const
{
    return "Investment";
}

void InvestmentTransaction::applyToAccount(Account &account) const
{
    account.invest(amount);
}

void InvestmentTransaction::rollbackFromAccount(Account &account) const
{
    account.revertInvest(amount);
}

Transaction *InvestmentTransaction::clone() const
{
    return new InvestmentTransaction(*this);
}

// ========================================================
// TransactionFactory Implementation
// ========================================================
Transaction *TransactionFactory::createTransaction(int id, int userId,
                                                   const string &date,
                                                   double amount,
                                                   const string &category,
                                                   const string &type,
                                                   const string &description)
{
    if (amount <= 0.0)
    {
        throw InvalidAmountException("Transaction amount must be strictly greater than zero.");
    }

    if (type == "Income" || type == "income" || type == "1")
    {
        return new IncomeTransaction(id, userId, date, amount, category, description);
    }
    else if (type == "Expense" || type == "expense" || type == "2")
    {
        return new ExpenseTransaction(id, userId, date, amount, category, description);
    }
    else if (type == "Investment" || type == "investment" || type == "3")
    {
        return new InvestmentTransaction(id, userId, date, amount, category, description);
    }
    else
    {
        throw InvalidTransactionException("Unknown transaction type: " + type + ". Must be Income, Expense, or Investment.");
    }
}