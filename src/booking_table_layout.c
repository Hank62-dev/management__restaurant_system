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
