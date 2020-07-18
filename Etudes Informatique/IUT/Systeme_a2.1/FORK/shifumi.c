#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdio.h>
#include <curses.h> 
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc , char * argv[])
{
	srand(time(NULL)+getpid());
	float max=3;
	int r;
	int i;
	if (argc!=2)
	{
		printf("erreur sur les arguments");
	}
	else
	{
		int nbr_fils = atoi(argv[1]);
		if (nbr_fils<2)
		{
			printf("erreur : arguments invalide \n");
		}
		else if(nbr_fils >15)
		{
			printf("erreur : arguments invalide \n");
		}
		else
		{
			for(i=0;i<nbr_fils;i++) {
				int alea=(int) (max*rand()/RAND_MAX);
				if ((r = fork()) < 0) {
					// traitement erreur fork()
					fprintf(stderr,"Erreur fatale : fork()\n");
					exit(EXIT_FAILURE);
				}
				if (r == 0) {
				
				switch (alea)
				{
					case 0 : printf("le processus fils %d joue Pierre \n",getpid()); break;
					case 1 : printf("le processus fils %d joue Ciseau \n",getpid()); break;
					case 2 : printf("le processus fils %d joue Feuille \n3",getpid()); break;
				}
	}
			}	
	}

	}
 return 0;
}	
