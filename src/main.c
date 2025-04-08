#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Tải CSS cho giao diện khách hàng
    load_css("Glade_CSS/UI_MenuCus.css");

    // Tải CSS cho giao diện quản lý
    load_css("Glade_CSS/UI_MenuMana.css");

    // Đọc menu từ file khi bắt đầu chương trình
    loadMenuFromFile(menuList, &menu_count);

    // Tải giao diện (chọn một trong hai tùy theo vai trò: khách hàng hoặc quản lý)
    // load_customer_ui();  // Giao diện khách hàng
    load_manager_ui();   // Giao diện quản lý

    gtk_main();
    return 0;
}