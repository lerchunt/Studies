#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "string.h"
#include <sys/ipc.h>
#include <sys/shm.h>


typedef struct joueur joueur;
struct joueur // structure joueur
{
    int pid;
    int alpha;
    int score;
};

void score(joueur *tab,int NB) {
    int l,i;
    for(l=0; l<NB-1; l++)
    {
        for(i=l+1; i<NB; i++)
        {
            if(((tab[i].alpha+1)%3)==tab[l].alpha)
                tab[l].score++;
            else if((((tab[l].alpha+1)%3)==tab[i].alpha))
                tab[i].score++;
        }
    }
}

int main(int argc, char *argv[]) //  fonction principale
{

    // Declaration de variables
    // nombre de joueur
    int NB=atoi(argv[1]);
    int i,j,status;
    int id;
    pid_t pid;
    key_t key;
    joueur tab[NB]; //Tableau de joueur de taille NB
   
    if((NB>=2)&&NB<=15) // entre 2 et 15 joueurs
    {
        for(i=0; i<NB; i++)
            tab[i].score=0;

        for(i=0; i< NB; i++)
        {
			 key=ftok(".",(char)i);
			 if (key==-1) {
				perror("ftok");
				exit(EXIT_FAILURE);
			}
			
			    id = shmget(key,sizeof(struct joueur),
                IPC_CREAT | IPC_EXCL | 0666);
                
            if ((tab[i].pid = fork()) < 0) //erreur
            {
                fprintf(stderr,"Erreur fatale : fork()\n");
                exit(EXIT_FAILURE);
            }
            if ( tab[i].pid == 0)	// on est dans le processus fils
            {
				char c =(char)i;
                execl("joueur","joueur",&c,0);
                printf("erreur execl\n");
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
        score(tab,NB);
        for(i=0; i<NB; i++)
        {
            printf("Processus de pid: %d Nombre de Point : %d \n", tab[i].pid,tab[i].score);
        }
    }
    return 0;
}
