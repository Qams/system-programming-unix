#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
// ----------------------------------------------------------

void *PrintHello(void *arg);
// ----------------------------------------------------------

int running = 0;

int main(int argc, char *argv[]){
	int i = 0;
	pthread_t thread[SIZE];
	pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
	
	for(i=0;i<SIZE;i++)
	{
		int *arg = malloc(sizeof(*arg));
		if(arg == NULL)
		{
			perror("Couldn't allocate memory");
			exit(EXIT_FAILURE);
		}
		*arg = running;
		int rc = pthread_create(&thread[i], NULL, PrintHello, arg);
		if (rc){
			printf("Return code: %d\n", rc);
			exit(-1);
		}
		
		pthread_mutex_lock(&mut);
		running++;
		pthread_mutex_unlock(&mut);
		 
	}
	i = 0;
	for(i = 0;i<SIZE;i++)
		pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&mut);
	printf("End of the main thread!\n");
	return 0;
}
// ----------------------------------------------------------

void *PrintHello(void *arg){
	
	sleep(1);
	printf("Next boring 'Hello World!' version! Argument: %d\n", *((int *)arg));
	return NULL;
}
