#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

typedef struct {
    int request[NUMBER_OF_RESOURCES];
} customerData;

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

void calculateNeed() {
    int i, j;
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
            
        }
    }
}

void printCustomer(int customer_num) {
    int j;
    printf("Available:  ");
    for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
        printf("[%d] ", available[j]);
    }
    printf("\nAllocation:\nCustomer %d: ", customer_num);
    for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
        printf("[%d] ", allocation[customer_num][j]);
    }
    printf("\nNeed:\nCustomer %d: ", customer_num);
    for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("[%d] ", need[customer_num][j]);
    }
    printf("\nMaximum:\nCustomer %d: ", customer_num);
    for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("[%d] ", maximum[customer_num][j]);
    }    
    printf("\n--------------------------------\n");
}

int checkRequestSafety(int customer_num, int request[]) { //checks if the resources for each request are available
    
    int j;
    for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
        if (request[j] > need[customer_num][j]) {
            return -1; //request cannot be granted, request is greater than customer's need
        }
        if (request[j] > available[j]) {
            return 0; //request cannot be granted, request is greater than available resources
        }
        
    }
    return 1; //request can be granted
}

int checkReleaseSafety(int customer_num, int release[]) {
    
    int j;
    for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
        if (release[j] > allocation[customer_num][j]) {
            return 0; //release call is greater than the customer's allocated resources
        }
    }
    return 1; //release can be granted
}

int request_resources(int customer_num, int request[]) {
    int j;
    printf("Request, C%d:", customer_num);
    for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
        printf("[%d] ", request[j]);
    }
    printf("\n");
    if (checkRequestSafety(customer_num, request) == -1) {
        printf("Error: System unable to allocate the requested resources. Request greater than need\n");
        return 0;
    }
    else if (checkRequestSafety(customer_num, request) == 0) {
        printf("Error: System is unable to allocate the requested resources. Request greater than  available resources\n");
        return 0;
    }
    else { //system can allocate resources
        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            available[j] = available[j] - request[j];
            allocation[customer_num][j] = allocation[customer_num][j] + request[j];
            need[customer_num][j] = need[customer_num][j] - request[j];
        }
    }
    printCustomer(customer_num);
    return -1;
}

int release_resources(int customer_num, int release[]) {
    int j;
    printf("Release, C%d:", customer_num);
    for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
        printf("[%d] ", release[j]);
    }
    printf("\n");
    if (checkReleaseSafety(customer_num, release) == 0) {
        printf("Error: System is unable to release the requested resources. Release greater than allocated resources\n");
        return 0;
    }
    else { //system can release resources
        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            available[j] = available[j] + release[j];
            allocation[customer_num][j] = allocation[customer_num][j] - release[j];
            need[customer_num][j] = need[customer_num][j] + release[j];
        }
    }
    printCustomer(customer_num);
    return -1;
}

void printBank() {
    int i, j;
    printf("Available:\n");
    for (i = 0; i < NUMBER_OF_RESOURCES; i++) {
        printf("[%d] ", available[i]);
        
    }
    printf("\nMaximum:\n");
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        printf("Customer %d: ", i);
        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("[%d] ", maximum[i][j]);
        }
        printf("\n");
    }
    printf("Allocation:\n");
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        printf("Customer %d: ", i);
        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("[%d] ", allocation[i][j]);
        }
        printf("\n");
    }    
    printf("Need:\n");
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        printf("Customer %d: ", i);
        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("[%d] ", need[i][j]);
        }
        printf("\n");
    }
    printf("\n--------------------------------\n");
}

void requestRandom() { //requests a random amount of resources from a random customer
    int i, customer_num;
    int request[NUMBER_OF_RESOURCES];
    for (i = 0; i < NUMBER_OF_RESOURCES; i++) {
        request[i] = rand() % 5;
    }
    customer_num = rand() % NUMBER_OF_CUSTOMERS;
    request_resources(customer_num, request);
}

void releaseRandom() { //releases a random amount of resources from a random customer
    int i, customer_num;
    int release[NUMBER_OF_RESOURCES];
    for (i = 0; i < NUMBER_OF_RESOURCES; i++) {
        release[i] = rand() % 5;
    }
    customer_num = rand() % NUMBER_OF_CUSTOMERS;
    release_resources(customer_num, release);
}

int main(int argc, char *argv[]){
    srand(0); //sets the seed of the random number generator
    int i = 1, j = 0, k = 2, numThreads = NUMBER_OF_CUSTOMERS; 
    for (i; i < argc; i++) { //sets the available array to the inputs from the terminal
        available[j] = atoi(argv[i]);
        j++;
    }

    calculateNeed();
    printBank();
    
    
   // int request[3] = {1, 0, 2};
//    int release[3] = {3, 0, 2};
    //printf("request safety: %d", checkSafety(1, request));
  //  request_resources(1, request);
//    release_resources(1, release);
   for (i = 0; i < 20; i++) {
        requestRandom();
        releaseRandom();
   }
    
   /* pthread_t *threadIds;
    pthread_attr_t attr;
    
    threadIds = malloc(sizeof(pthread_t) * numThreads);
    pthread_attr_init(&attr);
    
        //prepare data to send to the i-th thread
        customerData *data = malloc(sizeof(customerData));
        data->request[0] = 1;
        data->request[1] = 0;
        data->request[2] = 2;

        
        //create thread
        pthread_create(&threadIds[i], &attr, printingThread, voidPtrArr);*/
        

    
}