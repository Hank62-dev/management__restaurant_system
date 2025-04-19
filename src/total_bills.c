#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "total_bills.h"

#define MAX_ROWS 100
#define MAX_LINE_LEN 256

GtkWidget *btn_orders;

// Hàm apply CSS
void load_css_orders(const char *css_path) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, css_path, NULL);

    GdkScreen *screen = gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(screen,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);

    g_object_unref(provider);
}

// hàm lấy dữ liệu từ file
void load_labels_from_file(GtkButton *button, gpointer user_data) {
    GtkBuilder *builder = GTK_BUILDER(user_data);

    FILE *file = fopen("data/view_bill.txt", "r");
    if (!file) {
        g_print("Not open file view_bill.txt\n");
        return;
    }

    char line[MAX_LINE_LEN];
    int i = 0;

    while (fgets(line, sizeof(line), file) && i <= MAX_ROWS) {
        char id[50], name[100], date[50], price[50];

        line[strcspn(line, "\n")] = 0;

        if (sscanf(line, "%s %s %s %s", id, name, date, price) != 4) {
            g_print("Dòng %d không hợp lệ: %s\n", i, line);
            continue;
        }

        char id_label[32], name_label[32], date_label[32], price_label[32];
        sprintf(id_label, "id%d", i);
        sprintf(name_label, "name%d", i);
        sprintf(date_label, "date%d", i);
        sprintf(price_label, "price%d", i);

        GtkLabel *label_id = GTK_LABEL(gtk_builder_get_object(builder, id_label));
        GtkLabel *label_name = GTK_LABEL(gtk_builder_get_object(builder, name_label));
        GtkLabel *label_date = GTK_LABEL(gtk_builder_get_object(builder, date_label));
        GtkLabel *label_price = GTK_LABEL(gtk_builder_get_object(builder, price_label));

        if (label_id && label_name && label_date && label_price) {
            gtk_label_set_text(label_id, id);
            gtk_label_set_text(label_name, name);
            gtk_label_set_text(label_date, date);
            gtk_label_set_text(label_price, price);
        } else {
            g_print("Không tìm thấy label cho dòng %d\n", i);
        }

        i++;
    }

    fclose(file);
}

// Hàm chính hiện toàn bộ bills
void total_bills() {
    GtkBuilder *builder = gtk_builder_new_from_file("UI Glade/UI Orders.glade");
    GtkWidget *window_bills = GTK_WIDGET(gtk_builder_get_object(builder, "Orders_Window"));

    btn_orders = GTK_WIDGET(gtk_builder_get_object(builder, "btn_orders"));

   //kết nối sự kiện
    g_signal_connect(btn_orders, "clicked", G_CALLBACK(load_labels_from_file), builder);

    load_css_orders("Glade_CSS/orders.css");

    gtk_widget_show_all(window_bills);
}
