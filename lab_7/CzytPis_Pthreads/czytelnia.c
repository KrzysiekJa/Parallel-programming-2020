#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "czytelnia.h"







int my_read_lock_lock(czytelnia_t * czytelnia_p){
	pthread_mutex_lock(&czytelnia_p -> mutex);
	
	if(czytelnia_p -> liczba_pisz > 0 || czytelnia_p -> liczba_ocz_pisz > 0){
		(czytelnia_p -> liczba_ocz_czyt)++;
		pthread_cond_wait(&czytelnia_p -> czytelnicy, &czytelnia_p -> mutex);
		(czytelnia_p -> liczba_ocz_czyt)--;
	}
	
	(czytelnia_p -> liczba_czyt)++;
	printf("\tPiszarze: %d, czytelnicy: %d\n", czytelnia_p -> liczba_pisz, czytelnia_p -> liczba_czyt);
	
	//pthread_cond_signal(&czytelnia_p -> czytelnicy);
	
	pthread_mutex_unlock(&czytelnia_p -> mutex);
}


int my_read_lock_unlock(czytelnia_t * czytelnia_p){
	pthread_mutex_lock(&czytelnia_p -> mutex);
	
	(czytelnia_p -> liczba_czyt)--;
	printf("\tPiszarze: %d, czytelnicy: %d\n", czytelnia_p -> liczba_pisz, czytelnia_p -> liczba_czyt);
	
	if(czytelnia_p -> liczba_czyt == 0){
		pthread_cond_signal(&czytelnia_p -> pisarze);
	}
	
	pthread_mutex_unlock(&czytelnia_p -> mutex);
}


int my_write_lock_lock(czytelnia_t * czytelnia_p){
	pthread_mutex_lock(&czytelnia_p -> mutex);
		
	if((czytelnia_p -> liczba_czyt) + (czytelnia_p -> liczba_pisz) > 0){
		(czytelnia_p -> liczba_ocz_pisz)++;
		pthread_cond_wait(&czytelnia_p -> pisarze, &czytelnia_p -> mutex);
		(czytelnia_p -> liczba_ocz_pisz)--;
	}
	
	(czytelnia_p -> liczba_pisz)++;	
	printf("\tPiszarze: %d, czytelnicy: %d\n", czytelnia_p -> liczba_pisz, czytelnia_p -> liczba_czyt);
	pthread_mutex_unlock(&czytelnia_p -> mutex);
}


int my_write_lock_unlock(czytelnia_t * czytelnia_p){
	pthread_mutex_lock(&czytelnia_p -> mutex);
	
	(czytelnia_p -> liczba_pisz)--;
	printf("\tPiszarze: %d, czytelnicy: %d\n", czytelnia_p -> liczba_pisz, czytelnia_p -> liczba_czyt);
	
	
	if(czytelnia_p -> liczba_ocz_czyt == 1){
		pthread_cond_signal(&czytelnia_p -> czytelnicy);
	}else{
		pthread_cond_signal(&czytelnia_p -> pisarze);
	}
	
	pthread_mutex_unlock(&czytelnia_p ->  mutex);
}



void inicjuj(czytelnia_t * czytelnia_p){
	
	czytelnia_p -> liczba_czyt = 0;
	czytelnia_p -> liczba_pisz = 0;
	czytelnia_p -> liczba_ocz_czyt = 0;
	czytelnia_p -> liczba_ocz_pisz = 0;
	
	pthread_mutex_init(&czytelnia_p -> mutex, NULL);
	pthread_cond_init(&czytelnia_p -> czytelnicy, NULL);
	pthread_cond_init(&czytelnia_p -> pisarze, NULL);
}


void czytam(czytelnia_t * czytelnia_p){
	pthread_mutex_lock(&czytelnia_p -> mutex);
	usleep(rand()%1000000);
	pthread_mutex_unlock(&czytelnia_p ->  mutex);
}


void pisze(czytelnia_t * czytelnia_p){
	 pthread_mutex_lock(&czytelnia_p -> mutex);
    usleep(rand()%1000000);
	 pthread_mutex_unlock(&czytelnia_p ->  mutex);
}


