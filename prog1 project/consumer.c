#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consumer.h"

//global variables
struct User user[MAX_USERS];
int num_users = 0;

//function to create a new user
void signup() {
    struct User newUser;
    printf("Enter your name: ");
    scanf("%s", newUser.name);
    printf("Enter your phone number: ");
    scanf("%s", newUser.phoneno);
    newUser.num_orders = 0;

    //checking if user already exists
    for (int i = 0; i < num_users; i++) {
        if (strcmp(user[i].name, newUser.name) == 0 && strcmp(user[i].phoneno, newUser.phoneno) == 0) {
            printf("%s, welcome back again!\n", newUser.name);
            return;
        }
    }

    if (strlen(newUser.phoneno) < 10) {
        printf("Invalid signup.\n");
        return;
    }

    //adding a new entered member to the list
    user[num_users++] = newUser;

    FILE *fp = fopen("customer_info.txt", "a");
    if (fp == NULL) {
        printf("Error occured opening file\n");
        return;
    }
    if (strlen(newUser.phoneno) == 10) {
        fprintf(fp, "%s %s\n", newUser.name, newUser.phoneno);
        fclose(fp);
    }
}

//function to login a user
//function to login a user
int login() {
    char username[100], password[100];
    printf("Enter your name: ");
    scanf("%s", username);
    printf("Enter your phone number: ");
    scanf("%s", password);

    FILE *fp = fopen("customer_info.txt", "r");
    if (fp == NULL) {
        printf("Could not open file.\n");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        char name[100], phone[100];
        sscanf(line, "%s %s", name, phone);
        if (strcmp(name, username) == 0 && strcmp(phone, password) == 0) {
            fclose(fp);
            printf("Logged in successfully.\n");

            // check for table reservation
            FILE *reservations_fp = fopen("reservations.txt", "r");
            if (reservations_fp == NULL) {
                printf("Could not open reservations file.\n");
                return 0;
            }

            char reservation_line[256];
            while (fgets(reservation_line, sizeof(reservation_line), reservations_fp)) {
                char reservation_name[100], table_number[100];
                sscanf(reservation_line, "%s %s", reservation_name, table_number);
                if (strcmp(reservation_name, username) == 0) {
                    printf("Welcome, %s! You have a reservation for table %s.\n", username, table_number);
                    fclose(reservations_fp);
                    return 1;
                }
            }
            fclose(reservations_fp);
            printf("Welcome, %s! You do not have a table reservation.\n", username);
            return 1;
        }
    }
    fclose(fp);
    printf("User not found.\n");
    return 0;
}



