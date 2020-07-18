#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define TAILLE_SHM 1024 /* taille de la memoire partagee */

/* structure de donnees utilisee pour stocker dans la memoire partagee : */
struct tuple{
	int val; /* nombre tire au hasard */
	pid_t pid; /* pid correspondant au processus qui a tire val */
	int node; /* correspond au rang du processus */
};

int rang; /* correspond au numero de creation du processus (initialise par creer_processus) */
int shmid; /* correspond au segment de memoire de la memoire partagee */
struct tuple *adr_shm; /* correspond au pointeur attache au segment de memoire pour chaque processus */


/* Gere les erreurs qui peuvent etre retournees lors de la creation ou la liberation de la memoire partagee */
void handle_error(char *function_name, int return_value){
	char message[128] = "Error in function ";
	if(return_value == -1)
	{
		perror(strcat(message,function_name));
		exit(1);
	}
}

/* Renvoie un pointeur attache a un segment de memoire d'une taille donnee */
void *allouer_memoire_partagee(size_t size, int *shmid){
	int *ptr;
	*shmid = shmget(IPC_PRIVATE, size, IPC_CREAT | 0666);
	handle_error("shmget", *shmid);
	ptr = shmat(*shmid, NULL, 0);
	handle_error("shmat", *ptr);
	return ptr;
}

/* Libere un pointeur attache a un segment de memoire */
void liberer_memoire_partagee(void *ptr, int shmid){
	int cr;
	cr = shmdt(ptr);
	handle_error("shmdt",cr);
	cr = shmctl(shmid,IPC_RMID, NULL);
	handle_error("shmct1", cr);
}

/* Tire une valeur aleatoire pour chacun des processus, affiche et retourne la valeur obtenue */
int tirage_aleatoire(){
	srand(getpid());
	int val = rand();
	printf("processus pid %d node %d val = %d \n",getpid(),rang,val);
	return val;
}

/* Le processus principal (rang = 0) cree n-1 processus fils pour un total de n processus */
void creer_processus(int n){
	rang = 0;
	int i;
	for(i=0;i<n-1;i++)
	{
		pid_t pid = fork();
		switch(pid)
		{
			case -1: perror("fork");
					exit(-1);
			case 0: rang = i+1;
					sleep(1);
					return; 
		}
	 }
}

/* Le processus principal (rang = 0) attend la fin d'execution de ses processus fils */
void attendre_fin_processus(int n){
	if(rang==0)
	{
		int status=0;
		int i;
		for(i=0;i<n-1;i++)
		{
			wait(&status);
		}
	}
}

/* Ecrit la valeur maximale en comparant avec celle deja ecrite et la nouvellement tiree */
void ecriture_valeur(int n){
	struct tuple nbmax,nb;
	nb.val = tirage_aleatoire();
	nb.pid = getpid();
	nb.node = rang;
	
	if(rang==0)
	{
		memcpy(adr_shm, &nb,sizeof(nb));
	}
	else
	{
		memcpy(&nbmax,adr_shm,sizeof(nbmax));
		if(nbmax.val < nb.val)
		{
			memcpy(adr_shm, &nb,sizeof(nb));
		}
	}
}

/* Le processus principal ecrit la valeur maximale finale a partir de la memoire partagee */
void print_valeur(int n){
	if(rang == 0)
	{
		struct tuple nb;
		memcpy(&nb,adr_shm,sizeof(nb));
		printf("the winner is %d pid %d node %d \n",nb.val,nb.pid,nb.node);
	}
}

/* Programme principal */
int main(int argc, char** argv){
	if(argc!=2){
		printf("Ajoutez en argument le nombre de processus à creer. \n");
		exit(0);
	}
	int n = atoi(argv[1]);
	adr_shm = allouer_memoire_partagee(TAILLE_SHM,&shmid);
	creer_processus(n);
	ecriture_valeur(n);
	attendre_fin_processus(n);
	print_valeur(n);
	liberer_memoire_partagee(adr_shm, shmid);	

	return 0;
}
