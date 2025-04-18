#include <gtk/gtk.h>
#include "test.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    setup_orders_ui();
    gtk_main();
    return 0;
}
