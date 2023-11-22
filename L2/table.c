#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 4 

pthread_t threads[NUM_THREADS];
sem_t evenEntrance, oddEntrance, roomSem;
pthread_mutex_t roomMutex = PTHREAD_MUTEX_INITIALIZER;

void* person(void* arg) {
    int person_id = *((int*)arg);
    int partner_id;

    while (1) {
        // Osoba wykonuje swoje sprawy (sekcja lokalna)
        printf("Osoba %d wykonuje swoje sprawy.\n", person_id);

        // Osoba idzie na spotkanie
        if (person_id % 2 == 0) {
            sem_wait(&evenEntrance);
            partner_id = (person_id + 1) % NUM_THREADS;
        } else {
            sem_wait(&oddEntrance);
            partner_id = (person_id - 1 + NUM_THREADS) % NUM_THREADS;
        }

        // Osoba zajmuje miejsce przy stoliku
        pthread_mutex_lock(&roomMutex);
        sem_post(&roomSem); // Osoba wchodzi do pokoju
        printf("Osoba %d wchodzi do pomieszczenia.\n", person_id);

        // Czekanie na partnera
        while (sem_trywait(&roomSem) != 0) {
            pthread_mutex_unlock(&roomMutex);
            sched_yield(); // Pozwala na przełączenie się do innego wątku
            pthread_mutex_lock(&roomMutex);
        }

        // Spotkanie
        printf("Osoba %d spotyka osobę %d.\n", person_id, partner_id);
        printf("Osoba %d spotyka osobę %d.\n", partner_id, person_id);
        usleep(1000000); // Symulacja trwania spotkania

        // Opuszczenie miejsca przy stoliku
        sem_post(&roomSem);
        printf("Osoba %d opuszcza pomieszczenie.\n", person_id);
        pthread_mutex_unlock(&roomMutex);

        // Opuszczenie pomieszczenia
        if (person_id % 2 == 0) {
            sem_post(&evenEntrance);
        } else {
            sem_post(&oddEntrance);
        }

        // Oczekiwanie przed kolejnym spotkaniem
        usleep(2000000); // Symulacja czasu między spotkaniami
    }

    return NULL;
}

int main() {
    int thread_ids[NUM_THREADS];
    sem_init(&evenEntrance, 0, 1); // Inicjalizacja semaforów
    sem_init(&oddEntrance, 0, 1);
    sem_init(&roomSem, 0, 2); // Pojemność pomieszczenia to 2 osoby

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, person, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&evenEntrance);
    sem_destroy(&oddEntrance);
    sem_destroy(&roomSem);

    return 0;
}
