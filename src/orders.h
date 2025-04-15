#ifndef MENU_ORDER_H  // Kiểm tra xem file đã được định nghĩa chưa
#define MENU_ORDER_H  // Định nghĩa để tránh nạp lại file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100      // Số món trong mỗi đơn hàng
#define MAX_NAME_LEN 50    // Độ dài tên món ăn
#define MENU_SIZE 5        // Số lượng món trong menu
#define MAX_ORDERS 100     // Giới hạn số đơn hàng có thể lưu

// Cấu trúc món ăn trong menu
typedef struct {
    int id;                // ID món
    char name[MAX_NAME_LEN];  // Tên món ăn
    double price;          // Giá món
} MenuItem;

// Cấu trúc đơn hàng
typedef struct {
    int orderId;                    // ID đơn hàng
    int itemIds[MAX_ITEMS];         // Mảng lưu ID các món
    int itemQuantities[MAX_ITEMS];  // Mảng lưu số lượng từng món
    int itemCount;                  // Số lượng món trong đơn
    double totalPrice;              // Tổng giá trị đơn hàng
} Order;

// Menu món ăn
extern MenuItem menu[MENU_SIZE];

// Lưu danh sách các đơn hàng
extern Order orders[MAX_ORDERS];
extern int orderCount;

// Hàm thêm món vào đơn hàng
void addItem(Order *order, int itemId, int quantity);

// Hàm xóa món khỏi đơn hàng
void removeItem(Order *order, int index);

// Hàm tính tổng hóa đơn
double calculateTotalBill(const Order *order);

// Hàm hiển thị chi tiết đơn hàng
void printOrder(const Order *order);

// Hàm hiển thị menu
void printMenu();

// Hàm tạo đơn hàng mới
int createNewOrder();

// Hàm xử lý lựa chọn của người dùng trong menu chính
void handleUserChoice(int choice);

#endif // MENU_ORDER_H
