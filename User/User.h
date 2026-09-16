#pragma once

#include <string>

using namespace std;

class User {
protected:
    string id;
    string name;
    string phone;
    string email;

public:
    User();
        User(const string& id, const string& name,
            const string& phone, const string& email);
    virtual ~User() = default;

    string getId() const;
    string getName() const;
    string getPhone() const;
    string getEmail() const;

    void setName(const string& name);
    void setPhone(const string& phone);
    void setEmail(const string& email);

    virtual void input();
    virtual void displayInfo() const = 0;
    virtual string getType() const = 0;
};
