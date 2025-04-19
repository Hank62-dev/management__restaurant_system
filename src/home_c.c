#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employees.h"
#include "table_booking.h"
#include "menu_Cus.h"
#include "stats.h"
#include "total_bills.h"
#include <gtk/gtk.h>
GtkWidget *window_cus;
// Hàm khởi tạo TreeView
void setup_treeview(GtkBuilder *builder);
void apply_css_home_c(GtkWidget *widget, GtkCssProvider *provider) {
	
    if( gtk_css_provider_load_from_path(provider, "Glade_CSS/home_c.css", NULL) ){
    	g_print("CSS loaded successfully!!\n");
	}else{
		g_print("CSS load error!!!\n");
	}
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    if (GTK_IS_CONTAINER(widget)) {
        gtk_container_foreach(GTK_CONTAINER(widget), (GtkCallback)apply_css_home_c, provider);
    };
}

void on_btn_home_c_clicked(GtkWidget *widget, gpointer data){
    show_home_c();
    gtk_widget_hide(window_cus);
}
void on_btn_menu_c_clicked(GtkWidget *widget, gpointer data){
    show_Menu_Cus();
    gtk_widget_hide(window_cus);    
}
void on_btn_booking_c_clicked(GtkWidget *widget, gpointer data){
    show_booking_information();
    gtk_widget_hide(window_cus);  
}
void on_btn_orders_c_clicked(GtkWidget *widget, gpointer data){
    run_bill();
    gtk_widget_hide(window_cus);  
}


void show_home_c() {
    GtkBuilder *builder;
    GtkCssProvider *css_provider;
    GError *error = NULL;

    // Load file Glade
    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "UI_Glade/home_c.glade", &error)) {
        g_printerr("Error loading Glade: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    // Lấy các widget từ Glade
    window_cus                    = GTK_WIDGET(gtk_builder_get_object(builder, "home_c_window"));
    GtkWidget *btn_home_c     = GTK_WIDGET(gtk_builder_get_object(builder, "btn_home_c"));
    GtkWidget *btn_menu_c     = GTK_WIDGET(gtk_builder_get_object(builder, "btn_menu_c"));
    GtkWidget *btn_booking_c    = GTK_WIDGET(gtk_builder_get_object(builder, "btn_booking_c"));
    GtkWidget *btn_orders_c   = GTK_WIDGET(gtk_builder_get_object(builder, "btn_orders_c"));

    if (!window_cus) {
        g_printerr("Cannot find 'home_c_window' in Glade.\n");
        return;
    }

    // Gán CSS (nếu có)
    css_provider = gtk_css_provider_new();
    apply_css_home_c(window_cus, css_provider); 
    g_object_unref(css_provider);

    gtk_style_context_add_class(gtk_widget_get_style_context(btn_home_c), "btn_home_c");
    gtk_style_context_add_class(gtk_widget_get_style_context(btn_menu_c), "btn_menu_c");
    gtk_style_context_add_class(gtk_widget_get_style_context(btn_booking_c), "btn_booking_c");
    gtk_style_context_add_class(gtk_widget_get_style_context(btn_orders_c), "btn_orders_c");

    
    g_signal_connect(btn_home_c,"clicked", G_CALLBACK(on_btn_home_c_clicked), NULL);
    g_signal_connect(btn_menu_c,"clicked", G_CALLBACK(on_btn_menu_c_clicked), NULL);
    g_signal_connect(btn_booking_c,"clicked", G_CALLBACK(on_btn_booking_c_clicked), NULL);
    g_signal_connect(btn_orders_c,"clicked", G_CALLBACK(on_btn_orders_c_clicked), NULL);
    

    gtk_widget_show_all(window_cus);
    g_object_unref(builder);
}