#ifndef STATS_H  
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
void loadFromFile(Employee employees[], int *count);
void addEmployee(Employee employees[], int *count);
void displayEmployees(Employee employees[], int count);
void searchEmployee(Employee employees[], int count, int id);
void deleteEmployee(Employee employees[], int *count, int id);
void updateEmployee(Employee employees[], int *count, int id);

//hamUI
void addEmployeeFromUI(GtkBuilder *builder, Employee employees[], int *count);
void displayEmployeeInfo(GtkBuilder *builder, Employee emp);
void load_employees_from_file(GtkListStore *store, const char *filename);
void updateEmployeeFromUI(GtkBuilder *builder, Employee employees[], int *count,int id);

#endif