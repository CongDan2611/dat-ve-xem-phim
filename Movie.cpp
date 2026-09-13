#include "Movie.h"

// Khởi tạo các thuộc tính của phim thông qua Initializer list
Movie::Movie(string id, string t, int d, string g) 
    : movieId(id), title(t), duration(d), genre(g) {}

string Movie::getTitle() const { return title; }
int Movie::getDuration() const { return duration; }

// In thông tin định dạng sẵn ra màn hình console
void Movie::displayMovieInfo() const {
    cout << "Phim: " << title << " | The loai: " << genre 
         << " | Thoi luong: " << duration << " phut" << endl;
}