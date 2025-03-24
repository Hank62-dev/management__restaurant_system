#include <stdio.h>
#include <stdlib.h>
#include "stats.h"
#include "employees.h"


int main(int argc, char *argv[]) 
{

	int choice,id,count= 0;
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
 addEmployee(employees,count);
    break;
  case 2:
displayEmployees(employees, count);
    break;
  case 3:
 printf("Input Employee Id to search: ");
                scanf("%d", &id);
                searchEmployee(employees, count, id);
    break;
  case 4:
printf("Input Employee Id to update: ");
                scanf("%d", &id);
                updateEmployee(employees, count, id);
    break;
 case 5 :
    printf("Input Employee Id to delete: ");
                scanf("%d", &id);
                deleteEmployee(employees, &count, id);
	
	case 6:
          printf("\nExiting program...\n");
            exit(0);
            break;
	
	calculate_revenue_by_day();
	return 0;
}
}
}
