#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "table_booking.h"
<<<<<<< HEAD

// Structure to hold application data
typedef struct {
    GtkWidget *window_booking_table;
    GtkWidget *window_bill_layout;
    GtkBuilder *builder_booking_table;
    GtkBuilder *builder_bill_layout;
    char *selected_table; // Store selected table number
} AppData;
=======
>>>>>>> f1597c89f266a29ef1d0c4493895974cdfe156de

static char *selected_table = NULL;

void load_css_layout(void)
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

<<<<<<< HEAD
static void on_table_clicked(GtkToggleButton *button, gpointer user_data)
{
=======
static void on_menu3_clicked(GtkButton *button, gpointer data) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, 
                                              GTK_MESSAGE_INFO, GTK_BUTTONS_OK, 
                                              "Menu button clicked!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void on_booking3_clicked(GtkButton *button, gpointer data) {
    AppData *app_data = (AppData *)data;
    gtk_widget_hide(app_data->window_booking_table);
<<<<<<< HEAD
    
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
=======
    show_booking_information(app_data);
>>>>>>> f1597c89f266a29ef1d0c4493895974cdfe156de
}

// Callback for table buttons to store selected table number
static void on_table_clicked(GtkToggleButton *button, gpointer data) {
    AppData *app_data = (AppData *)data;
    
>>>>>>> e5961ab5687db564333e30ce2ef2b6150e0397a9
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

<<<<<<< HEAD
    // Update temp_data.txt with selected table
    FILE *file = fopen("temp_data.txt", "a");
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
=======
// Function to load CSS
static void load_css_layout(void) {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    
    gtk_style_context_add_provider_for_screen(screen, 
                                             GTK_STYLE_PROVIDER(provider), 
                                             GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    GError *error = NULL;
<<<<<<< HEAD
    gtk_css_provider_load_from_path(provider, "Glade_CSS/edit1.css", &error);
=======
    gtk_css_provider_load_from_path(provider, "style.css", &error);
>>>>>>> f1597c89f266a29ef1d0c4493895974cdfe156de
    
    if (error != NULL) {
        g_printerr("Error loading CSS: %s\n", error->message);
        g_error_free(error);
    }
    
    g_object_unref(provider);
}

void book_table_show(AppData *app_data) {
    // Load the booking table Glade file
    app_data->builder_booking_table = gtk_builder_new();
    GError *error = NULL;
    
<<<<<<< HEAD
    if (!gtk_builder_add_from_file(builder_booking_table, "UI Glade/window_booking_table.glade", &error)) {
=======
    if (!gtk_builder_add_from_file(app_data->builder_booking_table, "window_booking_table.glade", &error)) {
>>>>>>> f1597c89f266a29ef1d0c4493895974cdfe156de
        g_printerr("Error loading window_booking_table.glade: %s\n", error->message);
        g_error_free(error);
        g_object_unref(app_data->builder_booking_table);
>>>>>>> e5961ab5687db564333e30ce2ef2b6150e0397a9
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

    if (!gtk_builder_add_from_file(builder, "window_booking_table.glade", &error))
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
<<<<<<< HEAD

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window_booking_table"));
    g_object_set_data(G_OBJECT(window), "builder", builder); // Store builder for access in callback
    g_signal_connect(gtk_builder_get_object(builder, "confirm_booking_table_button"), "clicked", G_CALLBACK(on_confirm_booking_table_button_clicked), window);

    // Connect toggle signals for table buttons
    for (int i = 1; i <= 8; i++)
    {
=======
<<<<<<< HEAD
    
    // Create AppData structure
    AppData app_data = {0};
    app_data.builder_booking_table = builder_booking_table;
    app_data.selected_table = NULL;
=======
>>>>>>> f1597c89f266a29ef1d0c4493895974cdfe156de
    
    // Get the booking table window
    app_data->window_booking_table = GTK_WIDGET(gtk_builder_get_object(app_data->builder_booking_table, "window_booking_table"));
    
    // Connect signals
    gtk_builder_connect_signals(app_data->builder_booking_table, app_data);
    
    // Set table buttons as toggle buttons
    for (int i = 1; i <= 8; i++) {
>>>>>>> e5961ab5687db564333e30ce2ef2b6150e0397a9
        char table_id[16];
        snprintf(table_id, sizeof(table_id), "table%d", i);
        g_signal_connect(gtk_builder_get_object(builder, table_id), "toggled", G_CALLBACK(on_table_clicked), builder);
    }

    gtk_widget_show_all(window);
}