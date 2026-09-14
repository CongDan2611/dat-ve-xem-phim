#include "Person.h"
#include <iostream>
#include <limits>

using namespace std;

Person::Person() : id(""), name(""), phone(""), email("") {}

Person::Person(const string& id, const string& name,
               const string& phone, const string& email)
    : id(id), name(name), phone(phone), email(email) {}

string Person::getId() const { return id; }
string Person::getName() const { return name; }
string Person::getPhone() const { return phone; }
string Person::getEmail() const { return email; }

void Person::setName(const string& value) { name = value; }
void Person::setPhone(const string& value) { phone = value; }
void Person::setEmail(const string& value) { email = value; }

void Person::input() {
    cout << "Nhap ID: ";
    getline(cin, id);
    cout << "Nhap ho ten: ";
    getline(cin, name);
    cout << "Nhap so dien thoai: ";
    getline(cin, phone);
    cout << "Nhap email: ";
    getline(cin, email);
}
