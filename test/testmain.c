
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
    gtk_main();

    return 0;
}


