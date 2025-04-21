#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "table_booking.h"

void load_css_bill() {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GError *error = NULL;
    gtk_css_provider_load_from_path(provider, "Glade_CSS/style.css", &error);
    if (error) {
        g_printerr("Error loading CSS: %s\n", error->message);
        g_error_free(error);
    }
    g_object_unref(provider);
}

static void fill_bill_labels(GtkBuilder *builder) {
    char name[256] = "", date[32] = "", phone[32] = "", time[32] = "", guests[16] = "", table[16] = "";
    char orders_text[1024] = "";
    double subtotal = 0;


// Đọc temp_data.txt
FILE *temp = fopen("data/temp_data.txt", "r");
if (temp) {
    char line[256];
    while (fgets(line, sizeof(line), temp)) {
        if (strncmp(line, "Name:", 5) == 0) sscanf(line + 6, "%[^\n]", name);
        if (strncmp(line, "Date:", 5) == 0) sscanf(line + 6, "%[^\n]", date);
        if (strncmp(line, "Phone:", 6) == 0) sscanf(line + 7, "%[^\n]", phone);
        if (strncmp(line, "Time:", 5) == 0) sscanf(line + 6, "%[^\n]", time);
        if (strncmp(line, "Guests:", 7) == 0) sscanf(line + 8, "%[^\n]", guests);
        if (strncmp(line, "Table:", 6) == 0) sscanf(line + 7, "%[^\n]", table);
    }
    fclose(temp);
}


    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "customer_name")), name);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "date_ordered")), date);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "phone_contact")), phone);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "label_time")), time);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "enter_number_of_guest")), guests);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "table_ordered")), table);

    // Đọc orders.txt
    FILE *orders = fopen("data/orders.txt", "r");
    if (orders) {
        char line[256];
        while (fgets(line, sizeof(line), orders)) {
            strcat(orders_text, line);
            char code[32], item[64]; int qty; double price;
            int date[11];
            if (sscanf(line, "%s %s \"%[^\"]\" %d %lf",date, code, item, &qty, &price) == 5) {
                subtotal += price;
            }
        }
        fclose(orders);
    }

    char buf[64];
    double tax = subtotal * 0.1;
    double total = subtotal + tax;

    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "label_orders")), orders_text);

    snprintf(buf, sizeof(buf), "%.0f", subtotal);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "subtotal_bill")), buf);

    snprintf(buf, sizeof(buf), "%.0f", tax);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "tar")), buf);

    snprintf(buf, sizeof(buf), "%.0f", total);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "total_bill")), buf);

    // Hiển thị chi tiết món vào label "bill_infor"
char bill_lines[2048] = "";
FILE *orders_file = fopen("data/orders.txt", "r");
if (orders_file) {
    char code[32], item[64];
    int qty;
    double price;
    char line[256];
    int date[11];
    while (fgets(line, sizeof(line), orders_file)) {
        if (sscanf(line, "%s %s \"%[^\"]\" %d %lf",date, code, item, &qty, &price) == 5) {
            char line_out[256];
            snprintf(line_out, sizeof(line_out), "%s       x%d        %.0fđ\n", item, qty, price);
            strcat(bill_lines, line_out);
        }
    }
    fclose(orders_file);
}


GtkWidget *bill_label = GTK_WIDGET(gtk_builder_get_object(builder, "bill_infor"));
if (GTK_IS_LABEL(bill_label)) {
    if (GTK_IS_LABEL(bill_label)) {
        gtk_label_set_text(GTK_LABEL(bill_label), bill_lines);
        gtk_label_set_line_wrap(GTK_LABEL(bill_label), TRUE);
        gtk_label_set_line_wrap_mode(GTK_LABEL(bill_label), PANGO_WRAP_WORD_CHAR);
        gtk_widget_set_vexpand(bill_label, TRUE);
        gtk_widget_set_hexpand(bill_label, TRUE);
    } else {
        g_print("Không tìm thấy label 'bill_infor' trong glade!\n");
    }



}
}

static void on_confirm_bill_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = GTK_WIDGET(user_data);
    char name[256] = "Unknown", date[32] = "N/A";
    double subtotal = 0;

    FILE *temp = fopen("data/temp_data.txt", "r");
    if (temp) {
        char line[256];
        while (fgets(line, sizeof(line), temp)) {
            if (strncmp(line, "Name:", 5) == 0) sscanf(line + 6, "%255[^\n]", name);
            if (strncmp(line, "Date:", 5) == 0) sscanf(line + 6, "%31[^\n]", date);
        }
        fclose(temp);
    }

    FILE *orders = fopen("data/orders.txt", "r");
    if (orders) {
        char item[64]; int qty; double price; char code[16];
        char line[256];
        int date[11];
        while (fgets(line, sizeof(line), orders)) {
            if (sscanf(line, "%s %s %s %d %lf",date, code, item, &qty, &price) == 5) {
                subtotal += price;
            }
        }
        fclose(orders);
    }

    double tax = subtotal * 0.1;
    double total = subtotal + tax;

    int stt = 1;
    FILE *view = fopen("data/view_bill.txt", "r");
    if (view) {
        char tmp[256];
        while (fgets(tmp, sizeof(tmp), view)) stt++;
        fclose(view);
    }

    FILE *out = fopen("data/view_bill.txt", "a");
    if (out) {
        fprintf(out, "%d %s %s %.0f\n", stt, name, date, total);
        fclose(out);
    }

    gtk_widget_hide(window);
}

void run_bill() {
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    if (!gtk_builder_add_from_file(builder, "UI Glade/bill_layout.glade", &error)) {
        g_printerr("Error loading UI: %s\n", error->message);
        g_error_free(error);
        return;
    }

    load_css_bill();
    fill_bill_labels(builder);

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "bill_layout"));
    g_signal_connect(gtk_builder_get_object(builder, "confirm_bill_button"), "clicked", G_CALLBACK(on_confirm_bill_clicked), window);
    gtk_widget_show_all(window);
}

