#include "User.h"

User::User()
{
    username = "";
    password = "";
}

User::User(string username, string password)
{
    this->username = username;
    this->password = password;
}

// Getters

string User::getUsername() const
{
    return username;
}

string User::getPassword() const
{
    return password;
}

// Setters

void User::setUsername(string username)
{
    this->username = username;
}

void User::setPassword(string password)
{
    this->password = password;
}

// Display

void User::display() const
{
    cout << "Username : " << username << endl;
}

// Authentication

bool User::authenticate(string enteredPassword) const
{
    return password == enteredPassword;
}