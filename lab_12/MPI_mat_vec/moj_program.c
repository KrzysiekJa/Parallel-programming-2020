#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"
#include "pomiar_czasu.h"

#define WYMIAR 6400 
#define ROZMIAR 40960000 





void mat_vec(double* a, double* x, double* y, int n, int nt);



int main ( int argc, char** argv )
{
  static double x[WYMIAR],y[WYMIAR],z[WYMIAR];
  double *a;
  double t1;
  int n,nt,i,j;
  const int ione=1;
  const double done=1.0;
  const double dzero=0.0;

  int rank, size, tag=0; 
  int n_wier, n_wier_last;
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  
  
  
  n = WYMIAR;
  
  if(rank == 0){  
    
    a = (double *) malloc((ROZMIAR+1) * sizeof(double));
    
    for(i = 0; i < ROZMIAR; i++) a[i] = 1.0 *i;
    for(i = 0; i < WYMIAR; i++) x[i] = 1.0 *(WYMIAR-i);
    
    
    nt = 1;
    
    printf("poczatek (wykonanie sekwencyjne)\n");
    
    inicjuj_czas();
    t1 = MPI_Wtime();
    mat_vec(a,x,y,n,nt);
    t1 = MPI_Wtime() - t1;
    drukuj_czas();
    
    printf("\tczas wykonania (zaburzony przez MPI?): %lf, Gflop/s: %lf, GB/s> %lf\n", t1,  2.0e-9 * ROZMIAR /t1,  (1.0 + 1.0/n)* 8.0e-9 * ROZMIAR /t1);

  }
  
  
  
  if(size > 1){
    
    int iter;
    /************** || *******************/
    
    for(i = 0; i < WYMIAR; i++) z[i] = 0.0;
    MPI_Bcast(&nt, 1, MPI_INT, 0, MPI_COMM_WORLD );
    
    
    // row partition
    n_wier = ceil(WYMIAR / size);
    n_wier_last = WYMIAR - n_wier*(size-1);
    
    if(n_wier != n_wier_last){
      printf("This version does not work with WYMIAR not a multiple of size!\n");
      MPI_Finalize(); 
      exit(0);
      
    }
    
	 
	 
    if(rank > 0){
    
      for(i = 0; i < WYMIAR; i++) x[i] = 0.0;
      
		a = (double *) malloc(WYMIAR*n_wier * sizeof(double));
    }
    
	 
	 /* Group communication */
	 MPI_Scatter(a, n_wier*WYMIAR, MPI_DOUBLE, a, n_wier*WYMIAR, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	 MPI_Scatter(x, n_wier, MPI_DOUBLE, &x[rank*n_wier], n_wier, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	 
	 
    if(rank == 0) {
      inicjuj_czas();
      t1 = MPI_Wtime();
    }
    
    
    MPI_Allgather(&x[rank*n_wier], n_wier, MPI_DOUBLE, x, n_wier, MPI_DOUBLE, MPI_COMM_WORLD);
    
    
	 
    for(i = 0; i < n_wier; i++){
      
      double t = 0.0;
      int ni = n*i;
      
      for(j = 0; j < n; j++){
			t += a[ni+j] * x[j];
      }
      z[i] = t;
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    
   
	
	
    if(rank == 0) {
      t1 = MPI_Wtime() - t1;
      printf("Werja rownolegla MPI\n");
      drukuj_czas();
      printf("\tczas wykonania: %lf, Gflop/s: %lf, GB/s> %lf\n", t1, 2.0e-9 * ROZMIAR /t1, (1.0 + 1.0/n)* 8.0e-9 * ROZMIAR /t1);
      
    }
	 
    
    if(rank > 0){
      
      MPI_Send( z, n_wier, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD );
      
    } else {
      
      for(i = 1; i < size; i++){
			MPI_Recv( &z[i*n_wier], n_wier, MPI_DOUBLE, i, tag, MPI_COMM_WORLD, &status  );
	
      }
      
      for(i = 0; i < WYMIAR; i++){
			if(fabs(y[i]-z[i]) > 1.e-9 * z[i]) {
	  			printf("Blad! i=%d, y[i]=%lf, z[i]=%lf\n", i, y[i], z[i]);
			}
      }
      
    }
  }
  
  MPI_Finalize(); 
  
  
  return(0);
}
