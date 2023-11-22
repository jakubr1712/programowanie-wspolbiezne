# p1.c

a) Zmienna semafor jest używana do synchronizacji dostępu do zmiennej globalnej liczba pomiędzy dwoma wątkami. sem_wait(&semafor); blokuje semafor, co oznacza, że żaden inny wątek nie może zablokować tego samego semafora, dopóki pierwszy wątek nie odblokuje go za pomocą sem_post(&semafor);. To zapewnia, że tylko jeden wątek na raz może modyfikować zmienną liczba.

b) Jeśli wartość początkową semafora ustalimy na 2, to dwa wątki będą mogły jednocześnie wejść do sekcji krytycznej. Może to prowadzić do sytuacji wyścigu, gdzie oba wątki próbują modyfikować zmienną liczba jednocześnie, co może prowadzić do nieprzewidywalnych wyników.

c) Jeśli operacje na semaforze będą wykomentowane, program będzie działał szybciej, ponieważ operacje na semaforze są kosztowne pod względem czasu. Jednakże, może to prowadzić do sytuacji wyścigu, gdzie oba wątki próbują modyfikować zmienną liczba jednocześnie, co może prowadzić do nieprzewidywalnych wyników. Aby poprawić program w taki sposób, aby działał jak najszybciej, można zastosować inne mechanizmy synchronizacji, takie jak pthread_mutex_t, które są mniej kosztowne pod względem czasu niż semafory.

# p2.c

Jeśli wątek zakończyłby działanie podczas wykonywania funkcji wypisz, mogłoby to prowadzić do różnych problemów.

Jeśli wątek zakończyłby działanie po zablokowaniu mutexu (pthread_mutex_lock(&blokada);), ale przed jego odblokowaniem (pthread_mutex_unlock(&blokada);), mutex pozostanie zablokowany. To oznacza, że żaden inny wątek nie będzie mógł zablokować tego mutexu, co prowadzi do tzw. "zawieszenia" (deadlock). W efekcie, inne wątki, które próbują zablokować ten mutex, będą czekać na zawsze.

Jeśli wątek zakończyłby działanie przed wywołaniem printf, nie zostanie wydrukowane żadne wyjście dla tego wątku.

Jeśli wątek zakończyłby działanie podczas wykonywania printf, wyjście może być niekompletne lub niezgodne z oczekiwaniami.

W praktyce, zakończenie wątku podczas wykonywania funkcji wypisz bez odpowiedniego czyszczenia (np. odblokowania mutexu) jest zazwyczaj uważane za błąd programowania. Dlatego ważne jest, aby zawsze upewnić się, że zasoby (takie jak mutexy) są odpowiednio zwalniane, nawet w przypadku błędów lub nieoczekiwanego zakończenia wątku.

# 5philosophers.c

Klasyczny problem synchronizacji wielowątkowej. Pięciu filozofów siedzi przy okrągłym stole, każdy z nich ma widelce po obu stronach i muszą podnieść oba widelce, aby zjeść. Kod zapewnia, że każdy filozof na przemian myśli i je, unikając jednocześnie zakleszczenia poprzez zapewnienie, że filozof je tylko wtedy, gdy oba widelce są dostępne.

# Kiedy używamy semafora, a kiedy mutexu?

Mutexy są używane, gdy chcemy chronić sekcję krytyczną, która nie może być jednocześnie wykonywana przez więcej niż jeden wątek. Semafor może być używany do kontroli dostępu do zasobu, który może być używany przez określoną liczbę wątków jednocześnie.

# Czym się różni semafor od mutexu?

Semafor jest zmienną, która jest używana do synchronizacji procesów i wątków. Może mieć wartość większą niż 1 i jest używany do kontroli dostępu do zasobu, który może być używany przez określoną liczbę wątków jednocześnie. Mutex to specjalny typ semafora, który może mieć tylko wartości 0 lub 1. Jest używany do zapewnienia wzajemnego wykluczenia w sekcjach krytycznych kodu.

# Jak synchronizujemy procesy, w których występują sekcje krytyczne?

Synchronizację procesów, w których występują sekcje krytyczne, można osiągnąć za pomocą różnych mechanizmów, takich jak semafory, mutexy, monitory czy warunki wyścigu. Te mechanizmy zapewniają, że tylko jeden proces lub wątek na raz może wykonywać sekcję krytyczną.

# Jak zdefiniować funkcje bezpieczne ze względu na wielowątkowość?

Funkcje bezpieczne ze względu na wielowątkowość są tak zaprojektowane, aby unikać problemów związanych z równoczesnym dostępem do współdzielonych zasobów. Można to osiągnąć poprzez użycie mechanizmów synchronizacji, takich jak mutexy lub semafory, które zapewniają, że tylko jeden wątek na raz może wykonywać sekcję krytyczną funkcji.
