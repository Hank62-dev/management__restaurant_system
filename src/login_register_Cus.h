// login_register.h

#ifndef LOGIN_REGISTER_CUS_H
#define LOGIN_REGISTER_CUS_H

#include <gtk/gtk.h>

extern GtkWidget *stack;
extern GtkWidget *entry_firstname, *entry_lastname, *entry_phone;
extern GtkWidget *entry_password, *entry_confirm_password;
extern GtkWidget *entry_login_phone, *entry_login_password;

void show_identification();
void login_register_Customer();
#endif
