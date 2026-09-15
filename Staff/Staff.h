#pragma once

#include "../User/User.h"

using namespace std;

class Staff : public User {
private:
    string position;
    double salary;

public:
    Staff();
        Staff(const string& id, const string& name,
            const string& phone, const string& email,
            const string& position, double salary);

    string getPosition() const;
    double getSalary() const;

    void setPosition(const string& position);
    void setSalary(double salary);
    void increaseSalary(double amount);

    void input() override;
    void displayInfo() const override;
    string getType() const override;
};
