#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 100
#define THREAD_COUNT 10
#define SLEEP_TIME 1

void *printer (void *params);

//Global int
int threadCount = 0;
pthread_mutex_t mutex;

int main(int argc, char **argv){
    int i;
    
    //Array of pthread_t
    pthread_t threadIDs[THREAD_COUNT];
    
    //Attributes variables
    pthread_attr_t attr;

    //Sets the variables
    pthread_attr_init(&attr);
    pthread_mutex_init(pthread_mutex_t &mutex, NULL);

    //Create 10 threads
    for(i = 0; i < THREAD_COUNT; i ++)
        pthread_create(&threadIDs[i], &attr, printer, NULL);
    
    //parent waits for each thread to finish
    for(i = 0; i < THREAD_COUNT; i ++)
        pthread_join(threadIDs[i], NULL);

    printf("All threads complete!\n");
    pthread_mutex_destroy(&mutex);
}

void *printer(void *params){
    //Increment the thread count
    threadCount++;
    
    pthread_mutex_lock(&mutex);
    printf("Thread %d started\n", threadCount);

    //Waiting for 1 second
    sleep(SLEEP_TIME);

    printf("Thread %d done\n", threadCount);
    
    pthread_mutx_unlock(&mutex);


    pthread_exit(0);
}