#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

static volatile int totalPoints = 0;
int wanted = 0;
pthread_mutex_t lock;
void* count(void* param){
	pthread_mutex_lock(&lock);
	int i, upper =atoi(param);
	for(i = 0;i < upper; i++){
		double x = (double)rand() / RAND_MAX;
		double y = (double)rand() / RAND_MAX;
		if( ((x*x)+(y*y)) <= 1) totalPoints++;
	}
	pthread_mutex_unlock(&lock);
	return NULL;
	pthread_exit(0);
}
int main(int argc, char* argv[]){

	wanted = atoi(argv[1]) * atoi(argv[2]); //wanted number of points
	int nthreads = atoi(argv[2]); //number of threads
	//threading
	pthread_t thread[nthreads];
	//generate 100000 points per threads.
	for(int i = 0; i< nthreads; i++)
		pthread_create(&thread[i], NULL, &count, argv[1]);
	for(int i =0; i<nthreads; i++)
		pthread_join(thread[i],NULL);
	//calculating pi
	double points = 4.0 * totalPoints;
	double pi = points/ wanted;
	//pi
	printf("pi_mutex  value = %f\n",pi);
	return 0;	

}
