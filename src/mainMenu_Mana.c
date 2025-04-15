#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

// Biến toàn cục
MenuItem menuList[MAX_MENU_ITEMS];
int menuCount = 0;
GtkWidget *oldIdLabel, *oldNameLabel, *oldCategoryLabel, *oldPriceLabel, *oldImageLabel;
GtkWidget *newIdEntry, *newNameEntry, *newCategoryEntry, *newPriceEntry, *newImageEntry;
GtkWidget *menuGrid;

// Hàm hiển thị thông báo
void showMessage(GtkWindow *parent, const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(parent, GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Hàm cập nhật thông tin món được chọn
void updateSelectedItemInfo(const char *menuId, const char *dishName, 
                           const char *type, float price, const char *imagePath) {
    char priceStr[20];
    snprintf(priceStr, sizeof(priceStr), "%.0f", price);
    gtk_label_set_text(GTK_LABEL(oldIdLabel), menuId);
    gtk_label_set_text(GTK_LABEL(oldNameLabel), dishName);
    gtk_label_set_text(GTK_LABEL(oldCategoryLabel), type);
    gtk_label_set_text(GTK_LABEL(oldPriceLabel), priceStr);
    gtk_label_set_text(GTK_LABEL(oldImageLabel), imagePath);
}

// Hàm xóa thông tin món được chọn
void clearSelectedItemInfo() {
    gtk_label_set_text(GTK_LABEL(oldIdLabel), "...");
    gtk_label_set_text(GTK_LABEL(oldNameLabel), "...");
    gtk_label_set_text(GTK_LABEL(oldCategoryLabel), "...");
    gtk_label_set_text(GTK_LABEL(oldPriceLabel), "...");
    gtk_label_set_text(GTK_LABEL(oldImageLabel), "...");
}

// Hàm cập nhật danh sách món
void updateMenuList() {
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(menuGrid));
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
        GtkWidget *price = gtk_label_new(priceStr);
        GtkWidget *selectBtn = gtk_button_new_with_label("Chọn");

        gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(box), name, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(box), price, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(box), selectBtn, FALSE, FALSE, 0);

        g_object_set_data(G_OBJECT(selectBtn), "index", GINT_TO_POINTER(i));
        g_signal_connect(selectBtn, "clicked", G_CALLBACK(on_select_item_clicked), NULL);

        gtk_grid_attach(GTK_GRID(menuGrid), box, col, row, 1, 1);
    }

    gtk_widget_show_all(menuGrid);
    clearSelectedItemInfo();
}

// Hàm xử lý nút "Chọn"
void on_select_item_clicked(GtkButton *button, gpointer user_data) {
    int index = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "index"));
    updateSelectedItemInfo(menuList[index].menuId, menuList[index].dishName,
                          menuList[index].type, menuList[index].price, 
                          menuList[index].imagePath);
}

// Hàm xử lý nút "Thêm"
void on_add_clicked(GtkButton *button, gpointer user_data) {
    const char *id = gtk_entry_get_text(GTK_ENTRY(newIdEntry));
    const char *name = gtk_entry_get_text(GTK_ENTRY(newNameEntry));
    const char *category = gtk_entry_get_text(GTK_ENTRY(newCategoryEntry));
    const char *priceStr = gtk_entry_get_text(GTK_ENTRY(newPriceEntry));
    const char *imagePath = gtk_entry_get_text(GTK_ENTRY(newImageEntry));
    float price;

    if (strlen(id) == 0 || strlen(name) == 0 || strlen(category) == 0 || 
        strlen(priceStr) == 0 || strlen(imagePath) == 0) {
        showMessage(GTK_WINDOW(user_data), "Vui lòng điền đầy đủ thông tin!");
        return;
    }
    if (sscanf(priceStr, "%f", &price) != 1 || price <= 0) {
        showMessage(GTK_WINDOW(user_data), "Giá không hợp lệ!");
        return;
    }

    if (addItem(menuList, &menuCount, id, name, category, price, imagePath)) {
        saveMenuToFile(menuList, menuCount);
        updateMenuList();
        gtk_entry_set_text(GTK_ENTRY(newIdEntry), "");
        gtk_entry_set_text(GTK_ENTRY(newNameEntry), "");
        gtk_entry_set_text(GTK_ENTRY(newCategoryEntry), "");
        gtk_entry_set_text(GTK_ENTRY(newPriceEntry), "");
        gtk_entry_set_text(GTK_ENTRY(newImageEntry), "");
        showMessage(GTK_WINDOW(user_data), "Thêm món thành công!");
    } else {
        showMessage(GTK_WINDOW(user_data), "Mã món đã tồn tại!");
    }
}

// Hàm xử lý nút "Sửa"
void on_edit_clicked(GtkButton *button, gpointer user_data) {
    const char *oldId = gtk_label_get_text(GTK_LABEL(oldIdLabel));
    const char *newId = gtk_entry_get_text(GTK_ENTRY(newIdEntry));
    const char *newName = gtk_entry_get_text(GTK_ENTRY(newNameEntry));
    const char *newCategory = gtk_entry_get_text(GTK_ENTRY(newCategoryEntry));
    const char *newPriceStr = gtk_entry_get_text(GTK_ENTRY(newPriceEntry));
    const char *newImagePath = gtk_entry_get_text(GTK_ENTRY(newImageEntry));
    float newPrice;

    if (strcmp(oldId, "...") == 0) {
        showMessage(GTK_WINDOW(user_data), "Vui lòng chọn món để sửa!");
        return;
    }
    if (strlen(newId) == 0 || strlen(newName) == 0 || strlen(newCategory) == 0 || 
        strlen(newPriceStr) == 0 || strlen(newImagePath) == 0) {
        showMessage(GTK_WINDOW(user_data), "Vui lòng điền đầy đủ thông tin mới!");
        return;
    }
    if (sscanf(newPriceStr, "%f", &newPrice) != 1 || newPrice <= 0) {
        showMessage(GTK_WINDOW(user_data), "Giá mới không hợp lệ!");
        return;
    }

    if (strcmp(oldId, newId) != 0 && checkDuplicate(menuList, menuCount, newId)) {
        showMessage(GTK_WINDOW(user_data), "Mã mới đã tồn tại!");
        return;
    }

    if (editItem(menuList, menuCount, oldId, newName, newCategory, newPrice, newImagePath)) {
        if (strcmp(oldId, newId) != 0) {
            for (int i = 0; i < menuCount; i++) {
                if (strcmp(menuList[i].menuId, oldId) == 0) {
                    strcpy(menuList[i].menuId, newId);
                    break;
                }
            }
        }
        saveMenuToFile(menuList, menuCount);
        updateMenuList();
        gtk_entry_set_text(GTK_ENTRY(newIdEntry), "");
        gtk_entry_set_text(GTK_ENTRY(newNameEntry), "");
        gtk_entry_set_text(GTK_ENTRY(newCategoryEntry), "");
        gtk_entry_set_text(GTK_ENTRY(newPriceEntry), "");
        gtk_entry_set_text(GTK_ENTRY(newImageEntry), "");
        showMessage(GTK_WINDOW(user_data), "Sửa món thành công!");
    } else {
        showMessage(GTK_WINDOW(user_data), "Không tìm thấy món để sửa!");
    }
}

// Hàm xử lý nút "Xóa"
void on_delete_clicked(GtkButton *button, gpointer user_data) {
    const char *id = gtk_label_get_text(GTK_LABEL(oldIdLabel));

    if (strcmp(id, "...") == 0) {
        showMessage(GTK_WINDOW(user_data), "Vui lòng chọn món để xóa!");
        return;
    }

    if (deleteItem(menuList, &menuCount, id)) {
        saveMenuToFile(menuList, menuCount);
        updateMenuList();
        gtk_entry_set_text(GTK_ENTRY(newIdEntry), "");
        gtk_entry_set_text(GTK_ENTRY(newNameEntry), "");
        gtk_entry_set_text(GTK_ENTRY(newCategoryEntry), "");
        gtk_entry_set_text(GTK_ENTRY(newPriceEntry), "");
        gtk_entry_set_text(GTK_ENTRY(newImageEntry), "");
        showMessage(GTK_WINDOW(user_data), "Xóa món thành công!");
    } else {
        showMessage(GTK_WINDOW(user_data), "Không tìm thấy món để xóa!");
    }
}

// Hàm xử lý nút "CONFIRM"
void on_confirm_clicked(GtkButton *button, gpointer user_data) {
    showMessage(GTK_WINDOW(user_data), "Danh sách món đã được lưu!");
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "UI_MenuMana.glade", NULL)) {
        printf("Lỗi tải file UI_MenuMana.glade\n");
        return 1;
    }

    // Lấy widget
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "menuCustomer"));
    menuGrid = GTK_WIDGET(gtk_builder_get_object(builder, "menuListItemSelect"));
    oldIdLabel = GTK_WIDGET(gtk_builder_get_object(builder, "OldId"));
    oldNameLabel = GTK_WIDGET(gtk_builder_get_object(builder, "OldName"));
    oldCategoryLabel = GTK_WIDGET(gtk_builder_get_object(builder, "OldCategory"));
    oldPriceLabel = GTK_WIDGET(gtk_builder_get_object(builder, "OldPrice"));
    oldImageLabel = gtk_label_new("...");
    newIdEntry = GTK_WIDGET(gtk_builder_get_object(builder, "NewId"));
    newNameEntry = GTK_WIDGET(gtk_builder_get_object(builder, "NewName"));
    newCategoryEntry = GTK_WIDGET(gtk_builder_get_object(builder, "NewCategory"));
    newPriceEntry = GTK_WIDGET(gtk_builder_get_object(builder, "NewPrice"));
    newImageEntry = gtk_entry_new();
    GtkWidget *addBtn = GTK_WIDGET(gtk_builder_get_object(builder, "buttonAdd"));
    GtkWidget *editBtn = GTK_WIDGET(gtk_builder_get_object(builder, "buttonEdit"));
    GtkWidget *deleteBtn = GTK_WIDGET(gtk_builder_get_object(builder, "buttonDelete"));
    GtkWidget *confirmBtn = GTK_WIDGET(gtk_builder_get_object(builder, "buttonConfirm"));

    // Thêm widget cho imagePath vào Glade
    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(builder, "GtkGrid"));
    gtk_grid_insert_row(GTK_GRID(grid), 4);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Hình ảnh cũ:"), 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), oldImageLabel, 1, 4, 1, 1);
    gtk_grid_insert_row(GTK_GRID(grid), 9);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Hình ảnh mới:"), 0, 9, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), newImageEntry, 1, 9, 1, 1);

    if (!loadMenuFromFile(menuList, &menuCount)) {
        printf("Lỗi tải menu\n");
        return 1;
    }

    printMenu(menuList, menuCount);
    updateMenuList();

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(addBtn, "clicked", G_CALLBACK(on_add_clicked), window);
    g_signal_connect(editBtn, "clicked", G_CALLBACK(on_edit_clicked), window);
    g_signal_connect(deleteBtn, "clicked", G_CALLBACK(on_delete_clicked), window);
    g_signal_connect(confirmBtn, "clicked", G_CALLBACK(on_confirm_clicked), window);

    load_css("UI_MenuMana.css");
    gtk_widget_show_all(window);
    gtk_main();

    g_object_unref(builder);
    return 0;
}