#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "mpi.h"


struct package {
	int integer;
	double fdouble;
	char character[100];
};





int main( int argc, char** argv ){ 
  
  int rank, size, source, dest, tag; 
  int size1, size2, size3, Size;
  MPI_Status status;
  struct package pack = {0, 15.01, "character"};
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &size1);
  MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &size2);
  MPI_Pack_size(100, MPI_CHAR, MPI_COMM_WORLD, &size3);
  Size = size1 + size2 + size3;
  char * pBuf = malloc(Size * sizeof(char));
  int position = 0;
  
  
  
  if(size > 1){
    
    if( rank != 0 && rank != (size - 1)){
		 dest = rank + 1, tag = 0, source = rank - 1;
      
      MPI_Recv(pBuf, Size, MPI_PACKED, source, tag, MPI_COMM_WORLD, &status);
		
		MPI_Unpack(pBuf, Size, &position, &pack.integer, 1, MPI_INT, MPI_COMM_WORLD);
		MPI_Unpack(pBuf, Size, &position, &pack.fdouble, 1, MPI_DOUBLE, MPI_COMM_WORLD);
		MPI_Unpack(pBuf, Size, &position, &pack.character, 100, MPI_CHAR, MPI_COMM_WORLD);
		
		printf("Proces o randze: %d odebral liczbe %d od procesu (%d), struktura: %d, %f, %s\n", 
			rank, pack.integer, source, pack.integer, pack.fdouble, pack.character);
		
		
      pack.integer = dest;
		position = 0;
		MPI_Pack(&pack.integer, 1, MPI_INT, pBuf, Size, &position, MPI_COMM_WORLD);
		MPI_Pack(&pack.fdouble, 1, MPI_DOUBLE, pBuf, Size, &position, MPI_COMM_WORLD);
		MPI_Pack(&pack.character, 100, MPI_CHAR, pBuf, Size, &position, MPI_COMM_WORLD);
		
      MPI_Send(pBuf, position, MPI_PACKED, dest, tag, MPI_COMM_WORLD);
		printf("Proces o randze: %d wyslal liczbe %d do procesu (%d), struktura: %d, %f, %s\n", 
			rank, pack.integer, dest, pack.integer, pack.fdouble, pack.character);
		
		
    }else if(rank == 0){
		dest = rank + 1, tag = 0, source = size - 1;
      pack.integer = dest;
		
		MPI_Pack(&pack.integer, 1, MPI_INT, pBuf, Size, &position, MPI_COMM_WORLD);
		MPI_Pack(&pack.fdouble, 1, MPI_DOUBLE, pBuf, Size, &position, MPI_COMM_WORLD);
		MPI_Pack(&pack.character, 100, MPI_CHAR, pBuf, Size, &position, MPI_COMM_WORLD);
		
      MPI_Send(pBuf, position, MPI_PACKED, dest, tag, MPI_COMM_WORLD);
		printf("Proces o randze: %d wyslal liczbe %d do procesu (%d), struktura: %d, %f, %s\n", 
			rank, pack.integer, dest, pack.integer, pack.fdouble, pack.character);
      
		
	 } if( rank == size - 1){
		 dest = 0, tag = 0, source = rank - 1;
      
      MPI_Recv(pBuf, Size, MPI_PACKED, source, tag, MPI_COMM_WORLD, &status);
		
		position = 0;
		MPI_Unpack(pBuf, Size, &position, &pack.integer, 1, MPI_INT, MPI_COMM_WORLD);
		MPI_Unpack(pBuf, Size, &position, &pack.fdouble, 1, MPI_DOUBLE, MPI_COMM_WORLD);
		MPI_Unpack(pBuf, Size, &position, &pack.character, 100, MPI_CHAR, MPI_COMM_WORLD);
		
		printf("Proces o randze: %d odebral liczbe %d od procesu (%d), struktura: %d, %f, %s\n", 
			rank, pack.integer, source, pack.integer, pack.fdouble, pack.character);
		
		
    }else {
	printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }



  free(pBuf);
  MPI_Finalize(); 
  
  return(0);
 }
}

