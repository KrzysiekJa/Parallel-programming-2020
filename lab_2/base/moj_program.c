#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <time.h>
#include "../pomiar_czasu/pomiar_czasu.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64



int funkcja_watku( void* argument )
{
  int lokalna = *((int *) argument);
  

  for(int i = 0; i < 10000; ++i){
	  zmienna_globalna++;
	  lokalna++;
  }


  printf("Globalna: %d\n\n", zmienna_globalna);
  printf("Lokalna: %d\n\n", lokalna);
  
  return 0;
}



int main()
{

  void *stos1, *stos2;
  pid_t pid1, pid2;
  int i;

  
  stos1 = malloc( ROZMIAR_STOSU );
  stos2 = malloc( ROZMIAR_STOSU );
  
  if (stos1 == 0 || stos2 == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }


  pid1 = clone( &funkcja_watku, (void *) stos1+ROZMIAR_STOSU, 
	 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM,  &i);
	 
  pid2 = clone( &funkcja_watku, (void *) stos2+ROZMIAR_STOSU, 
   	 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM,  &i);


  waitpid(pid1, NULL, __WCLONE);
  waitpid(pid2, NULL, __WCLONE);



  free( stos1 );
  free( stos2 );
  
  return 0;
}
