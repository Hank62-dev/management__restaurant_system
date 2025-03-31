#include <stdio.h>
#include <stdlib.h>
#include "stats.h"
#include <gtk/gtk.h>
void apply_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "Glade_CSS/stats.css", NULL);

    GtkStyleContext *context = gtk_widget_get_style_context(GTK_WIDGET(window));
    gtk_style_context_add_provider(context,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
}

// Các biến toàn cục để truy cập widget từ nhiều hàm
GtkLabel *label_daily, *label_monthly, *label_best_food, *label_best_drink;

// Hàm cập nhật số liệu lên giao diện
void update_stats(GtkWidget *widget, gpointer data) {
    // Tạo buffer để lưu kết quả
    char buffer[256];

    // Cập nhật doanh thu theo ngày
    sprintf(buffer, "Daily Revenue: %d VND", calculate_revenue_by_day());
    gtk_label_set_text(GTK_LABEL(label_daily), buffer);

    // Cập nhật doanh thu theo tháng
    sprintf(buffer, "Monthly Revenue: %d VND", calculate_revenue_by_month());
    gtk_label_set_text(GTK_LABEL(label_monthly), buffer);

    // Cập nhật món ăn bán chạy nhất
    sprintf(buffer, "Best Selling Food: %s", find_food_best_selling());
    gtk_label_set_text(GTK_LABEL(label_best_food), buffer);

    // Cập nhật thức uống bán chạy nhất
    sprintf(buffer, "Best Selling Drink: %s", find_drink_best_selling());
    gtk_label_set_text(GTK_LABEL(label_best_drink), buffer);
}

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window, *btn_stats;

    gtk_init(&argc, &argv);

    // Load file Glade
    builder = gtk_builder_new_from_file("UI Glade/UI Stats.glade");

    // Lấy widget từ file Glade
    window = GTK_WIDGET(gtk_builder_get_object(builder, "Revenue_window"));
    btn_stats = GTK_WIDGET(gtk_builder_get_object(builder, "btn_stats"));

    label_daily = GTK_LABEL(gtk_builder_get_object(builder, "label_daily_data"));
    label_monthly = GTK_LABEL(gtk_builder_get_object(builder, "label_monthly_data"));
    label_best_food = GTK_LABEL(gtk_builder_get_object(builder, "label_selling_data"));
    label_best_drink = GTK_LABEL(gtk_builder_get_object(builder, "label_drink_data")); // cần thêm trong Glade

    // Gán sự kiện cho nút "Stats"
    g_signal_connect(btn_stats, "clicked", G_CALLBACK(update_stats), NULL);

    gtk_widget_show_all(window);
    apply_css();
    gtk_main();

    return 0;
}
/*
int main() {
	calculate_revenue_by_day();
	calculate_revenue_by_month();

	find_food_best_selling();
	find_drink_best_selling();
	return 0;
}*/