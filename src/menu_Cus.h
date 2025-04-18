#include <gtk/gtk.h>
#ifndef MENU_CUS_H
#define MENU_CUS_H

#define MAX_MENU_ITEMS 100
#define MAX_ID_LENGTH 6
#define MAX_NAME_LENGTH 100
#define MAX_TYPE_LENGTH 50
#define MAX_IMAGE_PATH 100
#define MAX_ORDER_ITEMS 100

// Cấu trúc cho món ăn
typedef struct {
    char menuId[MAX_ID_LENGTH];
    char dishName[MAX_NAME_LENGTH];
    char type[MAX_TYPE_LENGTH];
    float price;
    char imagePath[MAX_IMAGE_PATH];
} MenuItem;

// Cấu trúc cho món được chọn (khách hàng)
typedef struct {
    char menuId[MAX_ID_LENGTH];
    char dishName[MAX_NAME_LENGTH];
    int quantity;
    float price;
} OrderItem;

// Hàm cho giao diện khách hàng
int loadMenuFromFile(MenuItem menu[], int *count);
void printMenu(MenuItem menu[], int count);
int saveOrderToFile(OrderItem order[], int count);

#endif // MENU_CUS_H