#include "Menu.h"

#include <iostream>
#include <limits>
#include <string>

using namespace std;

namespace {
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string trimInput(const string& value) {
    size_t start = 0;
    while (start < value.size() && (value[start] == ' ' || value[start] == '\t' || value[start] == '\r')) {
        ++start;
    }
    size_t end = value.size();
    while (end > start && (value[end - 1] == ' ' || value[end - 1] == '\t' || value[end - 1] == '\r' || value[end - 1] == '\n')) {
        --end;
    }
    return value.substr(start, end - start);
}

string readLine(const string& prompt) {
    cout << prompt;
    string value;
    getline(cin, value);
    return trimInput(value);
}

int readChoice(const string& prompt) {
    cout << prompt;
    int choice;
    if (!(cin >> choice)) {
        clearInput();
        return -1;
    }
    clearInput();
    return choice;
}

void printAccount(const Account& account) {
    cout << account.id << " | " << account.username << " | " << account.role
         << " | " << account.fullName << " | " << account.phone << " | "
         << (account.active ? "Dang hoat dong" : "Da khoa") << '\n';
}

void registerMenu(AccountManager& manager) {
    const string username = readLine("Ten dang nhap: ");
    const string password = readLine("Mat khau: ");
    const string fullName = readLine("Ho ten: ");
    const string phone = readLine("So dien thoai: ");
    string error;
    if (manager.registerAccount(username, password, fullName, phone, error)) {
        cout << "Dang ky thanh cong.\n";
    } else {
        cout << "Dang ky that bai: " << error << '\n';
    }
}

void changePasswordMenu(AccountManager& manager, const Account& account) {
    const string oldPassword = readLine("Mat khau cu: ");
    const string newPassword = readLine("Mat khau moi: ");

    if (oldPassword.empty() || newPassword.empty()) {
        cout << "Mat khau khong duoc de trong.\n";
        return;
    }

    if (oldPassword != account.password) {
        cout << "Mat khau khong chinh xac.\n";
        return;
    }

    if (newPassword == account.password) {
        cout << "Mat khau da duoc thay doi.\n";
        return;
    }

    string error;
    if (manager.changePassword(account.id, oldPassword, newPassword, error)) {
        cout << "Doi mat khau thanh cong.\n";
    } else {
        cout << error << '\n';
    }
}

void profileMenu(AccountManager& manager, const Account& account) {
    cout << "\n===== THONG TIN CA NHAN =====\n";
    cout << "ID: " << account.id << "\n";
    cout << "Ten dang nhap: " << account.username << "\n";
    cout << "Ho ten: " << account.fullName << "\n";
    cout << "So dien thoai: " << account.phone << "\n";
    cout << "Vai tro: " << account.role << "\n";

    cout << "\nBan co muon chinh sua thong tin? (1: Co, 0: Khong): ";
    int choice = readChoice("");
    if (choice != 1) {
        cout << "Da xem thong tin ca nhan.\n";
        return;
    }

    string fullName = readLine("Ho ten moi: ");
    if (fullName.empty()) fullName = account.fullName;

    string phone = readLine("So dien thoai moi: ");
    if (phone.empty()) phone = account.phone;

    string error;
    if (manager.updateProfile(account.id, fullName, phone, error)) {
        cout << "Cap nhat thong tin thanh cong.\n";
    } else {
        cout << "Cap nhat that bai: " << error << '\n';
    }
}

void customerMenu(AccountManager& manager, const Account& account) {
    while (true) {
        cout << "\n===== MENU KHACH HANG =====\n"
             << "1. Quan ly thong tin ca nhan\n"
             << "2. Doi mat khau\n"
             << "4. Quan ly ve da dat\n"
             << "0. Dang xuat\n";
        switch (readChoice("Chon: ")) {
        case 1: profileMenu(manager, account); break;
        case 2: changePasswordMenu(manager, account); break;
        case 4: cout << "Chuc nang lich su va huy ve chua duoc ket noi.\n"; break;
        case 0: return;
        default: cout << "Lua chon khong hop le.\n";
        }
    }
}

void managementMenu(AccountManager& manager) {
    while (true) {
        cout << "\n===== MENU QUAN LY =====\n"
             << "1. Danh sach tat ca tai khoan\n"
             << "2. Danh sach Staff\n"
             << "3. Danh sach Customer\n"
             << "4. Khoa/Cấp lai tai khoan\n"
             << "0. Quay lai\n";
        const int choice = readChoice("Chon: ");
        if (choice == 0) return;
        if (choice >= 1 && choice <= 3) {
            for (const Account& account : manager.getAccounts()) {
                if (choice == 1 || (choice == 2 && account.role == "Staff") ||
                    (choice == 3 && account.role == "Customer")) {
                    printAccount(account);
                }
            }
        } else if (choice == 4) {
            const string id = readLine("ID tai khoan: ");
            const Account* account = manager.findById(id);
            if (!account || account->role == "Admin") {
                cout << "Khong tim thay tai khoan phu hop.\n";
                continue;
            }
            const bool active = readChoice("Nhap 1 de cap lai, 0 de khoa: ") == 1;
            cout << (manager.setAccountStatus(id, active) ? "Da cap nhat tai khoan.\n"
                                                         : "Cap nhat that bai.\n");
        } else {
            cout << "Lua chon khong hop le.\n";
        }
    }
}

void loginMenu(AccountManager& manager) {
    const string username = readLine("Ten dang nhap: ");
    const string password = readLine("Mat khau: ");

    const Account* account = nullptr;
    for (const Account& item : manager.getAccounts()) {
        if (item.username == username) {
            account = &item;
            break;
        }
    }

    if (!account) {
        cout << "Tai khoan hoac mat khau khong chinh xac.\n";
        return;
    }

    if (!account->active) {
        cout << "Tai khoan bi khoa.\n";
        return;
    }

    if (password == account->password) {
        cout << "Dang nhap thanh cong. Xin chao " << account->fullName << "!\n";
        if (account->role == "Admin") managementMenu(manager);
        else customerMenu(manager, *account);
        return;
    }

    if (account->password.rfind(password, 0) == 0 && password.size() < account->password.size()) {
        cout << "Mat khau thieu ky tu.\n";
        return;
    }

    cout << "Mat khau khong chinh xac.\n";
}
}

void runMainMenu(AccountManager& manager) {
    while (true) {
        cout << "\n===== MENU CHINH =====\n"
             << "1. Dang nhap\n"
             << "2. Dang ky\n"
             << "0. Thoat\n";
        switch (readChoice("Chon: ")) {
        case 1: loginMenu(manager); break;
        case 2: registerMenu(manager); break;
        case 0: return;
        default: cout << "Lua chon khong hop le.\n";
        }
    }
}