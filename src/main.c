#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

int main() {
	SetConsoleOutputCP(65001);
	MenuItem menuList[100];  // Danh sách chứa tối đa 100 món ăn
    int count = 0;
    int choice;
    
    //Đọc menu từ file khi bắt đầu ctrinh
	loadMenuFromFile(menuList, &count);

    while (1) {
        printf("\n======== MENU QUẢN LÝ ========\n");
        printf("1. Xem menu\n");
        printf("2. Thêm món\n");
        printf("3. Xóa món\n");
        printf("4. Sửa món\n");
        printf("5. Thoát\n");
        printf("Chọn chức năng: ");
        scanf("%d", &choice);
        getchar(); // Xóa ký tự '\n' trong bộ nhớ đệm

        switch (choice) {
            case 1:
                printMenu(menuList, count);
                break;
            case 2:
                addItem(menuList, &count);
                break;
            case 3:
                deleteItem(menuList, &count);
                break;
            case 4:
                editItem(menuList, &count);
                break;
            case 5:
                printf("Thoát chương trình.\n");
                return 0;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng nhập lại!\n");
        }
    }
    
    return 0;
}
