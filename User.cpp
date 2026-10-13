#include "User.h"

User::User()
{
    userId = 0;
    username = "";
    password = "";
}

User::User(int userId, string username, string password)
{
    this->userId = userId;
    this->username = username;
    this->password = password;
}

// Getters

int User::getUserId() const
{
    return userId;
}

string User::getUsername() const
{
    return username;
}

string User::getPassword() const
{
    return password;
}

// Setters

void User::setUserId(int userId)
{
    this->userId = userId;
}

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