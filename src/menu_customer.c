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

void load_customer_ui() {
    builder = gtk_builder_new();
    GError *error = NULL;
    if (gtk_builder_add_from_file(builder, "UI Glade/UI_MenuCus.glade", &error) == 0) {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        g_object_unref(builder);
        return;
    }

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "menuCustomer"));
    if (!window) {
        g_printerr("Error: Could not find menuCustomer window\n");
        g_object_unref(builder);
        return;
    }

    gtk_builder_connect_signals(builder, NULL);
    populate_menu_items();
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
}

void populate_menu_items() {
    GtkWidget *menu_list = GTK_WIDGET(gtk_builder_get_object(builder, "menuListItemSelect"));
    for (int i = 0; i < menu_count; i++) {
        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_widget_set_name(box, g_strdup_printf("menuListItem%d", i + 1));

        GtkWidget *image = gtk_image_new_from_icon_name("gtk-missing-image", GTK_ICON_SIZE_DIALOG);
        if (menuList[i].image_path[0] != '\0') {
            gtk_image_set_from_file(GTK_IMAGE(image), menuList[i].image_path);
        }
        gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 0);

        GtkWidget *name_label = gtk_label_new(menuList[i].dishName);
        gtk_box_pack_start(GTK_BOX(box), name_label, FALSE, FALSE, 0);

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

void on_add_item_clicked(GtkButton *button, gpointer user_data) {
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

void update_order_list() {
    GtkWidget *tree_view = GTK_WIDGET(gtk_builder_get_object(builder, "menuListItemSelected"));
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

void on_confirm_order_clicked(GtkButton *button, gpointer user_data) {
    g_list_free_full(order_items, g_free);
    order_items = NULL;
    update_order_list();
    g_print("Đơn hàng đã được xác nhận!\n");
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
}
