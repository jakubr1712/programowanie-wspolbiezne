#include <stdio.h>
#include <pthread.h>

#define ROZMIAR 5

int tab1[] = {2, 3, 6, 8, 10};
int tab2[] = {4, 6, 8, 10, 12};
int tab3[] = {3, 4, 5, 6, 7};
int wynik1 = -1, wynik2 = -1, wynik3 = -1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* znajdz_wspolna_watki(void* arg) {
    int* tab = (int*)arg;
    int i, j, k;
    
    for (i = 0; i < ROZMIAR; i++) {
        for (j = 0; j < ROZMIAR; j++) {
            for (k = 0; k < ROZMIAR; k++) {
                if (tab1[i] == tab2[j] && tab2[j] == tab3[k]) {
                    pthread_mutex_lock(&mutex);
                    if (tab == tab1) wynik1 = i;
                    if (tab == tab2) wynik2 = j;
                    if (tab == tab3) wynik3 = k;
                    pthread_mutex_unlock(&mutex);
                    return NULL;
                }
            }
        }
    }
    
    return NULL;
}

int main() {
    pthread_t watek1, watek2, watek3;
    
    pthread_create(&watek1, NULL, znajdz_wspolna_watki, (void*)tab1);
    pthread_create(&watek2, NULL, znajdz_wspolna_watki, (void*)tab2);
    pthread_create(&watek3, NULL, znajdz_wspolna_watki, (void*)tab3);
    
    pthread_join(watek1, NULL);
    pthread_join(watek2, NULL);
    pthread_join(watek3, NULL);
    
    if (wynik1 != -1 && wynik2 != -1 && wynik3 != -1) {
        printf("Wspolna liczba zostala znaleziona na indeksach %d, %d, %d w odpowiednich tablicach.\n", wynik1, wynik2, wynik3);
    } else {
        printf("Wspolna liczba nie zostala znaleziona w tablicach.\n");
    }

    return 0;
}