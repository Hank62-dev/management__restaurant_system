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
    while (fscanf(file, "%s \"%[^\"]\" \"%[^\"]\" %f\n", 
                  menuList[*count].menuId, 
                  menuList[*count].dishName, 
                  menuList[*count].category, 
                  &menuList[*count].price) == 4) {
        (*count)++;
    }
    fclose(file);
    return 1;
}


//Hàm tính số ký tự thực xuất hiện, không tính theo byte
int getVisibleLength(const char *str) {
    int length = 0;
    while (*str) {
        if ((*str & 0xC0) != 0x80) { // Bỏ qua byte tiếp theo của ký tự Unicode
            length++;
        }
        str++;
    }
    return length;
}


// In menu
void printMenu(MenuItem menuList[], int count) {

    printf("+------------+--------------------------------+--------------------------------+----------+\n");
    printf("| Mã món     | Tên món                        | Loại                           | Giá      |\n");
    printf("+------------+--------------------------------+--------------------------------+----------+\n");

    for (int i = 0; i < count; i++) {
        int nameLen = getVisibleLength(menuList[i].dishName);
        int catLen = getVisibleLength(menuList[i].category);

        printf("| %-10s | %-*s | %-*s | %8.0f |\n",
               menuList[i].menuId,
               30 - nameLen + strlen(menuList[i].dishName), menuList[i].dishName,
               30 - catLen + strlen(menuList[i].category), menuList[i].category,
               menuList[i].price);
    }

    printf("+------------+--------------------------------+--------------------------------+----------+\n");
}
	
//    for (int i = 0; i < count; i++) {
//        printf("|%-10s|%-30s|%-30s|%-30.f|\n", menuList[i].menuId, menuList[i].dishName,
//               menuList[i].category, menuList[i].price);
//    }
//}


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


// Kiểm tra trùng mã món hoặc tên món
int checkDuplicate(MenuItem menuList[], int count, char id[], char dishName[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(menuList[i].menuId, id) == 0 || strcmp(menuList[i].dishName, dishName) == 0) {
            return 1; // Trùng
        }
    }
    return 0; // Không trùng
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
    
    if(checkDuplicate(menuList, *count, menuList[*count].menuId, menuList[*count].dishName)) {
    	
        printf("Lỗi: Món ăn hoặc mã món đã tồn tại!\n");
        return;
    }
    printf("Nhập loại (Đồ ăn/Nước uống): ");
    fgets(menuList[*count].category, 100, stdin);
	menuList[*count].category[strcspn(menuList[*count].category, "\n")] = 0;
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

    menuList[found] = menuList[--(*count)];  // Ghi đè phần tử cuối lên vị trí cần xóa, giảm count
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