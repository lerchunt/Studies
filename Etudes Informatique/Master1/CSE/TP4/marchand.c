#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>

#define M 20

int nb_glaces = M;
sem_t glaces, decompte_glaces,vide;

void* acheter_glaces(){
	pthread_t tid ; 
	tid = pthread_self () ;
	sem_wait(&decompte_glaces);
	sem_wait(&glaces);
	nb_glaces--;
	if(nb_glaces == 0)
	{
		sem_post(&vide);
	}
    	printf ("Thread clients achete une glace %x :  il en reste %d \n", (unsigned int) tid, nb_glaces) ;
	usleep (rand() / RAND_MAX * 1000000.) ;
	sem_post(&glaces);
	return (void *) tid ;
}

void* recharger_glaces(){
	pthread_t tid ; 
	tid = pthread_self () ;
	int i;
	sem_wait(&vide);
	sem_wait(&glaces);
	nb_glaces+=M;
	for(i=0;i<M;i++)
	{
		sem_post(&decompte_glaces);
	}
	printf ("Thread marchand recharge les glaces %x :  il y en a %d \n", (unsigned int) tid, nb_glaces) ;
	usleep (rand() / RAND_MAX * 1000000.) ;
	sem_post(&glaces);
	return (void *) tid ;
}

int main(int argc, char** argv){
	int nb_threads;
	int i;
	pthread_t *tids;	
	
	if (argc != 2)
	{
    		fprintf(stderr, "usage : %s nb_threads\n", argv[0]) ;
    		exit (-1) ;
  	}

	nb_threads = atoi (argv[1]);
	tids = malloc (nb_threads*sizeof(pthread_t)) ;

	sem_init(&glaces,0,1);
	sem_init(&decompte_glaces,0,M);
	sem_init(&vide,0,0);

	for(i = 0 ; i<nb_threads/M;i++)
	{
		pthread_create (&tids[i], NULL, recharger_glaces, (void *) NULL) ;
	}

	for (i = nb_threads/M ; i < nb_threads; i++)
	{
   		pthread_create (&tids[i], NULL, acheter_glaces, (void *) NULL) ;
  	}

	/* Wait until every thread ened */ 
  	for (i = 0; i < nb_threads; i++)
	{
    		pthread_join (tids[i], NULL) ;
  	}
	
	free (tids) ;
  	return EXIT_SUCCESS;
}
