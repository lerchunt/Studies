#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
typedef struct joueur joueur;
struct joueur{
	int alpha;
	int score;
	int pid;
	};
	
int aleatoire(){
	float max=3;
	int alea=(int) (max*rand()/RAND_MAX);
	return alea;
}
int main(int argc, char *argv[]){
srand(time(NULL)+getpid());
int i,k;
pid_t pid;             // pid
int NB=atoi(argv[1]);
joueur tab[NB];
int r;
	if (NB>=2&&NB<=15)
	{
		for(i=0;i<NB;i++)
		tab[i].score=0;
		
		for(i=0; i<NB; i++)
		{
			if ((r = fork()) < 0)
			{
				// traitement erreur fork()
				fprintf(stderr,"Erreur fatale : fork()\n");
				exit(EXIT_FAILURE);
			}
			if (r == 0)
			{
				// un fils : il court....
				srand(time(NULL)+getpid());
				tab[i].pid=getpid();
				tab[i].alpha=aleatoire();
				
				switch(tab[i].alpha)
				{
					case 0:
						printf("le fils de pid %d joue pierre \n",tab[i].pid);
						break;
					case 1:
						printf("le fils de pid %d joue feuille \n",tab[i].pid);
						break;
					case 2:
						printf("le fils de pid %d joue ciseau \n",tab[i].pid);
						break;
				}
	  exit(EXIT_FAILURE);
		}
}
	int status;
		for(k= 0; k<NB; k++)		
		{
				pid = wait(&status);
			
			int p;
			for(p=0; p<NB; p++)
			{
				
				if(pid == tab[p].pid)
				{
					tab[p].alpha=status/256;
				}	
			}
		}	
		int z;
		for(z=0;z<NB-1;z++)
		{

			for(i=z+1;i<NB;i++)
			{
				if(((tab[i].alpha+1)%3)==tab[z].alpha)
				tab[z].score++;
				else if((((tab[z].alpha+1)%3)==tab[i].alpha))
				tab[i].score++;
			}
		}
		
		printf("\nPoint des Processus\n\n");	
			for(i=0; i<NB; i++)
			{
				printf("Processus : %d Point : %d \n", tab[i].pid,tab[i].score);
			}
			
			if (WIFSIGNALED(status)) // si probleme arret processus fils
			{
				printf(" Terminaison anormale du processus fils.\n"
						   " Tué par le signal : %d.\n", WTERMSIG(status));
			}
			else
				return 0;
	
	}
return 0;
	
}
  

