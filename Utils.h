#ifndef UTILS_H
#define UTILS_H

#include <string>

using namespace std;

class Utils
{
public:
    // Set the current transaction ID
    static void setCurrentId(int id);

    // Generate unique transaction ID
    static int generateTransactionId();

    // Validate date format (DD-MM-YYYY)
    static bool isValidDate(const string &date);

    // Print application title
    static void printHeader();
};

#endif