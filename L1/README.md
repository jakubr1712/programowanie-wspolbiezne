# Wątki w języku C z biblioteką pthreads

Wątek (ang. "thread") w języku C to jednostka równoległości, która może wykonywać się niezależnie od innych wątków w ramach tego samego procesu. Wątki pozwalają na jednoczesne wykonywanie wielu operacji w programie, co może poprawić wydajność i reaktywność aplikacji. Wątek jest częścią procesu, ma dostęp do tych samych zasobów procesu i może komunikować się z innymi wątkami w obrębie tego samego procesu.

## Tworzenie wątku

Wątek tworzy się za pomocą funkcji `pthread_create`. Przykładowe wywołanie tej funkcji wygląda następująco:

```c
pthread_t thread_id;
int result = pthread_create(&thread_id, NULL, funkcja_watku, argumenty);
if (result != 0) {
   // Obsługa błędu
}
```

Gdzie `thread_id` to identyfikator nowo utworzonego wątku, `funkcja_watku` to wskaźnik do funkcji, która ma być uruchomiona w nowym wątku, a `argumenty` to parametry przekazywane do tej funkcji.

## Definiowanie funkcji wątku

Funkcja wątku powinna mieć następujący prototyp:

```c
void* funkcja_watku(void* arg);
```

Funkcja ta przyjmuje wskaźnik do `void` jako argument, co pozwala przekazywać różne typy danych. Funkcja zwraca wskaźnik do `void`, co umożliwia zwracanie wyników z wątku.

## Parametry funkcji `pthread_create`

- `thread`: Wskaźnik do zmiennej `pthread_t`, do której zostanie zapisany identyfikator nowo utworzonego wątku.
- `attr`: Atrybuty wątku (możesz przekazać NULL, aby użyć domyślnych atrybutów).
- `start_routine`: Wskaźnik do funkcji, która ma być uruchomiona w nowym wątku.
- `arg`: Argumenty przekazywane do funkcji wątku.

## Funkcja `pthread_join`

Funkcja `pthread_join` służy do oczekiwania na zakończenie wykonania innego wątku. Pozwala na synchronizację między wątkami, ponieważ główny wątek będzie czekać, aż inny wątek zakończy swoje działanie.

## Zmienne lokalne a zmienne globalne wątku

Wątki w obrębie tego samego procesu mają dostęp do tych samych zmiennych globalnych i statycznych. Natomiast zmienne lokalne wątków są prywatne dla każdego wątku i niezależne od siebie.

## Scenariusze programu wielowątkowego

Programy wielowątkowe mogą być używane do wielu celów, takich jak:

- Wykonywanie obliczeń równoległych.
- Obsługa wielu klientów w serwerze.
- Aktualizacja interfejsu użytkownika w czasie rzeczywistym.
- Optymalizacja wydajności aplikacji poprzez równoległe przetwarzanie zadań.

## Zmiana atrybutu wątku trwałego na ulotny

Atrybuty wątku można zmieniać za pomocą funkcji `pthread_attr_setdetachstate`. Aby zmienić wątek trwały na ulotny, można ustawić atrybut `PTHREAD_CREATE_DETACHED`, co oznacza, że wątek nie będzie czekał na zakończenie.

## Różnica między wątkiem trwałym a ulotnym

- Wątek trwały: Wątek trwały oznacza, że po zakończeniu jego działania, zasoby takie jak identyfikator wątku nie zostaną zwolnione automatycznie. Musisz wywołać `pthread_join`, aby zwolnić te zasoby i uniknąć wycieku pamięci.

- Wątek ulotny: Wątek ulotny (detached) oznacza, że po zakończeniu działania wątku, jego zasoby zostaną zwolnione automatycznie, co oznacza, że nie musisz wywoływać `pthread_join`. Jednak nie możesz oczekiwać na zakończenie działania wątku ulotnego ani uzyskać jego wyniku.
