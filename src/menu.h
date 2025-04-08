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
    char image_path[256];    // Đường dẫn đến ảnh món (thêm để hỗ trợ giao diện GTK)
} MenuItem;

// Cấu trúc dữ liệu cho một món trong đơn hàng (dành cho giao diện khách hàng)
typedef struct {
    char name[100];          // Tên món
    int quantity;            // Số lượng
    float price;             // Giá
} OrderItem;

// Biến toàn cục
extern MenuItem menuList[MAX_MENU_ITEMS];  // Danh sách món ăn
extern int menu_count;                     // Số lượng món ăn
extern GList *order_items;                 // Danh sách món trong đơn hàng
extern GtkBuilder *builder;                // Đối tượng để tải giao diện từ Glade

// Hàm quản lý món ăn (giữ nguyên từ code cũ)
int loadMenuFromFile(MenuItem menuList[], int *count);
void saveMenuToFile(MenuItem menuList[], int count);
int checkDuplicate(MenuItem menuList[], int count, char menuId[], char dishName[]);
void addItem(MenuItem menuList[], int *count);
void deleteItem(MenuItem menuList[], int *count);
void editItem(MenuItem menuList[], int *count);

// Hàm khởi tạo và tải giao diện
void load_customer_ui();       // Tải giao diện khách hàng
void load_manager_ui();        // Tải giao diện quản lý
void load_css(const char *css_file);  // Tải file CSS

// Hàm xử lý giao diện khách hàng
void populate_menu_items();    // Hiển thị danh sách món ăn
void on_add_item_clicked(GtkButton *button, gpointer user_data);  // Thêm món vào đơn hàng
void on_delete_item_clicked(GtkButton *button, gpointer user_data);  // Xóa món khỏi đơn hàng
void on_confirm_order_clicked(GtkButton *button, gpointer user_data);  // Xác nhận đơn hàng
void update_order_list();      // Cập nhật bảng đơn hàng

//Hàm xử lý giao diện quản lý
void populate_menu_tree_view();  // Hiển thị danh sách món trong TreeView
void on_menu_tree_view_row_activated(GtkTreeView *tree_view, GtkTreePath *path, 
                                     GtkTreeViewColumn *column, gpointer user_data);  // Chọn một món
void on_button_add_clicked(GtkButton *button, gpointer user_data);  // Thêm món mới
void on_button_edit_clicked(GtkButton *button, gpointer user_data);  // Sửa món
void on_button_delete_clicked(GtkButton *button, gpointer user_data);  // Xóa món
void on_button_confirm_clicked(GtkButton *button, gpointer user_data);  // Xác nhận thêm/sửa món
void update_menu_item_details(MenuItem *item);  // Cập nhật thông tin món đã chọn

#endif // MENU_H