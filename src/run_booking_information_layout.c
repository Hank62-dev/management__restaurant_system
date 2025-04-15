#include <gtk/gtk.h>

// Signal handler cho các button
void on_home3_clicked(GtkButton *button, gpointer user_data) {
    g_print("HOME button clicked\n");
}

void on_menu3_clicked(GtkButton *button, gpointer user_data) {
    g_print("MENU button clicked\n");
}

void on_booking3_clicked(GtkButton *button, gpointer user_data) {
    g_print("BOOKING button clicked\n");
}

void on_bill3_clicked(GtkButton *button, gpointer user_data) {
    g_print("BILL button clicked\n");
}

void on_button_booking_table_clicked(GtkButton *button, gpointer user_data) {
    g_print("BOOK TABLE HERE button clicked\n");
}

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window;
    GtkCssProvider *css_provider;
    GdkDisplay *display;
    GdkScreen *screen;

    gtk_init(&argc, &argv);

    // Load file Glade
    builder = gtk_builder_new_from_file("edit1.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_booking_information"));

    // Kết nối các tín hiệu từ file Glade
    gtk_builder_connect_signals(builder, NULL);

    // Load CSS từ file
    css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "edit1.css", NULL);
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen,
                                              GTK_STYLE_PROVIDER(css_provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Hiển thị cửa sổ
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
