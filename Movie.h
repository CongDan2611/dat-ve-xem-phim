#pragma once
#include <string>
#include <iostream>

class Movie {
private:
    std::string movieId;  // Mã phim (VD: M01)
    std::string title;    // Tên phim (VD: Avengers)
    int duration;         // Thời lượng tính bằng phút
    std::string genre;    // Thể loại (Hành động, Hài...)

public:
    // Hàm khởi tạo đầy đủ tham số để tạo ra một bộ phim hoàn chỉnh
    Movie(std::string id, std::string t, int d, std::string g);

    // Getters để lấy thông tin phim khi cần in ra vé
    std::string getTitle() const;
    int getDuration() const;
    
    // Hàm in thông tin chi tiết của phim
    void displayMovieInfo() const;
};