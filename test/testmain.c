#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test.h"  
#include <gtk/gtk.h>

// Hàm áp dụng CSS cho giao diện
void apply_css(GtkWidget *window) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "Glade_CSS/stats.css", NULL);
    
    GtkStyleContext *context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
}

// Các biến toàn cục để truy cập widget từ nhiều hàm
GtkLabel *label_daily, *label_monthly, *label_best_food, *label_best_drink;

void update_stats(GtkWidget *widget, gpointer data) {
    char buffer[256];

    // Lấy thời gian hiện tại
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Định dạng ngày tháng năm (DD-MM-YYYY)
    sprintf(buffer, "Date: %02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    gtk_label_set_text(GTK_LABEL(label_daily), buffer);  // Cập nhật ngày vào label_daily

    int daily_revenue = calculate_revenue_by_day();
    int monthly_revenue = calculate_revenue_by_month();
    char *best_food = find_food_best_selling();
    char *best_drink = find_drink_best_selling();

    if (daily_revenue >= 0) {
        sprintf(buffer, "Daily Revenue: %d VND", daily_revenue);
        gtk_label_set_text(label_daily, buffer);
    }

    if (monthly_revenue >= 0) {
        sprintf(buffer, "Monthly Revenue: %d VND", monthly_revenue);
        gtk_label_set_text(label_monthly, buffer);
    }

    if (best_food) {
        sprintf(buffer, "Best Selling Food: %s", best_food);
        gtk_label_set_text(label_best_food, buffer);
    }

    if (best_drink) {
        sprintf(buffer, "Best Selling Drink: %s", best_drink);
        gtk_label_set_text(label_best_drink, buffer);
    }
}


int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window, *btn_stats;

    // Khởi tạo GTK
    gtk_init(&argc, &argv);

    // Load file Glade
    builder = gtk_builder_new_from_file("UI Glade/UI Stats.glade");

    // Lấy widget từ file Glade
    window = GTK_WIDGET(gtk_builder_get_object(builder, "Revenue_window"));
    btn_stats = GTK_WIDGET(gtk_builder_get_object(builder, "btn_stats"));

    label_daily = GTK_LABEL(gtk_builder_get_object(builder, "label_daily_data"));
    label_monthly = GTK_LABEL(gtk_builder_get_object(builder, "label_monthly_data"));
    label_best_food = GTK_LABEL(gtk_builder_get_object(builder, "label_best_food"));
    label_best_drink = GTK_LABEL(gtk_builder_get_object(builder, "label_best_drink"));

    // Gán sự kiện cho nút "Stats"
    g_signal_connect(btn_stats, "clicked", G_CALLBACK(update_stats), NULL);

    // Hiển thị cửa sổ và áp dụng CSS
    gtk_widget_show_all(window);
    apply_css(window);

    // Vòng lặp chính của GTK
    gtk_main();

    return 0;
}
