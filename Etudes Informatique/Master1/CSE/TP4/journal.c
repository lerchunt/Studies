#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>

struct lectred{
	int nb_lecteurs;
	sem_t lecteurs,redacteurs,acces;
}

void init(struct lectred* lr){
	lr->nb_lecteurs = 0;
	sem_init(&(lr->lecteurs),0,nb_lecteurs);
	sem_init(&(lr->redacteurs),0,1);
	sem_init(&(lr->acces),0,1);
}

void begin_read(struct lectred* lr){
	sem_wait(&(lr->redacteurs));
	sem_wait(&(lr->acces));
	lr->nb_lecteurs++;
	sem_post(&(lr->lecteurs));
	sem_post(&(lr->acces));
}

void end_read(struct lectred* lr){
	sem_wait(&(lr->acces));
	lr->nb_lecteurs--;
	sem_post(&(lr->acces));
	sem_wait(&(lr->lecteurs));
}

void begin_write(struct lectred* lr){
	
	for
	sem_wait(&(lr->redacteurs));
	
}

int main(int argc, char** argv){

}