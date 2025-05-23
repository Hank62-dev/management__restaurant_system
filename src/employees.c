#include <gtk/gtk.h>
#include "employees.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


Employee employees[MAX_EMPLOYEES];
int count = 0;

// Save employee data to file
void saveToFile(Employee employees[], int *count) {
    FILE *file = fopen("data/employees.txt", "w");  // đúng đường dẫn và ghi đè
    if (file == NULL) {
        g_print(" Error opening file.\n");
        return;
    }

    for (int i = 0; i < *count; i++) {
        fprintf(file, "%d|%s|%s|%.2f\n", 
            employees[i].employeeId, 
            employees[i].fullName, 
            employees[i].position, 
            employees[i].salary);
    }

    fclose(file);
    g_print(" Data saved to file.\n");
}
/* Load employee data from file
void loadFromFile(Employee employees[], int *count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf(" Cannot open file %s\n", filename);
        return;
    }

    *count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Employee emp;
        char *token;

        token = strtok(line, "|");
        if (token) emp.employeeId = atoi(token);

        token = strtok(NULL, "|");
        if (token) strcpy(emp.fullName, token);

        token = strtok(NULL, "|");
        if (token) strcpy(emp.position, token);

        token = strtok(NULL, "|");
        if (token) emp.salary = atof(token);

        employees[*count] = emp;
        (*count)++;
    }

    fclose(file);
    printf(" Loaded %d employees.\n", *count);
}*/
#define MAX_EMPLOYEES 100  // nếu chưa có

void loadEmployeesAll(const char *filename, Employee employees[], int *count, GtkListStore *store) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        g_print(" Cannot open file: %s\n", filename);
        return;
    }

    *count = 0;
    char line[256];

    if (store != NULL) {
        gtk_list_store_clear(store); // Xóa dữ liệu cũ trong TreeView nếu cần
    }

    while (fgets(line, sizeof(line), file)) {
        if (*count >= MAX_EMPLOYEES) {
            g_print(" Max employee reached!\n");
            break;
        }

        Employee emp;
        char *token;

        token = strtok(line, "|");
        if (token) emp.employeeId = atoi(token);

        token = strtok(NULL, "|");
        if (token) strcpy(emp.fullName, token);

        token = strtok(NULL, "|");
        if (token) strcpy(emp.position, token);

        token = strtok(NULL, "|");
        if (token) emp.salary = atof(token);

        employees[*count] = emp;
        (*count)++;

        // Nếu cần hiện TreeView
        if (store != NULL) {
            GtkTreeIter iter;
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, emp.employeeId,
                               1, emp.fullName,
                               2, emp.position,
                               3, emp.salary,
                               -1);
        }

        g_print("Loaded: %d | %s | %s | %.2f\n", emp.employeeId, emp.fullName, emp.position, emp.salary);
    }

    fclose(file);
    g_print(" Load complete: %d employees\n", *count);
}
void loadEmployeesToArrayOnly(const char *filename, Employee employees[], int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        g_print(" Cannot open file: %s\n", filename);
        return;
    }

    *count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (*count >= MAX_EMPLOYEES) {
            g_print(" Max employee limit reached!\n");
            break;
        }

        Employee emp;
        char *token;

        token = strtok(line, "|");
        if (token) emp.employeeId = atoi(token);

        token = strtok(NULL, "|");
        if (token) strcpy(emp.fullName, token);

        token = strtok(NULL, "|");
        if (token) strcpy(emp.position, token);

        token = strtok(NULL, "|");
        if (token) emp.salary = atof(token);

        employees[*count] = emp;
        (*count)++;
    }

    fclose(file);
    g_print(" Loaded %d employees into array.\n", *count);
}
// Add a new employee
void addEmployee(Employee employees[], int *count) {
    printf("Enter employee ID: ");
    scanf("%d", &employees[*count].employeeId);
    getchar();  // Clear the newline character
    printf("Enter full name: ");
    fgets(employees[*count].fullName, sizeof(employees[*count].fullName), stdin);
    employees[*count].fullName[strcspn(employees[*count].fullName, "\n")] = 0;

    printf("Enter position: ");
    fgets(employees[*count].position, sizeof(employees[*count].position), stdin);
    employees[*count].position[strcspn(employees[*count].position, "\n")] = 0;

    printf("Enter salary: ");
    scanf("%f", &employees[*count].salary);

    (*count)++;
    saveToFile(employees, count);
    printf("Employee added successfully!\n");
}

/*/ Display list of employees
void displayEmployees(Employee employees[], int count) {
    if (count == 0) {
        printf("No employees found.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("ID: %d, Name: %s, Position: %s, Salary: %.2f\n", 
               employees[i].employeeId, 
               employees[i].fullName, 
               employees[i].position, 
               employees[i].salary);
    }
}*/

// Search employee by ID
void searchEmployee(Employee employees[], int count, int id) {

    for (int i = 0; i < count; i++) {
        if (employees[i].employeeId == id) {
            printf("Employee found: ID: %d, Name: %s, Position: %s, Salary: %.2f\n", 
                   employees[i].employeeId, 
                   employees[i].fullName, 
                   employees[i].position, 
                   employees[i].salary);
            return;
        }
    }
    printf("Employee not found with ID: %d\n", id);
}

// Delete employee by ID
void deleteEmployee(Employee employees[], int *count, int id) {
    for (int i = 0; i < *count; i++) {
        if (employees[i].employeeId == id) {
            for (int j = i; j < *count - 1; j++) {
                employees[j] = employees[j + 1];
            }
            (*count)--;
            saveToFile(employees, count);
            printf("Employee deleted successfully!\n");
            return;
        }
    }
    printf("Employee not found with ID: %d\n", id);
}

// Update employee details by ID
void updateEmployee(Employee employees[], int *count, int id) {
    for (int i = 0; i < *count; i++) {
        if (employees[i].employeeId == id) {
            printf("Enter new full name: ");
            fgets(employees[i].fullName, sizeof(employees[i].fullName), stdin);
            employees[i].fullName[strcspn(employees[i].fullName, "\n")] = 0;

            printf("Enter new position: ");
            fgets(employees[i].position, sizeof(employees[i].position), stdin);
            employees[i].position[strcspn(employees[i].position, "\n")] = 0;

            printf("Enter new salary: ");
            scanf("%f", &employees[i].salary);

            saveToFile(employees, count);
            printf("Employee updated successfully!\n");
            return;
        }
    }
    printf("Employee not found with ID: %d\n", id);
}

 
