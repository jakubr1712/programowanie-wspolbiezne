#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define ROZMIAR 1000
#define LICZBA_WATKOW 10

int tablica[ROZMIAR];
int minima[LICZBA_WATKOW];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* oblicz_minimum(void* arg) {
    int poczatek = *(int*)arg;
    int koniec = poczatek + ROZMIAR / LICZBA_WATKOW;
    if (poczatek == (LICZBA_WATKOW - 1) * (ROZMIAR / LICZBA_WATKOW)) {
        koniec = ROZMIAR; // ostatni wątek obejmuje resztę tablicy
    }
    int lokalne_minimum = INT_MAX;

    for (int i = poczatek; i < koniec; i++) {
        if (tablica[i] < lokalne_minimum) {
            lokalne_minimum = tablica[i];
        }
    }

    pthread_mutex_lock(&mutex);
    minima[poczatek / (ROZMIAR / LICZBA_WATKOW)] = lokalne_minimum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t watki[LICZBA_WATKOW];
    int indeksy[LICZBA_WATKOW];

    srand(time(NULL));

    for (int i = 0; i < ROZMIAR; i++) {
        tablica[i] = rand() % 1000 + 1;
    }

    // Utwórz wątki
    for (int i = 0; i < LICZBA_WATKOW; i++) {
        indeksy[i] = i * (ROZMIAR / LICZBA_WATKOW);
        pthread_create(&watki[i], NULL, oblicz_minimum, &indeksy[i]);
    }

    // Czekaj na zakończenie wątków
    for (int i = 0; i < LICZBA_WATKOW; i++) {
        pthread_join(watki[i], NULL);
    }

    // Znajdź najmniejszą wartość
    int minimum = INT_MAX;
    for (int i = 0; i < LICZBA_WATKOW; i++) {
        if (minima[i] < minimum) {
            minimum = minima[i];
        }
    }

    printf("Najmniejsza liczba w tablicy: %d\n", minimum);

    return 0;
}