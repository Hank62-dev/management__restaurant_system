#ifndef BILL_H
#define BILL_H

#include <gtk/gtk.h>

// Khai báo các hàm xử lý sự kiện
void on_home3_clicked(GtkButton *button, gpointer user_data);
void on_menu3_clicked(GtkButton *button, gpointer user_data);
void on_booking3_clicked(GtkButton *button, gpointer user_data);
void on_bill3_clicked(GtkButton *button, gpointer user_data);
void on_confirm_bill_button_clicked(GtkButton *button, gpointer user_data);

// Khai báo các widget cần sử dụng trong Bill
extern GtkBuilder *builder;  // Builder để lấy các đối tượng từ Glade
extern GtkWidget *window_bill;  // Cửa sổ Bill

// Các Label cho thông tin hoá đơn
extern GtkLabel *label_customer_name;
extern GtkLabel *label_table_ordered;
extern GtkLabel *label_date_ordered;
extern GtkLabel *label_subtotal;
extern GtkLabel *label_tar;
extern GtkLabel *label_total;

#endif // BILL_H
