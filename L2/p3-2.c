#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


#define ILOSC_PROB 3
#define liczba_watkow 3

float t[liczba_watkow];
sem_t sem;


void* p (void* k) { // funkcja watku (watek)
         long nr=(long)k;
         int l,i;
 
	 for (i=0;i<ILOSC_PROB;i++) {
      	 l = rand()%100;
         
         t[nr-1] = l;
          
         printf("watek %ld wylosowal %d \n",nr,l);fflush(stdout);
         
	 }

	  sem_post(&sem);
         
return 0;     
}




int main(int arg, char **argv) {

pthread_t w[liczba_watkow];
long i=0,j;
float suma;

sem_init(&sem, 0, 1);

srand(time(0));


for (i=1;i<=liczba_watkow;i++)
{
    pthread_create(&w[i-1],0,p,(void*)i);
    sem_wait(&sem);

}


for (i=0;i<liczba_watkow;i++)
    pthread_join(w[i],0);

for (i=0;i<ILOSC_PROB;i++) {
  
suma=0;
for (j=0;j<liczba_watkow;j++) suma+= t[j];

printf("\nsrednia = %f\n",suma/liczba_watkow);
       
} 	


sem_destroy(&sem);

return 0;

}



