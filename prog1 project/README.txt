-->consumer panel : the makefile which will be outputed to customer
-->admin panel: the executable file which will be outputed to admin/manager

functions of each file:
1)menu.c:(Sanjeev)

This is a C program that allows the user to create a menu by entering the number of menu items, their names, and prices, which are saved to a text file named "menu.txt". The program also allows the user to edit and delete menu items by reading the items from the "menu.txt" file, displaying them to the user, and prompting the user to enter an item number to edit or delete. The edited menu is saved back to the "menu.txt" file. The program uses various functions to perform these tasks, including functions to create the menu, read the menu from the file, display the menu to the user, delete a menu item, edit a menu item, and repeatedly ask the user to enter the item number to edit or delete

2)bill.c:(Akash and Sanjeev)

This program is a basic implementation of a restaurant ordering system. It reads a menu from a file, displays it to the user, takes the user's order, calculates the bill, and writes the total bill to a file. The user can select menu items and specify the quantity, and the program will calculate the total cost of the order.

3)consumer.c:(Satwik)

The code defines two functions: signup and login for a user management system.
The signup function prompts the user to enter their name and phone number, checks if the user already exists, and then adds the new user to a global array of users and a file called customer_info.txt.
The login function prompts the user to enter their name and phone number, reads the customer_info.txt file to check if the user exists, and then checks if the user has a reservation for a table by reading a reservations.txt file.

4)advance_booking.c:(Aryan)

This is a program for managing table reservations. It reads and writes reservations to a file called "reservations.txt". The user can reserve tables, cancel reservations, and view available tables.


5)consumer_main.c:(Akash)
this is the main file that is outputed to customer

6)admin_main.c:(Sanjeev,Harshith,Kireeti)
this file has several functions like see and edit employees info and see restaurant finance.
Sanjeev,Harshith-->functions related to employees to read and edit them(name,salary,ag,etc)
kireeti-->functions related to finance,main

