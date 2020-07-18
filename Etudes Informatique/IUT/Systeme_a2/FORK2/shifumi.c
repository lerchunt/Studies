#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc , char * argv[])
{
	srand(time(NULL)+getpid());
	float max=3;
	int i;
	int j;
	int r;
	int status;
	pid_t pid;
	
	if (argc!=2)
	{
		printf("erreur sur les arguments");
	}
	else
	{
		int nbr_fils = atoi(argv[1]);
		
		if ((nbr_fils<2)||(nbr_fils>15))
		{
			printf("erreur : arguments invalide \n");
		}
		else
		{
			for(i=0;i<nbr_fils;i++){
				int alea=(int) (max*rand()/RAND_MAX);
			if ((r = fork()) < 0)
	{
	  // traitement erreur fork()
	  fprintf(stderr,"Erreur fatale : fork()\n");
	  exit(EXIT_FAILURE);
	}
      if (r == 0)
	{
	  // un fils : il court....
	  switch (alea){
					case 0 : printf("le processus fils %d joue Pierre \n",getpid());exit(0); break;
					case 1 : printf("le processus fils %d joue Ciseau \n",getpid());exit (1); break;
					case 2 : printf("le processus fils %d joue Feuille \n3",getpid());exit(2); break;
					}
	  
	}
      // dans le père
      // poursuite de la boucle for
    }
  
  // père
  for (i=1; i<=nbr_fils; i++)
    {
      pid = wait(&status);
      fprintf (stdout, "le processus %d parti numero %d est arrive numero %d\n",
	       pid, WEXITSTATUS(status), i);
      // status/256 --> WEXITSTATUS(status)
    }
			
}
		for (j=0;j<nbr_fils;j++){
		pid=wait(&status);
		fprintf (stdout, "le processus %d parti N ̊ %d est arriv ́ N ̊ %d\n", pid, status/256, i);

		}
	}
 

return 0;
}	
