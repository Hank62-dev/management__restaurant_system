#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu_Cus.h"

// Biến toàn cục
MenuItem menuList[MAX_MENU_ITEMS];
int menuCount = 0;
OrderItem orderItems[MAX_ORDER_ITEMS];
int orderCount = 0;
GtkWidget *menuListItemSelected;

// Hàm hiển thị thông báo
void showMessage(GtkWindow *parent, const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(parent, GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Hàm cập nhật danh sách món đã chọn
void updateSelectedList() {
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(menuListItemSelected));
    for (iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    for (int i = 0; i < orderCount; i++) {
        char stt[10], qty[10], price[20];
        snprintf(stt, sizeof(stt), "%d", i + 1);
        snprintf(qty, sizeof(qty), "%d", orderItems[i].quantity);
        snprintf(price, sizeof(price), "%.0f", orderItems[i].price * orderItems[i].quantity);

        GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        gtk_box_pack_start(GTK_BOX(row), gtk_label_new(stt), TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(row), gtk_label_new(orderItems[i].dishName), TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(row), gtk_label_new(qty), TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(row), gtk_label_new(price), TRUE, TRUE, 0);

        gtk_box_pack_start(GTK_BOX(menuListItemSelected), row, FALSE, FALSE, 0);
    }

    gtk_widget_show_all(menuListItemSelected);
}

// Hàm xử lý nút "+"
void on_add_item_clicked(GtkButton *button, gpointer user_data) {
    int index = GPOINTER_TO_INT(user_data);
    for (int i = 0; i < orderCount; i++) {
        if (strcmp(orderItems[i].menuId, menuList[index].menuId) == 0) {
            orderItems[i].quantity++;
            updateSelectedList();
            return;
        }
    }
    strcpy(orderItems[orderCount].menuId, menuList[index].menuId);
    strcpy(orderItems[orderCount].dishName, menuList[index].dishName);
    orderItems[orderCount].quantity = 1;
    orderItems[orderCount].price = menuList[index].price;
    orderCount++;
    updateSelectedList();
}

// Hàm xử lý nút "-"
void on_delete_item_clicked(GtkButton *button, gpointer user_data) {
    int index = GPOINTER_TO_INT(user_data);
    for (int i = 0; i < orderCount; i++) {
        if (strcmp(orderItems[i].menuId, menuList[index].menuId) == 0) {
            orderItems[i].quantity--;
            if (orderItems[i].quantity <= 0) {
                orderItems[i] = orderItems[--orderCount];
            }
            updateSelectedList();
            return;
        }
    }
}

// Hàm xử lý nút CONFIRM
void on_confirm_clicked(GtkButton *button, gpointer user_data) {
    if (orderCount == 0) {
        showMessage(GTK_WINDOW(user_data), "Chưa chọn món nào!");
        return;
    }

    if (saveOrderToFile(orderItems, orderCount)) {
        showMessage(GTK_WINDOW(user_data), "Đơn hàng đã được xác nhận!");
        orderCount = 0;
        updateSelectedList();
    } else {
        showMessage(GTK_WINDOW(user_data), "Lỗi lưu đơn hàng!");
    }
}

// Hàm khởi tạo danh sách món
void initMenuList(GtkWidget *grid) {
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(grid));
    for (iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    for (int i = 0; i < menuCount; i++) {
        int row = i / 4;
        int col = i % 4;

        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        GtkWidget *image = gtk_image_new_from_file(menuList[i].imagePath);
        GtkWidget *name = gtk_label_new(menuList[i].dishName);
        char priceStr[20];
        snprintf(priceStr, sizeof(priceStr), "%.0f", menuList[i].price);
        GtkWidget *priceBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        GtkWidget *deleteBtn = gtk_button_new_with_label("-");
        GtkWidget *price = gtk_label_new(priceStr);
        GtkWidget *addBtn = gtk_button_new_with_label("+");

        gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(box), name, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(priceBox), deleteBtn, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(priceBox), price, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(priceBox), addBtn, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(box), priceBox, FALSE, FALSE, 0);

        g_signal_connect(deleteBtn, "clicked", G_CALLBACK(on_delete_item_clicked), GINT_TO_POINTER(i));
        g_signal_connect(addBtn, "clicked", G_CALLBACK(on_add_item_clicked), GINT_TO_POINTER(i));

        gtk_grid_attach(GTK_GRID(grid), box, col, row, 1, 1);
    }

    gtk_widget_show_all(grid);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "UI_MenuCus.glade", NULL)) {
        printf("Lỗi tải file UI_MenuCus.glade\n");
        return 1;
    }

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "menuCustomer"));
    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(builder, "menuListItemSelect"));
    menuListItemSelected = GTK_WIDGET(gtk_builder_get_object(builder, "menuListItemSelected"));
    GtkWidget *confirmBtn = GTK_WIDGET(gtk_builder_get_object(builder, "buttonConfirm"));

    if (!loadMenuFromFile(menuList, &menuCount)) {
        printf("Lỗi tải menu\n");
        return 1;
    }

    printMenu(menuList, menuCount);
    initMenuList(grid);
    updateSelectedList();

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(confirmBtn, "clicked", G_CALLBACK(on_confirm_clicked), window);

    load_css("UI_MenuCus.css");
    gtk_widget_show_all(window);
    gtk_main();

    g_object_unref(builder);
    return 0;
}