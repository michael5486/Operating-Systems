#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

/* the available amount of each resource */
int available[NUMBER_OF_RESOURCES];

/*the maximum demand of each customer */
//int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int maximum[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2,}, {4, 3, 3}};


/* the amount currently allocated to each customer */
//int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1,}, {0, 0, 2}};


/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

int request_resources(int customer_num, int request[]) {
    
}

int release_resources(int customer_num, int release[]) {
    
}


void printBank() {
    int i = 0, j = 0;
    printf("Available:\n");
    for (i; i < NUMBER_OF_RESOURCES; i++) {
        printf("[%d] ", available[i]);
        
    }
    printf("\n");
    i = 0;
    printf("Maximum:\n");
    for (i; i < NUMBER_OF_CUSTOMERS; i++) {
        printf("Customer %d: ", i);
        for (j; j < NUMBER_OF_RESOURCES; j++) {
            printf("[%d] ", maximum[i][j]);
        }
        j = 0;
        printf("\n");
        
    }
    i = 0;
    j = 0;
    printf("Need:\n");
    for (i; i < NUMBER_OF_CUSTOMERS; i++) {
        printf("Customer %d: ", i);
        for (j; j < NUMBER_OF_RESOURCES; j++) {
            printf("[%d] ", need[i][j]);
        }
        j = 0;
        printf("\n");
        
    }
    j = 0;    
    
}


int main(int argc, char *argv[]){
    
    int i = 1, j = 0, k = 2, numThreads = NUMBER_OF_CUSTOMERS; 
    for (i; i < argc; i++) { //sets the available array to the inputs from the terminal
        available[j] = *argv[i] - '0';
        j++;
    }

    printBank();
    
    
    
}