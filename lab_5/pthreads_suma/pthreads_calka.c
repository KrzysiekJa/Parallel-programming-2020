#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include "pomiar_czasu.h"

double funkcja ( double x );
double funkcja ( double x ){ return( sin(x) ); }
double calka_sekw(double a, double b, double dx, int N);
double calka_zrownoleglenie_petli(double a, double b, double dx, int N);
double calka_dekompozycja_obszaru(double a, double b, double dx, int N);

#define LICZBA_W_MAX 1000
#define l_w_global 2

struct box{
	double a, b, dx;
	int id, N;
};






int main( int argc, char *argv[] ){

  int i; 
  double t1,t2,t3;
  double a, b, dx, calka;

  printf("\nProgram obliczania calki z funkcji (sinus) metoda trapezow.\n");

  a = 0.0;
  b = M_PI;


  printf("\nPodaj wysokosc pojedynczego trapezu:  ");
  scanf("%lf", &dx);

  int N = ceil((b-a)/dx);
  double dx_adjust = (b-a)/N;

  printf("Obliczona liczba trapezow: N = %d\n", N);



  printf("\nPoczatek obliczen sekwencyjnych\n");
  printf("a %lf, b %lf, n %d, dx %.12lf (dx_adjust %.12lf)\n", a, b, N, dx, dx_adjust);
  t1 = czas_zegara();

  calka = calka_sekw(a, b, dx_adjust, N);

  t1 = czas_zegara() - t1;
  printf("\nKoniec obliczen sekwencyjnych\n");
  printf("\tCzas wykonania %lf. \tObliczona calka = %.15lf\n", t1, calka);



  printf("\nPoczatek obliczen rownoleglych (zrownoleglenie petli)\n");
  printf("a %lf, b %lf, n %d, dx %.12lf (dx_adjust %.12lf)\n", a, b, N, dx, dx_adjust);
  t1 = czas_zegara();

  calka = calka_zrownoleglenie_petli(a, b, dx_adjust, N);

  t1 = czas_zegara() - t1;
  printf("\nKoniec obliczen  rownoleglych (zrownoleglenie petli) \n");
  printf("\tCzas wykonania %lf. \tObliczona calka = %.15lf\n", t1, calka);



  printf("\nPoczatek obliczen rownoleglych (dekompozycja obszaru)\n");
  printf("a %lf, b %lf, n %d, dx %.12lf (dx_adjust %.12lf)\n", a, b, N, dx, dx_adjust);
  t1 = czas_zegara();

  calka = calka_dekompozycja_obszaru(a, b, dx_adjust, N);

  t1 = czas_zegara() - t1;
  printf("\nKoniec obliczen  rownoleglych (dekompozycja obszaru) \n");
  printf("\tCzas wykonania %lf. \tObliczona calka = %.15lf\n", t1, calka);

  return 0;
}






double calka_sekw(double a, double b, double dx, int N){

  int i;
  double calka = 0.0;
  for(i = 0; i < N; i++){

    double x1 = a + i*dx;
    calka += 0.5*dx*(funkcja(x1)+funkcja(x1+dx));
  }

  return(calka);
}


static double calka_global = 0.0;
static double a_global;
static double b_global;
static double dx_global;
static int    N_global;
double global_array[l_w_global];
pthread_mutex_t muteks;






void* calka_fragment_petli_w(void* arg_wsk);

double calka_zrownoleglenie_petli(double a, double b, double dx, int N){

  int i, l_w = l_w_global;
  a_global = a; b_global = b; dx_global = dx; N_global = N;
  
  pthread_t watki[l_w];
  int indeksy[l_w]; 
  for(i = 0; i < l_w; i++) indeksy[i]=i;


  for(i = 0; i < l_w; i++ ) {
    pthread_create( &watki[i], NULL, calka_fragment_petli_w, (void *) &indeksy[i] );
  }
  
  for(i = 0; i < l_w; i++ ) {
    pthread_join( watki[i], NULL );
  }

  return(calka_global);
}




void* calka_fragment_petli_w(void* arg_wsk){

  int my_id  = (*(int *) arg_wsk);

  double a = a_global;
  double dx = dx_global; 
  int N = N_global; 
  int j = ceil((float)N / l_w_global);
  
  int my_start  = j * my_id;
  int my_end    = j * (my_id + 1);
  int my_stride = 1;


  printf("\nWatek %d\n", my_id);
  printf("my_start %d, my_end %d, my_stride %d\n", my_start, my_end, my_stride);


  int i;
  double calka = 0.0;
  for(i = my_start; i < my_end; i += my_stride){

    double x1 = a + i * dx;
    calka += 0.5 * dx * (funkcja(x1) + funkcja(x1+dx));

  }
  
  pthread_mutex_lock( &muteks );
  calka_global += calka;
  pthread_mutex_unlock( &muteks );

}




void* calka_podobszar_w(void* arg_wsk);

double calka_dekompozycja_obszaru(double a, double b, double dx, int N){

  int l_w = l_w_global;
  int i;
  double calka_suma_local = 0.0;
  pthread_t watki[l_w];
  struct box info_box[l_w];
  
  for(i = 0; i < l_w; i++){
	  info_box[i].b  = b;
	  info_box[i].dx = dx;
	  info_box[i].N  = ceil((float) N / l_w);
	  info_box[i].a  = a + i * dx;
	  info_box[i].id = i;
  }

  
  for(i = 0; i < l_w; i++ ) {
    pthread_create( &watki[i], NULL, calka_podobszar_w, (void *) &info_box[i]);
  }
  
  for(i = 0; i < l_w; i++ ) {
    pthread_join( watki[i], NULL);
    calka_suma_local += global_array[i];
  }
  
  return(calka_suma_local);
}




void* calka_podobszar_w(void* arg_wsk){

  struct box info = (*(struct box *) arg_wsk);
  double a_local  = info.a;
  double dx_local = info.dx;
  int N_local = info.N;

  int my_id = info.id;
  printf("\nWatek %d\n", my_id);
  printf("a_local %lf, dx_local %lf, n_local %d\n", a_local, dx_local, N_local);


  int i;
  double calka = 0.0;
  for(i = 0; i < N_local; i++){

    double x1 = a_local + i * dx_local;
    calka += 0.5 * dx_local * (funkcja(x1) + funkcja(x1+dx_local));
  }

  global_array[my_id] = calka;
}