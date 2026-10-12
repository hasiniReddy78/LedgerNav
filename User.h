#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class User
{
private:
    int userId;
    string username;
    string password;

public:
    // Constructors
    User();
    User(int userId, string username, string password);

    // Getters
    int getUserId() const;
    string getUsername() const;
    string getPassword() const;

    // Setters
    void setUserId(int userId);
    void setUsername(string username);
    void setPassword(string password);

    // Display user
    void display() const;

    // Check password
    bool authenticate(string enteredPassword) const;
};

#endif