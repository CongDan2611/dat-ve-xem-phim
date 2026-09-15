#include "AccountManager.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

using namespace std;

namespace {
const char* activeText(bool active) {
    return active ? "Active" : "Locked";
}
}

AccountManager::AccountManager(const string& fileName)
    : Manager<Account>(fileName) {
    load();
}

string AccountManager::trim(const string& value) {
    const auto first = value.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    const auto last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

vector<string> AccountManager::split(const string& line) {
    vector<string> fields;
    stringstream stream(line);
    string field;
    while (getline(stream, field, '|')) fields.push_back(trim(field));
    return fields;
}

string AccountManager::normalizeRole(const string& role) {
    string normalized = trim(role);
    transform(normalized.begin(), normalized.end(), normalized.begin(),
              [](unsigned char character) { return static_cast<char>(tolower(character)); });
    if (normalized == "admin") return "Admin";
    if (normalized == "staff") return "Staff";
    return "Customer";
}

bool AccountManager::isBlank(const string& value) {
    return trim(value).empty();
}

void AccountManager::ensureDefaultAdmin() {
    if (!items.empty()) return;
    items.push_back({"U01", "admin", "admin123", "Admin", "Administrator", "0900000000", true});
    save();
}

bool AccountManager::load() {
    items.clear();
    ifstream input(fileName);
    if (!input) {
        ensureDefaultAdmin();
        return true;
    }

    string line;
    while (getline(input, line)) {
        if (isBlank(line) || line[0] == '#') continue;
        const auto fields = split(line);
        if (fields.size() < 6 || fields[0] == "ID") continue;

        Account account{fields[0], fields[1], fields[2], normalizeRole(fields[3]),
                        fields[4], fields[5], true};
        if (fields.size() >= 7) {
            string status = trim(fields[6]);
            transform(status.begin(), status.end(), status.begin(),
                      [](unsigned char character) { return static_cast<char>(tolower(character)); });
            account.active = status != "locked";
        }
        items.push_back(account);
    }
    ensureDefaultAdmin();
    return true;
}

bool AccountManager::save() const {
    ofstream output(fileName);
    if (!output) return false;
    output << "ID | TenDangNhap | MatKhau | VaiTro | HoTen | SoDienThoai | TrangThai\n";
    for (const Account& account : items) {
        output << account.id << " | " << account.username << " | " << account.password
               << " | " << account.role << " | " << account.fullName << " | "
               << account.phone << " | " << activeText(account.active) << '\n';
    }
    return true;
}

const vector<Account>& AccountManager::getAccounts() const { return items; }

const Account* AccountManager::authenticate(const string& username,
                                             const string& password) const {
    for (const Account& account : items) {
        if (account.username == username && account.password == password && account.active) {
            return &account;
        }
    }
    return nullptr;
}

bool AccountManager::registerAccount(const string& username,
                                     const string& password,
                                     const string& fullName,
                                     const string& phone,
                                     string& errorMessage) {
    if (isBlank(username) || isBlank(password) || isBlank(fullName) || isBlank(phone)) {
        errorMessage = "Khong duoc de trong thong tin.";
        return false;
    }
    for (const Account& account : items) {
        if (account.username == username) {
            errorMessage = "Ten dang nhap da ton tai.";
            return false;
        }
    }

    items.push_back({"U" + to_string(items.size() + 1), username, password,
                     "Customer", fullName, phone, true});
    if (!save()) {
        items.pop_back();
        errorMessage = "Khong the ghi file users.txt.";
        return false;
    }
    return true;
}

bool AccountManager::changePassword(const string& userId,
                                    const string& oldPassword,
                                    const string& newPassword,
                                    string& errorMessage) {
    for (Account& account : items) {
        if (account.id == userId) {
            if (account.password != oldPassword) {
                errorMessage = "Mat khau cu khong dung.";
                return false;
            }
            if (isBlank(newPassword)) {
                errorMessage = "Mat khau moi khong duoc de trong.";
                return false;
            }
            account.password = newPassword;
            return save();
        }
    }
    errorMessage = "Khong tim thay tai khoan.";
    return false;
}

bool AccountManager::updateProfile(const string& userId,
                                   const string& fullName,
                                   const string& phone,
                                   string& errorMessage) {
    if (isBlank(fullName) || isBlank(phone)) {
        errorMessage = "Ho ten va so dien thoai khong duoc de trong.";
        return false;
    }
    for (Account& account : items) {
        if (account.id == userId) {
            account.fullName = fullName;
            account.phone = phone;
            return save();
        }
    }
    errorMessage = "Khong tim thay tai khoan.";
    return false;
}

bool AccountManager::setAccountStatus(const string& userId, bool active) {
    for (Account& account : items) {
        if (account.id == userId) {
            account.active = active;
            return save();
        }
    }
    return false;
}

const Account* AccountManager::findById(const string& userId) const {
    for (const Account& account : items) {
        if (account.id == userId) return &account;
    }
    return nullptr;
}