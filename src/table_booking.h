#ifndef TABLE_BOOKING_H
#define TABLE_BOOKING_H

#include <gtk/gtk.h>

void show_booking_information();
void run_bill();
void book_table_show ();
static void on_table_clicked(GtkButton *button, gpointer user_data);
static void on_confirm_booking_table_button_clicked(GtkButton *button, gpointer user_data);


#endif