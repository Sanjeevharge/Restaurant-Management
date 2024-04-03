#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLES 10
#define FILENAME "reservations.txt"
// Define a struct to hold reservation info
struct Reservation {
    char name[50];
    int num_people;
};
// Fuction to read reservation from files , update array of reservation
void read_reservations(struct Reservation *reservations) {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("Error: could not read reservations from file\n");
        return;
    }
// Read  reservation from file and store it in array
    for (int i = 0; i < MAX_TABLES; i++) {
        fscanf(fp, "%s %d\n", reservations[i].name, &reservations[i].num_people);
    }

    fclose(fp);
}

void write_reservations(struct Reservation *reservations) {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        printf("Error: could not write reservations to file\n");
        return;
    }

    for (int i = 0; i < MAX_TABLES; i++) {
        fprintf(fp, "%s %d\n", reservations[i].name, reservations[i].num_people);
    }

    fclose(fp);
}

void reserve_table(struct Reservation *reservations) {
    int table_number;
    printf("Enter the table number: ");
    scanf("%d", &table_number);
// Check if the table is reserved before
    if (reservations[table_number - 1].num_people == 0) {
        struct Reservation new_reservation;
        printf("Enter your name: ");
        scanf("%s", new_reservation.name);
        printf("Enter the number of people: ");
        scanf("%d", &new_reservation.num_people);
// Add a new reservation to the array and write to the file
        reservations[table_number - 1] = new_reservation;
        write_reservations(reservations);
        printf("Table %d reserved for %d people\n", table_number, new_reservation.num_people);
    } else {
        printf("Table %d is already reserved\n", table_number);
    }
}
// Function to cancel a reservation
void cancel_reservation(struct Reservation *reservations) {
    int table_number;
    printf("Enter the table number: ");
    scanf("%d", &table_number);
// Check if table is reserved before
    if (reservations[table_number - 1].num_people == 0) {
        printf("Table %d is not reserved\n", table_number);
    } else {
        char name[50];
        printf("Enter the name on the reservation: ");
        scanf("%s", name);
// Check if name matches reservation and cancel reservation if it does
        if (strcmp(reservations[table_number - 1].name, name) == 0) {
            reservations[table_number - 1].num_people = 0;
            write_reservations(reservations);
            printf("Reservation for table %d cancelled\n", table_number);
        } else {
            printf("Name does not match reservation\n");
        }
    }
}
// Function to view available tables
void view_available_tables(struct Reservation *reservations) {
    printf("Available tables:\n");
    for (int i = 0; i < MAX_TABLES; i++) {
        if (reservations[i].num_people == 0) {
            printf("Table %d\n", i + 1);
        }
    }
}
int main() {
    struct Reservation reservations[MAX_TABLES] = {0};

    while (1) {
        read_reservations(reservations);  // update reservations from file

        printf("\nTable Reservation System\n");
        printf("1. Reserve table\n");
        printf("2. Cancel reservation\n");
        printf("3. View available tables\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                reserve_table(reservations);
                break;
            case 2:
                cancel_reservation(reservations);
                break;
            case 3:
                view_available_tables(reservations);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}