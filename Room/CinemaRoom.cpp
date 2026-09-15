#include "CinemaRoom.h"
#include <iostream>

CinemaRoom::CinemaRoom(string id, string name) : roomId(id), roomName(name) {
    // Khởi tạo mẫu 6 ghế cho phòng chiếu (4 ghế thường, 2 ghế VIP)
    seats.push_back(Seat("A1", false));
    seats.push_back(Seat("A2", false));
    seats.push_back(Seat("A3", false));
    seats.push_back(Seat("A4", false));
    seats.push_back(Seat("B1", true)); // Ghế VIP
    seats.push_back(Seat("B2", true)); // Ghế VIP
}

string CinemaRoom::getRoomId() const { return roomId; }
string CinemaRoom::getRoomName() const { return roomName; }
vector<Seat>& CinemaRoom::getSeats() { return seats; }

void CinemaRoom::displayRoomMap() const {
    cout << "\n========================================" << endl;
    cout << "       --- MAN HINH CHIEU PHIM ---      " << endl;
    cout << "========================================" << endl;
    for (int i = 0; i < seats.size(); i++) {
        cout << "[" << i + 1 << "] Ghe " << seats[i].getSeatId() 
             << (seats[i].getIsVIP() ? " [VIP]" : " [Thuong]")
             << (seats[i].getIsBooked() ? " --> (Da duoc dat)" : " --> [Trong]") << endl;
    }
    cout << "----------------------------------------" << endl;
}