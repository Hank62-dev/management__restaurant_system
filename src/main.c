
#include <string.h>
#include <gtk/gtk.h>
#include "identification.h"
#include "login_register_Cus.h"
#include "login_register_Mana.h"
#include "utils.h"
#include "total_bills.h"
// Khai báo hàm sẽ viết trong identification.c


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    //show_identification();  
    total_bills();
    gtk_main();
    return 0;
}
