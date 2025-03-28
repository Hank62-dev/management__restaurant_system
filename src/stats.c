 
#include "stats.h" // gọi file header
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*
// Hàm tính tổng doanh thu theo ngày
void calculate_revenue_by_day(){
	FILE* file = fopen("data/orders.txt", "r");
	if(!file) {
		printf("\nKhong the mo file orders.txt");
		return;
	}	
	int total_day = 0, price = 0;
	char date[20], prev_date[20] = "", item[50], category[10];
	printf("\n-----Doanh thu theo ngay-----");
	
	while(fscanf(file, "%s %s %d %s", date, item, &price, category ) == 4 ){  // %*s: bỏ qua 1 chuỗi != EOF
		//Nếu gặp một ngày mới, in ra doanh thu của ngày trước đó
		if(strcmp(prev_date,"") != 0 &&  strcmp(prev_date, date) != 0 ){
			printf("\n%s : %d VND \n", prev_date, total_day);
			total_day = 0;
		}
		// Cộng dồn doanh thu của ngày hiện tại
		total_day += price;
		strcpy(prev_date, date); // sau mỗi lần cộng thì cpy sang để kiểm tra ngày tiếp theo có khác ngày mới cpy không
	}
	
	// in ra doanh thu ngày cuối cùng 
	if(strcmp(prev_date, "") != 0){
		printf("\n%s: %d VND ", prev_date, total_day);
	}
	fclose(file);
}

// Hàm tính tổng doanh thu theo tháng 
void calculate_revenue_by_month(){
	FILE *file = fopen("data/orders.txt", "r");
	if(!file){
		printf("\nKhong the mo file orders.txt");
		return;
	}
	
	char date[20], month[8], prev_month[8] = "", item[50], category[10];
	int price, total_month = 0;
	printf("\n----Doanh thu theo thang----");
	
	while(fscanf(file,"%s %s %d %s",date, item, &price, category) == 4){ //!= EOF
		strncpy(month, date, 7); // strncpy: lấy số kí tự cần lấy trong chuỗi, ở đây lấy YYYY-MM : 7 kí tự
		month[7] = '\0'; // tránh tràn số liệu
		
		// Nếu gặp tháng mới, in ra doanh thu của tháng cũ
		if(strcmp(prev_month,"") != 0 && strcmp(prev_month, month) != 0){
			printf("\n%s: %d VND", prev_month, total_month);
			total_month = 0;
		}
		// Cộng dồn doanh thu của tháng hiện tại
		total_month += price;
		strcpy(prev_month, month);
	}
	//in ra doanh thu tháng cuối cùng
	if(strcmp(prev_month, "") != 0 ){ //&& strcmp(prev_month, month) != 0
		printf("\n%s: %d VND", prev_month, total_month);
	}
	fclose(file);
}

//Hàm tìm món ăn và thức uống bán chạy nhất
void find_food_best_selling(){
	FILE *file_orders = fopen("data/orders.txt", "r");
	FILE *file_menu = fopen("data/menu.txt", "r");
	if(!file_orders || !file_menu){
		printf("\nKhong the mo file orders.txt hoac file menu.txt");
		return ;
	}
	
	char item[50]; // lưu từng món ăn đọc được từ orders.txt
	char menu_item[50], category[10]; // đọc từ menu.txt
	int price; 
	char date[20];
	//Lưu danh sách món ăn
	char food_items[100][50]; // lưu các món ăn duy nhất
	int food_count[100] = {0}; // số lần món đó được order
	int food_index = 0; // số lượng món được lưu vào food
	 
	//Đọc danh sách món ăn để lấy food ra
	while(fscanf(file_menu, "%s %d %s", menu_item, &price, category) != EOF){
		if(strcmp(category, "food") == 0){
			strcpy(food_items[food_index], menu_item);
			food_count[food_index++] = 0;
		}
	}
	fclose(file_menu);
	
	//Đọc file orders.txt đếm số lượng từng món ăn
	while(fscanf(file_orders, "%s %s %d %s", date, item, &price, category) == 4){
		//Kiểm tra nếu món ăn thuộc loại food
		for(int i = 0; i <= food_index - 1; i++ ){
			if(strcmp(food_items[i],item) == 0){
				food_count[i]++;
				break;
			}
		}
	}
	fclose(file_orders);

	//Tìm món ăn bán chạy nhất
	int maxFoodIndex = 0;
	for(int i = 0; i <= food_index - 1; i++){
		if(food_count[i] > food_count[maxFoodIndex]){
			maxFoodIndex = i;
		}
	}
	//in kết quả
	printf("\nThe best of food selling: %s", food_items[maxFoodIndex]);
}

void find_drink_best_selling(){
	FILE *file_menu = fopen("data/menu.txt" , "r");
	FILE *file_orders = fopen("data/orders.txt", "r");
	if(!file_menu || !file_orders){
		printf("\nKhong the mo file_menu.txt hoac file_orders.txt");
		return;
	}
	
	char item[50], category[8]; // món được đọc từ orders.txt và loại 
	char menu_item[50]; // tên món ăn đọc từ menu.txt
	int price;
	//lưu danh sách thức uống
	char drink_items[100][50]; // lưu các món ăn duy nhất
	int drink_count[100] = {0}; // lưu số lượng món đó được orders
	int drink_index = 0; // số lượng món được lưu vào drink
	
	//Đọc danh sách để lấy drink ra
	while(fscanf(file_menu, "%s %d %s", menu_item, &price, category) == 3){ //!= EOF
		if(strcmp(category,"drink") == 0){
			strcpy(drink_items[drink_index], menu_item);
			drink_count[drink_index++] = 0;
		}
	}
	fclose(file_menu);
	
	//Đọc file orders.txt để lấy số lượng thức uống ra
	while(fscanf(file_orders, "%s", item) != EOF){
		for(int i = 0; i <= drink_index - 1; i++){
			if(strcmp(drink_items[i], item) == 0){
				drink_count[i]++;
				break;
			}
		}
	}
	fclose(file_orders);
	
	//Tìm thức uống bán chạy nhất
	int maxDrinkSelling = 0;
	for(int i = 0; i <= drink_index - 1; i++){
		if(drink_count[i] > drink_count[maxDrinkSelling]){
			maxDrinkSelling = i;
		}
	}
	//in kết quả
	printf("\nThe best of drink selling: %s", drink_items[maxDrinkSelling]);
}
*/

#include "stats.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char best_food[100]; // 🔧 Sửa đổi: Biến toàn cục để lưu món bán chạy nhất
char best_drink[100]; // 🔧 Sửa đổi: Biến toàn cục để lưu thức uống bán chạy nhất

// 🔧 Sửa đổi: Hàm tính tổng doanh thu theo ngày trả về giá trị
int calculate_revenue_by_day() {
    FILE *file = fopen("data/orders.txt", "r");
    if (!file) return 0;

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

// 🔧 Sửa đổi: Hàm tính tổng doanh thu theo tháng trả về giá trị
int calculate_revenue_by_month() {
    FILE *file = fopen("data/orders.txt", "r");
    if (!file) return 0;

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
