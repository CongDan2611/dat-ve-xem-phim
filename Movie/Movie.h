#pragma once
#include <string>
#include <iostream>

using namespace std;

class Movie {
private:
    string movieId;
    string title;
    int duration;
    string genre;
    int ageLimit;
    string status; // Them thuoc tinh Trang thai: Dang chieu / Sap chieu

public:
    // Cập nhật Constructor có thêm biến status (mặc định là "Dang chieu")
    Movie(string id, string t, int d, string g, int age, string st = "Dang chieu") 
        : movieId(id), title(t), duration(d), genre(g), ageLimit(age), status(st) {}

    // --- GETTERS ---
    string getMovieId() const { return movieId; }
    string getTitle() const { return title; }
    int getDuration() const { return duration; }
    string getGenre() const { return genre; }
    int getAgeLimit() const { return ageLimit; }
    string getStatus() const { return status; }

    // --- SETTERS ---
    void setStatus(string st) { status = st; }
    void setTitle(string t) { title = t; }
    void setGenre(string g) { genre = g; }
    void setDuration(int d) { duration = d; }
    void setAgeLimit(int a) { ageLimit = a; }

    // Hàm in thông tin chi tiết của phim
    void displayMovieInfo() const;
};