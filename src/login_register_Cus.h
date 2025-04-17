// login_register.h

#ifndef LOGIN_REGISTER_CUS_H
#define LOGIN_REGISTER_CUS_H

#include <gtk/gtk.h>

 GtkWidget *stack_c;
 GtkWidget *entry_firstname_c, *entry_lastname_c, *entry_phone_c;
 GtkWidget *entry_password_c, *entry_confirm_password_c;
 GtkWidget *entry_login_phone_c, *entry_login_password_c;
 GtkWidget *Login_Register_window_c, *home_window_c, *window_c;
 
//khai báo các hàm sẽ xử lý
void show_identification();
void login_register_Customer();
void on_login_now_clicked_c(GtkButton *button, gpointer user_data);
void on_register_now_clicked_c(GtkButton *button, gpointer user_data);
void switch_to_back_c(GtkButton *button, gpointer data);
void switch_to_login_now_c(GtkButton *button, gpointer user_data);
void switch_to_register_c(GtkButton *button, gpointer user_data);
void switch_to_login_c(GtkButton *button, gpointer user_data);
#endif
