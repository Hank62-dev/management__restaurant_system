#include <gtk/gtk.h>

// Widget khai báo toàn cục
GtkWidget *home_window;
GtkWidget *employee_window;

// Callback: chuyển từ Home sang Employee
void on_btn_employee_clicked(GtkButton *button, gpointer user_data) {
    g_print("Employee button clicked\n");  // In ra để kiểm tra
    gtk_widget_hide(home_window);
    gtk_widget_show_all(employee_window);
}

// Callback: chuyển từ Employee về Home
void on_btn_home_clicked(GtkButton *button, gpointer user_data) {
    g_print("Home button clicked\n");  // In ra để kiểm tra
    gtk_widget_hide(employee_window);
    gtk_widget_show_all(home_window);
}

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkCssProvider *css_provider;
    GdkDisplay *display;
    GdkScreen *screen;

    gtk_init(&argc, &argv);

    // Load file Glade
    builder = gtk_builder_new_from_file("UI Glade/UIhome.glade");

    // Lấy widget từ Glade
    home_window = GTK_WIDGET(gtk_builder_get_object(builder, "home_c_window"));
     home_window = GTK_WIDGET(gtk_builder_get_object(builder, "home_m_window"));
    employee_window = GTK_WIDGET(gtk_builder_get_object(builder, "employee_window"));

    // Kết nối tín hiệu nút
    GtkWidget *btn_home = GTK_WIDGET(gtk_builder_get_object(builder, "btn_home_c"));
     GtkWidget *btn_home = GTK_WIDGET(gtk_builder_get_object(builder, "btn_home_m"));
    GtkWidget *btn_employee = GTK_WIDGET(gtk_builder_get_object(builder, "btn_employee"));
    g_signal_connect(btn_home_c, "clicked", G_CALLBACK(on_btn_home_clicked), NULL);
    g_signal_connect(btn_employee, "clicked", G_CALLBACK(on_btn_employee_clicked), NULL);
     g_signal_connect(btn_home_m, "clicked", G_CALLBACK(on_btn_home_clicked), NULL);

    // Kiểm tra lại tín hiệu có được kết nối không
    if (!btn_home_c) {
        g_print("btn_home is NULL!\n");
    }
    if (!btn_employee) {
        g_print("btn_employee is NULL!\n");
    }
 if (!btn_home_m) {
        g_print("btn_home is NULL!\n");
    }
    // Load CSS
    css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "Glade_CSS/home.css.css", NULL);
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen,
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Hiển thị cửa sổ chính
    gtk_widget_show_all(home_window);
    gtk_main();

    return 0;
}
