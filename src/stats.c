
#include "stats.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int calculate_revenue_by_day(const char* date_target) {
    FILE *file = fopen("data/orders.txt", "r");
    if (!file) {
        perror("No found file orders.txt");
        return 0;
    }

    int total_day = 0, price = 0;
    char date[20], item[50], category[10];
    int id[10];
    while (fscanf(file, "%s %s %s %d %s", date, id, item, &price, category) == 4) {
        if (strcmp(date, date_target) == 0) {
            total_day += price;  // Cộng dồn doanh thu cho ngày cần tìm
        }
    }

    fclose(file);
    return total_day;  // Trả về doanh thu
}

int calculate_revenue_by_month(int year, int month) {
    FILE *file = fopen("data/orders.txt", "r");
    if (!file) {
        perror("No found file orders.txt");
        return 0;
    }

    int total_month = 0, price = 0;
    char date[20], item[50], category[10];

    while (fscanf(file, "%s %s %d %s", date, item, &price, category) == 4) {
        int year_data, month_data;
        sscanf(date, "%d-%d", &year_data, &month_data);

        if (year_data == year && month_data == month) {
            total_month += price;  // Cộng dồn doanh thu cho tháng cần tìm
        }
    }

    fclose(file);
    return total_month;  // Trả về doanh thu cho tháng cần tìm
}
char best_food[100];   // Biến toàn cục để lưu món ăn bán chạy nhất
char best_drink[100];  // Biến toàn cục để lưu thức uống bán chạy nhất

// Hàm trả về món ăn bán chạy nhất (ID bắt đầu bằng 'F')
char* find_food_best_selling() {
    FILE *file_orders = fopen("data/orders.txt", "r");
    if (!file_orders) {
        printf("No found file!\n");
        return 0;
    }

    int maxCount = 0;
    strcpy(best_food, "None");

    char id[20], item[100];
    int quantity, price;
    char food_items[100][100];
    int food_count[100] = {0};
    int food_index = 0;
    int date[11];
    while (fscanf(file_orders, "%s %s \"%[^\"]\" %d %d", date , id, item, &quantity, &price) == 5) {
        if (id[0] == 'F') {
            int found = 0;
            for (int i = 0; i < food_index; i++) {
                if (strcmp(food_items[i], item) == 0) {
                    food_count[i] += quantity;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(food_items[food_index], item);
                food_count[food_index++] = quantity;
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

// Hàm trả về thức uống bán chạy nhất (ID bắt đầu bằng 'D')
char* find_drink_best_selling() {
    FILE *filed_orders = fopen("data/orders.txt", "r");
    if (!filed_orders) {
        printf("No found file!\n");
        return 0;
    }

    int maxCount = 0;
    strcpy(best_drink, "None");

    char id[20], item[100];
    int quantity, price;
    char drink_items[100][100];
    int drink_count[100] = {0};
    int drink_index = 0;
    int date[11];
    while (fscanf(filed_orders, "%s %s \"%[^\"]\" %d %d", date, id, item, &quantity, &price) == 5) {
        if (id[0] == 'D') {
            int found = 0;
            for (int i = 0; i < drink_index; i++) {
                if (strcmp(drink_items[i], item) == 0) {
                    drink_count[i] += quantity;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(drink_items[drink_index], item);
                drink_count[drink_index++] = quantity;
            }
        }
    }

    fclose(filed_orders);

    for (int i = 0; i < drink_index; i++) {
        if (drink_count[i] > maxCount) {
            maxCount = drink_count[i];
            strcpy(best_drink, drink_items[i]);
        }
    }
    return best_drink;
}