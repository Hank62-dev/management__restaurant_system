#include <gtk/gtk.h>
#include "table_booking.h"

// Define global variables
char *customer_name = NULL;
char *customer_date = NULL;
char *customer_phone = NULL;
char *customer_time = NULL;
char *customer_guests = NULL;
char *selected_table = NULL;

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Show the first window (booking information)
    show_booking_information();

    gtk_main();
    return 0;
}