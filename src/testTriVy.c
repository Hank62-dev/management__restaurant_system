#include <gtk/gtk.h>
#include "table_booking.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    // Create AppData structure
    AppData app_data = {0};
    app_data.name = NULL;
    app_data.date = NULL;
    app_data.phone = NULL;
    app_data.time = NULL;
    app_data.guests = NULL;
    app_data.selected_table = NULL;
    
    // Show booking information window
    show_booking_information(&app_data);
    
    gtk_main();
    
    // Cleanup
    if (app_data.name) g_free(app_data.name);
    if (app_data.date) g_free(app_data.date);
    if (app_data.phone) g_free(app_data.phone);
    if (app_data.time) g_free(app_data.time);
    if (app_data.guests) g_free(app_data.guests);
    if (app_data.selected_table) g_free(app_data.selected_table);
    if (app_data.builder_booking_information) g_object_unref(app_data.builder_booking_information);
    if (app_data.builder_booking_table) g_object_unref(app_data.builder_booking_table);
    if (app_data.builder_bill_layout) g_object_unref(app_data.builder_bill_layout);
    
    return 0;
}