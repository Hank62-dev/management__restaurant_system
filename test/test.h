<<<<<<< HEAD
#ifndef ORDERS_H
#define ORDERS_H

void setup_orders_ui();

#endif
=======
#ifndef STATS_H  
#define EMPLOYEES_H
#define MAX_EMPLOYEES 100

typedef struct {
    int employeeId;
    char fullName[50];
    char position[35];
    float salary;
} Employee;

void saveToFile(Employee employees[], int *count);
void loadFromFile(Employee employees[], int *count);
void addEmployee(Employee employees[], int *count);
void displayEmployees(Employee employees[], int count);
void searchEmployee(Employee employees[], int count, int id);
void deleteEmployee(Employee employees[], int *count, int id);
void updateEmployee(Employee employees[], int *count, int id);
void calculate_revenue_by_day();
#endif
>>>>>>> employee
