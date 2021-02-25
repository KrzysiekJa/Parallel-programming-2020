#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "mpi.h"




int main( int argc, char** argv ){ 
  
  int rank, ranksent, size, source, dest, tag; 
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  
  
  
  if(size > 1){
    
    if( rank != 0 && rank != (size - 1)){
		dest = rank + 1, tag = 0, source = rank - 1;
      
      MPI_Recv(&ranksent, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
		printf("Proces o randze: %d odebral liczbe %d od procesu (%d)\n", rank, ranksent, source);
		ranksent++;
      MPI_Send(&ranksent, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
		printf("Proces o randze: %d wyslal liczbe %d do procesu (%d)\n", rank, ranksent, dest);
		
		
    }else if(rank == 0){
		dest = rank + 1, tag = 0, source = size - 1;
      
      MPI_Send(&ranksent, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
		printf("Proces o randze: %d odebral liczbe %d od procesu (%d)\n", rank, ranksent, dest);
		ranksent++;
      MPI_Recv(&ranksent, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
		printf("Proces o randze: %d wyslal liczbe %d do procesu (%d)\n", rank, ranksent, source);
	 
	 
	 } else if(rank == size - 1){
      dest = 0, tag = 0, source = rank - 1;
		
      MPI_Recv(&ranksent, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
		printf("Proces o randze: %d odebral liczbe %d od procesu (%d)\n", rank, ranksent, source);
		ranksent++;
      MPI_Send(&ranksent, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
		printf("Proces o randze: %d wyslal liczbe %d do procesu (%d)\n", rank, ranksent, dest);
      
    } else {
	printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  
  
  MPI_Finalize();
  
  return(0);
 }
}

