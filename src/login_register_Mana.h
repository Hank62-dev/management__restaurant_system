/*login_register.h*/ 

#ifndef LOGIN_REGISTER_MANA_H
#define LOGIN_REGISTER_MANA_H

#include <gtk/gtk.h>

extern GtkWidget *stack_m;
extern GtkWidget *entry_firstname_m, *entry_lastname_m, *entry_phone_m;
extern GtkWidget *entry_password_m, *entry_confirm_password_m;
extern GtkWidget *entry_login_phone_m, *entry_login_password_m;
extern GtkWidget *Login_Register_window_m, *home_window_m, *window_m;

//khai báo các hàm sẽ xử lý
void show_identification();
void login_register_Management(GtkWidget *identification_window);
void on_login_now_clicked_m(GtkButton *button, gpointer user_data);
void on_register_now_clicked_m(GtkButton *button, gpointer user_data);
void switch_to_back_m(GtkButton *button, gpointer data);
void switch_to_login_now_m(GtkButton *button, gpointer user_data);
void switch_to_register_m(GtkButton *button, gpointer user_data);
void switch_to_login_m(GtkButton *button, gpointer user_data);
#endif
