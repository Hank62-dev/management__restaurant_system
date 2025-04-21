#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "table_booking.h"

void load_css_information() {
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

static void on_booking_info_confirm(GtkButton *button, gpointer user_data) {
    GtkWidget *window = GTK_WIDGET(user_data);
    GtkBuilder *builder = GTK_BUILDER(g_object_get_data(G_OBJECT(window), "builder"));

    GtkEntry *entry_name = GTK_ENTRY(gtk_builder_get_object(builder, "enter_name"));
    GtkEntry *entry_date = GTK_ENTRY(gtk_builder_get_object(builder, "enter_date"));
    GtkEntry *entry_phone = GTK_ENTRY(gtk_builder_get_object(builder, "enter_phone"));
    GtkEntry *entry_time = GTK_ENTRY(gtk_builder_get_object(builder, "enter_time"));
    GtkEntry *entry_guests = GTK_ENTRY(gtk_builder_get_object(builder, "enter_number_of_guest"));

    const char *name = gtk_entry_get_text(entry_name);
    const char *date = gtk_entry_get_text(entry_date);

    if (strlen(name) == 0 || strlen(date) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Please fill in Name and Date!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    FILE *file = fopen("data/temp_data.txt", "w");
    if (!file) {
        g_printerr("Failed to open temp_data.txt\n");
        return;
    }
    fprintf(file, "Name: %s\n", name);
    fprintf(file, "Date: %s\n", date);
    fprintf(file, "Phone: %s\n", gtk_entry_get_text(entry_phone));
    fprintf(file, "Time: %s\n", gtk_entry_get_text(entry_time));
    fprintf(file, "Guests: %s\n", gtk_entry_get_text(entry_guests));
    fclose(file);

    gtk_widget_hide(window);
    book_table_show(); // Mở giao diện chọn bàn
}

void show_booking_information() {
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    if (!gtk_builder_add_from_file(builder, "UI Glade/window_booking_information.glade", &error)) {
        g_printerr("Error loading UI: %s\n", error->message);
        g_error_free(error);
        return;
    }

    load_css_information();

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window_booking_information"));
    g_object_set_data(G_OBJECT(window), "builder", builder);
    g_signal_connect(gtk_builder_get_object(builder, "button_booking_table"), "clicked", G_CALLBACK(on_booking_info_confirm), window);

    gtk_widget_show_all(window);
}

