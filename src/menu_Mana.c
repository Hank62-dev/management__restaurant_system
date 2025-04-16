#include <stdio.h>
#include <string.h>
#include "menu_Mana.h"

int loadMenuFromFile(MenuItem menu[], int *count) {
    FILE *file = fopen("data/menu.txt", "r");
    if (!file) {
        perror("Lỗi mở file menu.txt");
        return 0;
    }

    *count = 0;
    char line[512];
    while (fgets(line, sizeof(line), file) && *count < MAX_MENU_ITEMS) {
        char menuId[MAX_ID_LENGTH];
        char dishName[MAX_NAME_LENGTH];
        char type[MAX_TYPE_LENGTH];
        float price;
        char imagePath[MAX_IMAGE_PATH];

        if (sscanf(line, "%5s \"%[^\"]\" \"%[^\"]\" %f \"%[^\"]\"", 
                   menuId, dishName, type, &price, imagePath) == 5) {
            strcpy(menu[*count].menuId, menuId);
            strcpy(menu[*count].dishName, dishName);
            strcpy(menu[*count].type, type);
            menu[*count].price = price;
            strcpy(menu[*count].imagePath, imagePath);
            (*count)++;
        }
    }

    fclose(file);
    return 1;
}

void printMenu(MenuItem menu[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s \"%s\" \"%s\" %.0f \"%s\"\n", 
               menu[i].menuId, menu[i].dishName, menu[i].type, 
               menu[i].price, menu[i].imagePath);
    }
}

int saveMenuToFile(MenuItem menu[], int count) {
    FILE *file = fopen("data/menu.txt", "w");
    if (!file) {
        perror("Lỗi mở file menu.txt");
        return 0;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s \"%s\" \"%s\" %.0f \"%s\"\n",
                menu[i].menuId, menu[i].dishName, menu[i].type, 
                menu[i].price, menu[i].imagePath);
    }

    fclose(file);
    return 1;
}

int checkDuplicate(MenuItem menu[], int count, const char *menuId) {
    for (int i = 0; i < count; i++) {
        if (strcmp(menu[i].menuId, menuId) == 0) {
            return 1;
        }
    }
    return 0;
}

int addItem(MenuItem menu[], int *count, const char *menuId, const char *dishName, 
            const char *type, float price, const char *imagePath) {
    if (*count >= MAX_MENU_ITEMS || checkDuplicate(menu, *count, menuId)) {
        return 0;
    }

    strcpy(menu[*count].menuId, menuId);
    strcpy(menu[*count].dishName, dishName);
    strcpy(menu[*count].type, type);
    menu[*count].price = price;
    strcpy(menu[*count].imagePath, imagePath);
    (*count)++;
    return 1;
}

int deleteItem(MenuItem menu[], int *count, const char *menuId) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(menu[i].menuId, menuId) == 0) {
            for (int j = i; j < *count - 1; j++) {
                menu[j] = menu[j + 1];
            }
            (*count)--;
            return 1;
        }
    }
    return 0;
}

int editItem(MenuItem menu[], int count, const char *menuId, 
             const char *newDishName, const char *newType, 
             float newPrice, const char *newImagePath) {
    for (int i = 0; i < count; i++) {
        if (strcmp(menu[i].menuId, menuId) == 0) {
            strcpy(menu[i].dishName, newDishName);
            strcpy(menu[i].type, newType);
            menu[i].price = newPrice;
            strcpy(menu[i].imagePath, newImagePath);
            return 1;
        }
    }
    return 0;
}