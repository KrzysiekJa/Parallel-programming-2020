#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

int zmienna_wspolna=0;

#define WYMIAR 1000
#define ROZMIAR WYMIAR*WYMIAR
double a[ROZMIAR],b[ROZMIAR],c[ROZMIAR];



typedef struct{
	int a;
	int b;
	int c;
} prism;




void * pthread_tast (void * arg_wsk)
{
	prism * wsk = (prism *) arg_wsk;
	
	printf("parametry: %d %d %d\n", wsk->a, wsk->b, wsk->c);
	
	wsk->a += 1;
	wsk->b += 2;
	wsk->c -= 1;
	
	printf("parametry: %d %d %d\n", wsk->a, wsk->b, wsk->c);
	
	return(NULL);
}



int main()
{
	pthread_t tid[2];
	pthread_attr_t attr;
	void *wynik = NULL;
	prism prism;
	prism.a = 1;
	prism.b = 1;
	prism.c = 1;



	printf("watek glowny: tworzenie watku potomnego \n");
	printf("parametry: %d %d %d\n", prism.a, prism.b, prism.c);
	
	pthread_create(&tid[0], NULL, pthread_tast, (void *) & prism);
	pthread_create(&tid[1], NULL, pthread_tast, (void *) & prism);
	
	
	
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	
	printf("parametry: %d %d %d\n", prism.a, prism.b, prism.c);
	
	pthread_detach(tid);
	pthread_exit(NULL);
}

