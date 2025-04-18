#ifndef EMPLOYEES_H
#define EMPLOYEES_H
#define MAX_EMPLOYEES 100
#include <gtk/gtk.h>

typedef struct {
    int employeeId;
    char fullName[50];
    char position[35];
    float salary;
} Employee;

extern Employee employees[MAX_EMPLOYEES];
extern int count;

void saveToFile(Employee employees[], int *count);
//void loadFromFile(Employee employees[], int *count, const char *filename)
void addEmployee(Employee employees[], int *count);
void displayEmployees(Employee employees[], int count);
void searchEmployee(Employee employees[], int count, int id);
void deleteEmployee(Employee employees[], int *count, int id);
void updateEmployee(Employee employees[], int *count, int id);


//hamUI
void loadEmployeesToArrayOnly(const char *filename, Employee employees[], int *count);
void loadEmployeesAll(const char *filename, Employee employees[], int *count, GtkListStore *store);
void load_employees_from_file(GtkListStore *store, const char *filename, Employee employees[], int *count);
void addEmployeeFromUI(GtkBuilder *builder, Employee employees[], int *count);
void displayEmployeeInfo(GtkBuilder *builder, Employee emp);
void updateEmployeeFromUI(GtkBuilder *builder, Employee employees[], int *count,int id);

//show
void show_home_m();
void show_employee();
void on_btn_home_m_clicked(GtkWidget *widget, gpointer data);
void on_btn_menu_m_clicked(GtkWidget *widget, gpointer data);
void on_btn_stats_m_clicked(GtkWidget *widget, gpointer data);
void on_btn_employee_m_clicked(GtkWidget *widget, gpointer data);
void on_btn_orders_m_clicked(GtkWidget *widget, gpointer data);
#endif