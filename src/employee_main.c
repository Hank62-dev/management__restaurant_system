#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "employees.h"
#include <math.h>


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
    GtkWidget *entry_id = GTK_WIDGET(gtk_builder_get_object(builder, "entry_id"));
    GtkWidget *entry_name = GTK_WIDGET(gtk_builder_get_object(builder, "entry_name"));
    GtkWidget *entry_position = GTK_WIDGET(gtk_builder_get_object(builder, "entry_position"));
    GtkWidget *entry_salary = GTK_WIDGET(gtk_builder_get_object(builder, "entry_salary"));
    GtkWidget *treeview = GTK_WIDGET(gtk_builder_get_object(builder, "employee_treeview"));

    const gchar *id_str = gtk_entry_get_text(GTK_ENTRY(entry_id));
    const gchar *name_str = gtk_entry_get_text(GTK_ENTRY(entry_name));
    const gchar *position_str = gtk_entry_get_text(GTK_ENTRY(entry_position));
    const gchar *salary_str = gtk_entry_get_text(GTK_ENTRY(entry_salary));

    int id = atoi(id_str);
    float salary = atof(salary_str);

    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    GtkListStore *store = GTK_LIST_STORE(model);

    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       0, id,
                       1, name_str,
                       2, position_str,
                       3, salary,
                       -1);
}

// lay du lieu tu search
int get_search_entry_id(GtkBuilder *builder) {
    GtkSearchEntry *search_entry = GTK_SEARCH_ENTRY(gtk_builder_get_object(builder, "entry_search_id"));
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(search_entry));
    int id = atoi(text);
    return id;
}
void load_employees_from_file(GtkListStore *store, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        g_print("Cant open file: %s\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Employee emp;
        char *token;

        token = strtok(line, "|");
        if (token) emp.employeeId = atoi(token);

        token = strtok(NULL, "|");
        if (token) {
            strcpy(emp.fullName, token);
            emp.fullName[strcspn(emp.fullName, "\n")] = '\0';
        }

        token = strtok(NULL, "|");
        if (token) {
            strcpy(emp.position, token);
            emp.position[strcspn(emp.position, "\n")] = '\0';
        }

        token = strtok(NULL, "|");
        if (token) emp.salary = atof(token);
        emp.salary = roundf(atof(token) * 100) / 100;

        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, emp.employeeId,
                           1, emp.fullName,
                           2, emp.position,
                           3, emp.salary,
                           -1);

        g_print("Loaded: %d | %s | %s | %.2f\n", emp.employeeId, emp.fullName, emp.position, emp.salary);
    }

    fclose(file);
}

/*/ham hien thi
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
}*/

//Ham xu ly employee
void on_btn_add_clicked(GtkWidget *widget, gpointer data) {
    addEmployeeFromUI(builder, employees,&count) ;
    saveToFile(employees, &count);
    return;
}
    void on_btn_edit_clicked(GtkWidget *widget, gpointer data) {
        GtkBuilder *builder = GTK_BUILDER(data);
        int id = get_search_entry_id(builder);
        loadFromFile(employees, &count);
        updateEmployee(employees, &count, id);      // ← xử lý sửa
                return;
            } 
    void on_btn_delete_clicked(GtkWidget *widget, gpointer data) {
        GtkBuilder *builder = GTK_BUILDER(data);
        Employee employees[100];
        int count = 0;
        int id = get_search_entry_id(builder);
        loadFromFile(employees, &count);
        deleteEmployee(employees, &count, id);      
            return;
    }

    void on_btn_find_clicked(GtkWidget *widget, gpointer data) {
        GtkBuilder *builder = GTK_BUILDER(data);
        int id = get_search_entry_id(builder);
        loadFromFile(employees, &count);
        searchEmployee(employees, count ,id); 
             return;
            }
    void setup_treeview(GtkBuilder *builder) {
        GtkWidget *treeview;
        GtkListStore *store;
        GtkCellRenderer *renderer;
    
        // Lấy treeview từ Glade (đảm bảo ID đúng trong file .glade)
        treeview = GTK_WIDGET(gtk_builder_get_object(builder, "employee_treeview"));
    
        // Tạo model với 4 cột: ID (int), Name (string), Position (string), Salary (float)
        store = gtk_list_store_new(4, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_FLOAT);
    
        // Gán model cho treeview
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        g_object_unref(store); // Giải phóng sau khi gán model
    
        // Tạo từng cột riêng biệt
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
                                                    "ID", renderer, "text", 0, NULL);
    
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
                                                    "Name", renderer, "text", 1, NULL);
    
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
                                                    "Position", renderer, "text", 2, NULL);
    
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
                                                    "Salary", renderer, "text", 3, NULL);
    }
    
    
// ==== lay entry ===

int main(int argc, char *argv[]) {
    GtkWidget *treeview;
    GtkBuilder *builder;
    GtkWidget *window;
    GtkListStore *store;
    GtkCellRenderer *renderer;

    gtk_init(&argc, &argv);
<<<<<<< HEAD
          // === Khởi tạo builder và load file Glade ===
          builder = gtk_builder_new_from_file("UI_Glade/employee.glade");
          if (!gtk_builder_add_from_file(builder, "UI_Glade/employee.glade", NULL)) {
              g_print(" Cant not load file Glade\n");
              return 1;
          }
      
          // === Lấy window chính ===
          window = GTK_WIDGET(gtk_builder_get_object(builder, "employee_window"));
          if (!window) {
              g_print(" Cant find window 'employee_window'in Glade\n");
              return 1;
          }
=======
        // === Khởi tạo builder và load file Glade ===
        builder = gtk_builder_new();
        if (!gtk_builder_add_from_file(builder, "UI_Glade/employee.glade", NULL)) {
            g_print("❌ Cant not load file Glade\n");
            return 1;
        }
>>>>>>> 18bbe1258c95b014c7991539a7f200188e24719e
    

    window = GTK_WIDGET(gtk_builder_get_object(builder, "employee_window"));
    treeview = GTK_WIDGET(gtk_builder_get_object(builder, "employee_treeview"));

    store = gtk_list_store_new(4,G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_FLOAT);
    load_employees_from_file(store, "data/employees.txt");
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "Id", renderer, "text", 0, NULL);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "Name", renderer, "text", 1, NULL);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "Position", renderer, "text", 2, NULL);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "Salary", renderer, "text", 3, NULL);

  
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