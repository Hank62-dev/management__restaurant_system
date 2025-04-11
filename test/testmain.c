#include <gtk/gtk.h>
#include "test.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);


    show_stats();

    gtk_main();
    return 0;
}