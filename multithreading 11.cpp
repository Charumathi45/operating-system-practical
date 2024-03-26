#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h> // For intptr_t

#define NUM_THREADS 5

// Function to be executed by each thread
void *thread_function(void *thread_id) {
    intptr_t tid = (intptr_t)thread_id;
    printf("Hello from thread %ld\n", (long)tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    intptr_t t; // Change the type to intptr_t

    // Create multiple threads
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %ld\n", (long)t);
        rc = pthread_create(&threads[t], NULL, thread_function, (void *)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Wait for all threads to complete
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("All threads have completed execution.\n");

    pthread_exit(NULL);
}

