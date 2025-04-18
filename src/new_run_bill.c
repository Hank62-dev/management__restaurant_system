#include <gtk/gtk.h>
#include <stdio.h>
#include <time.h>
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
    AppData *app_data = (AppData *)data;
    gtk_widget_hide(app_data->window_bill_layout);
    show_booking_information(app_data);
}

// Callback for the CONFIRM button to save bill to bill.txt
static void on_confirm_bill_button_clicked(GtkButton *button, gpointer data) {
    AppData *app_data = (AppData *)data;
    
    // Get label widgets
    GtkLabel *restaurant_name = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "restaurant_name"));
    GtkLabel *phone_contact = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "phone_contact"));
    GtkLabel *table_ordered = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "table_ordered"));
    GtkLabel *date_ordered = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "date_ordered"));
    GtkLabel *customer_name = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "customer_name"));
    GtkLabel *subtotal_bill = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "subtotal_bill"));
    GtkLabel *tar = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "tar"));
    GtkLabel *total_bill = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "total_bill"));
    
    // Get text from labels
    const gchar *restaurant = gtk_label_get_text(restaurant_name);
    const gchar *phone = gtk_label_get_text(phone_contact);
    const gchar *table = gtk_label_get_text(table_ordered);
    const gchar *date = gtk_label_get_text(date_ordered);
    const gchar *customer = gtk_label_get_text(customer_name);
    const gchar *subtotal = gtk_label_get_text(subtotal_bill);
    const gchar *tax = gtk_label_get_text(tar);
    const gchar *total = gtk_label_get_text(total_bill);
    
    // Open file to write bill details
    FILE *file = fopen("bill.txt", "a"); // Append mode to keep history
    if (file == NULL) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, 
                                                  GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, 
                                                  "Error: Could not open bill.txt for writing!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Write bill details to file
    fprintf(file, "===== Bill Information =====\n\n");
    fprintf(file, "Restaurant: %s\n", restaurant);
    fprintf(file, "Phone: %s\n", phone);
    fprintf(file, "Table: %s\n", table);
    fprintf(file, "Date: %s\n", date);
    fprintf(file, "Customer: %s\n", customer);
    fprintf(file, "Subtotal: %s\n", subtotal);
    fprintf(file, "Tax: %s\n", tax);
    fprintf(file, "Total: %s\n", total);
    fprintf(file, "===========================\n\n");
    
    // Close the file
    fclose(file);
    
    // Show confirmation dialog
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, 
                                              GTK_MESSAGE_INFO, GTK_BUTTONS_OK, 
                                              "Bill saved to bill.txt successfully!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Function to load CSS
static void load_css_bill(void) {
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

void run_bill(AppData *app_data) {
    // Load the Glade file
    app_data->builder_bill_layout = gtk_builder_new();
    GError *error = NULL;
    
    if (!gtk_builder_add_from_file(app_data->builder_bill_layout, "bill_layout.glade", &error)) {
        g_printerr("Error loading bill_layout.glade: %s\n", error->message);
        g_error_free(error);
        g_object_unref(app_data->builder_bill_layout);
        return;
    }
    
    // Load CSS
    load_css_bill();

    // Get the main window
    app_data->window_bill_layout = GTK_WIDGET(gtk_builder_get_object(app_data->builder_bill_layout, "bill_layout"));
    
    // Connect signals
    gtk_builder_connect_signals(app_data->builder_bill_layout, app_data);
    
    // Update labels with data from AppData
    if (app_data->selected_table) {
        GtkLabel *table_ordered = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "table_ordered"));
        char *table_text = g_strdup_printf("Table: %s", app_data->selected_table);
        gtk_label_set_text(table_ordered, table_text);
        g_free(table_text);
    }
    if (app_data->name) {
        GtkLabel *customer_name = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "customer_name"));
        char *customer_text = g_strdup_printf("Customer: %s", app_data->name);
        gtk_label_set_text(customer_name, customer_text);
        g_free(customer_text);
    }
    
    // Set current date
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    char date_str[20];
    strftime(date_str, sizeof(date_str), "%d/%m/%Y", tm);
    GtkLabel *date_ordered = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "date_ordered"));
    gtk_label_set_text(date_ordered, date_str);
    
    // Read from orders.txt (assuming format: Subtotal: X, Tax: Y, Total: Z)
    FILE *file = fopen("orders.txt", "r");
    if (file) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, "Subtotal:")) {
                char *value = strchr(line, ':') + 2;
                value[strcspn(value, "\n")] = 0;
                char *subtotal_text = g_strdup_printf("Subtotal: %s", value);
                GtkLabel *subtotal_bill = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "subtotal_bill"));
                gtk_label_set_text(subtotal_bill, subtotal_text);
                g_free(subtotal_text);
            } else if (strstr(line, "Tax:")) {
                char *value = strchr(line, ':') + 2;
                value[strcspn(value, "\n")] = 0;
                char *tax_text = g_strdup_printf("Tax: %s", value);
                GtkLabel *tar = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "tar"));
                gtk_label_set_text(tar, tax_text);
                g_free(tax_text);
            } else if (strstr(line, "Total:")) {
                char *value = strchr(line, ':') + 2;
                value[strcspn(value, "\n")] = 0;
                char *total_text = g_strdup_printf("Total: %s", value);
                GtkLabel *total_bill = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "total_bill"));
                gtk_label_set_text(total_bill, total_text);
                g_free(total_text);
            }
        }
        fclose(file);
    }
    
    // Show the window
    gtk_widget_show_all(app_data->window_bill_layout);
}