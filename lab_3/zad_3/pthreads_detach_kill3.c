#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>




typedef struct{
	int a;
	int b;
	int c;
} prism;




void * pthread_tast (void * arg_wsk)
{
	prism * wsk = (prism *) arg_wsk;
	int zm1, zm2, zm3;
	
	printf("parametry: %d %d %d\n", wsk->a, wsk->b, wsk->c);
	
	zm1 = wsk->a;
	zm2 = wsk->b;
	zm3 = wsk->c;
	
	zm1 += 1;
	zm2 += 2;
	zm3 -= 1;
	
	printf("parametry: %d %d %d\n", zm1, zm2, zm3);
	
	wsk->a = zm1;
	wsk->b = zm2;
	wsk->c = zm3;
	
	printf("parametry: %d %d %d\n", wsk->a, wsk->b, wsk->c);
	
	return(NULL);
}



int main()
{
	pthread_t tid[2];
	void *wynik = NULL;
	prism prism;
	prism.a = 1;
	prism.b = 1;
	prism.c = 1;



	printf("watek glowny: tworzenie watkow potomnych \n");
	printf("parametry: %d %d %d\n", prism.a, prism.b, prism.c);
	
	pthread_create(&tid[0], NULL, pthread_tast, (void *) & prism);
	pthread_create(&tid[1], NULL, pthread_tast, (void *) & prism);
	
	
	
	pthread_join(tid[0], wynik);
	pthread_join(tid[1], wynik);
	
	printf("parametry: %d %d %d\n", prism.a, prism.b, prism.c);
	
	pthread_exit(NULL);
}

