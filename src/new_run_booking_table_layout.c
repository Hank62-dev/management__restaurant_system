/*#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "table_booking.h"

static char *selected_table = NULL;

void load_css_layout(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GError *error = NULL;
    gtk_css_provider_load_from_path(provider, "Glade_CSS/style.css", &error);

    if (error != NULL)
    {
        g_printerr("Error loading CSS: %s\n", error->message);
        g_error_free(error);
    }

    g_object_unref(provider);
}

static void on_table_clicked(GtkToggleButton *button, gpointer user_data)
{
    // Only process if the button is active
    if (!gtk_toggle_button_get_active(button))
    {
        return;
    }

    GtkBuilder *builder = (GtkBuilder *)user_data;
    const gchar *label = gtk_button_get_label(GTK_BUTTON(button));

    // Free previous selected_table if exists
    if (selected_table)
    {
        g_free(selected_table);
        selected_table = NULL;
    }

    // Store table number (extract number from "TABLE X")
    if (strcmp(label, "TABLE 1") == 0) selected_table = g_strdup("1");
    else if (strcmp(label, "TABLE 2") == 0) selected_table = g_strdup("2");
    else if (strcmp(label, "TABLE 3") == 0) selected_table = g_strdup("3");
    else if (strcmp(label, "TABLE 4") == 0) selected_table = g_strdup("4");
    else if (strcmp(label, "TABLE 5") == 0) selected_table = g_strdup("5");
    else if (strcmp(label, "TABLE 6") == 0) selected_table = g_strdup("6");
    else if (strcmp(label, "TABLE 7") == 0) selected_table = g_strdup("7");
    else if (strcmp(label, "TABLE 8") == 0) selected_table = g_strdup("8");

    // Deactivate other table buttons
    for (int i = 1; i <= 8; i++)
    {
        char table_id[16];
        snprintf(table_id, sizeof(table_id), "table%d", i);
        GtkToggleButton *other_button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, table_id));
        if (other_button != button)
        {
            gtk_toggle_button_set_active(other_button, FALSE);
        }
    }

    g_print("Table clicked: %s\n", label);
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

    // Update temp_data.txt with selected table
    FILE *file = fopen("data/temp_data.txt", "w");
    if (file == NULL)
    {
        g_printerr("Error opening temp_data.txt\n");
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), 
                                                  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
                                                  GTK_MESSAGE_ERROR, 
                                                  GTK_BUTTONS_OK, 
                                                  "Cannot open temp_data.txt for writing!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    fprintf(file, "Table: %s\n", selected_table);
    fclose(file);
 
    // Hide current window
    gtk_widget_hide(window);
}

void book_table_show()
{
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    if (!gtk_builder_add_from_file(builder, "UI Glade/window_booking_table.glade", &error))
    {
        g_printerr("Error loading file: %s\n", error->message);
        GtkWidget *dialog = gtk_message_dialog_new(NULL, 
                                                  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
                                                  GTK_MESSAGE_ERROR, 
                                                  GTK_BUTTONS_OK, 
                                                  "Cannot load window_booking_table.glade!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        g_error_free(error);
        return;
    }

    load_css_layout();

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window_booking_table"));
    g_object_set_data(G_OBJECT(window), "builder", builder); // Store builder for access in callback
    g_signal_connect(gtk_builder_get_object(builder, "confirm_booking_table_button"), "clicked", G_CALLBACK(on_confirm_booking_table_button_clicked), window);

    // Connect toggle signals for table buttons
    for (int i = 1; i <= 8; i++)
    {
        char table_id[16];
        snprintf(table_id, sizeof(table_id), "table%d", i);
        g_signal_connect(gtk_builder_get_object(builder, table_id), "toggled", G_CALLBACK(on_table_clicked), builder);
    }

    gtk_widget_show_all(window);
}*/



/*
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "table_booking.h"

void load_css_layout(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GError *error = NULL;
    gtk_css_provider_load_from_path(provider, "Glade_CSS/style.css", &error);

    if (error != NULL)
    {
        g_printerr("Error loading CSS: %s\n", error->message);
        g_error_free(error);
    }

    g_object_unref(provider);
}

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
}*/






#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "table_booking.h"

static char *selected_table = NULL;

void load_css_layout() {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GError *error = NULL;
    gtk_css_provider_load_from_path(provider, "Glade_CSS/style.css", &error);
    if (error) {
        g_printerr("Error loading CSS: %s\n", error->message);
        g_error_free(error);
    }
    g_object_unref(provider);
}

static void on_table_clicked(GtkToggleButton *button, gpointer user_data) {
    if (!gtk_toggle_button_get_active(button)) return;

    GtkBuilder *builder = GTK_BUILDER(user_data);
    const gchar *label = gtk_button_get_label(GTK_BUTTON(button));

    if (selected_table) g_free(selected_table);
    selected_table = NULL;

    selected_table = g_strdup(label + 6); // skip "TABLE " to get number

    for (int i = 1; i <= 8; i++) {
        char table_id[16];
        snprintf(table_id, sizeof(table_id), "table%d", i);
        GtkToggleButton *other = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, table_id));
        if (GTK_WIDGET(other) != GTK_WIDGET(button)) {
            gtk_toggle_button_set_active(other, FALSE);
        }
    }
}

static void on_confirm_booking_table_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = GTK_WIDGET(user_data);
    if (!selected_table) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Please select a table first!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    FILE *append_file = fopen("data/temp_data.txt", "a");
    if (!append_file) {
        g_printerr("Error writing table to temp_data.txt\n");
        return;
    }
    fprintf(append_file, "Table: %s\n", selected_table);
    fclose(append_file);

    gtk_widget_hide(window);
    run_bill(); // Mở giao diện hóa đơn
}

void book_table_show() {
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    if (!gtk_builder_add_from_file(builder, "UI Glade/window_booking_table.glade", &error)) {
        g_printerr("Error loading UI: %s\n", error->message);
        g_error_free(error);
        return;
    }

    load_css_layout();

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window_booking_table"));
    g_object_set_data(G_OBJECT(window), "builder", builder);

    for (int i = 1; i <= 8; i++) {
        char table_id[16];
        snprintf(table_id, sizeof(table_id), "table%d", i);
        GtkWidget *btn = GTK_WIDGET(gtk_builder_get_object(builder, table_id));
        g_signal_connect(btn, "toggled", G_CALLBACK(on_table_clicked), builder);
    }

    g_signal_connect(gtk_builder_get_object(builder, "confirm_booking_table_button"), "clicked", G_CALLBACK(on_confirm_booking_table_button_clicked), window);

    gtk_widget_show_all(window);
}
