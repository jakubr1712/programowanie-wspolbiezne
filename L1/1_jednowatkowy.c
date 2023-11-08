#include <stdio.h>

// Wersja sekwencyjna (jednowątkowa):

typedef struct {
    int indeks1;
    int indeks2;
    int indeks3;
} Indeksy;


Indeksy znajdz_wspolna(int tab1[], int tab2[], int tab3[], int n) {
    Indeksy indeksy = {-1, -1, -1}; // Inicjalizacja indeksów na -1 (nie znaleziono)
    int i, j, k;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                if (tab1[i] == tab2[j] && tab2[j] == tab3[k]) {
                    indeksy.indeks1 = i;
                    indeksy.indeks2 = j;
                    indeksy.indeks3 = k;
                    return indeksy;
                }
            }
        }
    }
    
    return indeksy; //  indeksy (wszystkie będą -1, jeśli wspólna liczba nie została znaleziona)
}

int main() {
    int tab1[] = {2, 4, 6, 8, 10};
    int tab2[] = {4, 6, 8, 10, 12};
    int tab3[] = {3, 4, 5, 6, 7};
    int rozmiar = 5;

    Indeksy indeksy = znajdz_wspolna(tab1, tab2, tab3, rozmiar);
    
    if (indeksy.indeks1 != -1) {
        printf("Wspolna liczba zostala znaleziona na indeksach %d, %d, %d w kazdej z tablic.\n", indeksy.indeks1, indeksy.indeks2, indeksy.indeks3);
    } else {
        printf("Wspolna liczba nie zostala znaleziona w tablicach.\n");
    }

    return 0;
}


// W wersji współbieżnej każda z tablic jest przeszukiwana w osobnym wątku, a wyniki są zbierane i porównywane w głównym wątku. Warto pamiętać, że wersja współbieżna może być szybsza tylko w przypadku dużej ilości danych lub długotrwałych operacji w tablicach. W innych przypadkach, wersja sekwencyjna może być prostsza i wystarczająca.




