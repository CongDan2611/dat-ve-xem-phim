#include "Showtime.h"
#include <iostream>

// Khởi tạo các thuộc tính và gán con trỏ
Showtime::Showtime(std::string id, std::string time, Movie* m, CinemaRoom* r)
    : showtimeId(id), startTime(time), movie(m), room(r) {}

// Hàm in thông tin chi tiết
void Showtime::displayShowtimeInfo() const {
    std::cout << "== LICH CHIEU: " << showtimeId << " ==" << std::endl;
    std::cout << "Thoi gian: " << startTime << std::endl;
    
    // Rất quan trọng: Luôn kiểm tra con trỏ có null (rỗng) hay không trước khi gọi hàm
    // Nếu không kiểm tra, chương trình sẽ bị crash (lỗi văng ứng dụng) nếu con trỏ rỗng
    if (movie != nullptr) {
        movie->displayMovieInfo(); // Dùng toán tử '->' để gọi hàm từ con trỏ
    }
    if (room != nullptr) {
        std::cout << "Phong chieu: " << room->getRoomId() << std::endl;
    }
}