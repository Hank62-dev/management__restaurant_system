#include <gtk/gtk.h>
//Khai báo các include thư viện .h
#include "test.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

//Các hàm giao diện
    show_stats();

    gtk_main();
    return 0;
}