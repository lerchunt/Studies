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
int main(int argc, char *argv[]){
int i;

pid_t pid;             // pid
int status;
int NB=argc;
joueur tab[NB];
int r;

for(i=1; i<=NB; i++)
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
	  tab[i].pid=getpid();
	  exit(i);
	}   
}
return 1;   
}
