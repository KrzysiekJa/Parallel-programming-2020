#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "mpi.h"

#define SCALAR double

#ifndef M_PI // standardy C99 i C11 nie wymagaja definiowania stalej M_PI
#define M_PI (3.14159265358979323846)
#endif





int main( int argc, char** argv ){ // program obliczania przybliĹźenia PI za pomoca wzoru Leibniza
                   // PI = 4 * ( 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + itd. )
  int rank, ranksent, size, source, dest, tag;
  int delta;
  int max_liczba_wyrazow;
  int size1, size2, Size;
  SCALAR suma_plus, suma_minus, result, final = 0.0;
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  
  
  
  if(size > 0){
	  
	  if(rank == 0){
  	   printf("Podaj maksymalna liczbe wyrazow do obliczenia przybliezenia PI:\n");
  	   scanf("%d", &max_liczba_wyrazow);
	  }
	  
	  MPI_Bcast(&max_liczba_wyrazow, 1, MPI_INT, 0, MPI_COMM_WORLD);
	  
	  if(max_liczba_wyrazow == 0){
	  	 MPI_Finalize();
		 exit(0);
	  }
	  
	  
	  
	  int i;
	  delta = (int) ceil(max_liczba_wyrazow/size);
	  for(i = delta * rank; i < delta * (rank+1); ++i){
   
	     int j = 1 + 4 * i;
   
		  suma_plus  += 1.0 / j;
		  suma_minus += 1.0 / (j+2.0);
	  }
	  result = suma_plus - suma_minus;
	  
	  MPI_Reduce(&result, &final, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	  
	  
	  if(rank == 0){
  	    printf("PI obliczone: \t\t\t%20.15lf\n", 4 * final);
  	    printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
	  } 
  }



  MPI_Finalize(); 
  
  return(0);
}

