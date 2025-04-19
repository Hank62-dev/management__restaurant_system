<<<<<<< HEAD

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_LINE_LEN 256

void load_css_orders(const char *css_path) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, css_path, NULL);

    GdkScreen *screen = gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(screen,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);

    g_object_unref(provider);
}




void load_labels_from_file(GtkBuilder *builder) {
    FILE *file = fopen("data/view_bill.txt", "r");
    if (!file) {
        g_print("Not open file view_bill.txt\n");
        return;
    }

    char line[MAX_LINE_LEN];
    int i = 0;

    while (fgets(line, sizeof(line), file) && i <= MAX_ROWS) {
        char id[50], name[100], date[50], price[50];

        // Gỡ xuống dòng \n nếu có
        line[strcspn(line, "\n")] = 0;

        // Phân tích dòng bằng sscanf
        if (sscanf(line, "%s %s %s %s", id, name, date, price) != 4) {
            g_print("Dòng %d không hợp lệ: %s\n", i, line);
            continue;
        }

        // Tạo ID label name như trong Glade
        char id_label[32], name_label[32], date_label[32], price_label[32];
        sprintf(id_label, "id%d", i);
        sprintf(name_label, "name%d", i);
        sprintf(date_label, "date%d", i);
        sprintf(price_label, "price%d", i);

        // Lấy widget từ Glade
        GtkLabel *label_id = GTK_LABEL(gtk_builder_get_object(builder, id_label));
        GtkLabel *label_name = GTK_LABEL(gtk_builder_get_object(builder, name_label));
        GtkLabel *label_date = GTK_LABEL(gtk_builder_get_object(builder, date_label));
        GtkLabel *label_price = GTK_LABEL(gtk_builder_get_object(builder, price_label));

        // Nếu đủ label thì in ra
        if (label_id && label_name && label_date && label_price) {
            gtk_label_set_text(label_id, id);
            gtk_label_set_text(label_name, name);
            gtk_label_set_text(label_date, date);
            gtk_label_set_text(label_price, price);
        } else {
            g_print("Not found label for %d\n", i);
        }

        i++;
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new_from_file("UI Glade/UI Orders.glade");
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "Orders_Window"));

    load_css_orders("Glade_CSS/orders.css");
    load_labels_from_file(builder);

    gtk_widget_show_all(window);
=======
//#include <gtk/gtk.h>//

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
   GtkBuilder *builder_home_m = gtk_builder_new_from_file("home_m.ui");
GtkBuilder *builder_home_c = gtk_builder_new_from_file("home_c.ui");
GtkBuilder *builder_employee = gtk_builder_new_from_file("employee.ui");

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
    gtk_widget_show_all(home_c_window);
    gtk_widget_show_all(home_m_window);
>>>>>>> employee
    gtk_main();

    return 0;
}
<<<<<<< HEAD


=======
>>>>>>> employee
