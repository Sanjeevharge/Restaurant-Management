#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void create_menu();
int read_menu(char menu[][100]);
void display_menu(char menu[][100], int num_items);
void delete_menu_item(char menu[][100], int *num_items, int item_number);
void edit_menu_item(char menu[][100], int num_items, int item_number) ;
void edit_menu(char menu[][100], int num_items) ;
void write_menu(char menu[][100], int num_items);




int main (){

    printf("\n \n");
    printf("\t\t\tHello, Please choose a choice\n \n");
    printf("\t\t\t1 for creating new menu\n \n");
    printf("\t\t\t2 for for editing menu\n \n");
    int temp;
    printf("choice: ");
    scanf("%d",&temp);

    if (temp==1){
        create_menu();
    }
    else if (temp==2){
        char menu[10][100];
        int num_items = read_menu(menu);
        while (1) {
        display_menu(menu, num_items);
        edit_menu(menu, num_items);
        write_menu(menu, num_items);
    }
    }
    return 0;
}

void create_menu(){
    
    /*
        n=>number of items on menu
        i==>looping variable
        price=>price of rach item
    */
    int n, i, price;
    char item[50];
    FILE *fp;
    /*  
        User will enter the number of items on menu , item name and its price. I will Be saving it into The text file named menu.txt
    */
    printf("Enter the number of items on the menu: ");
    scanf("%d", &n);

    /*
        if fp is NULL ,it would indiacate that opening file was unsucessfull and 
    */
    fp = fopen("menu.txt", "w");
    if (fp == NULL) {
        printf("Unable to open the file!\n");
        
    }
    else {

        //getchar here will consumer the newline character '\n'. since i dont want newline character to be stored as input buffer while scanf line is executed
        getchar();   
        for (i = 1; i <= n; i++) {
            printf("Enter item #%d: ", i);
            fgets(item, sizeof(item), stdin);
        /*
            strcspn returns the index of the first occurrence of \n  in the item array and everntually we are changing it to null pointer .
            thereby removing it from the string and making it a valid C string.
        */
            item[strcspn(item, "\n")] = '\0';  // Remove the newline character from the input
            printf("Enter price for %s (in INR): ", item);
            scanf("%d", &price);
            fprintf(fp, "%s: %d INR\n", item, price);
            getchar(); 
        }

        fclose(fp);
        printf("Menu created and saved to menu.txt.\n");
    }

}


// Function to read the menu items from the file "menu.txt" and store them in a 2D array called "menu"
int read_menu(char menu[][100]) {
    // Read menu items from file
    FILE *file = fopen("menu.txt", "r");
    if (!file) {
        printf("Error opening menu file menu.txt.\n");
        return 1;
    }
    int num_items = 0;
    while (fgets(menu[num_items], 100, file) && num_items < 10) {
        num_items++;
    }
    fclose(file);
    return num_items;
}



// Function to display the menu items stored in "menu"
void display_menu(char menu[][100], int num_items) {
    printf("Menu contains %d items:\n", num_items);
    for (int i = 0; i < num_items; i++) {
        printf("%d. %s", i + 1, menu[i]);
    }
}


// Function to delete a menu item 
void delete_menu_item(char menu[][100], int *num_items, int item_number) {
    // Delete the menu item
    for (int i = item_number - 1; i < *num_items - 1; i++) {
        strcpy(menu[i], menu[i + 1]);
    }
    (*num_items)--;
    printf("Menu updated:\n");
    display_menu(menu, *num_items);
}

// Function to edit the price of a menu item or delete it
void edit_menu_item(char menu[][100], int num_items, int item_number) {
    printf("Enter new price for %s (in INR, or a negative value to delete the item): ", strtok(menu[item_number-1], ":"));
    int new_price;
    scanf("%d", &new_price);
    if (new_price < 0) {
    delete_menu_item(menu, &num_items, item_number);
    }

    else {
        // Update the menu item price
        char new_item[100];
        sprintf(new_item, "%s: %d INR\n", strtok(menu[item_number-1], ":"), new_price);
        strcpy(menu[item_number-1], new_item);
        printf("Menu updated:\n");
        display_menu(menu, num_items);
    }
}

// Function to repeatedly ask the user to enter the item number to edit, and call "edit_menu_item" function to edit the selected item
void edit_menu(char menu[][100], int num_items) {
    int item_number;
    while (1) {
        printf("Enter the item number to edit (or 0 to exit): ");
        scanf("%d", &item_number);
        if (item_number == 0) {
            exit(1);
        }
        else if (item_number < 1 || item_number > num_items) {
            printf("Invalid item number! Please enter a number between 1 and %d (or 0 to exit): ", num_items);
            continue;
        }
        else {
            edit_menu_item(menu, num_items, item_number);
        }
    }
}



// Function to write the updated menu back to the file "menu.txt"
void write_menu(char menu[][100], int num_items) {
    // Write updated menu to file
    FILE *file = fopen("menu.txt", "w");
    if (!file) {
        printf("Error opening menu file menu.txt for writing.\n");
        return;
    }
    for (int i = 0; i < num_items; i++) {
        fprintf(file, "%s", menu[i]);
    }
    fclose(file);
}

