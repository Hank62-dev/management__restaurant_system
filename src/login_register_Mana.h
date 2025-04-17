/*login_register.h*/ 

#ifndef LOGIN_REGISTER_MANA_H
#define LOGIN_REGISTER_MANA_H

#include <gtk/gtk.h>

extern GtkWidget *stack;
extern GtkWidget *entry_firstname, *entry_lastname, *entry_phone;
extern GtkWidget *entry_password, *entry_confirm_password;
extern GtkWidget *entry_login_phone, *entry_login_password;
extern GtkWidget  *Login_Register_window, *homewindow;


//khai báo các hàm sẽ xử lý
void show_identification();
void login_register_Management();
void on_login_now_clicked(GtkButton *button, gpointer user_data);
void on_register_now_clicked(GtkButton *button, gpointer user_data);
void switch_to_back(GtkButton *button, gpointer data);
void switch_to_login_now(GtkButton *button, gpointer user_data);
void switch_to_register(GtkButton *button, gpointer user_data);
void switch_to_login(GtkButton *button, gpointer user_data);
#endif
