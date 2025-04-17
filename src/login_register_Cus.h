// login_register.h

#ifndef LOGIN_REGISTER_CUS_H
#define LOGIN_REGISTER_CUS_H

#include <gtk/gtk.h>

GtkWidget *stack;
GtkWidget *entry_firstname, *entry_lastname, *entry_phone;
GtkWidget *entry_password, *entry_confirm_password;
GtkWidget *entry_login_phone, *entry_login_password;
GtkWidget  *Login_Register_window, *homewindow;

//khai báo các hàm sẽ xử lý
void show_identification();
void login_register_Customer();
void on_login_now_clicked(GtkButton *button, gpointer user_data);
void on_register_now_clicked(GtkButton *button, gpointer user_data);
void switch_to_back(GtkButton *button, gpointer data);
void switch_to_login_now(GtkButton *button, gpointer user_data);
void switch_to_register(GtkButton *button, gpointer user_data);
void switch_to_login(GtkButton *button, gpointer user_data);
#endif
