#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include "test.h"
#define MAX_DAYS 100  

typedef struct {
    char date[11]; // Định dạng YYYY-MM-DD
    int revenue;
} DailyRevenue;

// Các biến toàn cục để truy cập widget
GtkLabel *label_daily, *label_monthly, *label_best_food, *label_best_drink;

// Hàm áp dụng CSS cho giao diện
void apply_css(GtkWidget *window) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "Glade_CSS/stats.css", NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
}

// Hàm lấy doanh thu từ file orders.txt
int get_revenue_by_day(DailyRevenue revenues[], int *num_days) {
    FILE *file = fopen("data/orders.txt", "r");
    if (!file) {
        printf("No found file!\n");
        return -1;
    }

    char date[11], item[50], type[10];
    int amount;
    *num_days = 0;

    while (fscanf(file, "%s %s %d %s", date, item, &amount, type) != EOF) {
        int found = 0;
        for (int i = 0; i < *num_days; i++) {
            if (strcmp(revenues[i].date, date) == 0) {
                revenues[i].revenue += amount;
                found = 1;
                break;
            }
        }
        if (!found && *num_days < MAX_DAYS) {
            strcpy(revenues[*num_days].date, date);
            revenues[*num_days].revenue = amount;
            (*num_days)++;
        }
    }

    fclose(file);
    return 0;
}

// Hàm cập nhật doanh thu và hiển thị trên giao diện
void update_stats(GtkWidget *widget, gpointer data) {
    char buffer[2048] = "Daily Revenue:\n";  // Thêm markup để in đậm
    DailyRevenue revenues[MAX_DAYS];
    int num_days = 0;

    get_revenue_by_day(revenues, &num_days);

    // Lấy ngày hiện tại
    time_t t = time(NULL);
    struct tm today = *localtime(&t);

    // Hiển thị doanh thu từng ngày trong 7 ngày gần nhất
    for (int i = 6; i >= 0; i--) {
        struct tm day = today;
        day.tm_mday -= i;
        mktime(&day); // Chuẩn hóa ngày

        char date_str[11];
        sprintf(date_str, "%04d-%02d-%02d", day.tm_year + 1900, day.tm_mon + 1, day.tm_mday);

        int revenue = 0;
        for (int j = 0; j < num_days; j++) {
            if (strcmp(revenues[j].date, date_str) == 0) {
                revenue = revenues[j].revenue;
                break;
            }
        }

        char line[50];
        if (revenue == 0) {
            sprintf(line, "%s: No Revenue\n", date_str);
        } else {
            sprintf(line, "%s: %d VND\n", date_str, revenue);
        }
        strcat(buffer, line);
    }

    gtk_label_set_markup(GTK_LABEL(label_daily), buffer);  // Cập nhật GUI

    // 🔹 Hiển thị doanh thu 7 tháng gần nhất
    char buffer_monthly[2048] = "Monthly Revenue:\n";

    for (int j = 6; j >= 0; j--) {
        struct tm month_data = today;
        month_data.tm_mon -= j;
        if (month_data.tm_mon < 0) { // Xử lý khi tháng vượt qua tháng 0
            month_data.tm_mon = 11; // Tháng 12
            month_data.tm_year -= 1; // Giảm năm đi một đơn vị
        }
        mktime(&month_data);

        int year = month_data.tm_year + 1900;
        int month = month_data.tm_mon + 1;

        // Tính doanh thu tháng theo năm và tháng
        int monthly_revenue = calculate_revenue_by_month(year, month);

        // Cập nhật thông tin doanh thu tháng
        char line[50];
        if (monthly_revenue == 0) {
            sprintf(line, "%04d-%02d: No Revenue\n", year, month);
        } else {
            sprintf(line, "%04d-%02d: %d VND\n", year, month, monthly_revenue);
        }

        strcat(buffer_monthly, line); // Ghép vào buffer tháng
    }

    gtk_label_set_markup(GTK_LABEL(label_monthly), buffer_monthly);  // Cập nhật GUI

    // 🔹 Cập nhật món ăn & đồ uống bán chạy nhất
    char *best_food = find_food_best_selling();
    char *best_drink = find_drink_best_selling();

    if (best_food) {
        sprintf(buffer, "<b>Best Selling Food:</b> %s", best_food);
        gtk_label_set_markup(GTK_LABEL(label_best_food), buffer);
    }

    if (best_drink) {
        sprintf(buffer, "<b>Best Selling Drink:</b> %s", best_drink);
        gtk_label_set_markup(GTK_LABEL(label_best_drink), buffer);
    }
}



// Hàm khởi chạy chương trình GTK+
int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window, *btn_stats;

    // Khởi tạo GTK
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("UI Glade/UI Stats.glade");

    // Lấy widget từ file Glade
    window = GTK_WIDGET(gtk_builder_get_object(builder, "Revenue_window"));
    btn_stats = GTK_WIDGET(gtk_builder_get_object(builder, "btn_stats"));

    label_daily = GTK_LABEL(gtk_builder_get_object(builder, "label_daily_data"));
    label_monthly = GTK_LABEL(gtk_builder_get_object(builder, "label_monthly_data"));
    label_best_food = GTK_LABEL(gtk_builder_get_object(builder, "label_best_food"));
    label_best_drink = GTK_LABEL(gtk_builder_get_object(builder, "label_best_drink"));

    // Gán sự kiện cho nút Stats
    g_signal_connect(btn_stats, "clicked", G_CALLBACK(update_stats), NULL);

    // Hiển thị cửa sổ và áp dụng CSS
    gtk_widget_show_all(window);
    apply_css(window);

    gtk_main();

    return 0;
}

