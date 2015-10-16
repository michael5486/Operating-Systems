#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *threadFunction(void*);
void createThread(pthread_t *);

int main() {
    pthread_t threadID;
    
    createThread(&threadID);
    
    pthread_join(threadID, NULL);
}

void createThread(pthread_t *threadID) {
    pthread_attr_t attr;
    pthread_attr_init(&attr); //set to default values
    
    int *intPtr = malloc(sizeof(int));
    *intPtr = 100;
    
    pthread_create(threadID, &attr, threadFunction, intPtr);
}

void *threadFunction(void *data) {
    sleep(1); //Do some work for a second (unistd.h)
    int passedInt = *((int *)data);
    
    printf("The number passed to me is %d\n", passedInt);
    
    pthread_exit(0);
    
}