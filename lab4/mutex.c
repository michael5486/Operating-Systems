#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE 100
#define THREAD_COUNT 10
#define SLEEP_TIME 1

void *printer (void *params);

int threadCount = 0;
pthread_mutex_t mutex;

int main(int argc, char **argv){
    int i;
    pthread_t threadIDs[THREAD_COUNT];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_mutex_init(&mutex, NULL);

    for(i = 0; i < THREAD_COUNT; i ++)
        pthread_create(&threadIDs[i], &attr, printer, NULL);
    

    for(i = 0; i < THREAD_COUNT; i ++)
        pthread_join(threadIDs[i], NULL);

    printf("All threads complete!\n");
    pthread_mutex_destroy(&mutex);
}

void *printer(void *params){

    pthread_mutex_lock(&mutex);

    threadCount++;
    printf("Thread %d started\n", threadCount);

    sleep(SLEEP_TIME);

    printf("Thread %d done\n", threadCount);

    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}