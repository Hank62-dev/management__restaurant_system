#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "data/users.txt"

GtkWidget *stack;
GtkWidget *entry_firstname, *entry_lastname, *entry_phone, *entry_password, *entry_confirm_password;
GtkWidget *entry_login_phone, *entry_login_password;

void apply_css(GtkWidget *widget, GtkCssProvider *provider) {
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    if (GTK_IS_CONTAINER(widget)) {
        gtk_container_foreach(GTK_CONTAINER(widget), (GtkCallback)apply_css, provider);
    }
}

void on_register_now_clicked(GtkButton *button, gpointer user_data) {
    const gchar *firstname = gtk_entry_get_text(GTK_ENTRY(entry_firstname));
    const gchar *lastname = gtk_entry_get_text(GTK_ENTRY(entry_lastname));
    const gchar *phone = gtk_entry_get_text(GTK_ENTRY(entry_phone));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry_password));
    const gchar *confirm_password = gtk_entry_get_text(GTK_ENTRY(entry_confirm_password));

    if (g_strcmp0(password, confirm_password) != 0) {
        g_print("Passwords do not match!\n");
        return;
    }
    
    FILE *file = fopen(DATA_FILE, "a");
    if (file) {
        fprintf(file, "%s %s %s %s\n", firstname, lastname, phone, password);
        fclose(file);
        g_print("User registered successfully!\n");
    } else {
        g_print("Error saving data!\n");
    }
}

void on_login_now_clicked(GtkButton *button, gpointer user_data) {
    const gchar *phone = gtk_entry_get_text(GTK_ENTRY(entry_login_phone));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry_login_password));
    
    FILE *file = fopen(DATA_FILE, "r");
    if (!file) {
        g_print("Error opening data file!\n");
        return;
    }
    
    char firstname[50], lastname[50], stored_phone[20], stored_password[50];
    int found = 0;
    while (fscanf(file, "%s %s %s %s", firstname, lastname, stored_phone, stored_password) != EOF) {
        if (strcmp(phone, stored_phone) == 0 && strcmp(password, stored_password) == 0) {
            found = 1;
            break;
        }
    }
    fclose(file);
    
    if (found) {
        g_print("Login successful! Redirecting to Home...\n");
        // Chuyển sang giao diện Home
    } else {
        g_print("Invalid login credentials!\n");
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    GtkBuilder *builder = gtk_builder_new_from_file("UI Glade/UI Login_Register.glade");
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "VQHT Restaurant"));
    stack = GTK_WIDGET(gtk_builder_get_object(builder, "stack_form"));
    
    // Lấy các entry từ form
    entry_firstname = GTK_WIDGET(gtk_builder_get_object(builder, "entry_firstname"));
    entry_lastname = GTK_WIDGET(gtk_builder_get_object(builder, "entry_lastname"));
    entry_phone = GTK_WIDGET(gtk_builder_get_object(builder, "entry_phone"));
    entry_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_password"));
    entry_confirm_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_confirm_password"));
    entry_login_phone = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login_phone"));
    entry_login_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login_password"));
    
    GtkWidget *btn_register_now = GTK_WIDGET(gtk_builder_get_object(builder, "btn_register_now"));
    GtkWidget *btn_login_now = GTK_WIDGET(gtk_builder_get_object(builder, "btn_login_now"));
    
    g_signal_connect(btn_register_now, "clicked", G_CALLBACK(on_register_now_clicked), NULL);
    g_signal_connect(btn_login_now, "clicked", G_CALLBACK(on_login_now_clicked), NULL);
    
    // Áp dụng CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "Glade_CSS/login_register.css", NULL);
    apply_css(window, provider);
    g_object_unref(provider);
    
    gtk_widget_show_all(window);
    gtk_main();
    
    return 0;
}
