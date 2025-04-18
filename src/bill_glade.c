#include <gtk/gtk.h>
#include <stdio.h>

// Callback function prototypes
void on_home3_clicked(GtkButton *button, gpointer user_data);
void on_menu3_clicked(GtkButton *button, gpointer user_data);
void on_booking3_clicked(GtkButton *button, gpointer user_data);
void on_bill3_clicked(GtkButton *button, gpointer user_data);
void on_confirm_bill_button_clicked(GtkButton *button, gpointer user_data);

// Function to update bill information
void update_bill_info(GtkWidget *customer_name, GtkWidget *table_ordered, GtkWidget *date_ordered,
                      GtkWidget *subtotal_bill, GtkWidget *tar, GtkWidget *total_bill, 
                      const char *customer, const char *table, const char *date, 
                      double subtotal, double tax, double total) {
    char label[256];

    // Update customer name
    snprintf(label, sizeof(label), "Customer's name: %s", customer);
    gtk_label_set_text(GTK_LABEL(customer_name), label);

    // Update table number
    snprintf(label, sizeof(label), "Table: %s", table);
    gtk_label_set_text(GTK_LABEL(table_ordered), label);

    // Update order date
    snprintf(label, sizeof(label), "Date: %s", date);
    gtk_label_set_text(GTK_LABEL(date_ordered), label);

    // Update subtotal
    snprintf(label, sizeof(label), "Subtotal: %.2f", subtotal);
    gtk_label_set_text(GTK_LABEL(subtotal_bill), label);

    // Update tax (tar)
    snprintf(label, sizeof(label), "Tar: %.2f", tax);
    gtk_label_set_text(GTK_LABEL(tar), label);

    // Update total bill
    snprintf(label, sizeof(label), "Total: %.2f", total);
    gtk_label_set_text(GTK_LABEL(total_bill), label);
}

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window;

    gtk_init(&argc, &argv);

    // Load the .glade file
    builder = gtk_builder_new_from_file("UI Glade/bill_layout.glade");

    // Get the window and connect signals
    window = GTK_WIDGET(gtk_builder_get_object(builder, "bill_layout"));
    gtk_builder_connect_signals(builder, NULL);

    // Get widget references
    GtkWidget *customer_name = GTK_WIDGET(gtk_builder_get_object(builder, "customer_name"));
    GtkWidget *table_ordered = GTK_WIDGET(gtk_builder_get_object(builder, "table_ordered"));
    GtkWidget *date_ordered = GTK_WIDGET(gtk_builder_get_object(builder, "date_ordered"));
    GtkWidget *subtotal_bill = GTK_WIDGET(gtk_builder_get_object(builder, "subtotal_bill"));
    GtkWidget *tar = GTK_WIDGET(gtk_builder_get_object(builder, "tar"));
    GtkWidget *total_bill = GTK_WIDGET(gtk_builder_get_object(builder, "total_bill"));
    // khai bao
const char *customer ;
const char *table ;
const char *date ;
double subtotal ;
double tax ;
double total ;


    // Update bill information on the GUI
    update_bill_info(customer_name, table_ordered, date_ordered, subtotal_bill, tar, total_bill, 
                     customer, table, date, subtotal, tax, total);

    // Show the window
    gtk_widget_show_all(window);

    // Main GTK loop
    gtk_main();

    return 0;
}

void on_home3_clicked(GtkButton *button, gpointer user_data) {
    // Navigate to home screen
    printf("Home button clicked\n");
}

void on_menu3_clicked(GtkButton *button, gpointer user_data) {
    // Navigate to menu screen
    printf("Menu button clicked\n");
}

void on_booking3_clicked(GtkButton *button, gpointer user_data) {
    // Navigate to booking screen
    printf("Booking button clicked\n");
}

void on_bill3_clicked(GtkButton *button, gpointer user_data) {
    // Bill button clicked, show bill screen
    printf("Bill button clicked\n");
}

void on_confirm_bill_button_clicked(GtkButton *button, gpointer user_data) {
    // Confirm button clicked
    printf("Confirm bill button clicked\n");
    // In a real application, you might process the bill or finalize the payment here
}
