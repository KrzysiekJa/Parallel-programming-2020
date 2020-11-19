#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>




void * zadanie_watku (void * arg_wsk)
{
	printf("\tSystemowy ID: %d, indentyfikator: %d\n", (int) pthread_self(), *((int *) arg_wsk));
	
	return(NULL);
}





int main()
{
	int liczba_w = 10;
	int tab[liczba_w];
	pthread_t tid[liczba_w];
	void *wynik = NULL;



	
	for(int i = 0; i < liczba_w; ++i){
		tab[i] = i;
	}

	for (int i = 0; i < liczba_w; ++i){
		pthread_create(&tid[i], NULL, zadanie_watku, &tab[i]);

	}
	
	sleep(2);

	for (int i = 0; i < liczba_w; ++i){
		pthread_join(tid[i], wynik);
	}
	
	pthread_exit(NULL);
}

