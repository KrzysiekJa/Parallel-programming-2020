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

  zmienna_globalna++;

  int wynik;
  wynik=execv("./program",NULL);
  
  if(wynik==-1){
  	printf("Proces potomny nie wykonal programu\n");
  }

  return 0;
}



int main()
{

  void *stos;
  pid_t pid;
  int i; 
  
  stos = malloc( ROZMIAR_STOSU );
  
  if (stos == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }



  double t1 = czas_zegara(), t2 = czas_CPU();

  for(i=0;i<1000;i++){

    pid = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );

    waitpid(pid, NULL, __WCLONE);

  }


  t1 = czas_zegara() - t1;
  t2 = czas_CPU() - t2;
  
  printf("Czas wykonania %d operacji: \n\n",zmienna_globalna);
  printf("czas zegara: %lf\n", t1);
  printf("czas CPU:    %lf\n", t2);
  free( stos );
  
  return 0;
}
