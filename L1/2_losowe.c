#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define ROZMIAR 1000

int tablica[ROZMIAR];
int podzielne_przez_3 = 0, podzielne_przez_5 = 0, podzielne_przez_7 = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* oblicz(void* arg) {
    int dzielnik = *(int*)arg;
    int i;
    for (i = 0; i < ROZMIAR; i++) {
        if (tablica[i] % dzielnik == 0) {
            pthread_mutex_lock(&mutex);
            if (dzielnik == 3) podzielne_przez_3++;
            if (dzielnik == 5) podzielne_przez_5++;
            if (dzielnik == 7) podzielne_przez_7++;
            pthread_mutex_unlock(&mutex);
        }
    }
    return NULL;
}

int main() {
    pthread_t watek1, watek2, watek3;
    int dzielnik1 = 3, dzielnik2 = 5, dzielnik3 = 7;

    srand(time(NULL));

    for (int i = 0; i < ROZMIAR; i++) {
        int number = rand() % 1000 + 1;
        tablica[i] = number;
    }

    pthread_create(&watek1, NULL, oblicz, (void*)&dzielnik1);
    pthread_create(&watek2, NULL, oblicz, (void*)&dzielnik2);
    pthread_create(&watek3, NULL, oblicz, (void*)&dzielnik3);

    pthread_join(watek1, NULL);
    pthread_join(watek2, NULL);
    pthread_join(watek3, NULL);

    printf("Liczby podzielne przez 3: %d\n", podzielne_przez_3);
    printf("Liczby podzielne przez 5: %d\n", podzielne_przez_5);
    printf("Liczby podzielne przez 7: %d\n", podzielne_przez_7);

    return 0;
}