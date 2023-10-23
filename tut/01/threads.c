#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
//Inspired by: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html

pthread_mutex_t mutexCounter = PTHREAD_MUTEX_INITIALIZER;
short counter = 0;

void* printCounter(void* threadName);

typedef struct {
    pthread_t id;
    char* name;
    int retVal;
} threadInfo;

int main (void){
    threadInfo threads[2];
    threads[0].name = "Michi";
    threads[1].name = "Flo";

    threads[0].retVal = pthread_create(&(threads[0].id), NULL, printCounter, (void*) threads[0].name);
    threads[1].retVal = pthread_create(&(threads[1].id), NULL, printCounter, (void*) threads[1].name);

    pthread_join(threads[0].id, NULL);
    pthread_join(threads[1].id, NULL);

    printf("%s returns: %d\n", threads[0].name, threads[0].retVal);
    printf("%s returns: %d\n", threads[1].name, threads[1].retVal);
    
    pthread_exit(0);
    return 0;
}

void* printCounter(void* threadName){

    pthread_mutex_lock(&mutexCounter);
    while(counter < 10){
        pthread_mutex_unlock(&mutexCounter);
        pthread_mutex_lock(&mutexCounter);
        printf("Message from %s: Counter is at %hu\n", (char *) threadName, ++counter);
        pthread_mutex_unlock(&mutexCounter);
        sleep(2);
    }
}

