#include <gtk/gtk.h>
#include <string.h>
#include "table_booking.h"

// Callback functions for navigation buttons
static void on_home3_clicked(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, 
                                              GTK_MESSAGE_INFO, GTK_BUTTONS_OK, 
                                              "Home button clicked!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void on_menu3_clicked(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, 
                                              GTK_MESSAGE_INFO, GTK_BUTTONS_OK, 
                                              "Menu button clicked!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void on_booking3_clicked(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, 
                                              GTK_MESSAGE_INFO, GTK_BUTTONS_OK, 
                                              "Booking button clicked!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void on_bill3_clicked(GtkButton *button, gpointer data) {
    AppData *app_data = (AppData *)data;
    gtk_widget_hide(app_data->window_booking_information);
    run_bill(app_data);
}

// Callback for BOOK TABLE HERE button to switch to window_booking_table
static void on_button_booking_table_clicked(GtkButton *button, gpointer data) {
    AppData *app_data = (AppData *)data;
    
    // Get entry widgets
    GtkEntry *entry_name = GTK_ENTRY(gtk_builder_get_object(app_data->builder_booking_information, "enter_name"));
    GtkEntry *entry_date = GTK_ENTRY(gtk_builder_get_object(app_data->builder_booking_information, "enter_date"));
    GtkEntry *entry_phone = GTK_ENTRY(gtk_builder_get_object(app_data->builder_booking_information, "enter_phone"));
    GtkEntry *entry_time = GTK_ENTRY(gtk_builder_get_object(app_data->builder_booking_information, "enter_time"));
    GtkEntry *entry_guests = GTK_ENTRY(gtk_builder_get_object(app_data->builder_booking_information, "enter_number_of_guest"));
    
    // Get text from entries
    const gchar *name = gtk_entry_get_text(entry_name);
    const gchar *date = gtk_entry_get_text(entry_date);
    const gchar *phone = gtk_entry_get_text(entry_phone);
    const gchar *time = gtk_entry_get_text(entry_time);
    const gchar *guests = gtk_entry_get_text(entry_guests);
    
    // Store booking details
    if (app_data->name) g_free(app_data->name);
    if (app_data->date) g_free(app_data->date);
    if (app_data->phone) g_free(app_data->phone);
    if (app_data->time) g_free(app_data->time);
    if (app_data->guests) g_free(app_data->guests);
    
    app_data->name = g_strdup(name);
    app_data->date = g_strdup(date);
    app_data->phone = g_strdup(phone);
    app_data->time = g_strdup(time);
    app_data->guests = g_strdup(guests);
    
    // Validate input
    if (strlen(name) == 0 || strlen(date) == 0 || strlen(phone) == 0 || 
        strlen(time) == 0 || strlen(guests) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, 
                                                  GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, 
                                                  "Please fill in all booking details!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Hide booking information window
    gtk_widget_hide(app_data->window_booking_information);
    
    // Show booking table window
    book_table_show(app_data);
}

// Function to load CSS
static void load_css_information(void) {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    
    gtk_style_context_add_provider_for_screen(screen, 
                                             GTK_STYLE_PROVIDER(provider), 
                                             GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    GError *error = NULL;
    gtk_css_provider_load_from_path(provider, "style.css", &error);
    
    if (error != NULL) {
        g_printerr("Error loading CSS: %s\n", error->message);
        g_error_free(error);
    }
    
    g_object_unref(provider);
}

void show_booking_information(AppData *app_data) {
    // Load the booking information Glade file
    app_data->builder_booking_information = gtk_builder_new();
    GError *error = NULL;
    
    if (!gtk_builder_add_from_file(app_data->builder_booking_information, "window_booking_information.glade", &error)) {
        g_printerr("Error loading window_booking_information.glade: %s\n", error->message);
        g_error_free(error);
        g_object_unref(app_data->builder_booking_information);
        return;
    }
    
    // Load CSS
    load_css_information();
    
    // Get the booking information window
    app_data->window_booking_information = GTK_WIDGET(gtk_builder_get_object(app_data->builder_booking_information, "window_booking_information"));
    
    // Connect signals
    gtk_builder_connect_signals(app_data->builder_booking_information, app_data);
    
    // Show the booking information window
    gtk_widget_show_all(app_data->window_booking_information);
}