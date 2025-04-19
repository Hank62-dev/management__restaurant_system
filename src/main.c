<<<<<<< HEAD

#include <string.h>
#include <gtk/gtk.h>
#include "identification.h"
#include "login_register_Cus.h"
#include "login_register_Mana.h"
#include "utils.h"
#include "total_bills.h"



int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    //show_identification();  
    total_bills();
    gtk_main();
    return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu_Mana.h"
#include "menu_Cus.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);    
    show_Menu_Cus();
    gtk_main();
    return 0;
}
>>>>>>> menu
