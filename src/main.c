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