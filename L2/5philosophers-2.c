#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_t philosophers[NUM_PHILOSOPHERS];
sem_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *((int *)arg);
    int left_fork, right_fork;

    if (id % 2 == 0) {
        // Filozofowie o numerach parzystych biorą widelce odwrotnie
        right_fork = id;
        left_fork = (id + 1) % NUM_PHILOSOPHERS;
    } else {
        left_fork = id;
        right_fork = (id + 1) % NUM_PHILOSOPHERS;
    }

    while (1) {
        // Filozof myśli
        printf("Filozof %d myśli...\n", id);
        sleep(1);

        // Filozof chce jeść
        printf("Filozof %d chce jeść...\n", id);

        // Aby uniknąć zakleszczenia, stosujemy semafory do zarządzania widłami
        sem_wait(&forks[left_fork]);
        sem_wait(&forks[right_fork]);

        // Filozof je
        printf("Filozof %d je...\n", id);
        sleep(2);

        // Filozof skończył jedzenie i odkłada widelce
        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);
    }
}

int main() {
    int i;
    int ids[NUM_PHILOSOPHERS];

    // Inicjalizacja semaforów dla widelców
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Tworzenie wątków filozofów
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Oczekiwanie na zakończenie wątków
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Zniszczenie semaforów
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
