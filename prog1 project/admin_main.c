#include <stdio.h>
#include <string.h>
#include<stdlib.h>

 void clrscr(){
    printf("\033[2J"); // Escape sequence to clear screen
    printf("\033[%d;%dH", 0, 0); // Move cursor to the top left corner
}
// These functions manages a list of employees stored in a file called "employees.txt"
// It allows the user to view the list, add new employees, remove existing employees
// Function to display the list of employees 
void view_employees_list() {
    FILE* fp;
    char name[20];
    int age, salary;
    char designation[20];
// Open the file for reading
    fp = fopen("employees.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Name\tAge\tSalary\tDesignation\n");
    // Read the file line by line and display the employee information
    while (fscanf(fp, "%s %d %d %s", name, &age, &salary, designation) != EOF) {
        printf("%s\t%d\t%d\t%s\n", name, age, salary, designation);
    }
// Close the file
    fclose(fp);
}
// Function to add a new employee 
void add_employee() {
    FILE* fp;
    char name[20];
    int age, salary;
    char designation[20];
// Open the file for appending
    fp = fopen("employees.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
// Prompt the user to enter the employee information
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter age: ");	//take all the data we need to add an employee
    scanf("%d", &age);
    printf("Enter salary: ");
    scanf("%d", &salary);
    printf("Enter designation: ");
    scanf("%s", designation);

    fprintf(fp, "%s %d %d %s\n", name, age, salary, designation); 		//print that data in the file

    fclose(fp);	//close the file
}
//this functions helps in removing an employee from the list
void remove_employee() {
    FILE* fp, * temp_fp;//first declare the file pointers
    char name[20];
    int age, salary;
    char designation[20];
    char temp_name[20];
    int temp_age, temp_salary;
    char temp_designation[20];
    int found = 0;// a flag to indicate if the employee to be removed is found
// open the file for reading
    fp = fopen("employees.txt", "r");
    if (fp == NULL) {// error handling if the file can't be opened
        printf("Error opening file!\n");
        return;
    }

    printf("Enter name of employee to remove: ");
    scanf("%s", name);
// open a temporary file to write the contents of "employees.txt" except the line corresponding to the employee to be removed
    temp_fp = fopen("temp.txt", "w");
    if (temp_fp == NULL) {// error handling if the temporary file can't be opened
        printf("Error opening file!\n");
        return;
    }

    // Copy all the contents of the "employees.txt" file to "temp.txt",
    // except the line corresponding to the employee to be removed
    while (fscanf(fp, "%s %d %d %s", temp_name, &temp_age, &temp_salary, temp_designation) != EOF) {
        if (strcmp(name, temp_name) == 0) {// if the employee to be removed is found, set the flag to 1 and skip the current iteration of the loop
            found = 1;
            continue;
        }
        fprintf(temp_fp, "%s %d %d %s\n", temp_name, temp_age, temp_salary, temp_designation);
    }
//close both the files
    fclose(fp);
    fclose(temp_fp);

    // Delete the old "employees.txt" file and rename "temp.txt" to "employees.txt"
    if (found) {
        remove("employees.txt");
        rename("temp.txt", "employees.txt");
    } else {
        printf("Employee not found!\n");
        remove("temp.txt");
    }
}
// This function is used to update employee information in a file.
void update_employee_information() {
    FILE* fp;
    char name[20]; // Variable to store employee name
    int age, salary, field_choice;
    char designation[20];//variable to store employee designation
    char employee_name[20];//variable to store employee name which we want to update
// Ask user for name of employee to update
    printf("Enter the name of the employee you want to update: ");
    scanf("%s", employee_name);
// Open file for reading and writing
    fp = fopen("employees.txt", "r+");//open a file in read and write mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
// Loop through each employee in the file
    while (fscanf(fp, "%s %d %d %s", name, &age, &salary, designation) != EOF) {
    	// Check if the current employee is the one the user wants to update
        if (strcmp(name, employee_name) == 0) {
        	// If so, prompt the user for which field they want to update
            printf("Select the field you want to update:\n");
            printf("1. Age\n");
            printf("2. Salary\n");
            printf("3. Designation\n");
            printf("Choice: ");
            scanf("%d", &field_choice);
// Use a switch statement to update the selected field
            switch (field_choice) {
                case 1:
                    printf("Enter updated age: ");
                    scanf("%d", &age);
                    break;
                case 2:
                    printf("Enter updated salary: ");
                    scanf("%d", &salary);
                    break;
                case 3:
                    printf("Enter updated designation: ");
                    scanf("%s", designation);
                    break;
                default:
                	// If an invalid choice is made, print an error message and return
                    printf("Invalid choice. No changes will be made.\n");
                    fclose(fp);
                    return;
            }
            // Move the file pointer back to the beginning of the current employee's information

            fseek(fp, -1*(strlen(name)+sizeof(age)+sizeof(salary)+strlen(designation)+3), SEEK_CUR);
            // Overwrite the current employee's information with the updated values
            fprintf(fp, "%s %d %d %s\n", name, age, salary, designation);
            // Exit the loop, since we've found and updated the desired employee
            break;
        }
    }
//close the file
    fclose(fp);
}


//Will read salary from text file, and will return total  salary
int calculate_total_salary(int* p) {
    FILE* fp;
    int total_salary = 0;
    char name[20];
    int age, salary;
    char designation[20];

    fp = fopen("employees.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        
    }

    while (fscanf(fp, "%s %d %d %s", name, &age, &salary, designation) != EOF) {
        total_salary += salary;
    }
    *p = total_salary;
    fclose(fp);
    
}

//will read total amount of bill value and return
int sum_total_bill(int*orders) {
    int sum = 0;
    FILE *file;
    file = fopen("total_bill.txt", "r");
    if (file == NULL) {
        printf("Error: File not found\n");
        return 0;
    }
    int bill;
    while (fscanf(file, "%d", &bill) != EOF) {
        (*orders)++;
        sum += bill;

    }
    fclose(file);
    return sum;
}


int main()
{   
    clrscr();
    printf("\n");
    printf("\t\t\t\tWelcome to Imtech Dhaba Admin Panel\n");
    while(1){
        printf("\t\t\t\tPlease Choose one of the options\n");
        printf("\t\t\t\t1.View Employees List\n");
        printf("\t\t\t\t2.Add Employee\n");
        printf("\t\t\t\t3.Remove Employee\n");
        printf("\t\t\t\t4.Update Employee Information\n");
        printf("\t\t\t\t5.See Restaurant Finance\n");
        printf("\t\t\t\tPress Any other key to exit\n");

        printf("\n\n\n");
        int user_option;printf("\t\t\t\tOption:");scanf("%d",&user_option);
        printf("\n\n\n\n");
        switch (user_option)
        {       
        case 1:
            clrscr();
            view_employees_list();
            printf("\n\n\n\n");
            break;

        case 2:
            clrscr();
            add_employee();
            printf("Employee added successfully\n");
            printf("\n\n\n\n");
            break;

        case 3:
            clrscr();
            remove_employee();
            printf("Employee removed successfully\n");
            printf("\n\n\n\n");
            break;
        case 4:
            clrscr();
            update_employee_information();
            printf("Employee info updated successfully\n");
            printf("\n\n\n\n");
            break;
        case 5:
            clrscr();
            int total_salary=0;
            int total_orders=0;
            (calculate_total_salary(&total_salary));
            int total_bill = sum_total_bill(&total_orders);
            printf("Total Bills: %d\n", total_bill);
            printf("Total Orders: %d\n",total_orders);
            printf("Average Food Order: %f\n",((float)total_bill)/total_orders);
            //0.5 indicates amount got from each bill after removing cost price and 24 indicates number of working days
            float profit = (total_bill)*0.5 - (float)total_salary/24;
            printf("Total Profit:%0.2f",profit);
            printf("\n\n\n\n");
            break;
            

        default:
            exit(1);

            break;
        }
    }
    
    return 0;
}