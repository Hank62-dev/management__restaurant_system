struct Employee{
    int employeeId;
    char fullName[50];
    char position[30];
    float salary;
} ;

//khai bao ham
void calculate_revenue_by_day()
void savetofile(struct Employee employees[], int count);
void loadfromfile(struct Employee employees[], int *count);
void addEmployee(struct Employee employees[], int *count);
void displayEmployees(struct Employee employees[], int count);
void searchEmployee(struct Employee employees[], int count, int id);
void updateEmployee(struct Employee employees[], int count, int id);
void deleteEmployee(struct Employee employees[], int *count, int id);
