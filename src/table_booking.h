#ifndef TABLE_BOOKING_H
#define TABLE_BOOKING_H

#include <gtk/gtk.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
void show_booking_information();
void run_bill();
void book_table_show ();
static void on_table_clicked(GtkButton *button, gpointer user_data);
static void on_confirm_booking_table_button_clicked(GtkButton *button, gpointer user_data);
=======

<<<<<<< HEAD
void show_booking_information();
void book_table_show();
void run_bill();
=======
>>>>>>> 53b11d80021a4a360f91ed4760b60051ca69d9ef
// Structure to hold application data
typedef struct {
    GtkWidget *window_booking_information;
    GtkWidget *window_booking_table;
    GtkBuilder *builder_booking_information;
    GtkBuilder *builder_booking_table;
    char *name;
    char *date;
    char *phone;
    char *time;
    char *guests;
} AppData;
void show_booking_information();
void run_bill();
void book_table_show ();
static void on_table_clicked(GtkButton *button, gpointer user_data);
static void on_confirm_booking_table_button_clicked(GtkButton *button, gpointer user_data);

void show_booking_information(AppData *app_data);
void book_table_show(AppData *app_data);
void run_bill(AppData *app_data);
static void on_table_clicked(GtkButton *button, gpointer user_data);
static void on_confirm_booking_table_button_clicked(GtkButton *button, gpointer user_data);
static void on_confirm_bill_button_clicked(GtkButton *button, gpointer user_data);
>>>>>>> e5961ab5687db564333e30ce2ef2b6150e0397a9

#endif