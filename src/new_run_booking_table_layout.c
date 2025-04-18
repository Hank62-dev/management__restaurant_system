#include <gtk/gtk.h>
#include <string.h>

// Structure to hold application data
typedef struct {
    GtkWidget *window_booking_table;
    GtkWidget *window_bill_layout;
    GtkBuilder *builder_booking_table;
    GtkBuilder *builder_bill_layout;
    char *selected_table; // Store selected table number
} AppData;

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

// Callback for BILL button to switch to bill_layout
static void on_bill3_clicked(GtkButton *button, gpointer data) {
    AppData *app_data = (AppData *)data;
    
    // Hide booking table window
    gtk_widget_hide(app_data->window_booking_table);
    
    // Load bill_layout.glade if not already loaded
    if (!app_data->builder_bill_layout) {
        app_data->builder_bill_layout = gtk_builder_new();
        GError *error = NULL;
        
        if (!gtk_builder_add_from_file(app_data->builder_bill_layout, "UI Glade/bill_layout.glade", &error)) {
            g_printerr("Error loading bill_layout.glade: %s\n", error->message);
            g_error_free(error);
            g_object_unref(app_data->builder_bill_layout);
            return;
        }
        
        // Get bill window
        app_data->window_bill_layout = GTK_WIDGET(gtk_builder_get_object(app_data->builder_bill_layout, "bill_layout"));
        
        // Connect signals
        gtk_builder_connect_signals(app_data->builder_bill_layout, app_data);
    }
    
    // Update table_ordered label if a table is selected
    if (app_data->selected_table) {
        GtkLabel *table_ordered = GTK_LABEL(gtk_builder_get_object(app_data->builder_bill_layout, "table_ordered"));
        char *table_text = g_strdup_printf("Table: %s", app_data->selected_table);
        gtk_label_set_text(table_ordered, table_text);
        g_free(table_text);
    }
    
    // Show bill window
    gtk_widget_show_all(app_data->window_bill_layout);
}

// Callback for table buttons to store selected table number
static void on_table_clicked(GtkButton *button, gpointer data) {
    AppData *app_data = (AppData *)data;
    const gchar *label = gtk_button_get_label(button);
    
    // Free previous selected_table if exists
    if (app_data->selected_table) {
        g_free(app_data->selected_table);
    }
    
    // Store table number (extract number from "TABLE X")
    if (strcmp(label, "TABLE 1") == 0) app_data->selected_table = g_strdup("1");
    else if (strcmp(label, "TABLE 2") == 0) app_data->selected_table = g_strdup("2");
    else if (strcmp(label, "TABLE 3") == 0) app_data->selected_table = g_strdup("3");
    else if (strcmp(label, "TABLE 4") == 0) app_data->selected_table = g_strdup("4");
    else if (strcmp(label, "TABLE 5") == 0) app_data->selected_table = g_strdup("5");
    else if (strcmp(label, "TABLE 6") == 0) app_data->selected_table = g_strdup("6");
    else if (strcmp(label, "TABLE 7") == 0) app_data->selected_table = g_strdup("7");
    else if (strcmp(label, "TABLE 8") == 0) app_data->selected_table = g_strdup("8");
    
    // Show confirmation dialog
    char *message = g_strdup_printf("Selected Table: %s", app_data->selected_table);
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, 
                                              GTK_MESSAGE_INFO, GTK_BUTTONS_OK, 
                                              "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    g_free(message);
}

// Callback for CONFIRM button to switch to bill_layout
static void on_confirm_booking_table_button_clicked(GtkButton *button, gpointer data) {
    AppData *app_data = (AppData *)data;
    
    if (!app_data->selected_table) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, 
                                                  GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, 
                                                  "Please select a table first!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Call the same logic as on_bill3_clicked to switch to bill_layout
    on_bill3_clicked(button, data);
}

// Callback for confirm_bill_button in bill_layout
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
static void load_css(void) {
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

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    // Load the booking table Glade file
    GtkBuilder *builder_booking_table = gtk_builder_new();
    GError *error = NULL;
    
    if (!gtk_builder_add_from_file(builder_booking_table, "UI Glade/window_booking_table.glade", &error)) {
        g_printerr("Error loading window_booking_table.glade: %s\n", error->message);
        g_error_free(error);
        g_object_unref(builder_booking_table);
        return 1;
    }
    
    // Load CSS
    load_css();
    
    // Create AppData structure
    AppData app_data = {0};
    app_data.builder_booking_table = builder_booking_table;
    app_data.selected_table = NULL;
    
    // Get the booking table window
    app_data.window_booking_table = GTK_WIDGET(gtk_builder_get_object(builder_booking_table, "window_booking_table"));
    
    // Connect signals
    gtk_builder_connect_signals(builder_booking_table, &app_data);
    
    // Show the booking table window
    gtk_widget_show_all(app_data.window_booking_table);
    
    // Start the main loop
    gtk_main();
    
    // Cleanup
    if (app_data.selected_table) g_free(app_data.selected_table);
    if (app_data.builder_booking_table) g_object_unref(app_data.builder_booking_table);
    if (app_data.builder_bill_layout) g_object_unref(app_data.builder_bill_layout);
    
    return 0;
}