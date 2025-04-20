#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "table_booking.h"

void load_css_layout(void);

static char *selected_table = NULL;

static void table_button_toggled(GtkToggleButton *button, gpointer user_data)
{
    if (gtk_toggle_button_get_active(button))
    {
        selected_table = (char *)g_object_get_data(G_OBJECT(button), "table_number");
    }
}

static void on_confirm_booking_table_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = GTK_WIDGET(user_data);

    if (!selected_table)
    {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), 
                                                  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
                                                  GTK_MESSAGE_ERROR, 
                                                  GTK_BUTTONS_OK, 
                                                  "Please select a table first!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Check if temp_data.txt exists
    FILE *check_file = fopen("data/temp_data.txt", "r");
    if (check_file == NULL)
    {
        g_printerr("Error: temp_data.txt does not exist\n");
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), 
                                                  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
                                                  GTK_MESSAGE_ERROR, 
                                                  GTK_BUTTONS_OK, 
                                                  "Booking information not found! Please complete the booking information first.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    fclose(check_file);

    FILE *file = fopen("data/temp_data.txt", "a");
    if (file == NULL)
    {
        g_printerr("Error opening temp_data.txt: %s\n", strerror(errno));
        char error_msg[512];
        snprintf(error_msg, sizeof(error_msg), "Cannot open temp_data.txt for writing: %s", strerror(errno));
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), 
                                                  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
                                                  GTK_MESSAGE_ERROR, 
                                                  GTK_BUTTONS_OK, 
                                                  "%s", error_msg);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    fprintf(file, "Table: %s\n", selected_table);
    fclose(file);

    gtk_widget_hide(window);

    // Open the bill layout window
    run_bill();
}

void book_table_show()
{
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    if (!gtk_builder_add_from_file(builder, "UI Glade/window_booking_table.glade", &error))
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_error_free(error);
        return;
    }

    load_css_layout();

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window_booking_table"));

    // Connect toggle buttons for table selection
    char table_numbers[][3] = {"1", "2", "3", "4", "5", "6"};
    for (int i = 0; i < 6; i++)
    {
        char button_id[32];
        snprintf(button_id, sizeof(button_id), "table_%s", table_numbers[i]);
        GtkToggleButton *button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, button_id));
        g_object_set_data(G_OBJECT(button), "table_number", table_numbers[i]);
        g_signal_connect(button, "toggled", G_CALLBACK(table_button_toggled), NULL);
    }

    g_signal_connect(gtk_builder_get_object(builder, "confirm_booking_table_button"), "clicked", G_CALLBACK(on_confirm_booking_table_button_clicked), window);

    gtk_widget_show_all(window);
}