//Michael Esposito's Banker's Algorithm

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3
#define NUMBER_OF_LOOPS 20

typedef struct {
    int id;
} threadData;

pthread_mutex_t mutex; //mutex to control race conditions
int finish[NUMBER_OF_CUSTOMERS]; //array of booleans that will determine if system is in a safe state
int work[NUMBER_OF_CUSTOMERS];

/* the available amount of each resource */
int available[NUMBER_OF_RESOURCES];

/*the maximum demand of each customer */
//int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int maximum[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2,}, {4, 3, 3}}; //numbers from the book example


/* the amount currently allocated to each customer */
//int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1,}, {0, 0, 2}}; //numbers from the book example


/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]; //calculated in the following calculateNeed method

void calculateNeed() {
    int i, j;
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

void initializeFinish() { //initializes all values in finish array to 0
    int i;
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        finish[i] = 0;
    }
}

void printCustomer(int customer_num) { //prints the modified resource info for an individual customer
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

int checkAllSafety() {
    int i;
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        if (finish[i] == 0) {
            return 0; //finish is not true for all i, return 0 (false)
        }
    }
    return 1; //finish is true for all i, return 1 (true)
}

int step2(int work[]) { //safety algorithm as outlined on p331
    
    int i, j;
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        if (finish[i] == 0) {
            for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
                if (need[i][j] <= work[j]) {
                    return i; //found a customer i s.t. both finish[i]==false and need<= work
                }
            }        
        }
    }
    return -1; //step2 failed, must check if all customers are safe
}

int findSafeState() {
    
    int i, j, k, run = 1;
    int work[NUMBER_OF_RESOURCES];
    memcpy(work, available, NUMBER_OF_RESOURCES * sizeof(int)); //copies contents of available[] into work[]
    initializeFinish();
    
    while (run) {
        k = step2(work);
        if (k != -1) { //an i was wound, must run step 3
            for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
                work[j] = work[j] + allocation[k][j]; //work = work +allocation of customer from step 2
            }
            finish[k] = 1;
        }
        else {
            if (checkAllSafety() == 1) {
                run = 0; 
                return 1; //safety check is complete, return 1
            }
            else {
                run = 0;
                return 0; //safety check failed, return 0
            }
        }
    }
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

void printBank() { //prints the resource information of all customers
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
        request[i] = rand() % 5; //I picked 5 as a random threshold, this can be changed
    }
    customer_num = rand() % NUMBER_OF_CUSTOMERS;
    request_resources(customer_num, request);
    if (findSafeState() == 0) {
        printf("System is in unsafe state. Returning to old state");
        release_resources(customer_num, request); //releases resources, returns to old state
        pthread_mutex_unlock(&mutex); //unlock mutex
        sleep(1);
        pthread_mutex_lock(&mutex); //unlock mutex
        release_resources(customer_num, request); //going into critical section again
        pthread_mutex_unlock(&mutex); //unlock mutex
    }
    else {
        printf("System is in safe state\n");
    }
    
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

void *randomRequestAndRelease(void *data) { //makes threads loop 20 times, performing a request and release with each iteration
    int i, id;
    threadData myData = *((threadData *)data);
    id = myData.id;
   
    for (i = 0; i < NUMBER_OF_LOOPS; i++) {
        pthread_mutex_lock(&mutex); //lock mutex before going into critical section
        printf("I am thread %d: Counter: %d\n", id, i);
        requestRandom(); //each thread requests random number of resources
        pthread_mutex_unlock(&mutex); //unlock mutex
        
        sleep(1); //sleep for 1 second
        
        pthread_mutex_lock(&mutex); //lock mutex before going into critical section
        printf("I am thread %d: Counter: %d\n", id, i);
        releaseRandom(); //each thread releases random number of resources
        pthread_mutex_unlock(&mutex); //unlock mutex
        
    }
    pthread_exit(0); //pthread exits
}

int main(int argc, char *argv[]){
    srand(0); //sets the seed of the random number generator
    int i = 1, j = 0, num, numThreads = NUMBER_OF_CUSTOMERS; 
    for (i; i < argc; i++) { //sets the available array to the inputs from the terminal
        available[j] = atoi(argv[i]);
        j++;
    }

    calculateNeed();
    printBank();
    
    pthread_t *threadIds;
    pthread_attr_t attr;

    threadIds = malloc(sizeof(pthread_t) * NUMBER_OF_CUSTOMERS);
    pthread_attr_init(&attr);
    pthread_mutex_init(&mutex, NULL);
    
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        threadData *data = malloc(sizeof(threadData));
        data->id = i;
    
        //create thread
        pthread_create(&threadIds[i], &attr, randomRequestAndRelease, data);
    }
    
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        pthread_join(threadIds[i], NULL);
    }
    printf("All threads complete!\n");
    printBank(); //prints final resource information
    pthread_mutex_destroy(&mutex); //destroys mutex     
}