#pragma once

#include "../User/User.h"

using namespace std;

class Customer : public User {
private:
    int loyaltyPoints;

public:
    Customer();
    Customer(const string& id, const string& name,
             const string& phone, const string& email,
             int loyaltyPoints = 0);

    int getLoyaltyPoints() const;
    void setLoyaltyPoints(int points);
    void addPoints(int points);

    void input() override;
    void displayInfo() const override;
    string getType() const override;
};
