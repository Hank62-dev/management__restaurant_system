#include <gtk/gtk.h>
#include "utils.h"

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window;
    GError *error = NULL;

    gtk_init(&argc, &argv);

    // Load Builder
    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "booking_table.glade", &error)) {
        g_printerr("Error loading Glade file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // Load CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "edit1.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Get main window and connect signal
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_booking_table"));
    gtk_builder_connect_signals(builder, window);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
