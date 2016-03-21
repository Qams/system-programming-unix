#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 4
#define LENGTH 100
// ----------------------------------------------------------

typedef struct {
    long* a;
    long sum; 
    int veclen; 
} CommonData;

typedef struct 
{
	int start;
	int stop;
} Partition;

// ----------------------------------------------------------

CommonData data; 
pthread_t threads[NUM];
pthread_mutex_t mutex;

void* calc(void* arg); // Funkcja rozpoczecia
long initData();
void threadInit();
// ----------------------------------------------------------

int main (int argc, char *argv[]){

	srand(time(NULL));
	int running = 0;
	long i, sum = 0;
	void* status;     
	pthread_attr_t attr;
	pthread_t thread[NUM];

	sum = initData();
     //mutex initialization
	pthread_mutex_init(&mutex, NULL);
         
     //[1] setting thread attribute
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(i=0;i<NUM;i++){
		Partition* p = malloc(sizeof(Partition));
		p->start = running*LENGTH;
		p->stop = p->start + LENGTH - 1;
		pthread_create(&thread[running], &attr, calc, p);
		pthread_mutex_lock(&mutex);
		running++;
		pthread_mutex_unlock(&mutex);
	}

	//[1] destroy - not needed anymore
	pthread_attr_destroy(&attr);

	//join
	for(i=0;i<NUM;i++) {
		pthread_join(threads[i], &status);
	}

	//Print
	printf ("Correct result is: %ld \n", sum);
	printf ("Function result is: %ld \n", data.sum);

	//Clean
	free(data.a);
	pthread_mutex_destroy(&mutex);
	return 0;
}
// ----------------------------------------------------------

long initData()
{
	int i=0; long sum=0;
	data.a = (long*) malloc (NUM*LENGTH*sizeof(long));
	data.veclen = LENGTH; 
	data.sum = 0;
	for(i = 0; i < LENGTH; i++)
	{
		data.a[i] = rand()%50;
		sum+=data.a[i];
	}
	return sum;
}

// ----------------------------------------------------------
void* calc(void* arg)
{
	Partition* p = (Partition*) arg;
	long* x = data.a;
	long mysum = 0;
	int i;
	for (i=p->start;i<=p->stop;i++){
		mysum += x[i];
	}

	pthread_mutex_lock(&mutex);
	data.sum += mysum;
	pthread_mutex_unlock(&mutex);

	pthread_exit((void*) 0);
}
// ----------------------------------------------------------
