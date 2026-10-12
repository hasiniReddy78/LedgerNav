#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class User
{
private:
<<<<<<< HEAD
    int userId;
=======
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
    string username;
    string password;

public:
    // Constructors
    User();
<<<<<<< HEAD
    User(int userId, string username, string password);

    // Getters
    int getUserId() const;
=======
    User(string username, string password);

    // Getters
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
    string getUsername() const;
    string getPassword() const;

    // Setters
<<<<<<< HEAD
    void setUserId(int userId);
=======
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
    void setUsername(string username);
    void setPassword(string password);

    // Display user
    void display() const;

    // Check password
    bool authenticate(string enteredPassword) const;
};

#endif