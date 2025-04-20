#include <gtk/gtk.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "table_booking.h"

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
}

static void on_confirm_bill_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = GTK_WIDGET(user_data);

    // Open file to write bill
    FILE *file = fopen("view_bill.txt", "a");
    if (file == NULL)
    {
        g_printerr("Error opening view_bill.txt: %s\n", strerror(errno));
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), 
                                                  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
                                                  GTK_MESSAGE_ERROR, 
                                                  GTK_BUTTONS_OK, 
                                                  "Cannot open view_bill.txt for writing!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Calculate STT by counting existing bills in view_bill.txt
    int stt = 1;
    FILE *count_file = fopen("view_bill.txt", "r");
    if (count_file != NULL)
    {
        char line[256];
        while (fgets(line, sizeof(line), count_file))
        {
            stt++;
        }
        fclose(count_file);
    }

    // Get customer name and booking date from temp_data.txt
    char customer_name[256] = "N/A";
    char booking_date[256] = "N/A";
    char formatted_date[11] = "N/A";
    FILE *temp_file = fopen("temp_data.txt", "r");
    if (temp_file != NULL)
    {
        char line[256];
        while (fgets(line, sizeof(line), temp_file))
        {
            if (strncmp(line, "Name:", 5) == 0)
            {
                strncpy(customer_name, line + 6, sizeof(customer_name) - 1);
                customer_name[sizeof(customer_name) - 1] = '\0';
                customer_name[strcspn(customer_name, "\n")] = '\0';
            }
            else if (strncmp(line, "Date:", 5) == 0)
            {
                strncpy(booking_date, line + 6, sizeof(booking_date) - 1);
                booking_date[sizeof(booking_date) - 1] = '\0';
                booking_date[strcspn(booking_date, "\n")] = '\0';
                int year, month, day;
                if (sscanf(booking_date, "%d-%d-%d", &year, &month, &day) == 3)
                {
                    snprintf(formatted_date, sizeof(formatted_date), "%02d/%02d/%04d", day, month, year);
                }
            }
        }
        fclose(temp_file);
    }

    // Calculate total from orders.txt
    double subtotal = 0.0;
    FILE *orders_file = fopen("orders.txt", "r");
    if (orders_file != NULL)
    {
        char line[256];
        while (fgets(line, sizeof(line), orders_file))
        {
            char item_code[16], item_name[64];
            int quantity;
            double total_price;

            if (sscanf(line, "%s %s %d %lf", item_code, item_name, &quantity, &total_price) == 4)
            {
                subtotal += total_price;
            }
        }
        fclose(orders_file);
    }

    double tax = subtotal * 0.10;
    double total = subtotal + tax;

    // Write to view_bill.txt in the required format: stt tên_khách ngày_đặt tổng_tiền
    fprintf(file, "%d %s %s %.0f\n", stt, customer_name, formatted_date, total);
    fclose(file);

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

    // Check if temp_data.txt exists and has data
    FILE *temp_file = fopen("temp_data.txt", "r");
    int has_name = 0, has_date = 0;
    if (temp_file == NULL)
    {
        g_printerr("Error opening temp_data.txt\n");
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), 
                                                  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
                                                  GTK_MESSAGE_ERROR, 
                                                  GTK_BUTTONS_OK, 
                                                  "No booking data found! Please complete the booking process first.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        gtk_widget_destroy(window);
        return;
    }
    else
    {
        char line[256];
        while (fgets(line, sizeof(line), temp_file))
        {
            if (strncmp(line, "Name:", 5) == 0 && strlen(line) > 6 && line[6] != '\n')
            {
                has_name = 1;
            }
            if (strncmp(line, "Date:", 5) == 0 && strlen(line) > 6 && line[6] != '\n')
            {
                has_date = 1;
            }
        }
        fclose(temp_file);
        if (!has_name || !has_date)
        {
            g_printerr("Missing Name or Date in temp_data.txt\n");
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), 
                                                      GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
                                                      GTK_MESSAGE_ERROR, 
                                                      GTK_BUTTONS_OK, 
                                                      "Missing Name or Date! Please complete the booking process with valid data.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            gtk_widget_destroy(window);
            return;
        }
    }

    // Check if orders.txt exists and has data
    FILE *orders_file = fopen("orders.txt", "r");
    int has_items = 0;
    if (orders_file == NULL)
    {
        g_printerr("Error opening orders.txt\n");
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), 
                                                  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
                                                  GTK_MESSAGE_ERROR, 
                                                  GTK_BUTTONS_OK, 
                                                  "No order data found! Please add items to the order first.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        gtk_widget_destroy(window);
        return;
    }
    else
    {
        char line[256];
        while (fgets(line, sizeof(line), orders_file))
        {
            char item_code[16], item_name[64];
            int quantity;
            double total_price;

            if (sscanf(line, "%s %s %d %lf", item_code, item_name, &quantity, &total_price) == 4)
            {
                has_items = 1;
                break;
            }
        }
        fclose(orders_file);
        if (!has_items)
        {
            g_printerr("No valid items in orders.txt\n");
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), 
                                                      GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
                                                      GTK_MESSAGE_ERROR, 
                                                      GTK_BUTTONS_OK, 
                                                      "No valid items found in orders.txt! Please add items to the order.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            gtk_widget_destroy(window);
            return;
        }
    }

    // Initialize labels with default values
    GtkLabel *customer_name_label = GTK_LABEL(gtk_builder_get_object(builder, "customer_name"));
    gtk_label_set_text(customer_name_label, "Customer's name: N/A");
    GtkLabel *date_ordered = GTK_LABEL(gtk_builder_get_object(builder, "date_ordered"));
    gtk_label_set_text(date_ordered, "Date: N/A");
    GtkLabel *table_ordered = GTK_LABEL(gtk_builder_get_object(builder, "table_ordered"));
    gtk_label_set_text(table_ordered, "Table: N/A");

    // Read temp_data.txt to set labels
    temp_file = fopen("temp_data.txt", "r");
    char customer_name[256] = "N/A";
    char booking_date[256] = "N/A";
    char table_number[256] = "N/A";
    if (temp_file != NULL)
    {
        char line[256];
        while (fgets(line, sizeof(line), temp_file))
        {
            if (strncmp(line, "Name:", 5) == 0)
            {
                strncpy(customer_name, line + 6, sizeof(customer_name) - 1);
                customer_name[sizeof(customer_name) - 1] = '\0';
                customer_name[strcspn(customer_name, "\n")] = '\0';
                char display_name[256];
                snprintf(display_name, sizeof(display_name), "Customer's name: %s", customer_name);
                gtk_label_set_text(customer_name_label, display_name);
            }
            if (strncmp(line, "Date:", 5) == 0)
            {
                strncpy(booking_date, line + 6, sizeof(booking_date) - 1);
                booking_date[sizeof(booking_date) - 1] = '\0';
                booking_date[strcspn(booking_date, "\n")] = '\0';
                char display_date[256];
                snprintf(display_date, sizeof(display_date), "Date: %s", booking_date);
                gtk_label_set_text(date_ordered, display_date);
            }
            if (strncmp(line, "Table:", 6) == 0)
            {
                strncpy(table_number, line + 7, sizeof(table_number) - 1);
                table_number[sizeof(table_number) - 1] = '\0';
                table_number[strcspn(table_number, "\n")] = '\0';
                char display_table[256];
                snprintf(display_table, sizeof(display_table), "Table: %s", table_number);
                gtk_label_set_text(table_ordered, display_table);
            }
        }
        fclose(temp_file);
    }

    // Read orders.txt to display items in bill_information label and calculate subtotal, tax, and total
    double subtotal = 0.0;
    GString *items_text = g_string_new("Items:\n");
    orders_file = fopen("orders.txt", "r");
    if (orders_file != NULL)
    {
        char line[256];
        while (fgets(line, sizeof(line), orders_file))
        {
            char item_code[16], item_name[64];
            int quantity;
            double total_price;

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
    char display_date[256];
    snprintf(display_date, sizeof(display_date), "%s\nBill Date: %s", gtk_label_get_text(date_ordered), date_str);
    gtk_label_set_text(date_ordered, display_date);

    g_signal_connect(gtk_builder_get_object(builder, "confirm_bill_button"), "clicked", G_CALLBACK(on_confirm_bill_button_clicked), window);

    gtk_widget_show_all(window);
}