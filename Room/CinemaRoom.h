#pragma once
#include <string>
#include <vector>
#include "Seat.h"

using namespace std;

class CinemaRoom {
private:
    string roomId;
    string roomName;
    vector<Seat> seats;

public:
    CinemaRoom(string id = "ROOM01", string name = "Phong chieu 1");

    string getRoomId() const;
    string getRoomName() const;
    vector<Seat>& getSeats();

    void displayRoomMap() const;
};