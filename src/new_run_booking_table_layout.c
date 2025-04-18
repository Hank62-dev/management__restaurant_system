#include <gtk/gtk.h>
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
        // Set the parent of the dialog to the current window
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
}