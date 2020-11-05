#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>


#define WYMIAR 1000
#define ROZMIAR WYMIAR*WYMIAR
double a[ROZMIAR],b[ROZMIAR],c[ROZMIAR];




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
	pthread_attr_t attr;
	void *wynik = NULL;



	//Watek przylaczalny
	
	printf("watek glowny: tworzenie watku potomnego nr 1\n");
	for(int i = 0; i < liczba_w; ++i){
		tab[i] = i;
	}

	for (int i = 0; i < liczba_w; ++i){
		pthread_create(&tid[i], NULL, zadanie_watku, &tab[i]);

	}
	
	sleep(2); // czas na uruchomienie watku

	printf("\twatek glowny: wyslanie sygnalu zabicia watku\n");


	for (int i = 0; i < liczba_w; ++i){
		pthread_join(tid[i], wynik);
		if (wynik == PTHREAD_CANCELED)
			printf("\twatek glowny: watek potomny zostal zabity\n");
		else
			printf("\twatek glowny: watek potomny NIE zostal zabity - blad\n");
	}
	
	pthread_detach(tid);
	pthread_exit(NULL);
}

