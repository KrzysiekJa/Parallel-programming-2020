#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "czytelnia.h"

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;




int my_read_lock_lock(czytelnia_t * czytelnia_p){
	pthread_rwlock_wrlock(&rwlock);
	
	++czytelnia_p -> liczba_czyt;
	printf("\tCzytelnikow: %d, pisarzy: %d\n", czytelnia_p->liczba_czyt, czytelnia_p->liczba_pisz);
}


int my_read_lock_unlock(czytelnia_t * czytelnia_p){
	--czytelnia_p -> liczba_czyt;
	printf("\tCzytelnikow: %d, pisarzy: %d\n", czytelnia_p->liczba_czyt, czytelnia_p->liczba_pisz);
	
	pthread_rwlock_unlock(&rwlock);
}


int my_write_lock_lock(czytelnia_t * czytelnia_p){
	pthread_rwlock_wrlock(&rwlock);
	
	++czytelnia_p -> liczba_pisz;
	printf("\tCzytelnikow: %d, pisarzy: %d\n", czytelnia_p->liczba_czyt, czytelnia_p->liczba_pisz);
}


int my_write_lock_unlock(czytelnia_t * czytelnia_p){
	--czytelnia_p -> liczba_pisz;
	printf("\tCzytelnikow: %d, pisarzy: %d\n", czytelnia_p->liczba_czyt, czytelnia_p->liczba_pisz);
	
	pthread_rwlock_unlock(&rwlock);
}



void inicjuj(czytelnia_t * czytelnia_p){
	czytelnia_p -> liczba_pisz = 0;
	czytelnia_p -> liczba_czyt = 0;
}

void czytam(czytelnia_t * czytelnia_p){
    usleep(rand()%1000000);
}

void pisze(czytelnia_t * czytelnia_p){
    usleep(rand()%1000000);
}


