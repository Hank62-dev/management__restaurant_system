#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

#define MAX_MENU_ITEMS 100

// Đọc menu từ file
int loadMenuFromFile(MenuItem menuList[], int *count) {
    FILE *file = fopen("data/menu.txt", "r");
    if (!file) {
        perror("ERROR");
        return 0;
    }
    
    *count = 0;
    while (fscanf(file, "%s \"%[^\"]\" \"%[^\"]\" %f", menuList[*count].menuId, 
                  menuList[*count].dishName,
                  menuList[*count].category, &menuList[*count].price) == 4) {
        (*count)++;
    }
    fclose(file);
    return 1;
}

// In menu
void printMenu(MenuItem menuList[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s  %s  %s  %.f\n", menuList[i].menuId, menuList[i].dishName,
               menuList[i].category, menuList[i].price);
    }
}

// Lưu menu vào file
void saveMenuToFile(MenuItem menuList[], int count) {
    FILE *file = fopen("data/menu.txt", "w");
    if (!file) {
        perror("ERROR");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s \"%s\" \"%s\" %.f\n", 
                menuList[i].menuId, 
                menuList[i].dishName, 
                menuList[i].category, 
                menuList[i].price);
    }
    fclose(file);
}

// Thêm món ăn
void addItem(MenuItem menuList[], int *count) {
    if (*count >= MAX_MENU_ITEMS) {
        printf("Menu đã đầy!\n");
        return;
    }
    
    printf("Nhập mã món (Fxxxx hoặc Dxxxx): ");
    scanf("%s", menuList[*count].menuId);
    getchar();
    printf("Nhập tên món: ");
    fgets(menuList[*count].dishName, 100, stdin);
    menuList[*count].dishName[strcspn(menuList[*count].dishName, "\n")] = 0;
    printf("Nhập loại (Đồ ăn/Nước uống): ");
    scanf("%s", menuList[*count].category);
    getchar();
    printf("Nhập giá: ");
    scanf("%f", &menuList[*count].price);
    getchar();
    (*count)++;
    saveMenuToFile(menuList, *count);
    printf("Thêm món thành công!\n");
}

// Xóa món ăn
void deleteItem(MenuItem menuList[], int *count) {
    if (*count == 0) {
        printf("Menu không có món\n");
        return;
    }
    
    char id[6];
    printf("Nhập mã món cần xóa (Fxxxx/Dxxxx): ");
    scanf("%s", id);
    
    int found = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp(menuList[i].menuId, id) == 0) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Không tìm thấy món\n");
        return;
    }
    
    for (int i = found; i < *count - 1; i++) {
        menuList[i] = menuList[i + 1];
    }
    (*count)--;
    saveMenuToFile(menuList, *count);
    printf("Xóa món thành công\n");
}

// Sửa món ăn
void editItem(MenuItem menuList[], int *count) {
    if (*count == 0) {
        printf("Menu không có món\n");
        return;
    }
    
    char id[6];
    printf("Nhập mã món cần sửa (Fxxxx/Dxxxx): ");
    scanf("%s", id);
    
    int found = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp(menuList[i].menuId, id) == 0) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Không tìm thấy món\n");
        return;
    }
    getchar();
    printf("Nhập tên mới: ");
    fgets(menuList[found].dishName, 100, stdin);
    menuList[found].dishName[strcspn(menuList[found].dishName, "\n")] = 0;
    printf("Nhập loại mới (Đồ ăn/Nước uống): ");
    scanf("%s", menuList[found].category);
    getchar();
    printf("Nhập giá mới: ");
    scanf("%f", &menuList[found].price);
    getchar();
    saveMenuToFile(menuList, *count);
    printf("Sửa món thành công!\n");
}