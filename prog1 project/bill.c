#include <stdio.h>
#include <stdlib.h>


void read_menu(char item_name[][20], int item_price[], int *item_count);
/*
 This function reads the menu from a text file (menu.txt) and stores the item names and prices in two arrays (item_name and item_price) passed as arguments. 
 The number of items read is stored in a pointer (item_count) passed as an argument.
*/
void print_menu(char restaurant_name[], char item_name[][20], int item_price[], int item_count);
/*
This function prints the menu to the console, along with the name of the restaurant (restaurant_name).
It takes as arguments the same arrays and item count passed to read_menu.
*/
void take_order(char restaurant_name[], char item_name[][20], int item_price[], int item_count, int order[], int quantity[], int *order_count);
/*
This function prompts the user to enter the item numbers and quantities of the items they want to order.
It stores the item numbers and quantities in two arrays (order and quantity) passed as arguments, and increments a counter (order_count) passed as a pointer. The function continues prompting the user until they enter 0 to finish.
*/
void calculate_bill(char restaurant_name[], char item_name[][20], int item_price[], int item_count, int order[], int quantity[], int order_count);
/*
This function calculates the total bill based on the items ordered and their quantities. It prints the bill to the console, along with the restaurant name and the item names, quantities, and prices. 
It also writes the total bill amount to a text file (total_bill.txt).
*/

/*
The main function initializes the arrays for item names and prices, calls read_menu to populate them, and then calls print_menu to display the menu.
It then prompts the user to enter their order using take_order, and calculates the bill using calculate_bill.
*/

void read_menu(char item_name[][20], int item_price[], int *item_count) {
    FILE *menu_file = fopen("menu.txt", "r");
    if (menu_file == NULL) {
        printf("Menu file doesn't exist\n");
        exit(1);
    }
    while (fscanf(menu_file, "%[^:]: %d INR\n", item_name[*item_count], &item_price[*item_count]) != EOF) {
        (*item_count)++;
        if (*item_count == 10) {
            break;
        }
    }
    fclose(menu_file);
}

void print_menu(char restaurant_name[], char item_name[][20], int item_price[], int item_count) {
    printf("Welcome to %s!\n", restaurant_name);
    printf("MENU:\n");
    for (int i = 0; i < item_count; i++) {
        printf("%d. %s: %d INR\n", i+1, item_name[i], item_price[i]);
    }
    printf("\n");
}

void take_order(char restaurant_name[], char item_name[][20], int item_price[], int item_count, int order[], int quantity[], int *order_count) {
    for(;;) {
        int item_number, item_quantity;
        printf("Enter item number to add to cart (or 0 to finish): ");
        scanf("%d", &item_number);
        if (item_number < 0 || item_number > item_count) {
            printf("Invalid item number\n");
        } else if (item_number == 0) {
            break;
        } else {
            printf("Enter the quantity: ");
            scanf("%d", &item_quantity);
            order[*order_count] = item_number - 1;
            quantity[*order_count] = item_quantity;
            (*order_count)++;
        }
    }
}

void calculate_bill(char restaurant_name[], char item_name[][20], int item_price[], int item_count, int order[], int quantity[], int order_count) {
    int total = 0;
    printf("=========================================================================\n");
    printf("||\t\t\t\t||BILL:||                          \t||\n");
    printf("-------------------------------------------------------------------------\n");

    printf("||\t\t\t\tImtech Dhaba                           \t\t||\n");
    printf("-------------------------------------------------------------------------\n");

    printf("||Item Name\t\tQuantity\tPrice\t\t           \t||\n");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < order_count; i++) {
        int item_number = order[i];
        int item_quantity = quantity[i];
        printf("||%-15s\t\t%-10d\t%-10d INR\t\t||\n", item_name[item_number], item_quantity, item_price[item_number]*item_quantity);
        printf("-------------------------------------------------------------------------\n");

        total += item_price[item_number]*item_quantity;
    }
    printf("||Total: %d INR\t\t\t\t\t\t\t||\n", total);
    printf("=========================================================================\n");
    
    // Write total bill amount to file
    FILE *finance_file = fopen("total_bill.txt", "a");
    if (finance_file == NULL) {
        printf("Error: could not open finance file\n");
        return;
    }
    fprintf(finance_file, "%d\n", total);
    fclose(finance_file);
}

