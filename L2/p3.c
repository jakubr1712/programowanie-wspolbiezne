/**************************************************************
Działa ustalona liczba wątków, które generują liczby losowe. Każdy wątek wykonuje jednakową liczbę prób, w których losowana jest kolejna liczba. 
Wątek główny ma obliczyć i wypisać wartość średnią liczb uzyskanych 
przez wątki w każdej kolejnej próbie.
***************************************************************************/



#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


#define ILOSC_PROB 1
#define liczba_watkow 3

float t[liczba_watkow];



void* p (void* k) { // funkcja watku (watek)
         long nr=(long)k;
         int l,i;
 
	 for (i=0;i<ILOSC_PROB;i++) {
      	 l = rand()%10;
         
         t[nr-1] = l;
          
         printf("watek %ld wylosowal %d \n",nr,l);fflush(stdout);
         
	 }
	 
         
return 0;     
}




int main(int arg, char **argv) {

pthread_t w[liczba_watkow];
long i=0,j;
float suma;


srand(time(0));

for (i=1;i<=liczba_watkow;i++)
    pthread_create(&w[i-1],0,p,(void*)i);
 		
 		


// oblicza wartości srednie

for (i=0;i<ILOSC_PROB;i++) {
  
suma=0;
for (j=0;j<liczba_watkow;j++) suma+= t[j];

printf("\nsrednia = %f\n",suma/liczba_watkow);
       
} 	





for (i=0;i<liczba_watkow;i++)
    pthread_join(w[i],0);

return 0;

}



