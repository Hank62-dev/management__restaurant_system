#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
GtkWidget *employee_window;
GtkWidget *btn_add, *btn_edit, *btn_delete, *btn_find;
GtkWidget *entry_search_id;
//load css
void apply_css(GtkWidget *widget, GtkCssProvider *provider) {
	
    if( gtk_css_provider_load_from_path(provider, "Glade_CSS/employee.css", NULL) ){
    	g_print("CSS loaded successfully!!\n");
	}else{
		g_print("CSS load error!!!!\n");
	}
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    if (GTK_IS_CONTAINER(widget)) {
        gtk_container_foreach(GTK_CONTAINER(widget), (GtkCallback)apply_css, provider);
    };
}
    void on_btn_add_clicked(GtkWidget *widget, gpointer data) {
        addEmployee(employees, &count);
    }
// lay du lieu tu search
nt get_search_entry_id(GtkBuilder *builder) {
    GtkSearchEntry *search_entry = GTK_SEARCH_ENTRY(gtk_builder_get_object(builder, "entry_search_id"));
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(search_entry));
    int id = atoi(text);
    return id;
}
//ham hien thi
void displayEmployeeInfo(GtkBuilder *builder, Employee emp) {
    GtkEntry *entry_name = GTK_ENTRY(gtk_builder_get_object(builder, "entry_name"));
    GtkEntry *entry_position = GTK_ENTRY(gtk_builder_get_object(builder, "entry_position"));
    GtkEntry *entry_salary = GTK_ENTRY(gtk_builder_get_object(builder, "entry_salary"));

    gtk_entry_set_text(entry_name, emp.name);
    gtk_entry_set_text(entry_position, emp.position);

    char salary_str[20];
    sprintf(salary_str, "%d", emp.salary);
    gtk_entry_set_text(entry_salary, salary_str);
}

//Ham xu ly employee
    void on_btn_edit_clicked(GtkWidget *widget, gpointer data) {
        GtkBuilder *builder = GTK_BUILDER(data);
        int id = get_search_entry_id(builder);
        for (int i = 0; i < count; i++) {
            if (employees[i].id == id) {
                displayEmployeeInfo(builder, employees[i]); // ← hiển thị trước
                updateEmployee(employees, &count, id);      // ← xử lý sửa
                return;
            }
        }
        g_print("Không tìm thấy nhân viên ID %d\n", id);
    }
    
    void on_btn_delete_clicked(GtkWidget *widget, gpointer data) {
        GtkBuilder *builder = GTK_BUILDER(data);
        int id = get_search_entry_id(builder);
        for (int i = 0; i < count; i++) {
            if (employees[i].id == id) {
                displayEmployeeInfo(builder, employees[i]); // ← hiển thị trước
               deleteEmployee(employees, &count, id);      // ← xử lý sửa
                return;
            }
        }
        g_print("Không tìm thấy nhân viên ID %d\n", id);
    }
    
    void on_btn_find_clicked(GtkWidget *widget, gpointer data) {
        GtkBuilder *builder = GTK_BUILDER(data);
        int id = get_search_entry_id(builder);
        for (int i = 0; i < count; i++) {
            if (employees[i].id == id) {
                displayEmployeeInfo(builder, employees[i]); // <-- hiển thị thông tin
                g_print("Đã tìm thấy nhân viên ID %d\n", id);
                return;
            }
        }
    
        g_print("Không tìm thấy nhân viên ID %d\n", id);
    }
// ==== lay entry ===

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
entry_search_id = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_id"));

GtkWidget *btn_add = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add"));
GtkWidget *btn_edit = GTK_WIDGET(gtk_builder_get_object(builder, "btn_edit"));
GtkWidget *btn_delete = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete"));
GtkWidget *btn_find   = GTK_WIDGET(gtk_builder_get_object(builder, "btn_find"));


g_signal_connect(btn_add,    "clicked", G_CALLBACK(on_btn_add_clicked), builder);
g_signal_connect(btn_edit,   "clicked", G_CALLBACK(on_btn_edit_clicked), builder);
g_signal_connect(btn_delete, "clicked", G_CALLBACK(on_btn_delete_clicked), builder);
g_signal_connect(btn_find, "clicked", G_CALLBACK(on_btn_find_clicked), builder);

    // Áp dụng CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    apply_css(window, provider);
    g_object_unref(provider);
    
    gtk_widget_show_all(window);
    gtk_main();
    
    return 0;
    
}