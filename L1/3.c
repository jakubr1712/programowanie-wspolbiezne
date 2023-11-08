#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define ROZMIAR 1000
#define LICZBA_WATKOW 10

int tablica[ROZMIAR];
long long suma = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* oblicz_sume(void* arg) {
    int poczatek = *(int*)arg;
    int koniec = poczatek + ROZMIAR / LICZBA_WATKOW;
    if (poczatek == (LICZBA_WATKOW - 1) * (ROZMIAR / LICZBA_WATKOW)) {
        koniec = ROZMIAR; // ostatni wątek obejmuje resztę tablicy
    }
    long long lokalna_suma = 0;

    for (int i = poczatek; i < koniec; i++) {
        lokalna_suma += tablica[i];
    }

    pthread_mutex_lock(&mutex);
    suma += lokalna_suma;
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
        pthread_create(&watki[i], NULL, oblicz_sume, &indeksy[i]);
    }

    // Czekaj na zakończenie wątków
    for (int i = 0; i < LICZBA_WATKOW; i++) {
        pthread_join(watki[i], NULL);
    }

    printf("Suma liczb w tablicy: %lld\n", suma);

    return 0;
}