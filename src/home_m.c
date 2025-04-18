#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employees.h"
#include <gtk/gtk.h>

// Hàm khởi tạo TreeView
void setup_treeview(GtkBuilder *builder);
void apply_css_home_m(GtkWidget *widget, GtkCssProvider *provider) {
	
    if( gtk_css_provider_load_from_path(provider, "Glade_CSS/home_m.css", NULL) ){
    	g_print("CSS loaded successfully!!\n");
	}else{
		g_print("CSS load error!!!\n");
	}
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    if (GTK_IS_CONTAINER(widget)) {
        gtk_container_foreach(GTK_CONTAINER(widget), (GtkCallback)apply_css_home_m, provider);
    };
}
    void show_home_m () {
        GtkWidget *home_m_window;
        GtkBuilder *builder;
        GtkCssProvider *css_provider;
        GError *error = NULL;
    
        // Load file Glade
        builder = gtk_builder_new();
        if (!gtk_builder_add_from_file(builder, "UI_Glade/home_m.glade", &error)) {
            g_printerr(" Error loading Glade: %s\n", error->message);
            g_clear_error(&error);
            return;
        }
            GtkWidget *overlay_1 = gtk_overlay_new();
            GtkWidget *image_1 = gtk_image_new_from_file("UI_image/bg.jpg");
            gtk_widget_set_halign(image_1, GTK_ALIGN_FILL);
            gtk_widget_set_valign(image_1, GTK_ALIGN_FILL);
            gtk_overlay_add_overlay(GTK_OVERLAY(overlay_1), image_1);
       
    
        // Lấy widget
        GtkWidget *window         = GTK_WIDGET(gtk_builder_get_object(builder, "home_m_window"));
        GtkWidget *btn_home_m     = GTK_WIDGET(gtk_builder_get_object(builder, "btn_home_m"));
        GtkWidget *btn_menu_m     = GTK_WIDGET(gtk_builder_get_object(builder, "btn_menu_m"));
        GtkWidget *btn_stats_m    = GTK_WIDGET(gtk_builder_get_object(builder, "btn_stats_m"));
        GtkWidget *btn_employee_m = GTK_WIDGET(gtk_builder_get_object(builder, "btn_employee_m"));
        GtkWidget *btn_orders_m   = GTK_WIDGET(gtk_builder_get_object(builder, "btn_orders_m"));
    
        if (!window) {
            g_printerr(" Cant find 'home_m_window' in Glade.\n");
            return;
        }

        gtk_style_context_add_class(gtk_widget_get_style_context(btn_home_m), "btn_home_m");
        gtk_style_context_add_class(gtk_widget_get_style_context(btn_menu_m), "btn_menu_m");
        gtk_style_context_add_class(gtk_widget_get_style_context(btn_stats_m), "btn_stats_m");
        gtk_style_context_add_class(gtk_widget_get_style_context(btn_employee_m), "btn_employee_m");
        gtk_style_context_add_class(gtk_widget_get_style_context(btn_orders_m), "btn_orders_m");

        /*g_signal_connect(btn_home_m,     "clicked", G_CALLBACK(on_btn_home_m_clicked), NULL);
        g_signal_connect(btn_menu_m,     "clicked", G_CALLBACK(on_btn_menu_m_clicked), NULL);
        g_signal_connect(btn_stats_m,    "clicked", G_CALLBACK(on_btn_stats_m_clicked), NULL);
        g_signal_connect(btn_employee_m, "clicked", G_CALLBACK(on_btn_employee_m_clicked), NULL);
        g_signal_connect(btn_orders_m, "clicked", G_CALLBACK(on_btn_orders_m_clicked), NULL);*/
        // Gán CSS provider

        css_provider = gtk_css_provider_new();
        apply_css_home_m(window, css_provider);
        g_object_unref(css_provider);
    
        gtk_widget_show_all(window);
        g_object_unref(builder);
    }