#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "string.h"

typedef struct joueur joueur;
struct joueur // structure joueur
{
	int pid;
	int alpha;
	int score;
};

void aleatoire() // affichage pierre papier ciseaux à partir la valeur aleatoire
{
	float max=3;
	srand(time(NULL)+getpid());
	int alea = (int)(max * rand() / RAND_MAX);
	switch(alea)
	{
		case 0: printf("Le processus de pid %d joue PIERRE \n",getpid());
		break;
		case 1: printf("Le processus de pid %d joue PAPIER \n",getpid());
		break;
		case 2: printf("Le processus de pid %d joue CISEAUX \n",getpid());
		break;
	}
	exit(alea);
}

int main(int argc, char *argv[]) //  fonction principale
{
	
	// Declaration de variables
	int NB=atoi(argv[1]); // nombre de joueur
	int i,j,status; // compteur
	pid_t pid;
	joueur tab[NB]; //Tableau de joueur de taille NB
	if((NB>=2)&&NB<=15) // entre 2 et 15 joueurs
	{
		for(i=0;i<NB;i++)
		tab[i].score=0;

		for(i=0; i< NB; i++)
		{
			if ((tab[i].pid = fork()) < 0) //erreur
			{
			  fprintf(stderr,"Erreur fatale : fork()\n");
			  exit(EXIT_FAILURE);
			}
			if ( tab[i].pid == 0)	// on est dans le processus fils
			{	
				aleatoire();
				exit(EXIT_FAILURE);
			}
		}
		
		//pere
		for(j= 0; j<NB; j++)		
		{
			pid = wait(&status);
			int k;
			for(k=0; k<NB; k++)
			{
				
				if(pid == tab[k].pid)
				{
					tab[k].alpha=status/256;
				}	
			}
		}	
			int l;
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
				printf("Processus de pid: %d Nombre de Point : %d \n", tab[i].pid,tab[i].score);
			}
			return 0;
	}
			 
return 0;
	
}


