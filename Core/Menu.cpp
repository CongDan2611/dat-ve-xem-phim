#include "Menu.h"
#include "../Room/CinemaRoom.h"
#include <fstream>

Menu::Menu() {
    movieMgr.loadFromFile();
    showtimeMgr.loadFromFile();
}

void Menu::run() {
    int choice;
    do {
        cout << "\n============= HE THONG DAT VE XEM PHIM =============" << endl;
        cout << "1. Menu Khach Hang (Tim kiem & Dat ve)" << endl;
        cout << "2. Menu Quan Ly (Admin)" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "====================================================" << endl;
        cout << "Moi ban chon: ";
        cin >> choice;

        switch (choice) {
            case 1: showCustomerMenu(); break;
            case 2: showAdminMenu(); break;
            case 0: 
                cout << "Dang luu du lieu vao file txt..." << endl;
                movieMgr.saveToFile();
                showtimeMgr.saveToFile();
                cout << "Da luu thanh cong. Tam biet!" << endl;
                break;
            default: cout << "Lua chon khong hop le, vui long nhap lai!" << endl;
        }
    } while (choice != 0);
}

void Menu::showCustomerMenu() {
    int choice;
    do {
        cout << "\n--- MENU KHACH HANG ---" << endl;
        cout << "1. Dat ve ngay (Cac phim dang chieu)" << endl;
        cout << "2. Tim phim theo ten" << endl;
        cout << "3. Tim phim theo the loai" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "Moi chon: ";
        cin >> choice;

        if (choice == 1) {
            vector<Movie> list = movieMgr.getMoviesByStatus("Dang chieu");
            displayAndSelectMovie(list);
        } else if (choice == 2) {
            string keyword;
            cout << "Nhap ten phim can tim: ";
            cin.ignore();
            getline(cin, keyword);
            vector<Movie> list = movieMgr.searchMoviesByTitle(keyword);
            displayAndSelectMovie(list);
        } else if (choice == 3) {
            string keyword;
            cout << "Nhap the loai can tim (VD: Hanh dong): ";
            cin.ignore();
            getline(cin, keyword);
            vector<Movie> list = movieMgr.searchMoviesByGenre(keyword);
            displayAndSelectMovie(list);
        }
    } while (choice != 0);
}

void Menu::displayAndSelectMovie(vector<Movie>& movies) {
    if (movies.empty()) {
        cout << ">> Khong co bo phim nao phu hop!" << endl;
        return;
    }

    cout << "\n--- KET QUA TIM KIEM ---" << endl;
    for (int i = 0; i < movies.size(); i++) {
        cout << "[" << i + 1 << "] " << movies[i].getTitle() 
             << " | The loai: " << movies[i].getGenre() 
             << " | " << movies[i].getDuration() << " phut" << endl;
    }
    cout << "[0] Huy bo va quay lai" << endl;
    
    int select;
    cout << ">> Chon phim ban muon xem (Nhap so): ";
    cin >> select;

    if (select > 0 && select <= movies.size()) {
        bookingFlow(movies[select - 1]);
    }
}

void Menu::bookingFlow(Movie selectedMovie) {
    cout << "\n=======================================================" << endl;
    cout << ">> DANG DAT VE CHO PHIM: " << selectedMovie.getTitle() << " <<" << endl;
    
    vector<Showtime> listST = showtimeMgr.getShowtimesByMovieId(selectedMovie.getMovieId());
    
    if (listST.empty()) {
        cout << ">> Xin loi, phim nay hien chua co lich chieu nao!" << endl;
        return;
    }

    cout << "\n--- DANH SACH SUAT CHIEU ---" << endl;
    for (int i = 0; i < listST.size(); i++) {
        cout << "[" << i + 1 << "] ";
        listST[i].displayShowtime();
    }
    cout << "[0] Huy bo va quay lai" << endl;
    
    int selectST;
    cout << ">> Chon suat chieu (Nhap so): ";
    cin >> selectST;

    if (selectST > 0 && selectST <= listST.size()) {
        Showtime selectedST = listST[selectST - 1];
        CinemaRoom room(selectedST.getRoomId(), "Phong Chieu VIP");
        
        cout << "\n>> Ban da chon Suat: " << selectedST.getStartTime() << " (Phong: " << selectedST.getRoomId() << ")" << endl;
        room.displayRoomMap();
        
        int selectSeat;
        cout << ">> Chon so thu tu ghe ban muon ngoi: ";
        cin >> selectSeat;

        vector<Seat>& seats = room.getSeats();
        if (selectSeat > 0 && selectSeat <= seats.size()) {
            Seat& chosenSeat = seats[selectSeat - 1];
            
            if (chosenSeat.getIsBooked()) {
                cout << ">> Ghe nay da co nguoi dat! Vui long chon ghe khac." << endl;
                return;
            }

            chosenSeat.setBooked(true);
            
            Ticket* myTicket = nullptr;
            string ticketId = "TICKET_" + selectedST.getShowtimeId() + "_" + chosenSeat.getSeatId();
            string ticketType = "Thuong";
            double finalPrice = selectedST.getBasePrice();

            if (chosenSeat.getIsVIP()) {
                myTicket = new VIPTicket(ticketId, selectedST.getBasePrice());
                ticketType = "VIP";
                finalPrice = selectedST.getBasePrice() * 1.5;
            } else {
                myTicket = new StandardTicket(ticketId, selectedST.getBasePrice());
            }

            ofstream outFile("data/tickets.txt", ios::app);
            if (outFile.is_open()) {
                outFile << ticketId << "|" 
                        << selectedMovie.getTitle() << "|" 
                        << selectedST.getShowDate() << "|" 
                        << selectedST.getStartTime() << "|" 
                        << chosenSeat.getSeatId() << "|" 
                        << ticketType << "|" 
                        << finalPrice << "\n";
                outFile.close();
            }

            cout << "\n========================================" << endl;
            cout << "       DAT VE THANH CONG!               " << endl;
            cout << "========================================" << endl;
            cout << "Phim: " << selectedMovie.getTitle() << endl;
            cout << "Suat chieu: " << selectedST.getStartTime() << " | Ngay: " << selectedST.getShowDate() << endl;
            cout << "Vi tri ghe: " << chosenSeat.getSeatId() << endl;
            
            myTicket->displayTicket();
            cout << "========================================\n" << endl;

            delete myTicket;

        } else {
            cout << ">> Lua chon ghe khong hop le!" << endl;
        }
    }
}

void Menu::showAdminMenu() {
    int choice;
    do {
        cout << "\n--- MENU QUAN LY ---" << endl;
        cout << "1. Quan ly Phim (Them/Sua/Xoa)" << endl;
        cout << "2. Quan ly Suat chieu (Them suat chieu)" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "Moi chon: ";
        cin >> choice;

        if (choice == 1) {
            int action;
            cout << "\n--- QUAN LY PHIM ---" << endl;
            cout << "1. Them phim moi" << endl;
            cout << "2. Cap nhat trang thai phim" << endl;
            cout << "3. Xoa phim" << endl;
            cout << "0. Quay lai" << endl;
            cout << "Moi chon: ";
            cin >> action;
            
            if (action == 1) {
                string id, title, genre;
                int duration, ageLimit;
                
                cout << "Nhap Ma phim (VD: M02): "; cin >> id;
                cin.ignore(); 
                cout << "Nhap Ten phim: "; getline(cin, title); 
                cout << "Nhap The loai: "; getline(cin, genre);
                cout << "Nhap Thoi luong (phut): "; cin >> duration;
                cout << "Nhap Do tuoi quy dinh: "; cin >> ageLimit;

                Movie newMovie(id, title, duration, genre, ageLimit, "Dang chieu");
                movieMgr.add(newMovie);
                cout << ">> Them phim thanh cong!" << endl;
            } 
            else if (action == 2) {
                cout << "\n--- DANH SACH PHIM HIEN TAI ---" << endl;
                vector<Movie> allMovies = movieMgr.getAll();
                if (allMovies.empty()) {
                    cout << ">> Hien chua co phim nao trong he thong!" << endl;
                } else {
                    for (const auto& m : allMovies) {
                        cout << "[Ma: " << m.getMovieId() << "] " << m.getTitle() 
                             << " | Trang thai: " << m.getStatus() << endl;
                    }
                    string id, newStatus;
                    cout << "\nNhap Ma phim can cap nhat (VD: M01): "; cin >> id;
                    cin.ignore();
                    cout << "Nhap Trang thai moi (Dang chieu / Sap chieu): "; getline(cin, newStatus);
                    movieMgr.updateMovieStatus(id, newStatus);
                }
            } 
            else if (action == 3) {
                cout << "\n--- DANH SACH PHIM HIEN TAI ---" << endl;
                vector<Movie> allMovies = movieMgr.getAll();
                if (allMovies.empty()) {
                    cout << ">> Hien chua co phim nao trong he thong!" << endl;
                } else {
                    for (const auto& m : allMovies) {
                        cout << "[Ma: " << m.getMovieId() << "] " << m.getTitle() << endl;
                    }
                    string id;
                    cout << "\nNhap Ma phim can xoa: "; cin >> id;
                    movieMgr.deleteMovie(id);
                }
            }
        } 
        else if (choice == 2) {
            string id, movieId, roomId, date, time;
            double price;
            
            cout << "\n--- THEM SUAT CHIEU MOI ---" << endl;
            cout << "Nhap Ma suat chieu (VD: ST02): "; cin >> id;
            cout << "Nhap Ma phim (VD: M01): "; cin >> movieId;
            cout << "Nhap Ma phong (VD: ROOM01): "; cin >> roomId;
            cout << "Nhap Ngay chieu (YYYY-MM-DD): "; cin >> date;
            cout << "Nhap Gio chieu (HH:MM): "; cin >> time;
            cout << "Nhap Gia ve co ban: "; cin >> price;

            Showtime newShowtime(id, movieId, roomId, date, time, price);
            showtimeMgr.add(newShowtime);
            cout << ">> Them suat chieu thanh cong!" << endl;
        }
    } while (choice != 0);
}