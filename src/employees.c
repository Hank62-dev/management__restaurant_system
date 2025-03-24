#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employees.h"

    //dua du lieu vao file
     void saveToFile(struct Employee employees[], int count){
    FILE *file = fopen("employees.txt", "w");
    if (file == NULL) {
        printf("Error to open file !\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%.2f\n",
                employees[i].employeeId,
                employees[i].fullName,
                employees[i].position,
                employees[i].salary);
    } 
    fclose(file);
     } 
     
     //lay du lieu tu file
     void loadfromfile(struct Employee employees[], int *count){
     	FILE *file=fopen("employees.txt","r");
     	if (file == NULL) {
        printf("Error to open file !\n");
        return;
    }
     *count = 0;
    while (fscanf(file, "%d,%49[^,],%29[^,],%f\n",
                  &employees[*count].employeeId,
                  employees[*count].fullName,
                  employees[*count].position,
                  &employees[*count].salary) == 4) {
        (*count)++;
    }
    fclose(file);
}
     
     //Them nhan vien
      void addEmployee(struct Employee employees[], int *count) {
      	
         // them nhan vien
    printf("\nAdd Employee Id: ");
    scanf("%d", &employees[*count].employeeId);
    getchar();
    
    printf("Add full name: ");
    fgets(employees[*count].fullName, 50, stdin);
    employees[*count].fullName[strcspn(employees[*count].fullName, "\n")] = 0; // xoa \n

    printf("Add position: ");
    fgets(employees[*count].position, 35, stdin);
    employees[*count].position[strcspn(employees[*count].position, "\n")] = 0;  

    printf("Add salary: ");
    scanf("%f", &employees[*count].salary);
       
	(*count)++; 
	 saveToFile(employees, count);
	 printf("\nAdd Sucessfully!\n");
            return;
	 
	}
	
	//hien thi danh sach nhan vien
	void displayEmployees(struct Employee employees[], int count){
	
	
	if (count == 0) {
        printf("\nDo not have any employees.\n");
        return;
    }

    printf("\nEmployees list:\n");
    for (int i = 0; i < count; i++) {
        printf("Number: %d,ID: %d, Name: %s, Position: %s, Salary: %.2f \n" ,i,
               employees[i].employeeId,
               employees[i].fullName,
               employees[i].position,
               employees[i].salary);
    }
}
// tim kiem nhan vien
void searchEmployee(struct Employee employees[], int count, int id){
	for(int i=0 ,i<count,i++) {
		if (employee[i].employeeId==id){
		printf("Number: %d,ID: %d, Name: %s, Position: %s, Salary: %.2f \n" ,i,
               employees[i].employeeId,
               employees[i].fullName,
               employees[i].position,
               employees[i].salary);
               	}
               else printf("\nDo not have any employees for this Id %d\n", id);
	
	}
}
//xoa nhan vien
void deleteEmployee(Employee employees[], int *count, int id) {
    for (int i = 0; i < *count; i++) {
        if (employees[i].employeeId == id) {
            for (int j = i; j < *count - 1; j++) {
                employees[j] = employees[j + 1];
            }
            (*count)--;
            saveToFile(employees, *count);
            printf("\nDelete Sucessfully!\n");
            return;
        }
    }
    printf("\nDo not have any employees for this Id %d\n", id);
}
//update nhan vien
void updateEmployee(Employee employees[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (employees[i].employeeId == id) {
            printf("\nUpdate name: ");
            getchar();
            fgets(employees[i].fullName, sizeof(employees[i].fullName), stdin);
            employees[i].fullName[strcspn(employees[i].fullName, "\n")] = 0;

            printf("Update position: ");
            fgets(employees[i].position, sizeof(employees[i].position), stdin);
            employees[i].position[strcspn(employees[i].position, "\n")] = 0;

            printf("Update salary: ");
            scanf("%f", &employees[i].salary);

            saveToFile(employees, count);
            printf("\nUpdate Successful !\n");
            return;
        }
    }
    printf("\nDo not have any employees for this Id %d\n", id);
}

 
