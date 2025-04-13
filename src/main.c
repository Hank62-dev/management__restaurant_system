#include <stdio.h>
#include <stdlib.h>
#include "employees.h"
#include <gtk/gtk.h>

GtkWidget *home_m_window;
GtkWidget *employee_window;
GtkWidget *home_c_window;
//lay du lieu tu search entry
int get_search_entry_id(GtkBuilder *builder) {
    GtkSearchEntry *search_entry = GTK_SEARCH_ENTRY(gtk_builder_get_object(builder, "entry_search_id"));
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(search_entry));
    int id = atoi(text);  // Chuyển chuỗi thành số nguyên
    return id;
}
      //======CALLBACK HÀM======
    //home_m
    void on_btn_home_m_clicked(GtkWidget *widget, gpointer data) {
        gtk_widget_hide(home_c_window);
        gtk_widget_hide(employee_window);
        gtk_widget_show_all(home_m_window);
    }
    
    void on_btn_menu_m_clicked(GtkWidget *widget, gpointer data) {
        g_print("Go to MENU (home_m)\n");

    }

    
    void on_btn_stats_m_clicked(GtkWidget *widget, gpointer data) {
        g_print("Go to STATS (home_m)\n");

    }
    
    void on_btn_employee_m_clicked(GtkWidget *widget, gpointer data) {
        g_print("Go to EMPLOYEE (home_m)\n");
        gtk_widget_hide(home_m_window);
        gtk_widget_show_all(employee_window);
    }

    //home_c
    void on_btn_home_c_clicked(GtkWidget *widget, gpointer data) {
        gtk_widget_hide(home_m_window);
        gtk_widget_hide(employee_window);
        gtk_widget_show_all(home_c_window);
    }
    
    void on_btn_menu_c_clicked(GtkWidget *widget, gpointer data) {
         g_print("Go to MENU (home_c)\n");

    }
    
    void on_btn_booking_c_clicked(GtkWidget *widget, gpointer data) {
        g_print("Go to BOOKING (home_c)\n");
    }
    
    void on_btn_orders_c_clicked(GtkWidget *widget, gpointer data) {
        g_print("Go to ORDERS (home_c)\n");
    }
// employee
    // Hàm thêm nhân viên
    void on_btn_add_clicked(GtkWidget *widget, gpointer data) {
        addEmployee();  
        g_print("Add button clicked.\n");
    }
    // Hàm cập nhật nhân viên
    void on_btn_edit_clicked(GtkWidget *widget, gpointer data) {
          GtkBuilder *builder = GTK_BUILDER(user_data);

         int id = get_search_entry_id(builder);
         updateEmployee(employees, &count, id);
     }
     // Hàm xóa nhân viên
        g_print("Edit button clicked.\n");
        void on_btn_delete_clicked(GtkWidget *widget, gpointer data) {
         GtkBuilder *builder = GTK_BUILDER(user_data);
        int id = get_search_entry_id(builder);
         deleteEmployee(employees, &count, id);
        g_print("Delete button clicked.\n");
    }
    // Hàm tìm nhân viên
         void on_btn_find_clicked(GtkWidget *widget, gpointer data) {
         GtkBuilder *builder = GTK_BUILDER(user_data);
          int id = get_search_entry_id(builder);
          searchEmployee(employees, count, id);;  
         g_print("Find button clicked.\n");
    }
    


int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkCssProvider *css_provider;
    GdkDisplay *display;
    GdkScreen *screen;

    gtk_init(&argc, &argv);

    // Load file Glade
    builder = gtk_builder_new_from_file("UI Glade/home_c.glade");

    // Lấy widget từ Glade
    home_c_window = GTK_WIDGET(gtk_builder_get_object(builder, "home_c_window"));
     home_m_window = GTK_WIDGET(gtk_builder_get_object(builder, "home_m_window"));
    employee_window = GTK_WIDGET(gtk_builder_get_object(builder, "employee_window"));

    // Kết nối tín hiệu nút
    GtkWidget *btn_home_c = GTK_WIDGET(gtk_builder_get_object(builder, "btn_home_c"));
     GtkWidget *btn_home_m = GTK_WIDGET(gtk_builder_get_object(builder, "btn_home_m"));
    GtkWidget *btn_employee = GTK_WIDGET(gtk_builder_get_object(builder, "btn_employee"));
    g_signal_connect(btn_home_c, "clicked", G_CALLBACK(on_btn_home_c_licked), NULL);
    g_signal_connect(btn_employee, "clicked", G_CALLBACK(on_btn_employee_clicked), NULL);
    g_signal_connect(btn_home_m, "clicked", G_CALLBACK(on_btn_home_m_clicked), NULL);
// ======== home_c_window: LẤY VÀ KẾT NỐI NÚT ========
GtkWidget *btn_home_c     = GTK_WIDGET(gtk_builder_get_object(builder, "btn_home_c"));
GtkWidget *btn_menu_c     = GTK_WIDGET(gtk_builder_get_object(builder, "btn_menu_c"));
GtkWidget *btn_booking_c  = GTK_WIDGET(gtk_builder_get_object(builder, "btn_booking_c"));
GtkWidget *btn_orders_c   = GTK_WIDGET(gtk_builder_get_object(builder, "btn_orders_c"));

g_signal_connect(btn_home_c,    "clicked", G_CALLBACK(on_btn_home_c_clicked), NULL);
g_signal_connect(btn_menu_c,    "clicked", G_CALLBACK(on_btn_menu_c_clicked), NULL);
g_signal_connect(btn_booking_c, "clicked", G_CALLBACK(on_btn_booking_c_clicked), NULL);
g_signal_connect(btn_orders_c,  "clicked", G_CALLBACK(on_btn_orders_c_clicked), NULL);

// ======== home_m_window: LẤY VÀ KẾT NỐI NÚT ========
GtkWidget *btn_home_m     = GTK_WIDGET(gtk_builder_get_object(builder, "btn_home_m"));
GtkWidget *btn_menu_m     = GTK_WIDGET(gtk_builder_get_object(builder, "btn_menu_m"));
GtkWidget *btn_stats_m    = GTK_WIDGET(gtk_builder_get_object(builder, "btn_stats_m"));
GtkWidget *btn_employee_m = GTK_WIDGET(gtk_builder_get_object(builder, "btn_employee_m"));

g_signal_connect(btn_home_m,     "clicked", G_CALLBACK(on_btn_home_m_clicked), NULL);
g_signal_connect(btn_menu_m,     "clicked", G_CALLBACK(on_btn_menu_m_clicked), NULL);
g_signal_connect(btn_stats_m,    "clicked", G_CALLBACK(on_btn_stats_m_clicked), NULL);
g_signal_connect(btn_employee_m, "clicked", G_CALLBACK(on_btn_employee_m_clicked), NULL);


 // ======== employee_window: LẤY VÀ KẾT NỐI NÚT ========
 tkWidget *btn_add    = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add"));
GtkWidget *btn_edit     = GTK_WIDGET(gtk_builder_get_object(builder, "btn_edit"));
GtkWidget *btn_delete   = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete"));
GtkWidget *btn_find = GTK_WIDGET(gtk_builder_get_object(builder, "btn_find"));

g_signal_connect(btn_add,     "clicked", G_CALLBACK(on_btn_add_clicked), NULL);
g_signal_connect(btn_edit,     "clicked", G_CALLBACK(on_btn_edit_clicked), NULL);
g_signal_connect(btn_delete,    "clicked", G_CALLBACK(on_btn_delete_clicked), NULL);
g_signal_connect(btn_find, "clicked", G_CALLBACK(on_btn_find_clicked), NULL);
    // Kiểm tra lại tín hiệu có được kết nối không
    if (!btn_home_c) {
        g_print("btn_home_c is NULL!\n");
    }
    if (!btn_employee) {
        g_print("btn_employee is NULL!\n");
    }
 if (!btn_home_m) {
        g_print("btn_home_m is NULL!\n");
    }
    // Load CSS
    css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "Glade_CSS/home_m.css", NULL);
    gtk_css_provider_load_from_path(css_provider, "Glade_CSS/home_c.css", NULL);
    gtk_css_provider_load_from_path(css_provider, "Glade_CSS/employee.css", NULL);
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen,
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);

    //               Hiển thị cửa sổ chính
    //cho nay them cai if de hien cua so C(customer) hay m(maneger)
    gtk_widget_show_all(home_c_window);
    gtk_main();

    return 0;
//	calculate_revenue_by_day();
}
