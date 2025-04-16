#include <stdio.h>
#include <string.h>
#include "menu_Cus.h"

int loadMenuFromFile(MenuItem menu[], int *count) {
    FILE *file = fopen("data/menu.txt", "r");
    if (!file) {
        perror("Lỗi mở file menu.txt");
        return 0;
    }

    *count = 0;
    char line[512];
    while (fgets(line, sizeof(line), file) && *count < MAX_MENU_ITEMS) {
        char menuId[MAX_ID_LENGTH];
        char dishName[MAX_NAME_LENGTH];
        char type[MAX_TYPE_LENGTH];
        float price;
        char imagePath[MAX_IMAGE_PATH];

        // Định dạng: ID "Tên" "Loại" Giá "Hình ảnh"
        if (sscanf(line, "%5s \"%[^\"]\" \"%[^\"]\" %f \"%[^\"]\"", 
                   menuId, dishName, type, &price, imagePath) == 5) {
            strcpy(menu[*count].menuId, menuId);
            strcpy(menu[*count].dishName, dishName);
            strcpy(menu[*count].type, type);
            menu[*count].price = price;
            strcpy(menu[*count].imagePath, imagePath);
            (*count)++;
        }
    }

    fclose(file);
    return 1;
}

void printMenu(MenuItem menu[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s \"%s\" \"%s\" %.0f \"%s\"\n", 
               menu[i].menuId, menu[i].dishName, menu[i].type, 
               menu[i].price, menu[i].imagePath);
    }
}

int saveOrderToFile(OrderItem order[], int count) {
    FILE *file = fopen("data/order.txt", "w");
    if (!file) {
        perror("Lỗi mở file order.txt");
        return 0;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s \"%s\" %d %.0f\n",
                order[i].menuId, order[i].dishName, 
                order[i].quantity, order[i].price * order[i].quantity);
    }

    fclose(file);
    return 1;
}