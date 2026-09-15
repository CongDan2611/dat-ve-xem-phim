#include "Menu.h"

// Constructor: Tự động tải dữ liệu từ file txt lên khi mở app
Menu::Menu() {
    movieMgr.loadFromFile();
    showtimeMgr.loadFromFile();
}

// Vòng lặp chính của chương trình
void Menu::run() {
    int choice;
    do {
        cout << "\n============= HE THONG DAT VE XEM PHIM =============" << endl;
        cout << "1. Menu Khach Hang (Xem phim, tra cuu)" << endl;
        cout << "2. Menu Quan Ly (Them/Sua/Xoa du lieu)" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "====================================================" << endl;
        cout << "Moi ban chon: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                showCustomerMenu(); 
                break;
            case 2: 
                showAdminMenu(); 
                break;
            case 0: 
                cout << "Dang luu du lieu vao file txt..." << endl;
                movieMgr.saveToFile();
                showtimeMgr.saveToFile();
                cout << "Da luu thanh cong. Tam biet!" << endl;
                break;
            default: 
                cout << "Lua chon khong hop le, vui long nhap lai!" << endl;
        }
    } while (choice != 0);
}

void Menu::showCustomerMenu() {
    int choice;
    do {
        cout << "\n--- MENU KHACH HANG ---" << endl;
        cout << "1. Xem danh sach phim dang chieu" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "Moi chon: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n--- DANH SACH PHIM ---" << endl;
            // Gọi getAll() từ DataManager để lấy danh sách và in ra
            for (const auto& m : movieMgr.getAll()) {
                m.displayMovieInfo();
            }
        }
    } while (choice != 0);
}

void Menu::showAdminMenu() {
    int choice;
    do {
        cout << "\n--- MENU QUAN LY ---" << endl;
        cout << "1. Quan ly Phim (Movie)" << endl;
        cout << "2. Quan ly Suat chieu (Showtime)" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "Moi chon: ";
        cin >> choice;

        if (choice == 1) {
            cout << ">> Tinh nang Quan ly Phim dang duoc xay dung..." << endl;
        } else if (choice == 2) {
            cout << ">> Tinh nang Quan ly Suat chieu dang duoc xay dung..." << endl;
        }
    } while (choice != 0);
}