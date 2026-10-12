#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

// Base exception for all LedgerNav domain errors
class LedgerException : public std::exception
{
protected:
    std::string message;

public:
    explicit LedgerException(const std::string &msg) : message(msg) {}
    virtual const char *what() const noexcept override
    {
        return message.c_str();
    }
};

// Thrown when an invalid date is provided (format or calendar logic)
class InvalidDateException : public LedgerException
{
public:
    explicit InvalidDateException(const std::string &msg)
        : LedgerException("Invalid Date Error: " + msg) {}
};

// Thrown when transaction amount is non-positive or invalid
class InvalidAmountException : public LedgerException
{
public:
    explicit InvalidAmountException(const std::string &msg)
        : LedgerException("Invalid Amount Error: " + msg) {}
};

// Thrown when an expense or withdrawal exceeds the account balance
class InsufficientFundsException : public LedgerException
{
public:
    explicit InsufficientFundsException(const std::string &msg)
        : LedgerException("Insufficient Funds Error: " + msg) {}
};

// Thrown during invalid history navigation (e.g. undo at genesis or redo at tip)
class HistoryNavigationException : public LedgerException
{
public:
    explicit HistoryNavigationException(const std::string &msg)
        : LedgerException("History Navigation Error: " + msg) {}
};

// Thrown when a transaction specification or type is invalid
class InvalidTransactionException : public LedgerException
{
public:
    explicit InvalidTransactionException(const std::string &msg)
        : LedgerException("Transaction Error: " + msg) {}
};

// Thrown on user authentication or registration errors
class UserAuthException : public LedgerException
{
public:
    explicit UserAuthException(const std::string &msg)
        : LedgerException("Authentication Error: " + msg) {}
};

#endif // EXCEPTIONS_H
