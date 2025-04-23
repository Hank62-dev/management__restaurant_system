 #ifndef STATS_H  // Kiểm tra nếu chưa được định nghĩa
 #define STATS_H // Định nghĩa để tránh nạp lại file
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <gtk/gtk.h>
 //Cấu trúc dữ liệu thống kê
 typedef struct {
	 int totalRevenueByDay; // Tổng doanh thu theo ngày
	 int totalRenenueByMonth; // Tổng doanh thu theo tháng
	 char bestFoodSelling[100]; // Tên món bán chạy nhất
	 char bestDrinkSelling[100];
	 int bestFoodSellingCount; // Số lượng món bán chạy nhất
	 int bestDrinkSellingCount; // Sô lượng thức uống bán chạy nhất
 } Stats;

 typedef struct {
    char date[11]; // Định dạng YYYY-MM-DD
    int revenue;
} DailyRevenue;

 //Khai báo hàm cần làm
 int calculate_revenue_by_day();
 int calculate_revenue_by_month();
 char* find_food_best_selling();
 char* find_drink_best_selling();
 void show_stats();
 void update_stats(GtkWidget *widget, gpointer data);
 int get_revenue_by_month(DailyRevenue revenues[], int *num_months);
 int get_revenue_by_day(DailyRevenue revenues[], int *num_days);

 #endif