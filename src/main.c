#include <stdio.h>
#include <stdlib.h>
#include "employees.h"
#include <gtk/gtk.h>


int main(int argc, char *argv[]) {
//glade 
 GtkBuilder *builder;
    GtkWidget *window, *button, *label;
    GtkCssProvider *cssProvider;
    GdkDisplay *display;
    GdkScreen *screen;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("UIhome.glade");
      window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
       if (!window) {
        g_printerr("None widget with this ID 'main_window'\n");
        return 1;
    }
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}      
                 
// css
      cssProvider = gtk_css_provider_new();
gtk_css_provider_load_from_path(cssProvider, "home.css", NULL);
display = gdk_display_get_default();
screen = gdk_display_get_default_screen(display);

gtk_style_context_add_provider_for_screen(
    screen,
    GTK_STYLE_PROVIDER(cssProvider),
    GTK_STYLE_PROVIDER_PRIORITY_USER
);

//
	int choice,id,count=0;
	Employee employees[100];
	loadFromFile(employees,&count);
	while (choice != 6){
		printf("\t\t\t\t=====EMPLOYEE MANEGEMENT=====\t\t\t\t\t");
		printf("\n\n\n\n\t\t\t\t 1. Add Employee Record");
		printf("\n\t\t\t\t 2. Print Employee Record");
		printf("\n\t\t\t\t 3. Search Employee Record By Id");
		printf("\n\t\t\t\t 4. Update Employee Record");
		printf("\n\t\t\t\t 5. Delete Record");
		printf("\n\t\t\t\t 6. Exit Sign \n\n\n");
		printf("\n\t\t\t\t____________________________________\n");
		printf("\n\t\t\t\t ");
		scanf("%d",&choice); 
switch (choice) {
  case 1:
 addEmployee(employees,&count);
    break;
  case 2:
 displayEmployees(employees,count);
    break;
  case 3:
 printf("Input Employee Id to search: ");
                scanf("%d", &id);
                searchEmployee(employees, count, id);
    break;
  case 4:
printf("Input Employee Id to update: ");
                scanf("%d", &id);
                updateEmployee(employees, &count, id);
    break;
 case 5 :
    printf("Input Employee Id to delete: ");
                scanf("%d", &id);
                deleteEmployee(employees, &count, id);
	
	case 6:
          printf("\nExiting program...\n");
            exit(0);
            break;
	}

	return 0;

}
//	calculate_revenue_by_day();
}
