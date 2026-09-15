#pragma once

#include "../Manager.h"

#include <string>
#include <vector>

using namespace std;

struct Account {
    string id;
    string username;
    string password;
    string role;
    string fullName;
    string phone;
    bool active;
};

class AccountManager : public Manager<Account> {
private:
    static string trim(const string& value);
    static vector<string> split(const string& line);
    static string normalizeRole(const string& role);
    static bool isBlank(const string& value);
    void ensureDefaultAdmin();

public:
    explicit AccountManager(const string& fileName = "users.txt");

    bool load() override;
    bool save() const override;
    const Account* findById(const string& id) const override;
    const vector<Account>& getAccounts() const;

    const Account* authenticate(const string& username,
                                const string& password) const;
    bool registerAccount(const string& username,
                         const string& password,
                         const string& fullName,
                         const string& phone,
                         string& errorMessage);
    bool changePassword(const string& userId,
                        const string& oldPassword,
                        const string& newPassword,
                        string& errorMessage);
    bool updateProfile(const string& userId,
                       const string& fullName,
                       const string& phone,
                       string& errorMessage);
    bool setAccountStatus(const string& userId, bool active);
};