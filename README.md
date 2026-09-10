"# quan-ly-thu-cung" 

Ở đây chỉ chứa file cài đặt và file cấu hình không chứ bất cứ thư viện nào của VS

## 📌 Quy Định Làm Việc (Git Workflow)

Nhóm chúng ta thực hiện quy tắc **không push trực tiếp lên nhánh `main`**. Mọi thay đổi đều phải thông qua Pull Request (PR) và được phê duyệt (Approve).

### 1. Lấy code mới nhất trước khi làm việc
Mỗi khi bắt đầu ngày mới hoặc trước khi viết tính năng mới, hãy đồng bộ code từ nhánh `main` về máy:
```bash
git checkout main
git pull origin main

### 2. Tạo nhánh làm việc riêng (Feature Branch)
Không viết code trực tiếp trên main. Hãy tạo một nhánh mới mang tên bạn hoặc tên tính năng:
```bash
git checkout -b ten-nhanh-cua-ban

### 3. Lưu thay đổi và đẩy code lên GitHub (Push)
Sau khi code xong và test ổn định trên máy:
```bash
# Kiểm tra trạng thái các file đã thay đổi
git status

# Thêm tất cả file vào hàng chờ (ngoại trừ các file trong .gitignore)
git add .

# Lưu lịch sử thay đổi kèm theo mô tả rõ ràng
git commit -m "feat: mô tả chi tiết tính năng vừa làm"

# Đẩy nhánh lên GitHub (chạy lệnh này cho lần push đầu tiên của nhánh)
git push -u origin ten-nhanh-cua-ban

# Từ các lần push sau, bạn chỉ cần gõ:
git push
### 4. Lưu thay đổi và đẩy code lên GitHub (Push)
Tạo Pull Request (PR):
    1. Truy cập vào trang GitHub của repository.

    2. Nhấn nút Compare & pull request ở thông báo vừa hiển thị.

    3. Điền tiêu đề và mô tả rõ ràng, sau đó bấm Create pull request.

    4. Chờ quản lý vào kiểm tra code, bấm Approve và Merge để đưa code vào nhánh main.