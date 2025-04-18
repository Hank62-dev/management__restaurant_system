#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu_Mana.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);    
    show_Menu_Mana();
    gtk_main();
    return 0;
}