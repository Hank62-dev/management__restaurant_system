#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#define MAX_ROWS 100  // Số dòng tối đa từ file

void apply_css(GtkWidget *widget, GtkCssProvider *provider) {
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void load_css(const char *css_path, GtkWidget *widget) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, css_path, NULL);
    apply_css(widget, provider);
    g_object_unref(provider);
}

void load_labels_from_file(GtkBuilder *builder) {
    FILE *file = fopen("data/view_bill.txt", "r");
    if (!file) {
        g_print("Không thể mở file view_bill.txt\n");
        return;
    }

    char name[100], price[50], date[50], id[50];
    int i = 1;

    while (fscanf(file, "%s %s %s %s", name, price, date, id) == 4 && i <= MAX_ROWS) {
        char id_label[32], name_label[32], date_label[32], price_label[32];

        sprintf(id_label, "ID%d", i);
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

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new_from_file("UI_Glade/UI Orders.glade");
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "orders_window"));

    load_css("Glade_CSS/orders.css", window);
    load_labels_from_file(builder);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
