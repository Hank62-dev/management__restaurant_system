#include <gtk/gtk.h>
#include <stdio.h>
#include "table_booking.h"
<<<<<<< HEAD
=======
=======
#include <time.h>
#include <string.h>
#include "table_booking.h"

<<<<<<< HEAD
void load_css_bill(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GError *error = NULL;
    gtk_css_provider_load_from_path(provider, "style.css", &error);

    if (error != NULL)
    {
        g_printerr("Error loading CSS: %s\n", error->message);
        g_error_free(error);
    }

    g_object_unref(provider);
=======
>>>>>>> f1597c89f266a29ef1d0c4493895974cdfe156de
>>>>>>> 53b11d80021a4a360f91ed4760b60051ca69d9ef
// Callback functions for navigation buttons
static void on_home3_clicked(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, 
                                              GTK_MESSAGE_INFO, GTK_BUTTONS_OK, 
                                              "Home button clicked!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
>>>>>>> e5961ab5687db564333e30ce2ef2b6150e0397a9
}

static void on_confirm_bill_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = GTK_WIDGET(user_data);

    // Open file to write bill
    FILE *file = fopen("bill.txt", "a");
    if (file == NULL)
    {
        g_printerr("Error opening bill.txt\n");
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), 
                                                  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
                                                  GTK_MESSAGE_ERROR, 
                                                  GTK_BUTTONS_OK, 
                                                  "Cannot open bill.txt for writing!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

<<<<<<< HEAD
    // Get current date for the bill
=======
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
    app_data->builder_bill_layout = gtk_builder_new();
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
>>>>>>> e5961ab5687db564333e30ce2ef2b6150e0397a9
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date_str[11];
    strftime(date_str, sizeof(date_str), "%Y-%m-%d", t);

    // Write bill details to file
    fprintf(file, "===== Bill =====\n");

    // Read temp_data.txt to write to bill
    FILE *temp_file = fopen("temp_data.txt", "r");
    if (temp_file == NULL)
    {
        g_printerr("Error opening temp_data.txt\n");
        fprintf(file, "No customer data available.\n");
    }
    else
    {
        char line[256];
        while (fgets(line, sizeof(line), temp_file))
        {
            fprintf(file, "%s", line);
        }
        fclose(temp_file);
    }

    fprintf(file, "Bill Date: %s\n", date_str);
    fprintf(file, "Items:\n");

    // Read orders.txt to write items, calculate subtotal, tax, and total
    double subtotal = 0.0;
    FILE *orders_file = fopen("orders.txt", "r");
    if (orders_file == NULL)
    {
        g_printerr("Error opening orders.txt\n");
        fprintf(file, "No order data available.\n");
    }
    else
    {
        char line[256];
        while (fgets(line, sizeof(line), orders_file))
        {
            char item_code[16], item_name[64];
            int quantity;
            double total_price;

            // Parse each line: item_code item_name quantity total_price
            if (sscanf(line, "%s %s %d %lf", item_code, item_name, &quantity, &total_price) == 4)
            {
                fprintf(file, "Item: %s %s, Quantity: %d, Total: %.2f\n", item_code, item_name, quantity, total_price);
                subtotal += total_price;
            }
        }
        fclose(orders_file);
    }
<<<<<<< HEAD

    // Calculate tax (10% of subtotal) and total
    double tax = subtotal * 0.10;
    double total = subtotal + tax;

    fprintf(file, "Subtotal: %.2f\n", subtotal);
    fprintf(file, "Tax: %.2f\n", tax);
    fprintf(file, "Total: %.2f\n", total);
    fprintf(file, "================\n\n");
    fclose(file);

    // Hide current window
    gtk_widget_hide(window);
}

void run_bill()
{
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    if (!gtk_builder_add_from_file(builder, "bill_layout.glade", &error))
    {
        g_printerr("Error loading file: %s\n", error->message);
        GtkWidget *dialog = gtk_message_dialog_new(NULL, 
                                                  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
                                                  GTK_MESSAGE_ERROR, 
                                                  GTK_BUTTONS_OK, 
                                                  "Cannot load bill_layout.glade!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        g_error_free(error);
        return;
    }

    load_css_bill();

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "bill_layout"));

    // Read temp_data.txt to set labels
    FILE *temp_file = fopen("temp_data.txt", "r");
    if (temp_file == NULL)
    {
        g_printerr("Error opening temp_data.txt\n");
        GtkLabel *customer_name_label = GTK_LABEL(gtk_builder_get_object(builder, "customer_name"));
        gtk_label_set_text(customer_name_label, "Customer: N/A");
        GtkLabel *date_ordered = GTK_LABEL(gtk_builder_get_object(builder, "date_ordered"));
        gtk_label_set_text(date_ordered, "Date: N/A");
        GtkLabel *table_ordered = GTK_LABEL(gtk_builder_get_object(builder, "table_ordered"));
        gtk_label_set_text(table_ordered, "Table: N/A");
    }
    else
    {
        char line[256];
        char ordered_date[256] = "Date: N/A";
        while (fgets(line, sizeof(line), temp_file))
        {
            if (strncmp(line, "Name:", 5) == 0)
            {
                GtkLabel *customer_name_label = GTK_LABEL(gtk_builder_get_object(builder, "customer_name"));
                gtk_label_set_text(customer_name_label, line);
            }
            if (strncmp(line, "Date:", 5) == 0)
            {
                strncpy(ordered_date, line, sizeof(ordered_date) - 1);
                ordered_date[sizeof(ordered_date) - 1] = '\0';
            }
            if (strncmp(line, "Table:", 6) == 0)
            {
                GtkLabel *table_ordered = GTK_LABEL(gtk_builder_get_object(builder, "table_ordered"));
                gtk_label_set_text(table_ordered, line);
            }
        }
        fclose(temp_file);

        // Set ordered date
        GtkLabel *date_label = GTK_LABEL(gtk_builder_get_object(builder, "date_ordered"));
        gtk_label_set_text(date_label, ordered_date);
    }

    // Read orders.txt to display items in bill_information label and calculate subtotal, tax, and total
    double subtotal = 0.0;
    GString *items_text = g_string_new("Items:\n");
    FILE *orders_file = fopen("orders.txt", "r");
    if (orders_file == NULL)
    {
        g_printerr("Error opening orders.txt\n");
        g_string_append(items_text, "No order data available.\n");
    }
    else
    {
        char line[256];
        while (fgets(line, sizeof(line), orders_file))
        {
            char item_code[16], item_name[64];
            int quantity;
            double total_price;

            // Parse each line: item_code item_name quantity total_price
            if (sscanf(line, "%s %s %d %lf", item_code, item_name, &quantity, &total_price) == 4)
            {
                g_string_append_printf(items_text, "%s %s, Quantity: %d\n", item_code, item_name, quantity);
                subtotal += total_price;
            }
        }
        fclose(orders_file);
    }

    // Display items in bill_information label
    GtkLabel *bill_info_label = GTK_LABEL(gtk_builder_get_object(builder, "bill_information"));
    gtk_label_set_text(bill_info_label, items_text->str);
    g_string_free(items_text, TRUE);

    // Calculate tax (10% of subtotal) and total
    double tax = subtotal * 0.10;
    double total = subtotal + tax;

    // Set labels for subtotal, tax, and total
    GtkLabel *subtotal_label = GTK_LABEL(gtk_builder_get_object(builder, "subtotal_bill"));
    char subtotal_text[32];
    snprintf(subtotal_text, sizeof(subtotal_text), "Subtotal: %.2f", subtotal);
    gtk_label_set_text(subtotal_label, subtotal_text);

    GtkLabel *tax_label = GTK_LABEL(gtk_builder_get_object(builder, "tar"));
    char tax_text[32];
    snprintf(tax_text, sizeof(tax_text), "Tax: %.2f", tax);
    gtk_label_set_text(tax_label, tax_text);

    GtkLabel *total_label = GTK_LABEL(gtk_builder_get_object(builder, "total_bill"));
    char total_text[32];
    snprintf(total_text, sizeof(total_text), "Total: %.2f", total);
    gtk_label_set_text(total_label, total_text);

    // Set current date on the bill (as Bill Date)
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date_str[11];
    strftime(date_str, sizeof(date_str), "%Y-%m-%d", t);
    GtkLabel *date_label = GTK_LABEL(gtk_builder_get_object(builder, "date_ordered"));
    char *current_date_text = g_strdup_printf("%sBill Date: %s", gtk_label_get_text(date_label), date_str);
    gtk_label_set_text(date_label, current_date_text);
    g_free(current_date_text);

    g_signal_connect(gtk_builder_get_object(builder, "confirm_bill_button"), "clicked", G_CALLBACK(on_confirm_bill_button_clicked), window);

    gtk_widget_show_all(window);
=======
    
    // Show the window
    gtk_widget_show_all(window);
    

    
    // Cleanup
    g_object_unref(builder);

<<<<<<< HEAD
=======
=======
    gtk_widget_show_all(app_data->window_bill_layout);
>>>>>>> f1597c89f266a29ef1d0c4493895974cdfe156de
>>>>>>> e5961ab5687db564333e30ce2ef2b6150e0397a9
>>>>>>> 53b11d80021a4a360f91ed4760b60051ca69d9ef
}