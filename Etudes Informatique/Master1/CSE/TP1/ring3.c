#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>

int rang; /* correspond au numero de creation du processus (initialise par creer_processus) */
int** tpipe; /* tableau de tubes utilise pour la communication entre les processus (initialise par creer_tubes) */

/* Le processus principal initialise le tableau de tubes */
void creer_tubes(int n){
	tpipe = malloc(n * sizeof(int*)); /* tpipe[n] : n tubes utilises pour n processus */
	int i;
	for(i = 0;i<n;i++)
	{
		tpipe[i] = malloc(2 * sizeof(int));
		pipe(tpipe[i]);
	} 
}

/* renvoie le resultat positif de i modulo n */
inline int modulo_positif(int i, int n) {
    return (i % n + n) % n;
}

/* selectionne les tubes utilises par le processus en fermant ceux qui n'en necessitent pas l'acces */
void selectionner_tubes(int n){
	int i;
	for(i = 0;i<n;i++)
	{
		if((i!=modulo_positif(rang-1,n)) && (i!= modulo_positif(rang,n)))
		{
			close(tpipe[i][0]);
			close(tpipe[i][1]);
		}
	}
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
			case -1:perror("fork");
				exit(-1);
			case 0: rang = i+1;
				return; 
		}
	 }
}

/* Tire une valeur aleatoire pour chacun des processus, affiche et retourne la valeur obtenue */
int tirage_aleatoire(){
	srand(getpid());
	int val = rand();
	printf("processus pid %d node %d val = %d \n",getpid(),rang,val);
	return val;
}

/* Transmet la valeur maximale tiree de processus en processus */
void transmission_valeur(int n){
	int nbmax[3];
	int nb[3];
	int x;
	nb[0]= tirage_aleatoire();
	nb[1] = getpid();
	nb[2] = rang;

	if(rang==0)
	{	
		x =write(tpipe[rang][1],nb,sizeof(int)*3);
		if(x != sizeof(int)*3){ /* Verifie que l'ecriture s'est bien passee */
			perror("write : Erreur d'ecriture ");
			exit(-1);
		}
	}
	else
	{
		x = read(tpipe[modulo_positif(rang-1,n)][0],nbmax,sizeof(int)*3);
		if(x != sizeof(int)*3){ /* Verifie que la lecture s'est bien passee */
			perror("read : Erreur de lecture ");
			exit(-1);
		}
		if(nbmax[0] < nb[0]) 
		{
			x = write(tpipe[modulo_positif(rang,n)][1],nb,sizeof(int)*3);
		}
		else
		{
			x = write(tpipe[modulo_positif(rang,n)][1],nbmax,sizeof(int)*3);
		}
		if(x != sizeof(int)*3){ /* Verifie que l'ecriture s'est bien passee */
			perror("write : Erreur d'ecriture ");
			exit(-1);
		}
	}
}

/* Transmet la valeur maximale gagnante de processus en processus */
void transmission_winner(int n){
	int nbfinal[3];
	int x;
	close(tpipe[modulo_positif(rang-1,n)][1]);
	x = read(tpipe[modulo_positif(rang-1,n)][0],nbfinal,sizeof(int)*3);
	if(x != sizeof(int)*3){ /* Verifie que la lecture s'est bien passee */
		perror("read : Erreur de lecture ");
		exit(-1);
	}
	close(tpipe[modulo_positif(rang-1,n)][0]);
	
	printf("Node %d the winner is %d pid %d node %d \n",rang,nbfinal[0],nbfinal[1],nbfinal[2]);

	close(tpipe[rang][0]);
	x = write(tpipe[rang][1],nbfinal,sizeof(int)*3);
	if(x != sizeof(int)*3){ /* Verifie que l'ecriture s'est bien passee */
		perror("write : Erreur d'ecriture ");
		exit(-1);
	}
	close(tpipe[rang][1]);
}

/* Le processus principal (rang = 0) attend la fin d'execution de ses processus fils */
void attendre_fin_processus(int n){
	if(rang==0)
	{
		int status;
		int i;
		for(i=1;i<n-1;i++)
		{
			wait(&status);
		}
	}
}

/* Programme principal */
int main(int argc, char** argv){
	if(argc!=2){
		printf("Ajoutez en argument le nombre de processuss à creer. \n");
		exit(0);
	}
	int n = atoi(argv[1]);
	creer_tubes(n);
	creer_processus(n);
	selectionner_tubes(n);
	transmission_valeur(n);
	transmission_winner(n);
	attendre_fin_processus(n);
	
	return 0;
}
