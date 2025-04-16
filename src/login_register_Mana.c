#include "utils.h"
#include "stats.h"
#include "login_register_Cus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#define DATA_FILE "data/users.txt"

GtkWidget *stack;
GtkWidget *entry_firstname, *entry_lastname, *entry_phone, *entry_password, *entry_confirm_password;
GtkWidget *entry_login_phone, *entry_login_password;
/*
//Áp dụng css
void apply_css(GtkWidget *widget, GtkCssProvider *provider) {
	
    if( gtk_css_provider_load_from_path(provider, "Glade_CSS/login_register.css", NULL) ){
    	g_print("CSS loaded successfully!!\n");
	}else{
		g_print("CSS load error!!!!\n");
	}
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    if (GTK_IS_CONTAINER(widget)) {
        gtk_container_foreach(GTK_CONTAINER(widget), (GtkCallback)apply_css, provider);
    }
}*/
// Chuyển form khi nhấn nút login/register
void switch_to_login(GtkButton *button, gpointer user_data){
	gtk_stack_set_visible_child_name(GTK_STACK(stack),"login_box");	
}
void switch_to_register(GtkButton *button, gpointer user_data){
	gtk_stack_set_visible_child_name(GTK_STACK(stack),"register_box");
}
void switch_to_login_now(GtkButton *button, gpointer user_data){
    GtkBuilder *builder = gtk_builder_new_from_file("UI Glade/UI Stats.glade");
    GtkWidget *home_window = GTK_WIDGET(gtk_builder_get_object(builder,"Revenue_window"));//id home
    gtk_widget_show_all(home_window);
    gtk_widget_hide(Login_Register_window);
}
// Lưu trữ thông tin đăng kí
void on_register_now_clicked(GtkButton *button, gpointer user_data) {
    const gchar *firstname = gtk_entry_get_text(GTK_ENTRY(entry_firstname));
    const gchar *lastname = gtk_entry_get_text(GTK_ENTRY(entry_lastname));
    const gchar *phone = gtk_entry_get_text(GTK_ENTRY(entry_phone));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry_password));
    const gchar *confirm_password = gtk_entry_get_text(GTK_ENTRY(entry_confirm_password));

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
void on_login_now_clicked(GtkButton *button, gpointer user_data) {
    const gchar *phone = gtk_entry_get_text(GTK_ENTRY(entry_login_phone));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry_login_password));
    
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
void login_register_Management(){
    GtkBuilder *builder = gtk_builder_new_from_file("UI Glade/UI Login_Register_Mana.glade");
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "Login_Register_window"));
    Login_Register_window = window;
    //resize ảnh
    GtkWidget *image = GTK_WIDGET(gtk_builder_get_object(builder,"logo_login_register"));
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("UI_image/logores.jpg", NULL);
    int width = 390, height = 390;
    pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);

    // CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "Glade_CSS/login_register.css", NULL);
    apply_css(window, provider);
    g_object_unref(provider);

    // Lấy widget
    stack = GTK_WIDGET(gtk_builder_get_object(builder, "stack_form"));
    entry_firstname = GTK_WIDGET(gtk_builder_get_object(builder, "entry_firstname"));
    entry_lastname = GTK_WIDGET(gtk_builder_get_object(builder, "entry_lastname"));
    entry_phone = GTK_WIDGET(gtk_builder_get_object(builder, "entry_phone"));
    entry_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_password"));
    entry_confirm_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_confirm_password"));
    entry_login_phone = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login_phone"));
    entry_login_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login_password"));

    GtkWidget *btn_register_now = GTK_WIDGET(gtk_builder_get_object(builder, "btn_register_now"));
    GtkWidget *btn_login_now = GTK_WIDGET(gtk_builder_get_object(builder, "btn_login_now"));
    GtkWidget *btn_login = GTK_WIDGET(gtk_builder_get_object(builder, "btn_login"));
    GtkWidget *btn_register = GTK_WIDGET(gtk_builder_get_object(builder, "btn_register"));
    GtkWidget *btn_back = GTK_WIDGET(gtk_builder_get_object(builder, "btn_back"));

    // Gắn sự kiện
    g_signal_connect(btn_register_now, "clicked", G_CALLBACK(on_register_now_clicked), NULL);
    g_signal_connect(btn_login_now, "clicked", G_CALLBACK(on_login_now_clicked), NULL);
    g_signal_connect(btn_login, "clicked", G_CALLBACK(switch_to_login), NULL);
    g_signal_connect(btn_register, "clicked", G_CALLBACK(switch_to_register), NULL);
    g_signal_connect(btn_back, "clicked", G_CALLBACK(switch_to_back), NULL);

    // Hiện cửa sổ
    gtk_widget_show_all(window);
}