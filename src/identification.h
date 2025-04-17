#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

#include <gtk/gtk.h>

 GtkWidget *stack;
 GtkWidget *window_identification;
 GtkWidget *btn_management;
 GtkWidget *btn_customer;

void show_identification();
void on_management_clicked(GtkButton *button, gpointer user_data);
void on_customer_clicked(GtkButton *button, gpointer user_data);
#endif