#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>

#include "pomiar_czasu.h"

#define ROZMIAR 100000000 
#define LICZBA_W 2

pthread_mutex_t muteks; 
pthread_t watki[LICZBA_W];
double global_array_of_local_sums[LICZBA_W];


void *suma_w( void *arg_wsk);
void *suma_w_no_mutex( void *arg_wsk);

double *tab;
double suma=0; 





int main( int argc, char *argv[] ){

  int i; 
  double t1,t2,t3;
  int indeksy[LICZBA_W];
  
  for(i = 0; i < LICZBA_W; i++) indeksy[i]=i;

  tab = (double *) malloc(ROZMIAR*sizeof(double));
  for(i = 0; i < ROZMIAR; i++ ) tab[i] = ((double) i+1) / ROZMIAR; 



  printf("Obliczenia sekwencyjne\n");
  t1 = czas_zegara();
  for( i = 0; i < ROZMIAR; i++){ 
    suma += tab[i]; 
  }
  t1 = czas_zegara() - t1;
  printf("suma = %lf\n", suma);
  printf("Czas obliczen sekwencyjnych = %lf\n", t1);



  pthread_mutex_init( &muteks, NULL);

  printf("Poczatek tworzenia watkow\n");
  t1 = czas_zegara();

  suma = 0;
  for(i = 0; i < LICZBA_W; i++ ) 
    pthread_create( &watki[i], NULL, suma_w, (void *) &indeksy[i] );
   

  for(i = 0; i < LICZBA_W; i++ ) pthread_join( watki[i], NULL );

  t1 = czas_zegara() - t1;
  printf("suma = %lf\n", suma);
  printf("Czas obliczen %d wątków = %lf\n", LICZBA_W, t1);



  // version with array of local sums (to eliminate the mutex) 
  suma = 0;
  printf("Poczatek tworzenia watkow\n");
  t1 = czas_zegara();

  for(i = 0; i < LICZBA_W; i++ ) {
    global_array_of_local_sums[i]=0.0;
    pthread_create( &watki[i], NULL, suma_w_no_mutex, (void *) &indeksy[i] );
  }

  for(i = 0; i < LICZBA_W; i++ ) {
    pthread_join( watki[i], NULL );
    suma += global_array_of_local_sums[i];
  }

  t1 = czas_zegara() - t1;
  printf("suma = %lf\n", suma);
  printf("Czas obliczen %d wątków (no mutex) = %lf\n", LICZBA_W, t1);

  return 0;
}





void *suma_w( void *arg_wsk){

  int i, j, moj_id;
  double moja_suma = 0;
  moj_id = *( (int *) arg_wsk ); 
  j = ceil( (float)ROZMIAR/LICZBA_W );
  
  
  for( i = j*moj_id; i < j*(moj_id+1); i++){ 
    moja_suma += tab[i]; 
  }

  pthread_mutex_lock( &muteks );
  suma += moja_suma;
  pthread_mutex_unlock( &muteks );

  pthread_exit( (void *)0);
}




void *suma_w_no_mutex( void *arg_wsk){

  int i, j, moj_id;
  moj_id = *( (int *) arg_wsk ); 
  j = ceil( (float)ROZMIAR/LICZBA_W );
  
  
  for( i = j*moj_id; i < j*(moj_id+1); i++){ 
    // not optimal - false sharing of data in single cache line
    global_array_of_local_sums[moj_id] += tab[i]; 
  }

  pthread_exit( (void *)0);
}
