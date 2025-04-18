/*#include <gtk/gtk.h>
#include <string.h>

GtkBuilder *builder;
GtkWidget *Orders_Window;
GtkListStore *list_store;
GtkTreeView *orders_view;

// Load CSS
void load_css_orders() {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "Glade_CSS/orders.css", NULL); // Đường dẫn tới file CSS

    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

// Load dữ liệu từ view_bill.txt vào TreeView
void load_orders_data(const char *filename) {
    GtkListStore *list_store = gtk_list_store_new(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING); // 4 cột
    GtkTreeIter iter;

    FILE *file = fopen(filename, "r");
    if (!file) {
        g_warning("Không thể mở file %s: %s", filename, strerror(errno));
        return;
    }

    char name[100], price[100], date[100], id[100];
    while (fscanf(file, "%s %s %s %s", name, price, date, id) == 4) {
        printf("Name: %s, Price: %s, Date: %s, ID: %s\n", name, price, date, id);
        gtk_list_store_append(list_store, &iter);
        gtk_list_store_set(list_store, &iter,
            0, name,
            1, price,
            2, date,
            3, id,
            -1);
    }

    fclose(file);

    gtk_tree_view_set_model(GTK_TREE_VIEW(orders_view), GTK_TREE_MODEL(list_store));
    g_object_unref(list_store);
}

// Khởi tạo giao diện Orders
void setup_orders_ui() {
    builder = gtk_builder_new_from_file("UI Glade/UI Orders.glade");

    Orders_Window = GTK_WIDGET(gtk_builder_get_object(builder, "Orders_Window"));
    orders_view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "orders_view"));

    load_css_orders();
    load_orders_data("data/view_bill.txt");

    gtk_widget_show_all(Orders_Window);
}
*/
/*
#include <gtk/gtk.h>
#include <string.h>
#include <errno.h> // Bổ sung để dùng strerror()

GtkBuilder *builder;
GtkWidget *Orders_Window;
GtkTreeView *orders_view;

// Load CSS
void load_css_orders() {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "Glade_CSS/orders.css", NULL);

    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

// Load dữ liệu từ view_bill.txt vào TreeView
void load_orders_data(const char *filename) {
    GtkListStore *store = gtk_list_store_new(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING); // 4 cột
    GtkTreeIter iter;

    FILE *file = fopen(filename, "r");
    if (!file) {
        g_warning("Không thể mở file %s: %s", filename, strerror(errno));
        return;
    }

    char name[100], price[100], date[100], id[100];
    while (fscanf(file, "%s %s %s %s", name, price, date, id) == 4) {
        printf("Name: %s, Price: %s, Date: %s, ID: %s\n", name, price, date, id);
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            0, name,
            1, price,
            2, date,
            3, id,
            -1);
    }

    fclose(file);

    gtk_tree_view_set_model(GTK_TREE_VIEW(orders_view), GTK_TREE_MODEL(store));
    g_object_unref(store); 
}

// Khởi tạo giao diện Orders
void setup_orders_ui() {
    builder = gtk_builder_new_from_file("UI Glade/UI Orders.glade");

    Orders_Window = GTK_WIDGET(gtk_builder_get_object(builder, "Orders_Window"));
    orders_view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "orders_view"));

    load_css_orders();
    load_orders_data("data/view_bill.txt");

    gtk_widget_show_all(Orders_Window);
}*/
#include <gtk/gtk.h>
#include <string.h>
#include <errno.h>

GtkBuilder *builder;
GtkWidget *Orders_Window;
GtkTreeView *orders_view;

// ======================= Load CSS =======================
void load_css_orders() {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "Glade_CSS/orders.css", NULL);

    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(
        screen,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );
}

// ======================= Load dữ liệu từ file =======================
void load_orders_data(const char *filename) {
    GtkListStore *store = gtk_list_store_new(
        4,
        G_TYPE_STRING, // Tên khách hàng
        G_TYPE_STRING, // Tổng tiền
        G_TYPE_STRING, // Ngày thanh toán
        G_TYPE_STRING  // ID hóa đơn
    );

    GtkTreeIter iter;
    FILE *file = fopen(filename, "r");
    if (!file) {
        g_warning("Không thể mở file %s: %s", filename, strerror(errno));
        return;
    }

    char name[100], price[100], date[100], id[100];
    while (fscanf(file, "%s %s %s %s", name, price, date, id) == 4) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            0, name,
            1, price,
            2, date,
            3, id,
            -1);
    }

    fclose(file);
    gtk_tree_view_set_model(GTK_TREE_VIEW(orders_view), GTK_TREE_MODEL(store));
    g_object_unref(store); // Giải phóng vì TreeView đã giữ reference
}

// ======================= Khởi tạo giao diện =======================
void setup_orders_ui() {
    builder = gtk_builder_new_from_file("UI Glade/UI Orders.glade");

    Orders_Window = GTK_WIDGET(gtk_builder_get_object(builder, "Orders_Window"));
    orders_view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "orders_view"));

    load_css_orders();
    load_orders_data("data/view_bill.txt");

    gtk_widget_show_all(Orders_Window);
}

