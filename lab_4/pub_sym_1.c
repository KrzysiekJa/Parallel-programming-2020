#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

void * watek_klient (void * arg);

pthread_mutex_t mutex_kf, mutex_kr;
int l_kl, l_kf;




int main(void){

  pthread_t *tab_klient;
  int *tab_klient_id;
  int l_kr = 1, i;
  

  printf("\nLiczba klientow: "); scanf("%d", &l_kl);

  printf("\nLiczba kufli: "); scanf("%d", &l_kf);



  tab_klient = (pthread_t *) malloc(l_kl * sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl * sizeof(int));
  for(i = 0; i < l_kl; i++) tab_klient_id[i] = i;


  printf("\nOtwieramy pub (simple)!\n");
  printf("\nLiczba wolnych kufli %d\n", l_kf); 


  
  pthread_mutex_init(&mutex_kf, NULL);
  pthread_mutex_init(&mutex_kr, NULL);
  
  for(i = 0; i < l_kl; i++){
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]); 
  }
  
  for(i = 0; i < l_kl; i++){
    pthread_join(tab_klient[i], NULL);
  }
  
  printf("\nZamykamy pub!\n");
  printf("\nLiczba kufli na koniec: %d\n", l_kf);


  pthread_exit(NULL);
  return 0;
}




void * watek_klient (void * arg_wsk){

  int moj_id = * ((int *) arg_wsk);

  int i, j = 0, kufel = 0;
  int ile_musze_wypic = 2;

  printf("Klient %d, wchodzi do pubu\n", moj_id); 
  
  
  
  for(i = 0; i < ile_musze_wypic; i++){
	
	do{
		pthread_mutex_lock(&mutex_kf);
		if(l_kf > 0){
			printf("Sprawdzenie dostepnosci kufla.\n");
			--l_kf;
			kufel = 1;
			printf("Kufel zabrany.\n");
		}
		pthread_mutex_unlock(&mutex_kf);
		
		if(kufel == 0){
			printf("Jem orzeszki, klient nr %d.\n", moj_id);
			usleep(300);
		}
	}while(kufel == 0);


    printf("Klient %d, wybieram kufel\n", moj_id);     
	
	pthread_mutex_lock(&mutex_kr);
    printf("Klient %d, nalewam z kranu %d\n", moj_id, j); 
    usleep(300);
	pthread_mutex_unlock(&mutex_kr);
    
    printf("Klient %d, pije\n", moj_id);
	
    nanosleep((struct timespec[]){{0, 500000000L}}, NULL);
    
    printf("Klient %d, odkladam kufel\n", moj_id);
	
	
	pthread_mutex_lock(&mutex_kf);
	kufel = 0;
	++l_kf;
	printf("Kufel oddany.\n");
	pthread_mutex_unlock(&mutex_kf);
  }
  
  
  printf("Klient %d, wychodzi z pubu\n", moj_id); 
    
  return(NULL);
} 
