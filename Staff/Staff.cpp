#include "Staff.h"
#include <iostream>
#include <limits>

using namespace std;

Staff::Staff() : Person(), position(""), salary(0) {}

Staff::Staff(const string& id, const string& name,
             const string& phone, const string& email,
             const string& position, double salary)
    : Person(id, name, phone, email),
      position(position), salary(salary < 0 ? 0 : salary) {}

string Staff::getPosition() const { return position; }
double Staff::getSalary() const { return salary; }

void Staff::setPosition(const string& value) { position = value; }
void Staff::setSalary(double value) { salary = value < 0 ? 0 : value; }

void Staff::increaseSalary(double amount) {
    if (amount > 0) salary += amount;
}

void Staff::input() {
    Person::input();
    cout << "Nhap chuc vu: ";
    getline(cin, position);
    cout << "Nhap luong: ";
    cin >> salary;
    if (salary < 0) salary = 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Staff::displayInfo() const {
    cout << "\n===== THONG TIN NHAN VIEN =====\n";
    cout << "Loai: " << getType() << '\n';
    cout << "ID: " << id << '\n';
    cout << "Ho ten: " << name << '\n';
    cout << "So dien thoai: " << phone << '\n';
    cout << "Email: " << email << '\n';
    cout << "Chuc vu: " << position << '\n';
    cout << "Luong: " << salary << '\n';
}

string Staff::getType() const { return "Staff"; }
