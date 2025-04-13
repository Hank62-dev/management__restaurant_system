#ifndef MENU_H
#define MENU_H

#include <gtk/gtk.h>

#define MAX_MENU_ITEMS 100

// Cấu trúc dữ liệu cho một món ăn
typedef struct {
    char menuId[6];          // Mã món (Fxxxx hoặc Dxxxx)
    char dishName[100];      // Tên món
    char category[100];      // Loại món (Đồ ăn/Nước uống)
    float price;             // Giá món
    char image_path[256];    // Đường dẫn đến ảnh món
} MenuItem;

// Cấu trúc dữ liệu cho một món trong đơn hàng
typedef struct {
    char name[100];          // Tên món
    int quantity;            // Số lượng
    float price;             // Giá
} OrderItem;

// Biến toàn cục
extern MenuItem menuList[MAX_MENU_ITEMS];
extern int menu_count;
extern GList *order_items;
extern GtkBuilder *builder;

// Hàm chung
int loadMenuFromFile(MenuItem menuList[], int *count);
void saveMenuToFile(MenuItem menuList[], int count);
int checkDuplicate(MenuItem menuList[], int count, char menuId[], char dishName[]);
void load_css(const char *css_file);

// Hàm giao diện khách hàng
void load_customer_ui();
void populate_menu_items();
void on_add_item_clicked(GtkButton *button, gpointer user_data);
void on_delete_item_clicked(GtkButton *button, gpointer user_data);
void on_confirm_order_clicked(GtkButton *button, gpointer user_data);
void update_order_list();

// Hàm giao diện quản lý
void load_manager_ui();
void populate_menu_tree_view();
void on_menu_tree_view_row_activated(GtkTreeView *tree_view, GtkTreePath *path, 
                                     GtkTreeViewColumn *column, gpointer user_data);
void on_button_add_clicked(GtkButton *button, gpointer user_data);
void on_button_edit_clicked(GtkButton *button, gpointer user_data);
void on_button_delete_clicked(GtkButton *button, gpointer user_data);
void on_button_confirm_clicked(GtkButton *button, gpointer user_data);
void update_menu_item_details(MenuItem *item);

// Hàm xử lý button điều hướng
void on_button_home_clicked(GtkButton *button, gpointer user_data);
void on_button_menu_clicked(GtkButton *button, gpointer user_data);
void on_button_booking_clicked(GtkButton *button, gpointer user_data);
void on_button_bill_clicked(GtkButton *button, gpointer user_data);

#endif // MENU_H