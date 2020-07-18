#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 256
#define WRITE 0
#define READ 1
char tube[MAX];
pthread_mutex_t mutex; // protege l'indice i
int i; // i devient partage
char c; // c devient partage entre producteurs
int rw; // prochaine etape : lecture (cons) ou ecriture (prod)

void* producteur(void* arg) 
{
	printf("producteur\n");
	int prodnum = (int)arg;
	while(i<MAX) 
	{
	  pthread_mutex_lock(&mutex); // section critique
	  if (rw == WRITE) {
		i++;
		tube[i]=c;
		printf("prod %d : ecrit : %c\n", prodnum, c);
		c++;
		if(c>'z')
		  c='a';
		rw = READ;
	  }
	  pthread_mutex_unlock(&mutex);
	  sleep(1);
	}
	return NULL;
}

void* consommateur(void* arg)
{
	printf("consommateur\n");
	int consnum = (int)arg;
	while(i < MAX) {
	  pthread_mutex_lock(&mutex); // section critique
	  if (rw == READ) {
		if (tube[i]!=0) {
		  printf("conso %d : lu : %c\n", consnum, tube[i]);
		  tube[i]=0;
		}
		rw = WRITE;
	  }
	  pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(int argc, char** argv) 
{
  pthread_t prod1, prod2, cons1, cons2;
	memset(tube, 0, MAX);
	i=0;
	c='a';
	rw = WRITE;
	
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&prod1, NULL, producteur, (void *)1);
	pthread_create(&prod2, NULL, producteur, (void *)2);
	pthread_create(&cons1, NULL, consommateur, (void *)1);
	pthread_create(&cons2, NULL, consommateur, (void *)2);

	pthread_join(prod1, NULL);
	pthread_join(prod2, NULL);
	pthread_join(cons1, NULL);
	pthread_join(cons2, NULL);

	pthread_mutex_destroy(&mutex);

	return 0;
}
