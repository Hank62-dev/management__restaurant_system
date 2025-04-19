#include <gtk/gtk.h>
#include <string.h>
#include "utils.h"
#include "identification.h"
#include "login_register_Cus.h"
#include "login_register_Mana.h"
#define DATA_FILE "data/users.txt"

GtkWidget *window_identification = NULL;
GtkWidget *btn_customer = NULL;
GtkWidget *btn_management = NULL;


void show_identification() {
    GtkBuilder *builder = gtk_builder_new_from_file("UI_Glade/UI Identification.glade");
    window_identification = GTK_WIDGET(gtk_builder_get_object(builder, "identification_window"));

    GtkWidget *btn_customer = GTK_WIDGET(gtk_builder_get_object(builder, "btn_customer"));
    GtkWidget *btn_management = GTK_WIDGET(gtk_builder_get_object(builder, "btn_management"));

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "Glade_CSS/identification.css", NULL);
    apply_css(window_identification, provider);
    g_object_unref(provider);

    g_signal_connect(btn_customer, "clicked", G_CALLBACK(on_customer_clicked), NULL);
    g_signal_connect(btn_management, "clicked", G_CALLBACK(on_management_clicked), NULL);

    gtk_widget_show_all(window_identification);
    gtk_main();
}

// Khi nhấn nút Customer
void on_customer_clicked(GtkButton *button, gpointer user_data) {
    gtk_widget_hide(window_identification);
    login_register_Customer(window_identification);
  
}

// Khi nhấn Management 
void on_management_clicked(GtkButton *button, gpointer user_data) {
    gtk_widget_hide(window_identification);
    login_register_Management(window_identification);

}

