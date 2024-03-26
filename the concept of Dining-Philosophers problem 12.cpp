#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *((int *) arg);
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", id);
        usleep(rand() % 1000000);

        // Pick up forks
        printf("Philosopher %d is hungry and trying to pick up forks.\n", id);
        pthread_mutex_lock(&forks[left_fork]);
        printf("Philosopher %d picked up fork %d (left).\n", id, left_fork);
        pthread_mutex_lock(&forks[right_fork]);
        printf("Philosopher %d picked up fork %d (right).\n", id, right_fork);

        // Eating
        printf("Philosopher %d is eating.\n", id);
        usleep(rand() % 1000000);

        // Put down forks
        pthread_mutex_unlock(&forks[left_fork]);
        printf("Philosopher %d put down fork %d (left).\n", id, left_fork);
        pthread_mutex_unlock(&forks[right_fork]);
        printf("Philosopher %d put down fork %d (right).\n", id, right_fork);
    }
}

int main() {
    int i;
    int ids[NUM_PHILOSOPHERS];

    // Initialize mutexes for each fork
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create threads for each philosopher
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

