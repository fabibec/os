#include <stdio.h>
#include <pthread.h>
//Inspired by: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html


pthread_mutex_t mutexCounter = PTHREAD_MUTEX_INITIALIZER;
short counter = 0;

void* printCounter(void* threadName);

int main (void){
    pthread_t threads[2];
    char* threadNames[2] = {"Thread 1", "Thread 2"};
    int iret1, iret2;

    iret1 = pthread_create(threads, NULL, printCounter, (void*) threadNames[0]);
    iret2 = pthread_create((threads + 1), NULL, printCounter, (void*) threadNames[1]);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    printf("Thread 1 returns: %d\n2", iret1);
    printf("Thread 2 returns: %d\n", iret2);
    return 0;
}

void* printCounter(void* threadName){
    while(counter < 10){
        pthread_mutex_lock(&mutexCounter);
        printf("Message from %s: Counter is at %hu\n", (char *) threadName, ++counter);
        pthread_mutex_unlock(&mutexCounter);
        sleep(2);
    }
}
