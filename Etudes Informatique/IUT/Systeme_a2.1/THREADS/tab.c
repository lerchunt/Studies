#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "string.h"


#define NB_THREADS 10
double tab[100];
	

void *f_thread(void *arg)
{
	struct drand48_data buffer;
	srand48_r(time(NULL),&buffer);
	double x;
	

	int i=0;
	int id=arg;
	printf("Bonjour, je suis le thread %d\n", id);
	
	for(i=id*10;i<id*10+10;i++)
	{	
		drand48_r(&buffer,&x);
		tab[i]= x*1000;
	}
  return (void*)id;
}

int main(int argc, char**argv)
{ 
  pthread_t tid[NB_THREADS];
  int i;
  for(i=0;i<NB_THREADS;i++) 
  {
    int ret = pthread_create(&tid[i], NULL, f_thread, (void*)i);
    if(ret) {
      fprintf(stderr, "Impossible de créer le thread %d\n", i);
      return 1;
    }
  }
  
  void *ret_val;
  for(i=0;i<NB_THREADS;i++) 
  {
    int ret = pthread_join(tid[i], &ret_val);
    
    if(ret) {
      fprintf(stderr, "Erreur lors de l'attente du thread %d\n", i);
      return 1;
    }
    
  }
  int j;


	
  for (i=0;i<100;i++){
		printf("tab[%d] = %.0f \n", i, tab[i]);
	}
  return 0;
}
