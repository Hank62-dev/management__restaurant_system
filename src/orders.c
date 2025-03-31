#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_NAME_LEN 50
#define MENU_SIZE 5
#define MAX_ORDERS 100 // Giới hạn số đơn hàng có thể lưu

// Structure to define a menu item (Cấu trúc định nghĩa món ăn trong menu)
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    double price;
} MenuItem;

// Structure to define an order (Cấu trúc đơn hàng)
typedef struct {
    int orderId;
    int itemIds[MAX_ITEMS];
    int itemQuantities[MAX_ITEMS]; // Array to store quantity of each item (Mảng lưu số lượng từng món)
    int itemCount;
    double totalPrice;
} Order;

// Predefined menu (Menu có sẵn)
MenuItem menu[MENU_SIZE] = {
    {1, "Pho", 50000},
    {2, "Banh mi", 25000},
    {3, "Com ga", 60000},
    {4, "Hu tieu", 40000},
    {5, "Bun bo", 55000}
};

// Order storage (Lưu danh sách các đơn hàng)
Order orders[MAX_ORDERS];
int orderCount = 0;

// Function to add multiple items to the order with quantity (Thêm nhiều món với số lượng)
void addItem(Order *order, int itemId, int quantity) {
    if (order->itemCount < MAX_ITEMS) {
        for (int i = 0; i < MENU_SIZE; i++) {
            if (menu[i].id == itemId) {
                order->itemIds[order->itemCount] = itemId;
                order->itemQuantities[order->itemCount] = quantity;
                order->totalPrice += menu[i].price * quantity;
                order->itemCount++;
                printf("Added %d x %s to the order.\n", quantity, menu[i].name);
                return;
            }
        }
        printf("Invalid item ID!\n");
    } else {
        printf("Cannot add more items, order is full!\n");
    }
}

// Function to remove an item from the order (Xóa món khỏi đơn hàng)
void removeItem(Order *order, int index) {
    if (index < 0 || index >= order->itemCount) {
        printf("Invalid item position!\n");
        return;
    }
    for (int i = 0; i < MENU_SIZE; i++) {
        if (menu[i].id == order->itemIds[index]) {
            order->totalPrice -= menu[i].price * order->itemQuantities[index];
            break;
        }
    }
    for (int i = index; i < order->itemCount - 1; i++) {
        order->itemIds[i] = order->itemIds[i + 1];
        order->itemQuantities[i] = order->itemQuantities[i + 1];
    }
    order->itemCount--;
    printf("Item removed from order.\n");
}

// Function to calculate total bill (Tính tổng hóa đơn)
double calculateTotalBill(const Order *order) {
    return order->totalPrice;
}

// Function to display order details (Hiển thị chi tiết đơn hàng)
void printOrder(const Order *order) {
    printf("\nOrder ID: %d\n", order->orderId);
    printf("Ordered items:\n");
    for (int i = 0; i < order->itemCount; i++) {
        for (int j = 0; j < MENU_SIZE; j++) {
            if (menu[j].id == order->itemIds[i]) {
                printf("%d. %s x%d - %.2f\n", i + 1, menu[j].name, order->itemQuantities[i], menu[j].price * order->itemQuantities[i]);
            }
        }
    }
    printf("Total price: %.2f\n", calculateTotalBill(order));
}

// Function to display menu (Hiển thị menu)
void printMenu() {
    printf("\nMenu:\n");
    for (int i = 0; i < MENU_SIZE; i++) {
        printf("%d. %s - %.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
}

// Main function (Hàm chính)
int main() {
    int choice, itemId, quantity, index;

    do {
        // Hiển thị menu lựa chọn
        printf("\nSelect an action:\n");
        printf("1. Display menu\n");
        printf("2. Create new order\n");
        printf("3. Add items by ID\n");
        printf("4. Remove item\n");
        printf("5. Display order\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printMenu(); // Hiển thị menu
                break;
            case 2:
                if (orderCount < MAX_ORDERS) {
                    orders[orderCount].orderId = orderCount + 1;
                    orders[orderCount].itemCount = 0;
                    orders[orderCount].totalPrice = 0.0;
                    printf("New order created with ID: %d\n", orders[orderCount].orderId);
                    orderCount++;
                } else {
                    printf("Order storage is full!\n");
                }
                break;
            case 3:
                if (orderCount == 0) {
                    printf("No active orders! Create a new order first.\n");
                    break;
                }
                printf("Enter item ID: ");
                scanf("%d", &itemId);
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                addItem(&orders[orderCount - 1], itemId, quantity);
                break;
            case 4:
                printf("Enter position of item to remove: ");
                scanf("%d", &index);
                removeItem(&orders[orderCount - 1], index - 1);
                break;
            case 5:
                if (orderCount == 0) {
                    printf("No orders available!\n");
                } else {
                    printOrder(&orders[orderCount - 1]);
                }
                break;
            case 6:
                printf("Thank you for your order! Enjoy your meal!\n"); // Cảm ơn khách hàng
                break;
            default:
                printf("Invalid choice!\n"); // Lựa chọn không hợp lệ
        }
    } while (choice != 6);

    return 0;
}