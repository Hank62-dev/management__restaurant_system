#ifndef MENU_ITEM_H
#define MENU_ITEM_H
 
typedef struct {
    char menuId[6];          //1 chữ cái F hoặc D và 3 số đi kèm sau. Đồ ăn thì đầu dòng là F còn nước thì là D, EX: F0001, D0001
    char dishName[100];
    char category[100];  //đồ ăn hay nước uống
    float price;
    
} MenuItem;

int loadMenuFromFile(MenuItem menuList[], int *count);

void printMenu(MenuItem menuList[], int count);

void saveMenuToFile(MenuItem menuList[], int count); // Sửa tham số *count thành count

void addItem(MenuItem menuList[], int *count);

void deleteItem(MenuItem menuList[], int *count);

void editItem(MenuItem menuList[], int *count);

#endif