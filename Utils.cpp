#include "Utils.h"
#include <iostream>
#include <ctime>

using namespace std;

// Stores the latest transaction ID
static int currentId = 1000;

// Set the starting transaction ID
void Utils::setCurrentId(int id)
{
    currentId = id;
}

// Generate a unique transaction ID
int Utils::generateTransactionId()
{
    return ++currentId;
}

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
}