#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "string.h"
#include <pthread.h>

typedef struct joueur joueur;
int NB;

struct joueur // structure joueur
{
	int id;
	int alpha;
	int score;
};
joueur tab[15]; //car 15 joueur au maximum

void aleatoire(int alea, int id) // affichage pierre papier ciseaux à partir la valeur aleatoire
{
	switch(alea)
	{
		case 0: printf("Le thread d'id %d joue PIERRE \n",id);
		break;
		case 1: printf("Le thread d'id %d joue PAPIER \n",id);
		break;
		case 2: printf("Le thread d'id %d joue CISEAUX \n",id);
		break;
	}
}

void *f_thread(void *arg)
{
	int id=(int)arg;
	float max=3;
	int alea = (int)(max * rand() / RAND_MAX);
	tab[id].id=id;	
	tab[id].alpha= alea;
  return (void*)id;
}

int main(int argc, char *argv[]) //  fonction principale
{
	srand(time(NULL));
	// Declaration de variables
	NB=atoi(argv[1]); // nombre de joueur
	int i;
	pthread_t tid[NB];	
	
	if((NB>=2)&&NB<=15) // entre 2 et 15 joueurs
	{
		for(i=0;i<NB;i++){
		tab[i].score=0;
			
		}
		for(i=0; i< NB; i++)
		{
			int ret = pthread_create(&tid[i], NULL, f_thread, (void*)i);
			
			if(ret) {
				fprintf(stderr, "Impossible de créer le thread %d\n", i);
				return 1;
			}
		}
	}
	int l;
		for (i=0;i<NB;i++){
			aleatoire(tab[i].alpha, i);
		}
		for(l=0;l<NB-1;l++)
		{
			for(i=l+1;i<NB;i++)
			{

				if(((tab[i].alpha+1)%3)==tab[l].alpha)
				tab[l].score++;
				else if((((tab[l].alpha+1)%3)==tab[i].alpha))
				tab[i].score++;
			}
		}	
		for(i=0; i<NB; i++)
		{
			printf("Thread d'id: %d Nombre de Point : %d \n", tab[i].id,tab[i].score);
		}
	return 0;
}


