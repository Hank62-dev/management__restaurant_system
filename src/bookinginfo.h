#ifndef BOOKING_H
#define BOOKING_H

#include <gtk/gtk.h>

// Các widget cần sử dụng trong giao diện đặt bàn
extern GtkWidget *window_booking_information;
extern GtkWidget *window_booking_table;

// Các entry để lấy dữ liệu từ người dùng
extern GtkEntry *entry_name;
extern GtkEntry *entry_phone;
extern GtkEntry *entry_date;
extern GtkEntry *entry_time;
extern GtkEntry *entry_number_of_guest;

// Các hàm xử lý sự kiện
void on_button_booking_table_clicked(GtkButton *button, gpointer user_data);
void on_home3_clicked(GtkButton *button, gpointer user_data);
void on_menu3_clicked(GtkButton *button, gpointer user_data);
void on_booking3_clicked(GtkButton *button, gpointer user_data);
void on_bill3_clicked(GtkButton *button, gpointer user_data);

#endif // BOOKING_H
