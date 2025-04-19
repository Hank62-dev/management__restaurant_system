#include "utils.h"
#include "stats.h"
#include "login_register_Cus.h"
#include "identification.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#define DATA_FILE "data/users.txt"

GtkWidget *stack_c;
GtkWidget *entry_firstname_c, *entry_lastname_c, *entry_phone_c;
GtkWidget *entry_password_c, *entry_confirm_password_c;
GtkWidget *entry_login_phone_c, *entry_login_password_c;
GtkWidget *Login_Register_window_c, *home_window_c, *window_c;
static GtkWidget *identification = NULL;

// Chuyển form khi nhấn nút login/register
void switch_to_login_c(GtkButton *button, gpointer user_data){
	gtk_stack_set_visible_child_name(GTK_STACK(stack_c),"login_box");	
}
void switch_to_register_c(GtkButton *button, gpointer user_data){
	gtk_stack_set_visible_child_name(GTK_STACK(stack_c),"register_box");
}
void switch_to_login_now_c(GtkButton *button, gpointer user_data){
    GtkBuilder *builder = gtk_builder_new_from_file("UI Glade/UI Stats.glade");
    home_window_c = GTK_WIDGET(gtk_builder_get_object(builder,"Revenue_window"));//id home
    gtk_widget_show_all(home_window_c);
    gtk_widget_hide(Login_Register_window_c);
}
void switch_to_back_c(GtkButton *button, gpointer data) {
    //GtkWidget *identification = GTK_WIDGET(data);
    gtk_widget_show_all(identification);
    gtk_widget_hide(Login_Register_window_c);
    
}
// Lưu trữ thông tin đăng kí
void on_register_now_clicked_c(GtkButton *button, gpointer user_data) {
    const gchar *firstname = gtk_entry_get_text(GTK_ENTRY(entry_firstname_c));
    const gchar *lastname = gtk_entry_get_text(GTK_ENTRY(entry_lastname_c));
    const gchar *phone = gtk_entry_get_text(GTK_ENTRY(entry_phone_c));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry_password_c));
    const gchar *confirm_password = gtk_entry_get_text(GTK_ENTRY(entry_confirm_password_c));

    if (g_strcmp0(password, confirm_password) != 0) {
        g_print("Passwords do not match!\n");
        return;
    }
     
    FILE *file = fopen(DATA_FILE, "a");
    if (file) {
        fprintf(file, "%s %s %s %s\n", firstname, lastname, phone, password);
        fclose(file);
        g_print("User registered successfully!\n");
    } else {
        g_print("Error saving data!\n");
    }
}
// Kiểm tra thông tin đăng nhập
void on_login_now_clicked_c(GtkButton *button, gpointer user_data) {
    const gchar *phone = gtk_entry_get_text(GTK_ENTRY(entry_login_phone_c));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry_login_password_c));
    
    FILE *file = fopen(DATA_FILE, "r");
    if (!file) {
        g_print("Error opening data file!\n");
        return;
    }
    
    char firstname[50], lastname[50], stored_phone[20], stored_password[50];
    int found = 0;
    while (fscanf(file, "%s %s %s %s", firstname, lastname, stored_phone, stored_password) != EOF) {
        if (strcmp(phone, stored_phone) == 0 && strcmp(password, stored_password) == 0) {
            found = 1;
            break;
        }
    }
    fclose(file);
    
    if (found) {
        g_print("Login successful! Redirecting to Home...\n");
        // Chuyển sang giao diện Home
        show_stats();

    } else {
        g_print("Invalid login credentials!\n");
    }
}


void login_register_Customer(GtkWidget *identification_window){

    GtkBuilder *builder = gtk_builder_new_from_file("UI Glade/UI Login_Register_Cus.glade");
    window_c = GTK_WIDGET(gtk_builder_get_object(builder, "Login_Register_window"));
    Login_Register_window_c = window_c;
    identification = identification_window;
    //resize ảnh
	GtkWidget *image = GTK_WIDGET(gtk_builder_get_object(builder, "logo_login_register"));
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("UI_image/logores.jpg", NULL); 
	int width = 390, height = 390;
	pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
	gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "Glade_CSS/login_register.css", NULL);
    apply_css_Cus(window_c, provider);
    g_object_unref(provider);

    stack_c = GTK_WIDGET(gtk_builder_get_object(builder, "stack_form"));
    
    // Lấy các entry từ form
    entry_firstname_c = GTK_WIDGET(gtk_builder_get_object(builder, "entry_firstname"));
    entry_lastname_c = GTK_WIDGET(gtk_builder_get_object(builder, "entry_lastname"));
    entry_phone_c = GTK_WIDGET(gtk_builder_get_object(builder, "entry_phone"));
    entry_password_c = GTK_WIDGET(gtk_builder_get_object(builder, "entry_password"));
    entry_confirm_password_c = GTK_WIDGET(gtk_builder_get_object(builder, "entry_confirm_password"));
    entry_login_phone_c = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login_phone"));
    entry_login_password_c = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login_password"));
    
    GtkWidget *btn_register_now_c = GTK_WIDGET(gtk_builder_get_object(builder, "btn_register_now"));
    GtkWidget *btn_login_now_c = GTK_WIDGET(gtk_builder_get_object(builder, "btn_login_now"));
    
    GtkWidget *btn_login_c = GTK_WIDGET(gtk_builder_get_object(builder,"btn_login"));
    GtkWidget *btn_register_c = GTK_WIDGET(gtk_builder_get_object(builder,"btn_register"));
    GtkWidget *btn_back_c = GTK_WIDGET(gtk_builder_get_object(builder, "btn_back"));


    g_signal_connect(btn_register_now_c, "clicked", G_CALLBACK(on_register_now_clicked_c), NULL);
    g_signal_connect(btn_login_now_c, "clicked", G_CALLBACK(on_login_now_clicked_c), NULL);
    
    g_signal_connect(btn_login_c,"clicked",G_CALLBACK(switch_to_login_c), NULL);
    g_signal_connect(btn_register_c,"clicked",G_CALLBACK(switch_to_register_c), NULL);
    g_signal_connect(btn_back_c, "clicked", G_CALLBACK(switch_to_back_c), NULL);
    // Áp dụng CSS

    gtk_widget_show_all(window_c);
    
}
