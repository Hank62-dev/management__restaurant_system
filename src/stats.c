

#include "stats.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char best_food[100]; // Biến toàn cục để lưu món bán chạy nhất
char best_drink[100]; //Biến toàn cục để lưu thức uống bán chạy nhất

//Hàm tính tổng doanh thu theo ngày trả về giá trị
int calculate_revenue_by_day() {
    FILE *file = fopen("data/orders.txt", "r");
    if (!file){
        printf("Khong tim thay file orders\n");
        return;
    } 

    int total_day = 0, price = 0;
    char date[20], prev_date[20] = "", item[50], category[10];

    while (fscanf(file, "%s %s %d %s", date, item, &price, category) == 4) {
        if (strcmp(prev_date, "") != 0 && strcmp(prev_date, date) != 0) {
            strcpy(prev_date, date);
        }	
        total_day += price;
    }
    fclose(file);
    return total_day;
}

//Hàm tính tổng doanh thu theo tháng trả về giá trị
int calculate_revenue_by_month() {
    FILE *file = fopen("data/orders.txt", "r");
    if (!file) {
        printf("Khong tim thay file orders\n");
        return;
    } 

    int total_month = 0, price = 0;
    char date[20], month[8], prev_month[8] = "", item[50], category[10];

    while (fscanf(file, "%s %s %d %s", date, item, &price, category) == 4) {
        strncpy(month, date, 7);
        month[7] = '\0';

        if (strcmp(prev_month, "") != 0 && strcmp(prev_month, month) != 0) {
            strcpy(prev_month, month);
        }
        total_month += price;
    }
    fclose(file);
    return total_month;
}

//Hàm trả về chuỗi chứa món ăn bán chạy nhất
char* find_food_best_selling() {
    FILE *file_orders = fopen("data/orders.txt", "r");
    if (!file_orders){
        printf("Khong tim thay file orders\n");
        return;
    } 

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

// Hàm trả về chuỗi chứa thức uống bán chạy nhất
char* find_drink_best_selling() {
    FILE *file_orders = fopen("data/orders.txt", "r");
    if (!file_orders){
        printf("Khong tim thay file orders\n");
        return;
    } 

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
