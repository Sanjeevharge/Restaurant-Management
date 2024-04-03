#ifndef BILL_H
#define BILL_H

void read_menu(char item_name[][20], int item_price[], int *item_count);
void print_menu(char restaurant_name[], char item_name[][20], int item_price[], int item_count);
void take_order(char restaurant_name[], char item_name[][20], int item_price[], int item_count, int order[], int quantity[], int *order_count);
void calculate_bill(char restaurant_name[], char item_name[][20], int item_price[], int item_count, int order[], int quantity[], int order_count);

#endif

