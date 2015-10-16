#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
    Program that takes two command line arguments:
        1) The number of threads to create.
        2) The message that each thread will print out
        
    Threads will:
        1) Print out their thread number } passed to each thread
        2) Print out the message         } via void*
        
    Usage: ./a.out N message*/
    
void *printingThread(void *);    
    
typedef struct {
    int id;
    char *message;
} threadData;
    
int main(int argc, char *argv[]) {
    int i, numThreads;
    char *threadMessage;
    
    pthread_t *threadIds;
    pthread_attr_t attr;
    
    numThreads = atoi(argv[1]);
    threadMessage = argv[2];
    
    printf("Number of threads = %d, Thread message = %s\n", numThreads, threadMessage);
    
    threadIds = malloc(sizeof(pthread_t) * numThreads);
    
    pthread_attr_init(&attr);
    
    for (i = 0; i < numThreads; i++) {
        //prepare data to send to the i-th thread
        /*threadData *data = malloc(sizeof(threadData));
        data->id = i;
        data->message = threadMessage;*/
        void **voidPtrArr = malloc(sizeof(void *) * 2);
        int *spaceFori = malloc(sizeof(int));
        *spaceFori = i;
        voidPtrArr[0] = spaceFori;
        voidPtrArr[1] = threadMessage;
        
        //create thread
        pthread_create(&threadIds[i], &attr, printingThread, voidPtrArr);
        
    }
    
    for (i = 0; i < numThreads; i++) {
        pthread_join(threadIds[i], NULL);
    }
    
}

void *printingThread(void *data) {
    int id;
    char *message;
    void **ptrArr = (void **)data;
    
    sleep(1);
    id = *((int *)ptrArr[0]);
    message = (char *)ptrArr[1];
    
    //threadData myData = *((threadData *)data);
    //id = myData.id;
    //message = myData.message;
    printf("I am thread %d: %s\n", id, message);
    
    pthread_exit(0);
    
}