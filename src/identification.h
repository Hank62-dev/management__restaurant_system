#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

#include <gtk/gtk.h>


extern GtkWidget *window_identification;
extern GtkWidget *btn_management;
extern GtkWidget *btn_customer;


void show_identification();
void on_management_clicked(GtkButton *button, gpointer user_data);
void on_customer_clicked(GtkButton *button, gpointer user_data);
#endif