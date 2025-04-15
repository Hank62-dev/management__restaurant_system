#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
/*    if (!loadMenuFromFile(menuList, &menu_count)) {
        fprintf(stderr, "Failed to load menu data\n");
        return 1;
    }

    if (argc > 1 && strcmp(argv[1], "customer") == 0) {
        load_css("Glade_CSS/UI_MenuCus.css");
        load_customer_ui();
    } else {
        load_css("Glade_CSS/UI_MenuMana.css");
        load_manager_ui();
    }
*/

    
    load_css("Glade_CSS/UI_MenuMana.css");
    load_manager_ui();
    gtk_main();
    return 0;
}