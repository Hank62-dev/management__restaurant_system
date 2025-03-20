#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int main() {
	
	SetConsoleOutputCP(65001);
	
    MenuItem menuList[100];  // Danh sách chứa tối đa 100 món ăn
    int count = 0;
    loadMenuFromFile(menuList, &count);
    
    printMenu(menuList, count);

    return 0;
}
