#include "Utils.h"
<<<<<<< HEAD
#include "Exceptions.h"
#include <iostream>
=======
#include <iostream>
#include <ctime>
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74

using namespace std;

// Stores the latest transaction ID
static int currentId = 1000;

<<<<<<< HEAD
void Utils::setCurrentId(int id)
{
    if (id > currentId)
    {
        currentId = id;
    }
}

=======
// Set the starting transaction ID
void Utils::setCurrentId(int id)
{
    currentId = id;
}

// Generate a unique transaction ID
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
int Utils::generateTransactionId()
{
    return ++currentId;
}

<<<<<<< HEAD
bool Utils::isValidDate(const string &date)
{
    try
    {
        validateDate(date);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

void Utils::validateDate(const string &date)
{
    if (date.length() != 10)
    {
        throw InvalidDateException("Date must be in DD-MM-YYYY format (10 characters). Received: " + date);
    }

    if (date[2] != '-' || date[5] != '-')
    {
        throw InvalidDateException("Date separators must be hyphens ('-'). Format: DD-MM-YYYY.");
    }

    int day = 0, month = 0, year = 0;
    try
    {
        day = stoi(date.substr(0, 2));
        month = stoi(date.substr(3, 2));
        year = stoi(date.substr(6, 4));
    }
    catch (...)
    {
        throw InvalidDateException("Date contains non-numeric parts: " + date);
    }

    if (year < 1900 || year > 2100)
    {
        throw InvalidDateException("Year out of reasonable range (1900-2100): " + to_string(year));
    }

    if (month < 1 || month > 12)
    {
        throw InvalidDateException("Month must be between 01 and 12. Received: " + to_string(month));
    }

    // Days per month check including leap year
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (isLeapYear)
    {
        daysInMonth[2] = 29;
    }

    if (day < 1 || day > daysInMonth[month])
    {
        throw InvalidDateException("Day " + to_string(day) + " is invalid for month " +
                                   to_string(month) + " in year " + to_string(year) + ".");
    }
}

void Utils::validateAmount(double amount)
{
    if (amount <= 0.0)
    {
        throw InvalidAmountException("Transaction amount must be strictly greater than 0. Received: " + to_string(amount));
    }
}

void Utils::validateString(const string &str, const string &fieldName)
{
    if (str.empty())
    {
        throw InvalidTransactionException(fieldName + " cannot be empty.");
    }
    if (str.find('|') != string::npos)
    {
        throw InvalidTransactionException(fieldName + " cannot contain the reserved pipe delimiter ('|').");
    }
}

void Utils::printHeader()
{
    cout << "=====================================================\n";
    cout << "         LedgerNav - Transaction Navigator           \n";
    cout << "    [Doubly Linked List | Undo/Redo | OOP Engine]    \n";
    cout << "=====================================================\n\n";
}

void Utils::printDivider()
{
    cout << "-----------------------------------------------------\n";
=======
// Basic date validation
bool Utils::isValidDate(const string &date)
{
    if (date.length() != 10)
        return false;

    if (date[2] != '-' || date[5] != '-')
        return false;

    return true;
}

// Print project header
void Utils::printHeader()
{
    cout << "=========================================\n";
    cout << "          LedgerNav v1.0\n";
    cout << "    Transaction History Navigator\n";
    cout << "=========================================\n\n";
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
}