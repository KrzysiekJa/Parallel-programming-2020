#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <time.h>
#include "../pomiar_czasu/pomiar_czasu.h"


int zmienna_globalna=0;




int main(){
  
  int pid, wynik, i;
  
  
  double t1 = czas_zegara(), t2 = czas_CPU();
  
  for(i=0;i<1000;i++){
    
	  pid = fork(); 			
    
	  if(pid==0){ 			
      
      zmienna_globalna++;
      
      wynik = execv("./program",NULL);
	  
      if(wynik==-1)
		  printf("Proces potomny nie wykonal programu\n");

      exit(0);
      
  	  } else {					
      
      wait(NULL);
      
  	  }
  }
  
  t1 = czas_zegara() - t1;
  t2 = czas_CPU() - t2;
  
  printf("Czas wykonania %d operacji: \n\n",zmienna_globalna);
  printf("czas zegara: %lf\n", t1);
  printf("czas CPU:    %lf\n", t2);
  
  return 0;
}

  
