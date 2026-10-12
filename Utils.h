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

    // Basic date validation predicate
    static bool isValidDate(const string &date);

    // Strict date validation throwing InvalidDateException
    static void validateDate(const string &date);

    // Strict amount validation throwing InvalidAmountException
    static void validateAmount(double amount);

    // String validation (non-empty, no pipe delimiter)
    static void validateString(const string &str, const string &fieldName);

    // Print application title & navigation banners
    static void printHeader();
    static void printDivider();
};

#endif // UTILS_H