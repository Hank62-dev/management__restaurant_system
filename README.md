# Phần Mềm Quản Lý Nhà Hàng – VQHT Restaurant

## Thành viên nhóm  
- **Võ Gia Huy** (Leader)  
- **Phan Chí Thuận** (Member)  
- **Vũ Việt Quang** (Member)  
- **Nguyễn Trí Vỹ** (Member)  

---

## Mô tả dự án  

Trước nhu cầu ăn uống ngày càng tăng cao, các nhà hàng mới liên tục xuất hiện. Điều này khiến phần mềm quản lý nhà hàng trở thành một yếu tố quan trọng trong việc vận hành và phát triển hiệu quả.

Nhận thấy điều đó, nhóm chúng tôi quyết định xây dựng phần mềm “**VQHT Restaurant**” – hệ thống quản lý nhà hàng thân thiện, tiện dụng và phù hợp thực tế, vừa đáp ứng yêu cầu kỹ thuật của TrainC, vừa mở rộng nhiều tính năng để giải quyết các bài toán phổ biến trong quản lý nhà hàng.

---

## Chi tiết dự án  

### Công nghệ sử dụng  

- **Ngôn ngữ**: C thuần  
- **Thiết kế giao diện**: Glade + CSS  
- **Lưu trữ dữ liệu**: File `.txt`

### Các file dữ liệu bao gồm:
- `customers.txt` – thông tin khách hàng  
- `employees.txt` – thông tin nhân viên  
- `menu.txt` – thông tin món ăn  
- `orders.txt` – dữ liệu đơn hàng  
- `view_bill.txt` – hóa đơn đã thanh toán  
- Và các file phụ trợ khác  

---

## Chức năng chính của phần mềm

### 🔑 Phân quyền người dùng
- **Khách hàng**:
  - Đăng ký / Đăng nhập tài khoản
  - Đặt bàn, đặt món ăn
  - Xem hóa đơn đã thanh toán

- **Quản lý**:
  - Quản lý món ăn
  - Quản lý nhân viên
  - Thống kê doanh thu theo ngày / tháng
  - Xem chi tiết hóa đơn khách hàng

---

## Hướng dẫn chạy phần mềm

### 1. **Cài đặt môi trường**  
- Linux hoặc Windows (khuyên dùng MSYS2 nếu dùng Win)  
- Cài đặt: `GTK+ 3`, `Glade`, `GCC`

### 2. **Biên dịch chương trình**
```bash
gcc -o restaurant_VQHT src/*.c $(pkg-config --cflags --libs gtk+-3.0)
./restaurant_VQHT
