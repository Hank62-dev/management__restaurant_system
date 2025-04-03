#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>


GtkWidget *window;
GtkWidget *stack;  
GtkWidget *register_box, *login_box;
GtkWidget *entry_firstname, *entry_lastname, *entry_phone, *entry_password, *entry_confirm_password;
GtkWidget *entry_login_phone, *entry_login_password;

//Hàm xử lý khi nhấn nút register
void on_register_now_clicked(GtkButton *button, gpointer user_data) {
    const char *first_name = gtk_entry_get_text(GTK_ENTRY(entry_firstname));
    const char *last_name = gtk_entry_get_text(GTK_ENTRY(entry_lastname));
    const char *phone = gtk_entry_get_text(GTK_ENTRY(entry_phone));
    const char *password = gtk_entry_get_text(GTK_ENTRY(entry_password));
    const char *confirm_password = gtk_entry_get_text(GTK_ENTRY(entry_confirm_password));

    // Kiểm tra mật khẩu 
    if (strcmp(password, confirm_password) != 0) {
        gtk_label_set_text(GTK_LABEL(user_data), "Passwords do not match!");
        return;
    }

    // lưu file
    FILE *file = fopen("data/users.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s,%s,%s,%s\n", first_name, last_name, phone, password);
        fclose(file);
        gtk_label_set_text(GTK_LABEL(user_data), "Registration successful!");
    } else {
        gtk_label_set_text(GTK_LABEL(user_data), "Error saving user data.");
    }
}

//Hàm xử lý khi nhấn nút login
void on_login_now_clicked(GtkButton *button, gpointer user_data) {
    const char *phone = gtk_entry_get_text(GTK_ENTRY(entry_login_phone));
    const char *password = gtk_entry_get_text(GTK_ENTRY(entry_login_password));
    
    FILE *file = fopen("data/users.txt", "r");
    if (file != NULL) {
        char line[256];
        int found = 0;
        
        while (fgets(line, sizeof(line), file)) {
            char stored_phone[50], stored_password[50];
            sscanf(line, "%*[^,],%*[^,],%49[^,],%49[^\n]", stored_phone, stored_password);
            
            // Check if phone and password match
            if (strcmp(stored_phone, phone) == 0 && strcmp(stored_password, password) == 0) {
                found = 1;
                break;
            }
        }
        
        fclose(file);
        
        if (found) {
            //Nếu đúng login chuyển sang giao diện home
            GtkBuilder *home_builder = gtk_builder_new_from_file("UI Glade/home.glade");
            window = GTK_WIDGET(gtk_builder_get_object(home_builder, "home_window"));
            gtk_widget_show_all(window);
            gtk_main_quit();  //đóng cửa sổ hiện tại chuyển sang trang mới 
        } else {
            gtk_label_set_text(GTK_LABEL(user_data), "Invalid login. Try again.");
        }
    } else {
        gtk_label_set_text(GTK_LABEL(user_data), "Error reading user data.");
    }
}

//Hàm chuyển đổi sang form register 
void on_register_clicked(GtkButton *button, gpointer user_data) {
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "register_box");  // Make sure "register_box" exists in Glade
}

//Hàm chuyển đổi sang form login
void on_login_clicked(GtkButton *button, gpointer user_data) {
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "login_box");  // Make sure "login_box" exists in Glade
}


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    //Load file login/register.glade
    GtkBuilder *builder = gtk_builder_new_from_file("UI Glade/UI Login_Register.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "VQHT Restaurant"));
    
    // lấy stack của 2 form login với register
    stack = GTK_WIDGET(gtk_builder_get_object(builder, "stack_form")); 
    register_box = GTK_WIDGET(gtk_builder_get_object(builder, "register_box"));
    login_box = GTK_WIDGET(gtk_builder_get_object(builder, "login_box"));

    // liên kết các mục nhập
    entry_firstname = GTK_WIDGET(gtk_builder_get_object(builder, "entry_firstname"));
    entry_lastname = GTK_WIDGET(gtk_builder_get_object(builder, "entry_lastname"));
    entry_phone = GTK_WIDGET(gtk_builder_get_object(builder, "entry_phone"));
    entry_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_password"));
    entry_confirm_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_confirm_password"));
    entry_login_phone = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login_phone"));
    entry_login_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login_password"));

    // kết nối sự kiện
    GtkWidget *btn_register_now = GTK_WIDGET(gtk_builder_get_object(builder, "btn_register_now"));
    g_signal_connect(btn_register_now, "clicked", G_CALLBACK(on_register_now_clicked), gtk_builder_get_object(builder, "register_label"));
    
    GtkWidget *btn_login_now = GTK_WIDGET(gtk_builder_get_object(builder, "btn_login_now"));
    g_signal_connect(btn_login_now, "clicked", G_CALLBACK(on_login_now_clicked), gtk_builder_get_object(builder, "login_label"));
    
    GtkWidget *btn_register = GTK_WIDGET(gtk_builder_get_object(builder, "btn_register"));
    g_signal_connect(btn_register, "clicked", G_CALLBACK(on_register_clicked), NULL);
    
    GtkWidget *btn_login = GTK_WIDGET(gtk_builder_get_object(builder, "btn_login"));
    g_signal_connect(btn_login, "clicked", G_CALLBACK(on_login_clicked), NULL);

    //áp dụng css vào gtk
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "Glade_CSS/login_register.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    //hiện màn hình cửa sổ chính 
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
