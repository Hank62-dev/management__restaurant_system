#include "utils.h"
#include <string.h>

static GtkWidget *selected_table = NULL;

void on_table_clicked(GtkButton *button, gpointer user_data) {
    // Nếu đã chọn bàn trước đó thì reset style
    if (selected_table) {
        gtk_widget_set_name(GTK_WIDGET(selected_table), "table_button");
    }

    // Đặt tên mới để áp dụng CSS cho nút đang chọn
    selected_table = GTK_WIDGET(button);
    gtk_widget_set_name(selected_table, "selected_table");

    const gchar *label = gtk_button_get_label(button);
    g_print("Selected table: %s\n", label);
}

void on_confirm_booking_table_button_clicked(GtkButton *button, gpointer user_data) {
    if (selected_table) {
        const gchar *label = gtk_button_get_label(GTK_BUTTON(selected_table));
        g_print("Confirming booking for %s\n", label);
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(user_data),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "You have booked %s!", label);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(user_data),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Please select a table first!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}
