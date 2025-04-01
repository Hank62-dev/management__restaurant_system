#include "stats.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char best_food[100]; // 🔧 Sửa đổi: Biến toàn cục để lưu món bán chạy nhất
char best_drink[100]; // 🔧 Sửa đổi: Biến toàn cục để lưu thức uống bán chạy nhất

int calculate_revenue_by_day() {
    FILE *file = fopen("data/orders.txt", "r");
    if (!file) {
        perror("Lỗi mở file orders.txt");
        return 0;
    }

    int total_day = 0, price = 0;
    char date[20], prev_date[20] = "", item[50], category[10];
    char day_buffer[256];

    // Tính doanh thu theo ngày và lưu vào biến
    while (fscanf(file, "%s %s %d %s", date, item, &price, category) == 4) {
        if (strcmp(prev_date, "") != 0 && strcmp(prev_date, date) != 0) {
            // Khi ngày thay đổi, in ra doanh thu của ngày cũ
            if (total_day > 0) {
                sprintf(day_buffer, "%s: %d VND", prev_date, total_day);
                printf("%s\n", day_buffer);  // In ra màn hình nếu cần
            }
            total_day = 0;  // Reset doanh thu cho ngày mới
        }
        total_day += price;  // Cộng dồn doanh thu

        // Lưu lại ngày để so sánh khi chuyển sang ngày khác
        strcpy(prev_date, date);
    }

    // In ra doanh thu của ngày cuối cùng
    if (total_day > 0) {
        sprintf(day_buffer, "%s: %d VND", prev_date, total_day);
        printf("%s\n", day_buffer);  // In ra màn hình
    }

    fclose(file);
    return total_day;  // Trả về doanh thu theo ngày
}

int calculate_revenue_by_month() {
    FILE *file = fopen("data/orders.txt", "r");
    if (!file) {
        perror("Lỗi mở file orders.txt");
        return 0;
    }

    int total_month = 0, price = 0;
    char date[20], month[8], prev_month[8] = "", item[50], category[10];
    char month_buffer[256];

    // Tính doanh thu theo tháng và lưu vào biến
    while (fscanf(file, "%s %s %d %s", date, item, &price, category) == 4) {
        strncpy(month, date, 7);  // Lấy tháng và năm từ ngày
        month[7] = '\0';

        if (strcmp(prev_month, "") != 0 && strcmp(prev_month, month) != 0) {
            // Khi tháng thay đổi, in ra doanh thu của tháng cũ
            if (total_month > 0) {
                sprintf(month_buffer, "%s: %d VND", prev_month, total_month);
                printf("%s\n", month_buffer);  // In ra màn hình nếu cần
            }
            total_month = 0;  // Reset doanh thu cho tháng mới
        }
        total_month += price;  // Cộng dồn doanh thu

        // Lưu lại tháng để so sánh khi chuyển sang tháng khác
        strcpy(prev_month, month);
    }

    // In ra doanh thu của tháng cuối cùng
    if (total_month > 0) {
        sprintf(month_buffer, "%s: %d VND", prev_month, total_month);
        printf("%s\n", month_buffer);  // In ra màn hình
    }

    fclose(file);
    return total_month;  // Trả về doanh thu theo tháng
}
// 🔧 Sửa đổi: Hàm trả về chuỗi chứa món ăn bán chạy nhất
char* find_food_best_selling() {
    FILE *file_orders = fopen("data/orders.txt", "r");
    if (!file_orders) return "N/A";

    int maxCount = 0;
    strcpy(best_food, "None");

    char item[50], category[10], date[20];
    int price;
    char food_items[100][50];
    int food_count[100] = {0};
    int food_index = 0;

    while (fscanf(file_orders, "%s %s %d %s", date, item, &price, category) == 4) {
        if (strcmp(category, "food") == 0) {
            int found = 0;
            for (int i = 0; i < food_index; i++) {
                if (strcmp(food_items[i], item) == 0) {
                    food_count[i]++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(food_items[food_index], item);
                food_count[food_index++] = 1;
            }
        }
    }
    fclose(file_orders);

    for (int i = 0; i < food_index; i++) {
        if (food_count[i] > maxCount) {
            maxCount = food_count[i];
            strcpy(best_food, food_items[i]);
        }
    }
    return best_food;
}

// 🔧 Sửa đổi: Hàm trả về chuỗi chứa thức uống bán chạy nhất
char* find_drink_best_selling() {
    FILE *file_orders = fopen("data/orders.txt", "r");
    if (!file_orders) return "N/A";

    int maxCount = 0;
    strcpy(best_drink, "None");

    char item[50], category[10], date[20];
    int price;
    char drink_items[100][50];
    int drink_count[100] = {0};
    int drink_index = 0;

    while (fscanf(file_orders, "%s %s %d %s", date, item, &price, category) == 4) {
        if (strcmp(category, "drink") == 0) {
            int found = 0;
            for (int i = 0; i < drink_index; i++) {
                if (strcmp(drink_items[i], item) == 0) {
                    drink_count[i]++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(drink_items[drink_index], item);
                drink_count[drink_index++] = 1;
            }
        }
    }
    fclose(file_orders);

    for (int i = 0; i < drink_index; i++) {
        if (drink_count[i] > maxCount) {
            maxCount = drink_count[i];
            strcpy(best_drink, drink_items[i]);
        }
    }
    return best_drink;
}
