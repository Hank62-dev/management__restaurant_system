#include <gtk/gtk.h>
#include "employees.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    show_employee();

    gtk_main();
    return 0;
}
