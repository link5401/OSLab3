#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
static volatile int totalPoints = 0;
int wanted = 0;
static sem_t lock;
void* count(void* param){
	sem_wait(&lock);
	int i, upper =atoi(param);
	for(i = 0;i < upper; i++){
		double x = (double)rand() / RAND_MAX;
		double y = (double)rand() / RAND_MAX;
		if( ((x*x)+(y*y)) <= 1) totalPoints++;
	}
	sem_post(&lock);
	return NULL;
	pthread_exit(0);
}
int main(int argc, char* argv[]){

	wanted = atoi(argv[1]) * atoi(argv[2]); //wanted number of points
	int nthreads = atoi(argv[2]); //number of threads
	//threading
	pthread_t thread[nthreads];
	//generate 100000 points per threads.
	sem_init(&lock, 0, 1);
	for(int i = 0; i< nthreads; i++)
		pthread_create(&thread[i], NULL, &count, argv[1]);
	for(int i =0; i<nthreads; i++)
		pthread_join(thread[i],NULL);
	sem_destroy(&lock);
	//calculating pi
	double points = 4.0 * totalPoints;
	double pi = points/ wanted;
	//pi
	printf("pi_mutex  value = %f\n",pi);
	return 0;	

}
