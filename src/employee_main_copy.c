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
void apply_css_employee(GtkWidget *widget, GtkCssProvider *provider) {
	
    if( gtk_css_provider_load_from_path(provider, "Glade_CSS/employee.css", NULL) ){
    	g_print("CSS loaded successfully!!\n");
	}else{
		g_print("CSS load error!!!\n");
	}
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    if (GTK_IS_CONTAINER(widget)) {
        gtk_container_foreach(GTK_CONTAINER(widget), (GtkCallback)apply_css_employee, provider);
    };
}
void show_message(GtkWindow *parent, const gchar *message) {
    GtkWidget *dialog = gtk_message_dialog_new(
        parent,
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "%s", message
    );
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
    // lay du lieu tu entry vào add 
    void addEmployeeFromUI(GtkBuilder *builder, Employee employees[], int *count) {
        GtkWidget *entry_id       = GTK_WIDGET(gtk_builder_get_object(builder, "entry_id"));
        GtkWidget *entry_name     = GTK_WIDGET(gtk_builder_get_object(builder, "entry_name"));
        GtkWidget *entry_position = GTK_WIDGET(gtk_builder_get_object(builder, "entry_position"));
        GtkWidget *entry_salary   = GTK_WIDGET(gtk_builder_get_object(builder, "entry_salary"));
    
        const gchar *id_str       = gtk_entry_get_text(GTK_ENTRY(entry_id));
        const gchar *name_str     = gtk_entry_get_text(GTK_ENTRY(entry_name));
        const gchar *position_str = gtk_entry_get_text(GTK_ENTRY(entry_position));
        const gchar *salary_str   = gtk_entry_get_text(GTK_ENTRY(entry_salary));
    
        g_print("🔍 id='%s' | name='%s' | position='%s' | salary='%s'\n", id_str, name_str, position_str, salary_str);
    
        if (!id_str || !name_str || !position_str || !salary_str ||
            strlen(id_str) == 0 || strlen(name_str) == 0 || strlen(position_str) == 0 || strlen(salary_str) == 0) {
         show_message(GTK_WINDOW(parent_window), "Missing information!");
            return ;
        }
    
        if (*count >= MAX_EMPLOYEES) {
            g_print("Employee list is full.\n");
            return ;
        }
        int new_id = atoi(id_str);

        // 🔁 Kiểm tra trùng ID
        for (int i = 0; i < *count; i++) {
            if (employees[i].employeeId == new_id) {
                 show_message(GTK_WINDOW(parent_window),"Employee ID %d already exists. Cannot add.\n", new_id);
                return;
            }
        }
        employees[*count].employeeId = atoi(id_str);
        strncpy(employees[*count].fullName, name_str, sizeof(employees[*count].fullName) - 1);
        employees[*count].fullName[sizeof(employees[*count].fullName) - 1] = '\0';
    
        strncpy(employees[*count].position, position_str, sizeof(employees[*count].position) - 1);
        employees[*count].position[sizeof(employees[*count].position) - 1] = '\0';
    
        employees[*count].salary = atof(salary_str);
        (*count)++;
        saveToFile(employees, count);
        show_message(GTK_WINDOW(parent_window), "✅ Employee added successfully!");
    
    }

     void updateEmployeeFromUI(GtkBuilder *builder, Employee employees[], int *count, int id) {
        for (int i = 0; i < *count; i++) {
            if (employees[i].employeeId == id) {
                GtkWidget *entry_id       = GTK_WIDGET(gtk_builder_get_object(builder, "entry_id"));
                GtkWidget *entry_name     = GTK_WIDGET(gtk_builder_get_object(builder, "entry_name"));
                GtkWidget *entry_position = GTK_WIDGET(gtk_builder_get_object(builder, "entry_position"));
                GtkWidget *entry_salary   = GTK_WIDGET(gtk_builder_get_object(builder, "entry_salary"));

                const gchar *id_str       = gtk_entry_get_text(GTK_ENTRY(entry_id));
                const gchar *name_str     = gtk_entry_get_text(GTK_ENTRY(entry_name));
                const gchar *position_str = gtk_entry_get_text(GTK_ENTRY(entry_position));
                const gchar *salary_str   = gtk_entry_get_text(GTK_ENTRY(entry_salary));
    
                if (!name_str || !position_str || !salary_str ||
                    strlen(name_str) == 0 || strlen(position_str) == 0 || strlen(salary_str) == 0) {
                     show_message(GTK_WINDOW(parent_window)," Missing input fields during update!\n");
                    return;
                }
                int new_id = atoi(id_str);

                // Nếu ID bị thay đổi, kiểm tra xem có trùng không
                if (new_id != employees[i].employeeId) {
                    for (int j = 0; j < *count; j++) {
                        if (j != i && employees[j].employeeId == new_id) {
                             show_message(GTK_WINDOW(parent_window)," ID %d already exists. Cannot update.\n", new_id);
                            return;
                        }
                    }
                }
                employees[i].employeeId = new_id;
                strncpy(employees[i].fullName, name_str, sizeof(employees[i].fullName) - 1);
                employees[i].fullName[sizeof(employees[i].fullName) - 1] = '\0';
    
                strncpy(employees[i].position, position_str, sizeof(employees[i].position) - 1);
                employees[i].position[sizeof(employees[i].position) - 1] = '\0';
    
                employees[i].salary = atof(salary_str);
    
                // Ghi vào file theo định dạng `|`
                saveToFile(employees, count);
    
                g_print(" Updated employee with ID %d\n", id);
                return;
            }
        }
    
        show_message(GTK_WINDOW(parent_window)," Employee with ID %d not found for update.\n", id);
    }
// lay du lieu tu search
int get_search_entry_id(GtkBuilder *builder) {
    GtkSearchEntry *search_entry = GTK_SEARCH_ENTRY(gtk_builder_get_object(builder, "entry_search_id"));
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(search_entry));
    int id = atoi(text);
    return id;
}
void load_employees_from_file(GtkListStore *store, const char *filename, Employee employees[], int *count) {
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
    employees[*count] = emp;
    (*count)++;
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
//add
void on_btn_add_clicked(GtkWidget *widget, gpointer data) {
    GtkBuilder *builder = GTK_BUILDER(data);

    loadEmployeesToArrayOnly("data/employees.txt", employees, &count);
    addEmployeeFromUI(builder, employees, &count);
        GtkTreeView *treeview = GTK_TREE_VIEW(gtk_builder_get_object(builder, "employee_treeview"));
        GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
        loadEmployeesAll("data/employees.txt", employees, &count, store);
    }
        void on_btn_edit_clicked(GtkWidget *widget, gpointer data) {
            GtkBuilder *builder = GTK_BUILDER(data);
            int id = get_search_entry_id(builder);
        
            loadEmployeesToArrayOnly("data/employees.txt", employees, &count);
    
            updateEmployeeFromUI(builder, employees, &count, id);
        
            saveToFile(employees, &count);
        
            // Cập nhật lại TreeView
            GtkTreeView *treeview = GTK_TREE_VIEW(gtk_builder_get_object(builder, "employee_treeview"));
            GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
            loadEmployeesAll("data/employees.txt", employees, &count, store);
        }
    //delete
    void on_btn_delete_clicked(GtkWidget *widget, gpointer data) {
        GtkBuilder *builder = GTK_BUILDER(data);
        int id = get_search_entry_id(builder);
    
        loadEmployeesToArrayOnly("data/employees.txt", employees, &count);
        deleteEmployee(employees, &count, id);
        saveToFile(employees, &count);
        GtkTreeView *treeview = GTK_TREE_VIEW(gtk_builder_get_object(builder, "employee_treeview"));
        GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
        loadEmployeesAll("data/employees.txt", employees, &count, store);
    }

//find 
void on_btn_find_clicked(GtkWidget *widget, gpointer data) {
    GtkBuilder *builder = GTK_BUILDER(data);

    // Lấy ID từ ô tìm kiếm
    int id = get_search_entry_id(builder);
    if (id <= 0) {
        g_print("❌ Invalid ID entered.\n");
        return;
    }

    // Load dữ liệu từ file vào mảng (không cần TreeView)
    loadEmployeesAll("data/employees.txt", employees, &count, NULL);
    // Tìm nhân viên theo ID
    for (int i = 0; i < count; i++) {
        if (employees[i].employeeId == id) {
            GtkEntry *entry_id     = GTK_ENTRY(gtk_builder_get_object(builder, "entry_id"));
            GtkEntry *entry_name     = GTK_ENTRY(gtk_builder_get_object(builder, "entry_name"));
            GtkEntry *entry_position = GTK_ENTRY(gtk_builder_get_object(builder, "entry_position"));
            GtkEntry *entry_salary   = GTK_ENTRY(gtk_builder_get_object(builder, "entry_salary"));

            char id_buf[10];
            snprintf(id_buf, sizeof(id_buf), "%d", employees[i].employeeId);
            gtk_entry_set_text(entry_id, id_buf);

            gtk_entry_set_text(entry_name, employees[i].fullName);
            gtk_entry_set_text(entry_position, employees[i].position);

            char salary_buf[20];
            snprintf(salary_buf, sizeof(salary_buf), "%.2f", employees[i].salary);
            gtk_entry_set_text(entry_salary, salary_buf);

            char message[256];
snprintf(message, sizeof(message),
         "✅ Employee found:\n\nID: %d\nName: %s\nPosition: %s\nSalary: $%.2f",
         employees[i].employeeId,
         employees[i].fullName,
         employees[i].position,
         employees[i].salary);

// Hiển thị popup
show_message(GTK_WINDOW(parent_window), message);
return;
            return;
        }
    }
    // Không tìm thấy
     show_message(GTK_WINDOW(parent_window)," Employee not found with ID: %d\n", id);
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

void show_employee() {

    GtkWidget *treeview;
    GtkBuilder *builder;
    GtkWidget *window;
    GtkListStore *store;
    GtkCellRenderer *renderer;

          // === Khởi tạo builder và load file Glade ===
          builder = gtk_builder_new_from_file("UI_Glade/employee.glade");
          
          if (!gtk_builder_add_from_file(builder, "UI_Glade/employee.glade", NULL)) {
              g_print(" Cant not load file Glade\n");
              return ;
          }
      
          // === Lấy window chính ===
          window = GTK_WIDGET(gtk_builder_get_object(builder, "employee_window"));
          if (!window) {
              g_print(" Cant find window 'employee_window'in Glade\n");
              return ;
        // === Khởi tạo builder và load file Glade ===
        builder = gtk_builder_new();
        if (!gtk_builder_add_from_file(builder, "UI_Glade/employee.glade", NULL)) {
            g_print("Cant not load file Glade\n");
            return ;
        }
          }
    
    window = GTK_WIDGET(gtk_builder_get_object(builder, "employee_window"));
    treeview = GTK_WIDGET(gtk_builder_get_object(builder, "employee_treeview"));

    store = gtk_list_store_new(4,G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_FLOAT);
    load_employees_from_file(store, "data/employees.txt", employees, &count);
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
    apply_css_employee(window, provider);
    g_object_unref(provider);
    gtk_widget_show_all(window);
}   