#include <gtk/gtk.h>
#include <stdio.h>
#include "table_booking.h"


void load_css_information(void)
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

static void on_button_booking_table_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = GTK_WIDGET(user_data);

    // Get data from entries
    GtkEntry *entry_name = GTK_ENTRY(gtk_builder_get_object(g_object_get_data(G_OBJECT(window), "builder"), "enter_name"));
    GtkEntry *entry_date = GTK_ENTRY(gtk_builder_get_object(g_object_get_data(G_OBJECT(window), "builder"), "enter_date"));
    GtkEntry *entry_phone = GTK_ENTRY(gtk_builder_get_object(g_object_get_data(G_OBJECT(window), "builder"), "enter_phone"));
    GtkEntry *entry_time = GTK_ENTRY(gtk_builder_get_object(g_object_get_data(G_OBJECT(window), "builder"), "enter_time"));
    GtkEntry *entry_guests = GTK_ENTRY(gtk_builder_get_object(g_object_get_data(G_OBJECT(window), "builder"), "enter_number_of_guest"));

    // Open file to write data
    FILE *file = fopen("temp_data.txt", "w");
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
<<<<<<< HEAD

    // Write data to file
    fprintf(file, "Name: %s\n", gtk_entry_get_text(entry_name));
    fprintf(file, "Date: %s\n", gtk_entry_get_text(entry_date));
    fprintf(file, "Phone: %s\n", gtk_entry_get_text(entry_phone));
    fprintf(file, "Time: %s\n", gtk_entry_get_text(entry_time));
    fprintf(file, "Guests: %s\n", gtk_entry_get_text(entry_guests));
    fclose(file);

    // Hide current window
    gtk_widget_hide(window);
=======
    
    // Hide booking information window
    gtk_widget_hide(app_data->window_booking_information);
    
    // Load window_booking_table.glade
    app_data->builder_booking_table = gtk_builder_new();
    GError *error = NULL;
    
    if (!gtk_builder_add_from_file(app_data->builder_booking_table, "UI Glade/window_booking_table.glade", &error)) {
        g_printerr("Error loading window_booking_table.glade: %s\n", error->message);
        g_error_free(error);
        g_object_unref(app_data->builder_booking_table);
        return;
    }
    
    // Get booking table window
    app_data->window_booking_table = GTK_WIDGET(gtk_builder_get_object(app_data->builder_booking_table, "window_booking_table"));
    
    // Connect signals
    gtk_builder_connect_signals(app_data->builder_booking_table, app_data);
    
    // Show booking table window
    book_table_show(app_data);
>>>>>>> e5961ab5687db564333e30ce2ef2b6150e0397a9
}

void show_booking_information()
{
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;
<<<<<<< HEAD

    if (!gtk_builder_add_from_file(builder, "window_booking_information.glade", &error))
    {
        g_printerr("Error loading file: %s\n", error->message);
        GtkWidget *dialog = gtk_message_dialog_new(NULL, 
                                                  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
                                                  GTK_MESSAGE_ERROR, 
                                                  GTK_BUTTONS_OK, 
                                                  "Cannot load window_booking_information.glade!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
=======
    gtk_css_provider_load_from_path(provider, "Glade_CSS/style.css", &error);
    
    if (error != NULL) {
        g_printerr("Error loading CSS: %s\n", error->message);
        g_error_free(error);
    }
    
    g_object_unref(provider);
}

void show_booking_information() {
    
    // Load the booking information Glade file
    app_data->builder_booking_information = gtk_builder_new();
    GError *error = NULL;
    
    if (!gtk_builder_add_from_file(builder_booking_information, "UI Glade/window_booking_information.glade", &error)) {
        g_printerr("Error loading window_booking_information.glade: %s\n", error->message);
        g_error_free(error);
        g_object_unref(builder_booking_information);
        return ;
<<<<<<< HEAD
=======
=======
    if (!gtk_builder_add_from_file(app_data->builder_booking_information, "window_booking_information.glade", &error)) {
        g_printerr("Error loading window_booking_information.glade: %s\n", error->message);
>>>>>>> e5961ab5687db564333e30ce2ef2b6150e0397a9
        g_error_free(error);
        return;
>>>>>>> f1597c89f266a29ef1d0c4493895974cdfe156de
>>>>>>> 53b11d80021a4a360f91ed4760b60051ca69d9ef
    }

    load_css_information();
<<<<<<< HEAD
=======
<<<<<<< HEAD

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window_booking_information"));
    g_object_set_data(G_OBJECT(window), "builder", builder); // Store builder for access in callback
    g_signal_connect(gtk_builder_get_object(builder, "button_booking_table"), "clicked", G_CALLBACK(on_button_booking_table_clicked), window);

    gtk_widget_show_all(window);
=======
<<<<<<< HEAD
>>>>>>> 53b11d80021a4a360f91ed4760b60051ca69d9ef
    
    // Create AppData structure
    AppData app_data = {0};
    app_data.builder_booking_information = builder_booking_information;
    app_data.name = NULL;
    app_data.date = NULL;
    app_data.phone = NULL;
    app_data.time = NULL;
    app_data.guests = NULL;
    
    // Get the booking information window
    app_data->window_booking_information = GTK_WIDGET(gtk_builder_get_object(app_data->builder_booking_information, "window_booking_information"));
    
    // Connect signals
    gtk_builder_connect_signals(app_data->builder_booking_information, app_data);
    
    // Show the booking information window
    gtk_widget_show_all(app_data.window_booking_information);
    

    
    // Cleanup
    if (app_data.name) g_free(app_data.name);
    if (app_data.date) g_free(app_data.date);
    if (app_data.phone) g_free(app_data.phone);
    if (app_data.time) g_free(app_data.time);
    if (app_data.guests) g_free(app_data.guests);
    if (app_data.builder_booking_information) g_object_unref(app_data.builder_booking_information);
    if (app_data.builder_booking_table) g_object_unref(app_data.builder_booking_table);
    

<<<<<<< HEAD
=======
=======
    gtk_widget_show_all(app_data->window_booking_information);
>>>>>>> f1597c89f266a29ef1d0c4493895974cdfe156de
>>>>>>> e5961ab5687db564333e30ce2ef2b6150e0397a9
>>>>>>> 53b11d80021a4a360f91ed4760b60051ca69d9ef
}