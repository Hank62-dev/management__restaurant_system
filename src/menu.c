#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

// Định nghĩa biến toàn cục
MenuItem menuList[MAX_MENU_ITEMS];
int menu_count = 0;
GList *order_items = NULL;
GtkBuilder *builder = NULL;

void load_css(const char *css_file) {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen,
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GError *error = NULL;
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(css_file), &error);

    if (error != NULL) {
        g_printerr("Error loading CSS: %s\n", error->message);
        g_error_free(error);
    }

    g_object_unref(provider);
}

// Đọc menu từ file (giữ nguyên)
int loadMenuFromFile(MenuItem menuList[], int *count) {
    FILE *file = fopen("data/menu.txt", "r");
    if (!file) {
        perror("ERROR");
        return 0;
    }

    *count = 0;
    while (fscanf(file, "%s \"%[^\"]\" \"%[^\"]\" %f \"%[^\"]\"\n", 
                  menuList[*count].menuId, 
                  menuList[*count].dishName, 
                  menuList[*count].category, 
                  &menuList[*count].price,
                  menuList[*count].image_path) == 5) {
        (*count)++;
    }
    fclose(file);
    return 1;
}

// Lưu menu vào file (giữ nguyên)
void saveMenuToFile(MenuItem menuList[], int count) {
    FILE *file = fopen("data/menu.txt", "w");
    if (!file) {
        perror("ERROR");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s \"%s\" \"%s\" %.0f \"%s\"\n", 
                menuList[i].menuId, 
                menuList[i].dishName, 
                menuList[i].category, 
                menuList[i].price,
                menuList[i].image_path);
    }
    fclose(file);
}

// Kiểm tra trùng mã món hoặc tên món (giữ nguyên)
int checkDuplicate(MenuItem menuList[], int count, char id[], char dishName[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(menuList[i].menuId, id) == 0 || strcmp(menuList[i].dishName, dishName) == 0) {
            return 1; // Trùng
        }
    }
    return 0; // Không trùng
}

// Thêm món ăn (giữ nguyên)
void addItem(MenuItem menuList[], int *count) {
    if (*count >= MAX_MENU_ITEMS) {
        printf("Menu đã đầy!\n");
        return;
    }          
    printf("Nhập mã món (Fxxxx hoặc Dxxxx): ");
    scanf("%s", menuList[*count].menuId);
    getchar();
    printf("Nhập tên món: ");
    fgets(menuList[*count].dishName, 100, stdin);
    menuList[*count].dishName[strcspn(menuList[*count].dishName, "\n")] = 0;
    
    if (checkDuplicate(menuList, *count, menuList[*count].menuId, menuList[*count].dishName)) {
        printf("Lỗi: Món ăn hoặc mã món đã tồn tại!\n");
        return;
    }
    printf("Nhập loại (Đồ ăn/Nước uống): ");
    fgets(menuList[*count].category, 100, stdin);
    menuList[*count].category[strcspn(menuList[*count].category, "\n")] = 0;
    printf("Nhập giá: ");
    scanf("%f", &menuList[*count].price);
    getchar();
    // Mặc định image_path là rỗng (có thể cập nhật sau)
    strcpy(menuList[*count].image_path, "");
    (*count)++;
    saveMenuToFile(menuList, *count);
    printf("Thêm món thành công!\n");
}

// Xóa món ăn (giữ nguyên)
void deleteItem(MenuItem menuList[], int *count) {
    if (*count == 0) {
        printf("Menu không có món\n");
        return;
    }

    char id[6];
    printf("Nhập mã món cần xóa (Fxxxx/Dxxxx): ");
    scanf("%s", id);

    int found = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp(menuList[i].menuId, id) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Không tìm thấy món\n");
        return;
    }

    menuList[found] = menuList[--(*count)];  // Ghi đè phần tử cuối lên vị trí cần xóa, giảm count
    saveMenuToFile(menuList, *count);
    printf("Xóa món thành công\n");
}

// Sửa món ăn (giữ nguyên)
void editItem(MenuItem menuList[], int *count) {
    if (*count == 0) {
        printf("Menu không có món\n");
        return;
    }
    
    char id[6];
    printf("Nhập mã món cần sửa (Fxxxx/Dxxxx): ");
    scanf("%s", id);
    
    int found = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp(menuList[i].menuId, id) == 0) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Không tìm thấy món\n");
        return;
    }
    
    getchar();
    printf("Nhập tên mới: ");
    fgets(menuList[found].dishName, 100, stdin);
    menuList[found].dishName[strcspn(menuList[found].dishName, "\n")] = 0;
    printf("Nhập loại mới (Đồ ăn/Nước uống): ");
    scanf("%s", menuList[found].category);
    getchar();
    printf("Nhập giá mới: ");
    scanf("%f", &menuList[found].price);
    getchar();
    saveMenuToFile(menuList, *count);
    printf("Sửa món thành công!\n");
}

// Tải giao diện khách hàng
void load_customer_ui() {
    builder = gtk_builder_new_from_file("UI Glade/UI_MenuCus.glade");
    gtk_builder_connect_signals(builder, NULL);

    // Hiển thị cửa sổ chính
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "menuCustomer"));
    gtk_widget_show_all(window);

    // Hiển thị danh sách món ăn
    populate_menu_items();
}

// Tải giao diện quản lý
void load_manager_ui() {
    builder = gtk_builder_new_from_file("UI Glade/UI_MenuMana.glade");
    gtk_builder_connect_signals(builder, NULL);

    // Hiển thị cửa sổ chính
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "menuManager"));
    gtk_widget_show_all(window);

    // Hiển thị danh sách món trong TreeView
    populate_menu_tree_view();
}

// Hiển thị danh sách món ăn (giao diện khách hàng)
void populate_menu_items() {
    GtkWidget *menu_list = GTK_WIDGET(gtk_builder_get_object(builder, "menuListItemSelect"));
    for (int i = 0; i < menu_count; i++) {
        // Tạo một box cho mỗi món ăn
        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_widget_set_name(box, g_strdup_printf("menuListItem%d", i + 1));

        // Hình ảnh món (mặc định nếu không có ảnh)
        GtkWidget *image = gtk_image_new_from_icon_name("gtk-missing-image", GTK_ICON_SIZE_DIALOG);
        if (menuList[i].image_path[0] != '\0') {
            gtk_image_set_from_file(GTK_IMAGE(image), menuList[i].image_path);
        }
        gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 0);

        // Tên món
        GtkWidget *name_label = gtk_label_new(menuList[i].dishName);
        gtk_box_pack_start(GTK_BOX(box), name_label, FALSE, FALSE, 0);

        // Box chứa nút "-" giá và nút "+"
        GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        GtkWidget *delete_button = gtk_button_new_with_label("-");
        g_signal_connect(delete_button, "clicked", G_CALLBACK(on_delete_item_clicked), GINT_TO_POINTER(i));
        gtk_box_pack_start(GTK_BOX(button_box), delete_button, FALSE, FALSE, 0);

        char price_str[20];
        snprintf(price_str, sizeof(price_str), "%.0f", menuList[i].price);
        GtkWidget *price_label = gtk_label_new(price_str);
        gtk_box_pack_start(GTK_BOX(button_box), price_label, TRUE, TRUE, 0);

        GtkWidget *add_button = gtk_button_new_with_label("+");
        g_signal_connect(add_button, "clicked", G_CALLBACK(on_add_item_clicked), GINT_TO_POINTER(i));
        gtk_box_pack_start(GTK_BOX(button_box), add_button, FALSE, FALSE, 0);

        gtk_box_pack_start(GTK_BOX(box), button_box, FALSE, FALSE, 0);
        gtk_grid_attach(GTK_GRID(menu_list), box, i % 4, i / 4, 1, 1);
    }
    gtk_widget_show_all(menu_list);
}

// Thêm món vào đơn hàng
void on_add_item_clicked(GtkButton *button, gpointer user_data) {
    int index = GPOINTER_TO_INT(user_data);
    OrderItem *item = NULL;

    // Kiểm tra xem món đã có trong đơn hàng chưa
    for (GList *l = order_items; l != NULL; l = l->next) {
        OrderItem *existing_item = l->data;
        if (strcmp(existing_item->name, menuList[index].dishName) == 0) {
            item = existing_item;
            break;
        }
    }

    if (item) {
        item->quantity++;
    } else {
        item = g_new(OrderItem, 1);
        strcpy(item->name, menuList[index].dishName);
        item->quantity = 1;
        item->price = menuList[index].price;
        order_items = g_list_append(order_items, item);
    }

    update_order_list();
}

// Xóa món khỏi đơn hàng
void on_delete_item_clicked(GtkButton *button, gpointer user_data) {
    int index = GPOINTER_TO_INT(user_data);
    OrderItem *item = NULL;

    for (GList *l = order_items; l != NULL; l = l->next) {
        OrderItem *existing_item = l->data;
        if (strcmp(existing_item->name, menuList[index].dishName) == 0) {
            item = existing_item;
            break;
        }
    }

    if (item) {
        item->quantity--;
        if (item->quantity <= 0) {
            order_items = g_list_remove(order_items, item);
            g_free(item);
        }
        update_order_list();
    }
}

// Cập nhật bảng đơn hàng
void update_order_list() {
    GtkWidget *tree_view = GTK_WIDGET(gtk_builder_get_object(builder, "menuListItemSellected"));
    GtkListStore *store = gtk_list_store_new(4, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_FLOAT);
    int stt = 1;

    for (GList *l = order_items; l != NULL; l = l->next) {
        OrderItem *item = l->data;
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, stt++,
                           1, item->name,
                           2, item->quantity,
                           3, item->price * item->quantity,
                           -1);
    }

    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

// Xác nhận đơn hàng
void on_confirm_order_clicked(GtkButton *button, gpointer user_data) {
    // Lưu đơn hàng hoặc xử lý logic xác nhận (có thể lưu vào file)
    g_list_free_full(order_items, g_free);
    order_items = NULL;
    update_order_list();
    // Hiển thị thông báo (có thể thêm dialog)
    printf("Đơn hàng đã được xác nhận!\n");
}

// Hiển thị danh sách món trong TreeView (giao diện quản lý)
void populate_menu_tree_view() {
    GtkWidget *tree_view = GTK_WIDGET(gtk_builder_get_object(builder, "menuTreeView"));
    GtkListStore *store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_FLOAT);

    for (int i = 0; i < menu_count; i++) {
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, menuList[i].dishName,
                           1, menuList[i].price,
                           -1);
    }

    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

// Chọn một món trong TreeView
void on_menu_tree_view_row_activated(GtkTreeView *tree_view, GtkTreePath *path, 
                                     GtkTreeViewColumn *column, gpointer user_data) {
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    GtkTreeIter iter;
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gchar *name;
        gtk_tree_model_get(model, &iter, 0, &name, -1);

        for (int i = 0; i < menu_count; i++) {
            if (strcmp(menuList[i].dishName, name) == 0) {
                update_menu_item_details(&menuList[i]);
                break;
            }
        }
        g_free(name);
    }
}

// Cập nhật thông tin món đã chọn
void update_menu_item_details(MenuItem *item) {
    GtkWidget *label_id = GTK_WIDGET(gtk_builder_get_object(builder, "labelId"));
    GtkWidget *label_name = GTK_WIDGET(gtk_builder_get_object(builder, "labelName"));
    GtkWidget *label_category = GTK_WIDGET(gtk_builder_get_object(builder, "labelCategory"));
    GtkWidget *label_price = GTK_WIDGET(gtk_builder_get_object(builder, "labelPrice"));
    GtkWidget *image_display = GTK_WIDGET(gtk_builder_get_object(builder, "imageDisplay"));

    gtk_label_set_text(GTK_LABEL(label_id), item->menuId);
    gtk_label_set_text(GTK_LABEL(label_name), item->dishName);
    gtk_label_set_text(GTK_LABEL(label_category), item->category);
    char price_str[20];
    snprintf(price_str, sizeof(price_str), "%.0f", item->price);
    gtk_label_set_text(GTK_LABEL(label_price), price_str);

    if (item->image_path[0] != '\0') {
        gtk_image_set_from_file(GTK_IMAGE(image_display), item->image_path);
    } else {
        gtk_image_set_from_icon_name(GTK_IMAGE(image_display), "gtk-missing-image", GTK_ICON_SIZE_DIALOG);
    }
}

// Thêm món mới (giao diện quản lý)
void on_button_add_clicked(GtkButton *button, gpointer user_data) {
    if (menu_count >= MAX_MENU_ITEMS) {
        printf("Menu đã đầy!\n");
        return;
    }

    GtkWidget *entry_id = GTK_WIDGET(gtk_builder_get_object(builder, "entryId"));
    GtkWidget *entry_name = GTK_WIDGET(gtk_builder_get_object(builder, "entryName"));
    GtkWidget *entry_category = GTK_WIDGET(gtk_builder_get_object(builder, "entryCategory"));
    GtkWidget *entry_price = GTK_WIDGET(gtk_builder_get_object(builder, "entryPrice"));
    GtkWidget *image_chooser = GTK_WIDGET(gtk_builder_get_object(builder, "imageChooser"));

    const char *id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    const char *name = gtk_entry_get_text(GTK_ENTRY(entry_name));
    const char *category = gtk_entry_get_text(GTK_ENTRY(entry_category));
    const char *price_str = gtk_entry_get_text(GTK_ENTRY(entry_price));
    float price = atof(price_str);
    const char *image_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(image_chooser));

    if (checkDuplicate(menuList, menu_count, (char *)id, (char *)name)) {
        printf("Lỗi: Món ăn hoặc mã món đã tồn tại!\n");
        return;
    }

    strcpy(menuList[menu_count].menuId, id);
    strcpy(menuList[menu_count].dishName, name);
    strcpy(menuList[menu_count].category, category);
    menuList[menu_count].price = price;
    if (image_path) {
        strcpy(menuList[menu_count].image_path, image_path);
    } else {
        menuList[menu_count].image_path[0] = '\0';
    }

    menu_count++;
    saveMenuToFile(menuList, menu_count);
    populate_menu_tree_view();
    printf("Thêm món thành công!\n");
}

// Sửa món (giao diện quản lý)
void on_button_edit_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *label_id = GTK_WIDGET(gtk_builder_get_object(builder, "labelId"));
    const char *id = gtk_label_get_text(GTK_LABEL(label_id));

    int found = -1;
    for (int i = 0; i < menu_count; i++) {
        if (strcmp(menuList[i].menuId, id) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Không tìm thấy món\n");
        return;
    }

    GtkWidget *entry_name = GTK_WIDGET(gtk_builder_get_object(builder, "entryName"));
    GtkWidget *entry_category = GTK_WIDGET(gtk_builder_get_object(builder, "entryCategory"));
    GtkWidget *entry_price = GTK_WIDGET(gtk_builder_get_object(builder, "entryPrice"));
    GtkWidget *image_chooser = GTK_WIDGET(gtk_builder_get_object(builder, "imageChooser"));

    const char *name = gtk_entry_get_text(GTK_ENTRY(entry_name));
    const char *category = gtk_entry_get_text(GTK_ENTRY(entry_category));
    const char *price_str = gtk_entry_get_text(GTK_ENTRY(entry_price));
    float price = atof(price_str);
    const char *image_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(image_chooser));

    strcpy(menuList[found].dishName, name);
    strcpy(menuList[found].category, category);
    menuList[found].price = price;
    if (image_path) {
        strcpy(menuList[found].image_path, image_path);
    }

    saveMenuToFile(menuList, menu_count);
    populate_menu_tree_view();
    update_menu_item_details(&menuList[found]);
    printf("Sửa món thành công!\n");
}

// Xóa món (giao diện quản lý)
void on_button_delete_clicked(GtkButton *button, gpointer user_data) {
    if (menu_count == 0) {
        printf("Menu không có món\n");
        return;
    }

    GtkWidget *label_id = GTK_WIDGET(gtk_builder_get_object(builder, "labelId"));
    const char *id = gtk_label_get_text(GTK_LABEL(label_id));

    int found = -1;
    for (int i = 0; i < menu_count; i++) {
        if (strcmp(menuList[i].menuId, id) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Không tìm thấy món\n");
        return;
    }

    menuList[found] = menuList[--menu_count];
    saveMenuToFile(menuList, menu_count);
    populate_menu_tree_view();
    printf("Xóa món thành công\n");
}

// Xác nhận thêm/sửa món
void on_button_confirm_clicked(GtkButton *button, gpointer user_data) {
    // Logic xác nhận đã được xử lý trong on_button_add_clicked và on_button_edit_clicked
    printf("Xác nhận thành công!\n");
}