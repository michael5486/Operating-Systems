#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

/* the available amount of each resource */
int available[NUMBER_OF_RESOURCES];

/*the maximum demand of each customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* the amount currently allocated to each customer */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

int request_resources(int customer_num, int request[]) {
    
}

int release_resources(int customer_num, int release[]) {
    
}


int main(int argc, char *argv[]){
    
    if (argc == 4) {
        int arg1 = *argv[1] - '0';
        int arg2 = *argv[2] - '0';
        int arg3 = *argv[3] - '0';
        
        printf("args: %d %d %d\n", arg1, arg2, arg3);
    } 
    else {
        printf("Invalid number of arguments\n");
        
    }
        
    
}