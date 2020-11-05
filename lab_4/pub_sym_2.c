#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<pthread.h>


struct struktura_t { 
  int l_kf;
  pthread_mutex_t *tab_kuf;
  int l_kr;
  pthread_mutex_t *tab_kran;
};

struct struktura_t pub_wsk;
pthread_mutex_t mutex_kf;
int l_kl, l_kf, l_kr;

void * watek_klient (void * arg);




int main(void){
  pthread_t *tab_klient;
  int *tab_klient_id;
  l_kr = 5;
  int i;


  printf("\nLiczba klientow: "); scanf("%d", &l_kl);

  printf("\nLiczba kufli: "); scanf("%d", &l_kf);
  pub_wsk.l_kf = l_kf;

  printf("\nLiczba kranow: "); scanf("%d", &l_kr);
  pub_wsk.l_kr = l_kr;



  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++) tab_klient_id[i]=i;

  pub_wsk.tab_kuf = (pthread_mutex_t *) malloc(l_kf*sizeof(pthread_mutex_t));
  for(i=0;i<l_kf;i++) pthread_mutex_init(&pub_wsk.tab_kuf[i], NULL);

  pub_wsk.tab_kran = (pthread_mutex_t *) malloc(l_kr*sizeof(pthread_mutex_t));
  for(i=0;i<l_kr;i++) pthread_mutex_init(&pub_wsk.tab_kran[i], NULL);


  printf("\nOtwieramy pub (simple)!\n");
  printf("\nLiczba wolnych kufli %d\n", l_kf);



  for(i = 0;i < l_kl; i++){
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]); 
  }
  
  for(i = 0;i < l_kl; i++){
    pthread_join( tab_klient[i], NULL);
  }
  
  printf("\nZamykamy pub!\n");
  printf("\nLiczba kufli na koniec: %d\n", l_kf);
  printf("\nLiczba kranów na koniec: %d\n", l_kr);


  pthread_exit(NULL);
  return 0;
}




void * watek_klient (void * arg_wsk){

  int moj_id = * ((int *)arg_wsk);
  int i, j, kran = 0, kufel = 0, result = 0;
  int ile_musze_wypic = 2;

  printf("\nKlient %d, wchodzi do pubu\n", moj_id); 
  
  

  for(i = 0; i < ile_musze_wypic; i++){

    printf("\nKlient %d, wybieram kufel\n", moj_id); 

	
	do{
		pthread_mutex_lock(&mutex_kf);
		if(l_kf > 0){
			printf("\nSprawdzenie dostepnosci kufla.\n");
			--l_kf;
			kufel = 1;
			printf("\nKufel zabrany.\n");
		}
		pthread_mutex_unlock(&mutex_kf);
		
		if(kufel == 0){
			//printf("\nJem orzeszki, klient nr %d.\n", moj_id);
			usleep(300);
		}
	}while(kufel == 0);



    // printf("\nKlient %d, wybralem kufel %d\n", moj_id, kufel);
	
    printf("\nKlient %d, wybieram kran\n", moj_id); 
	
	j = 0;
	while(pthread_mutex_trylock(&pub_wsk.tab_kran[j]) != 0){
		++j;
		if(j == l_kr){
			j = 0;
		}
		
		//printf("\nJem orzeszki, klient nr %d.\n", moj_id);
		usleep(300);
	}
	kran = j;
	
	
    printf("\nKlient %d, nalewam z kranu %d\n", moj_id, kran);
    sleep(1);

    
    if(kran==0)  printf("\nKlient %d, pije piwo Guinness\n", moj_id); 
    else if(kran==1)  printf("\nKlient %d, pije piwo Zywiec\n", moj_id); 
    else if(kran==2)  printf("\nKlient %d, pije piwo Heineken\n", moj_id); 
    else if(kran==3)  printf("\nKlient %d, pije piwo Okocim\n", moj_id); 
    else if(kran==4)  printf("\nKlient %d, pije piwo Karlsberg\n", moj_id); 
	
	pthread_mutex_unlock(&pub_wsk.tab_kran[j]);



    sleep(1);

	pthread_mutex_lock(&pub_wsk.tab_kuf[0]);
	kufel = 0;
	result = 0;
	++l_kf;
	printf("\nKufel oddany.\n");
	pthread_mutex_unlock(&pub_wsk.tab_kuf[0]);

    printf("\nKlient %d, odkladam kufel %d\n", moj_id, kufel); 

  }

  return(NULL);
} 