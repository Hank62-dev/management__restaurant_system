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

int checkDuplicate(MenuItem menuList[], int count, char id[], char dishName[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(menuList[i].menuId, id) == 0 || strcmp(menuList[i].dishName, dishName) == 0) {
            return 1;
        }
    }
    return 0;
}

void load_manager_ui() {
    builder = gtk_builder_new();
    GError *error = NULL;
    if (gtk_builder_add_from_file(builder, "UI Glade/UI_MenuMana.glade", &error) == 0) {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        g_object_unref(builder);
        return;
    }

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "menuManager"));
    if (!window) {
        g_printerr("Error: Could not find menuManager window\n");
        g_object_unref(builder);
        return;
    }

    gtk_builder_connect_signals(builder, NULL);
    populate_menu_tree_view();
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
}

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

void on_button_add_clicked(GtkButton *button, gpointer user_data) {
    if (menu_count >= MAX_MENU_ITEMS) {
        g_print("Menu đã đầy!\n");
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
        g_print("Lỗi: Món ăn hoặc mã món đã tồn tại!\n");
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
    g_print("Thêm món thành công!\n");
}

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
        g_print("Không tìm thấy món\n");
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
    g_print("Sửa món thành công!\n");
}

void on_button_delete_clicked(GtkButton *button, gpointer user_data) {
    if (menu_count == 0) {
        g_print("Menu không có món\n");
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
        g_print("Không tìm thấy món\n");
        return;
    }

    menuList[found] = menuList[--menu_count];
    saveMenuToFile(menuList, menu_count);
    populate_menu_tree_view();
    g_print("Xóa món thành công\n");
}

void on_button_confirm_clicked(GtkButton *button, gpointer user_data) {
    g_print("Xác nhận thành công!\n");
}

void on_button_home_clicked(GtkButton *button, gpointer user_data) {
    g_print("Home button clicked!\n");
}

void on_button_menu_clicked(GtkButton *button, gpointer user_data) {
    g_print("Menu button clicked!\n");
}

void on_button_booking_clicked(GtkButton *button, gpointer user_data) {
    g_print("Booking button clicked!\n");
}

void on_button_bill_clicked(GtkButton *button, gpointer user_data) {
    g_print("Bill button clicked!\n");
<<<<<<< HEAD
}
=======
}
>>>>>>> 680354f2caa3a94ab1db6a154d995f8d1a814a49
