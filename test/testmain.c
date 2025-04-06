#include <gtk/gtk.h>
#include "employees.h"

Employee employees[MAX_EMPLOYEES];
int employee_count = 0;

// Widget toàn cục
GtkWidget *home_window;
GtkWidget *employee_window;
GtkTreeView *tree_employee;
GtkListStore *liststore;

// Hàm load CSS
void load_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "Glade_CSS/Home + employee.css", NULL);

    GdkScreen *screen = gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(screen,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
}

// Hiển thị dữ liệu nhân viên vào GtkTreeView
void load_employee_to_treeview() {
    GtkTreeIter iter;
    gtk_list_store_clear(liststore);

    loadFromFile(employees, &employee_count);

    for (int i = 0; i < employee_count; i++) {
        char id[10], salary[20];
        sprintf(id, "%d", employees[i].employeeId);
        sprintf(salary, "%.2f", employees[i].salary);

        gtk_list_store_append(liststore, &iter);
        gtk_list_store_set(liststore, &iter,
                           0, id,
                           1, employees[i].fullName,
                           2, employees[i].position,
                           3, salary,
                           -1);
    }
}

// Sự kiện khi nhấn nút "Employee"
void on_btn_employee_clicked(GtkButton *button, gpointer user_data) {
    gtk_widget_hide(home_window);
    gtk_widget_show_all(employee_window);
    load_employee_to_treeview();
}

// Sự kiện quay về Home
void on_btnhome_clicked(GtkButton *button, gpointer user_data) {
    gtk_widget_hide(employee_window);
    gtk_widget_show_all(home_window);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    load_css();

    GtkBuilder *builder = gtk_builder_new_from_file("UI Glade/UI Home + employee.glade");

    // Lấy các widget
    home_window = GTK_WIDGET(gtk_builder_get_object(builder, "home_window"));
    employee_window = GTK_WIDGET(gtk_builder_get_object(builder, "employee_window"));

    GtkWidget *btn_employee = GTK_WIDGET(gtk_builder_get_object(builder, "btn_employee"));
    GtkWidget *btnhome = GTK_WIDGET(gtk_builder_get_object(builder, "btnhome"));

    tree_employee = GTK_TREE_VIEW(gtk_builder_get_object(builder, "tree_employee"));
    liststore = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));

    // Gắn sự kiện
    g_signal_connect(btn_employee, "clicked", G_CALLBACK(on_btn_employee_clicked), NULL);
    g_signal_connect(btnhome, "clicked", G_CALLBACK(on_btnhome_clicked), NULL);

    gtk_widget_show_all(home_window);
    gtk_main();

    return 0;
}
