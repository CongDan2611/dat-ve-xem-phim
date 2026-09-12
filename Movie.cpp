#include "Movie.h"

// Khởi tạo các thuộc tính của phim thông qua Initializer list
Movie::Movie(std::string id, std::string t, int d, std::string g) 
    : movieId(id), title(t), duration(d), genre(g) {}

std::string Movie::getTitle() const { return title; }
int Movie::getDuration() const { return duration; }

// In thông tin định dạng sẵn ra màn hình console
void Movie::displayMovieInfo() const {
    std::cout << "Phim: " << title << " | The loai: " << genre 
              << " | Thoi luong: " << duration << " phut" << std::endl;
}