#include "User.h"
#include <iostream>
#include <limits>

using namespace std;

User::User() : id(""), name(""), phone(""), email("") {}

User::User(const string& id, const string& name,
               const string& phone, const string& email)
    : id(id), name(name), phone(phone), email(email) {}

string User::getId() const { return id; }
string User::getName() const { return name; }
string User::getPhone() const { return phone; }
string User::getEmail() const { return email; }

void User::setName(const string& value) { name = value; }
void User::setPhone(const string& value) { phone = value; }
void User::setEmail(const string& value) { email = value; }

void User::input() {
    cout << "Nhap ID: ";
    getline(cin, id);
    cout << "Nhap ho ten: ";
    getline(cin, name);
    cout << "Nhap so dien thoai: ";
    getline(cin, phone);
    cout << "Nhap email: ";
    getline(cin, email);
}
