#pragma once
#include "DataManager.h"
#include "Showtime.h"
#include <fstream>
#include <iostream>

using namespace std;

class ShowtimeManager : public DataManager<Showtime> {
public:
    ShowtimeManager() : DataManager<Showtime>("showtimes.txt") {}

    void loadFromFile() override {
        ifstream file(fileName);
        if (!file.is_open()) return;

        string id, movieId, roomId, date, time;
        double price;
        
        // Đọc liên tục các khoảng trắng cho đến hết file
        while (file >> id >> movieId >> roomId >> date >> time >> price) {
            // Tạm thời truyền nullptr cho Movie và Room vì chúng ta sẽ liên kết chúng sau
            Showtime st(id, date, time, price, nullptr, nullptr);
            add(st);
        }
        file.close();
    }

    void saveToFile() override {
        ofstream file(fileName);
        if (!file.is_open()) return;

        for (const auto& st : dataList) {
            // Tương tự, bạn cần bổ sung Getters bên Showtime.h để lấy dữ liệu ghi vào file
        }
        file.close();
    }
};