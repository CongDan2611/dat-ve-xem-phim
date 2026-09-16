#include "Customer.h"
#include <iostream>
#include <limits>
using namespace std;

Customer::Customer() : User(), loyaltyPoints(0) {}

Customer::Customer(const string& id, const string& name,
                   const string& phone, const string& email,
                   int loyaltyPoints)
    : User(id, name, phone, email), loyaltyPoints(loyaltyPoints) {}

int Customer::getLoyaltyPoints() const { return loyaltyPoints; }
void Customer::setLoyaltyPoints(int points) { loyaltyPoints = points < 0 ? 0 : points; }
void Customer::addPoints(int points) {
    if (points > 0) loyaltyPoints += points;
}

void Customer::input() {
    User::input();
    cout << "Nhap diem tich luy: ";
    cin >> loyaltyPoints;
    if (loyaltyPoints < 0) loyaltyPoints = 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Customer::displayInfo() const {
    cout << "\n===== THONG TIN KHACH HANG =====\n";
    cout << "Loai: " << getType() << '\n';
    cout << "ID: " << id << '\n';
    cout << "Ho ten: " << name << '\n';
    cout << "So dien thoai: " << phone << '\n';
    cout << "Email: " << email << '\n';
    cout << "Diem tich luy: " << loyaltyPoints << '\n';
}

string Customer::getType() const { return "Customer"; }
