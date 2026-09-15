#include "Movie.h"

// In thông tin định dạng sẵn ra màn hình console
void Movie::displayMovieInfo() const {
    cout << "Phim: " << title << " | The loai: " << genre 
         << " | Thoi luong: " << duration << " phut | Trang thai: " << status << endl;
}