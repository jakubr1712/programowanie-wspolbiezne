#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 4 

sem_t semaphore; // Semafor do synchronizacji wątków
pthread_mutex_t mutex; // Mutex do ochrony danych współdzielonych

int total_sum = 0; // Suma wszystkich wygenerowanych liczb

// Struktura przechowująca dane dla każdego wątku
typedef struct {
    int thread_id;
    int sum;
} ThreadData;

// Funkcja wykonywana przez wątki
void *ThreadFunction(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int random_num1 = rand() % 10 + 1; // Generowanie losowej liczby 1-10
    int random_num2 = rand() % 10 + 1; // Generowanie losowej liczby 1-10

    // Obliczanie sumy wygenerowanych liczb
    data->sum = random_num1 + random_num2;

    // Blokada mutexu przed modyfikacją danych współdzielonych
    pthread_mutex_lock(&mutex);

    // Dodawanie sumy do ogólnej sumy
    total_sum += data->sum;

    // Odblokowanie mutexu
    pthread_mutex_unlock(&mutex);

    // Oczekiwanie na informację od wątku głównego
    sem_wait(&semaphore);

    // Sprawdzanie czy wątek wygrał czy przegrał
    if (data->sum > total_sum / NUM_THREADS) {
        printf("Wątek %d wygrał.\n", data->thread_id);
    } else {
        printf("Wątek %d przegrał.\n", data->thread_id);
    }

    sem_post(&semaphore); // Informowanie wątku głównego o zakończeniu

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    // Inicjalizacja semafora
    sem_init(&semaphore, 0, 0);

    // Inicjalizacja mutexu
    pthread_mutex_init(&mutex, NULL);

    // Tworzenie wątków
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].thread_id = i;
        pthread_create(&threads[i], NULL, ThreadFunction, (void *)&thread_data[i]);
    }

    // Oczekiwanie na zakończenie wątków
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Informowanie wątków o zakończeniu
    for (int i = 0; i < NUM_THREADS; i++) {
        sem_post(&semaphore);
    }

    // Zniszczenie mutexu i semafora
    pthread_mutex_destroy(&mutex);
    sem_destroy(&semaphore);

    return 0;
}
