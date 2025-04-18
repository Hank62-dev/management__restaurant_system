#include <gtk/gtk.h>

GtkWidget *window_booking_information;
GtkWidget *window_booking_table;

// Các entry để lấy dữ liệu
GtkEntry *entry_name, *entry_phone, *entry_date, *entry_time, *entry_number_of_guest;

// Hàm xử lý khi nhấn nút "BOOK TABLE HERE"
void on_button_booking_table_clicked(GtkButton *button, gpointer user_data) {
    // Lấy dữ liệu từ GtkEntry
    const gchar *name = gtk_entry_get_text(entry_name);
    const gchar *phone = gtk_entry_get_text(entry_phone);
    const gchar *date = gtk_entry_get_text(entry_date);
    const gchar *time = gtk_entry_get_text(entry_time);
    const gchar *num_guest = gtk_entry_get_text(entry_number_of_guest);

    // In ra terminal
    g_print("Thông tin đặt bàn:\n");
    g_print("Tên: %s\n", name);
    g_print("SĐT: %s\n", phone);
    g_print("Ngày: %s\n", date);
    g_print("Giờ: %s\n", time);
    g_print("Số khách: %s\n", num_guest);

    // Chuyển sang giao diện đặt bàn
    gtk_widget_hide(window_booking_information);

    GtkBuilder *builder2 = gtk_builder_new_from_file("window_booking_table.glade");
    window_booking_table = GTK_WIDGET(gtk_builder_get_object(builder2, "window_booking_table"));
    gtk_builder_connect_signals(builder2, NULL);

    gtk_widget_show_all(window_booking_table);
}

// Các nút menu đơn giản
void on_home3_clicked(GtkButton *button, gpointer user_data) {
    g_print("HOME clicked\n");
}
void on_menu3_clicked(GtkButton *button, gpointer user_data) {
    g_print("MENU clicked\n");
}
void on_booking3_clicked(GtkButton *button, gpointer user_data) {
    g_print("BOOKING clicked\n");
}
void on_bill3_clicked(GtkButton *button, gpointer user_data) {
    g_print("BILL clicked\n");
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv__);

    GtkBuilder *builder = gtk_builder_new_from_file("window_booking_information.glade");
    window_booking_information = GTK_WIDGET(gtk_builder_get_object(builder, "window_booking_information"));

    // Lưu các GtkEntry để dùng trong handler
    entry_name = GTK_ENTRY(gtk_builder_get_object(builder, "enter_name"));
    entry_phone = GTK_ENTRY(gtk_builder_get_object(builder, "enter_phone"));
    entry_date = GTK_ENTRY(gtk_builder_get_object(builder, "enter_date"));
    entry_time = GTK_ENTRY(gtk_builder_get_object(builder, "enter_time"));
    entry_number_of_guest = GTK_ENTRY(gtk_builder_get_object(builder, "enter_number_of_guest"));

    gtk_builder_connect_signals(builder, NULL);

    // Load CSS
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "edit1.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_show_all(window_booking_information);
    gtk_main();
    return 0;
}
