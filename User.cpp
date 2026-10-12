#include "User.h"

User::User()
{
<<<<<<< HEAD
    userId = 0;
=======
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
    username = "";
    password = "";
}

<<<<<<< HEAD
User::User(int userId, string username, string password)
{
    this->userId = userId;
=======
User::User(string username, string password)
{
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
    this->username = username;
    this->password = password;
}

// Getters

<<<<<<< HEAD
int User::getUserId() const
{
    return userId;
}

=======
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
string User::getUsername() const
{
    return username;
}

string User::getPassword() const
{
    return password;
}

// Setters

<<<<<<< HEAD
void User::setUserId(int userId)
{
    this->userId = userId;
}

=======
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
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