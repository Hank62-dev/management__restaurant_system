#include <string.h>
#include <gtk/gtk.h>
#include "table_booking.h"

// Khai báo hàm sẽ viết trong identification.c


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    //run_bill();
    //show_booking_information(); 
    book_table_show (); 
    gtk_main();
    return 0;
}