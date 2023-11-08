#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_LICZB 1000

double sumy[MAX_LICZB];
int liczby[MAX_LICZB];
int liczba_liczb = 0;

void* oblicz_sume(void* arg) {
    int indeks = *(int*)arg;
    int liczba = liczby[indeks];
    double suma = 0;

    for (int i = 1; i <= liczba; i++) {
        suma += i;
    }

    sumy[indeks] = suma;

    return NULL;
}

int main() {
    pthread_t watki[MAX_LICZB];
    int indeksy[MAX_LICZB];

    // Pobierz liczby z pliku
    FILE* plik = fopen("liczby.txt", "r");
    if (plik == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return 1;
    }

    while (fscanf(plik, "%d", &liczby[liczba_liczb]) == 1) {
        liczba_liczb++;
    }

    fclose(plik);

    // Utwórz wątki
    for (int i = 0; i < liczba_liczb; i++) {
        indeksy[i] = i;
        pthread_create(&watki[i], NULL, oblicz_sume, &indeksy[i]);
    }

    // Czekaj na zakończenie wątków
    for (int i = 0; i < liczba_liczb; i++) {
        pthread_join(watki[i], NULL);
    }

    // Wypisz sumy
    for (int i = 0; i < liczba_liczb; i++) {
        printf("Suma liczb naturalnych do %d: %.2f\n", liczby[i], sumy[i]);
    }

    return 0;
}