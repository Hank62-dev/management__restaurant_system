#include <gtk/gtk.h>

static void on_home1_clicked(GtkButton *button, gpointer user_data) {
    g_print("Home button clicked\n");
}

static void on_menu1_clicked(GtkButton *button, gpointer user_data) {
    g_print("Menu button clicked\n");
}

static void on_booking1_clicked(GtkButton *button, gpointer user_data) {
    g_print("Booking button clicked\n");
}

static void on_bill1_clicked(GtkButton *button, gpointer user_data) {
    g_print("Bill button clicked\n");
}

static void on_table1_clicked(GtkButton *button, gpointer user_data) {
    g_print("Table 1 clicked\n");
}

static void on_table2_clicked(GtkButton *button, gpointer user_data) {
    g_print("Table 2 clicked\n");
}

static void on_table3_clicked(GtkButton *button, gpointer user_data) {
    g_print("Table 3 clicked\n");
}

static void on_table4_clicked(GtkButton *button, gpointer user_data) {
    g_print("Table 4 clicked\n");
}

static void on_table5_clicked(GtkButton *button, gpointer user_data) {
    g_print("Table 5 clicked\n");
}

static void on_table6_clicked(GtkButton *button, gpointer user_data) {
    g_print("Table 6 clicked\n");
}

static void on_table7_clicked(GtkButton *button, gpointer user_data) {
    g_print("Table 7 clicked\n");
}

static void on_table8_clicked(GtkButton *button, gpointer user_data) {
    g_print("Table 8 clicked\n");
}

static void on_confirm_booking_table_button_clicked(GtkButton *button, gpointer user_data) {
    g_print("Booking confirmed\n");
}

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window;
    GtkCssProvider *css_provider;
    GError *error = NULL;

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Load Glade file
    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "edit2.glade", &error)) {
        g_critical("Error loading file: %s", error->message);
        g_error_free(error);
        return 1;
    }

    // Get the window from Glade
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_booking_table"));

    // Connect signals
    gtk_builder_connect_signals(builder, NULL);

    // Load CSS file
    css_provider = gtk_css_provider_new();
    if (!gtk_css_provider_load_from_file(css_provider, "edit1.css", &error)) {
        g_critical("Error loading CSS: %s", error->message);
        g_error_free(error);
        return 1;
    }

    // Apply CSS to the entire application
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Show the window
    gtk_widget_show(window);

    // Main loop
    gtk_main();

    // Clean up
    g_object_unref(builder);
    g_object_unref(css_provider);

    return 0;
}
