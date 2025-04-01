/*Idea: 
Dữ liệu thống kê bao gồm:
- Doanh thu(Revenue): Tổng tiền bán được theo ngày/tháng
- Món bán chạy nhất(bestSelling): Món có số lượng bán nhiều nhất
Lưu ý: dữ liệu sẽ được tính toán từ orders.txt
 */


#ifndef TEST_H  // Kiểm tra nếu chưa được định nghĩa
#define TEST_H // Định nghĩa để tránh nạp lại file

#include <stdio.h>
#include <stdlib.h>

//Cấu trúc dữ liệu thống kê
typedef struct {
	int totalRevenueByDay; // Tổng doanh thu theo ngày
	int totalRenenueByMonth; // Tổng doanh thu theo tháng
	char bestFoodSelling[100]; // Tên món bán chạy nhất
	char bestDrinkSelling[100];
	int bestFoodSellingCount; // Số lượng món bán chạy nhất
	int bestDrinkSellingCount; // Sô lượng thức uống bán chạy nhất
} Stats;

//Khai báo hàm cần làm
int calculate_revenue_by_day();
int calculate_revenue_by_month();
char* find_food_best_selling();
char* find_drink_best_selling();

/*
void calculate_revenue_by_day();
void calculate_revenue_by_month();

void find_food_best_selling();
void find_drink_best_selling();
*/
#endif // kết thúc khai báo chương trình