#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "employees.h"

extern Employee employees[];
extern int count;
GtkBuilder *builder;
GtkWidget *window;
GtkWidget *employee_window;
GtkWidget *btn_add, *btn_edit, *btn_delete, *btn_find;
GtkWidget *entry_search_id;
GtkWidget *employee_treeview;

//load css
void apply_css(GtkWidget *widget, GtkCssProvider *provider) {
	
    if( gtk_css_provider_load_from_path(provider, "Glade_CSS/employee.css", NULL) ){
    	g_print("CSS loaded successfully!!\n");
	}else{
		g_print("CSS load error!!!\n");
	}
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    if (GTK_IS_CONTAINER(widget)) {
        gtk_container_foreach(GTK_CONTAINER(widget), (GtkCallback)apply_css, provider);
    };
}
    // lay du lieu tu entry vào add 
    void addEmployeeFromUI(GtkBuilder *builder, Employee employees[], int *count) {
        const char *id_str = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_id")));
        const char *name_str = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_name")));
        const char *position_str = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_position")));
        const char *salary_str = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_salary")));
    
        // Gán giá trị vào employees[*count]
        employees[*count].employeeId = atoi(id_str);
        strncpy(employees[*count].fullName, name_str, sizeof(employees[*count].fullName));
        strncpy(employees[*count].position, position_str, sizeof(employees[*count].position));
        employees[*count].salary = atof(salary_str);
    
        (*count)++;
        saveToFile(employees, count);
        printf("Employee added successfully!\n");
    }
// lay du lieu tu search
int get_search_entry_id(GtkBuilder *builder) {
    GtkSearchEntry *search_entry = GTK_SEARCH_ENTRY(gtk_builder_get_object(builder, "entry_search_id"));
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(search_entry));
    int id = atoi(text);
    return id;
}
//ham hien thi
void displayEmployeeInfo(GtkBuilder *builder, Employee emp) {
    GtkEntry *entry_id = GTK_ENTRY(gtk_builder_get_object(builder, "entry_id"));
    GtkEntry *entry_name = GTK_ENTRY(gtk_builder_get_object(builder, "entry_name"));
    GtkEntry *entry_position = GTK_ENTRY(gtk_builder_get_object(builder, "entry_position"));
    GtkEntry *entry_salary = GTK_ENTRY(gtk_builder_get_object(builder, "entry_salary"));

    gtk_entry_set_text(entry_name, emp.fullName);
    gtk_entry_set_text(entry_position, emp.position);

    char salary_str[20];
    sprintf(salary_str, "%d", emp.salary);
    gtk_entry_set_text(entry_salary, salary_str);
}

//Ham xu ly employee
    void on_btn_add_clicked(GtkWidget *widget, gpointer data) {
    addEmployeeFromUI(builder, employees, &count);}

    void on_btn_edit_clicked(GtkWidget *widget, gpointer data) {
        GtkBuilder *builder = GTK_BUILDER(data);
        int id = get_search_entry_id(builder);
        for (int i = 0; i < count; i++) {
            if (employees[i].employeeId == id) {
                displayEmployeeInfo(builder, employees[i]); // ← hiển thị trước
                updateEmployee(employees, &count, id);      // ← xử lý sửa
                return;
            }
        }
        g_print("Cant find this ID %d\n", id);
    }
    
    void on_btn_delete_clicked(GtkWidget *widget, gpointer data) {
        GtkBuilder *builder = GTK_BUILDER(data);
        int id = get_search_entry_id(builder);
        for (int i = 0; i < count; i++) {
            if (employees[i].employeeId == id) {
                displayEmployeeInfo(builder, employees[i]); // ← hiển thị trước
               deleteEmployee(employees, &count, id);      // ← xử lý sửa
                return;
            }
        }
        g_print("Cant find this ID %d\n", id);
    }
    
    void on_btn_find_clicked(GtkWidget *widget, gpointer data) {
        GtkBuilder *builder = GTK_BUILDER(data);
        int id = get_search_entry_id(builder);
        for (int i = 0; i < count; i++) {
            if (employees[i].employeeId == id) {
                displayEmployeeInfo(builder, employees[i]); // <-- hiển thị thông tin
                g_print("Đã tìm thấy nhân viên ID %d\n", id);
                return;
            }
        }
    
        g_print("Cant find this ID %d\n", id);
    }
    //treeview
    void setup_treeview(GtkBuilder *builder) {
        GtkWidget *treeview;
        GtkListStore *store;
        GtkCellRenderer *renderer;
        GtkTreeViewColumn *column;
        // Lấy đối tượng treeview từ file .glade

        // Tạo ListStore với 3 cột: ID, Name, Salary
        store = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_FLOAT);
    
        // Gán ListStore cho TreeView
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        g_object_unref(store); // Giải phóng sau khi gán model
    
        // Tạo renderer và thêm các cột
        renderer = gtk_cell_renderer_text_new();
    
        column = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
        column = gtk_tree_view_column_new_with_attributes("Position", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
        column = gtk_tree_view_column_new_with_attributes("Salary", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }
    
// ==== lay entry ===

int main(int argc, char *argv[]) {
    GtkWidget *treeview;
    GtkBuilder *builder;
    GtkWidget *window;
    GtkListStore *store;
    GtkCellRenderer *renderer;

    gtk_init(&argc, &argv);
        // === Khởi tạo builder và load file Glade ===
        builder = gtk_builder_new();
        if (!gtk_builder_add_from_file(builder, "UI_Glade/employee.glade", NULL)) {
            g_print("❌ Cant not load file Glade\n");
            return 1;
        }
    
        // === Lấy window chính ===
        window = GTK_WIDGET(gtk_builder_get_object(builder, "employee_window"));
        if (!window) {
            g_print("❌ Cant find window 'employee_window' trong Glade\n");
            return 1;
        }
entry_search_id = GTK_WIDGET(gtk_builder_get_object(builder, "entry_search_id"));
GtkWidget *btn_add = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add"));
GtkWidget *btn_edit = GTK_WIDGET(gtk_builder_get_object(builder, "btn_edit"));
GtkWidget *btn_delete = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete"));
GtkWidget *btn_find   = GTK_WIDGET(gtk_builder_get_object(builder, "btn_find"));

    gtk_style_context_add_class(gtk_widget_get_style_context(btn_add), "btn_add");
    gtk_style_context_add_class(gtk_widget_get_style_context(btn_edit), "btn_edit");
    gtk_style_context_add_class(gtk_widget_get_style_context(btn_delete), "btn_delete");
    gtk_style_context_add_class(gtk_widget_get_style_context(btn_find), "btn_find");
    gtk_style_context_add_class(gtk_widget_get_style_context(employee_window), "employee_window");

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