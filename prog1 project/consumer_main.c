#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consumer.h"
#include "bill.h"

void update_inventory(char item_name[][20], int quantity[], int order_count) {
    FILE *fp;
    fp = fopen("inventory.txt", "a");
    for (int i = 0; i < order_count; i++) {
        fprintf(fp, "%s %d\n", item_name[i], quantity[i]);
    }
    fclose(fp);
}

int main() {
    int choice;
    printf("1. Sign up\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            signup();
            break;
        case 2:
            if (login()) {
                printf("Logged in successfully.\n");
            }
            break;
        default:
            exit(0);
    }
    
    char restaurant_name[] = "IMTECH DHABA";
    char item_name[10][20];
    int item_price[10];
    int item_count = 0;
    read_menu(item_name, item_price, &item_count);
    print_menu(restaurant_name, item_name, item_price, item_count);


    int order[10];
    int quantity[10];
    int order_count = 0;
    printf("\n\n\n\n");
    take_order(restaurant_name, item_name, item_price, item_count, order, quantity, &order_count);
    calculate_bill(restaurant_name, item_name, item_price, item_count, order, quantity, order_count);
    update_inventory(item_name, quantity, order_count);

    return 0;
}

