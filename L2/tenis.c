#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 4 

sem_t courtSemaphore;
pthread_mutex_t mutex;
int players[NUM_THREADS] = {0};
int match_count = 0;

void *player(void *thread_id) {
    int player_id = *((int *)thread_id);

    while (1) {
        printf("Gracz %d czeka na partnera.\n", player_id);
        pthread_mutex_lock(&mutex);
        if (players[0] == 0) {
            players[0] = player_id;
            pthread_mutex_unlock(&mutex);
        } else {
            int partner_id = players[0];
            players[0] = 0;
            pthread_mutex_unlock(&mutex);

            sem_wait(&courtSemaphore);

            printf("Nowy mecz!\n");
            printf("Gracz %d gra z Graczem %d.\n", player_id, partner_id);
            usleep(rand() % 2000000); // Symulacja trwania meczu (0-2 sekundy)

            printf("Gracz %d dziękuje Graczowi %d.\n", player_id, partner_id);

            sem_post(&courtSemaphore);
            break;
        }
    }

    // Sekcja lokalna
    printf("Gracz %d zajmuje się swoimi sprawami.\n", player_id);
    usleep(rand() % 1000000); // Symulacja zajmowania się sprawami (0-1 sekundy)

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    sem_init(&courtSemaphore, 0, 2);
    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        int *player_id = (int *)malloc(sizeof(int));
        *player_id = i + 1;
        pthread_create(&threads[i], NULL, player, (void *)player_id);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&courtSemaphore);
    pthread_mutex_destroy(&mutex);

    return 0;
}
