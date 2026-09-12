#pragma once
#include <string>
#include "Movie.h"
#include "CinemaRoom.h"

class Showtime {
private:
    std::string showtimeId;  // Mã lịch chiếu (VD: ST01)
    std::string startTime;   // Giờ chiếu (VD: "18:00 20/10/2023")
    
    // MỐI QUAN HỆ KẾT HỢP (Aggregation): 
    // Lịch chiếu trỏ tới Phim và Phòng chứ không trực tiếp tạo ra chúng.
    // Dùng con trỏ (*) vì Phim và Phòng được quản lý ở nơi khác, lịch chiếu chỉ lấy ra dùng.
    Movie* movie; 
    CinemaRoom* room; 

public:
    // Constructor nhận vào con trỏ của Movie và CinemaRoom
    Showtime(std::string id, std::string time, Movie* m, CinemaRoom* r);

    // In thông tin tổng hợp của 1 lịch chiếu
    void displayShowtimeInfo() const;
};