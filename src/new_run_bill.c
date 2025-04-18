#include <gtk/gtk.h>
#include <stdio.h>
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
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, 
                                              GTK_MESSAGE_INFO, GTK_BUTTONS_OK, 
                                              "Bill button clicked!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Callback for the CONFIRM button to save bill to bill.txt
static void on_confirm_bill_button_clicked(GtkButton *button, gpointer data) {
    GtkBuilder *builder = GTK_BUILDER(data);
    
    // Get label widgets
    GtkLabel *restaurant_name = GTK_LABEL(gtk_builder_get_object(builder, "restaurant_name"));
    GtkLabel *phone_contact = GTK_LABEL(gtk_builder_get_object(builder, "phone_contact"));
    GtkLabel *table_ordered = GTK_LABEL(gtk_builder_get_object(builder, "table_ordered"));
    GtkLabel *date_ordered = GTK_LABEL(gtk_builder_get_object(builder, "date_ordered"));
    GtkLabel *customer_name = GTK_LABEL(gtk_builder_get_object(builder, "customer_name"));
    GtkLabel *subtotal_bill = GTK_LABEL(gtk_builder_get_object(builder, "subtotal_bill"));
    GtkLabel *tar = GTK_LABEL(gtk_builder_get_object(builder, "tar"));
    GtkLabel *total_bill = GTK_LABEL(gtk_builder_get_object(builder, "total_bill"));
    
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
    FILE *file = fopen("bill.txt", "w");
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
    fprintf(file, "===========================\n");
    
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
    gtk_css_provider_load_from_path(provider, "Glade_CSS/edit1.css", &error);
    
    if (error != NULL) {
        g_printerr("Error loading CSS: %s\n", error->message);
        g_error_free(error);
    }
    
    g_object_unref(provider);
}

void run_bill() {
    
    // Load the Glade file
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;
    
    if (!gtk_builder_add_from_file(builder, "UI Glade/bill_layout.glade", &error)) {
        g_printerr("Error loading Glade file: %s\n", error->message);
        g_error_free(error);
        g_object_unref(builder);
        return ;
    }
    
    // Load CSS
    load_css_bill();
    
    // Get the main window
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "bill_layout"));
    
    // Connect signals
    gtk_builder_connect_signals(builder, builder);
    
    // Show the window
    gtk_widget_show_all(window);
    

    
    // Cleanup
    g_object_unref(builder);

}