#ifndef CONSUMER_H
#define CONSUMER_H

#define MAX_USERS 10
#define MAX_RECOMMENDATIONS 5

//user struct
struct User {
    char name[20];
    char phoneno[10];
    int num_orders;
    int order_history[MAX_RECOMMENDATIONS];
};

//function prototypes
void signup();
int login();

#endif
