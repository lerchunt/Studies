#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "string.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#define PIERRE 0
#define PAPIER 1
#define CISEAUX 2

typedef struct joueur joueur;
struct joueur // structure joueur
{
    int pid;
    int alpha;
    int score;
};

int aleatoire() // affichage pierre papier ciseaux à partir la valeur aleatoire
{
    float max=3;
    srand(time(NULL)+getpid());
    int alea = (int)(max * rand() / RAND_MAX);
    

    switch(alea)
    {
    case PIERRE:
        printf("Le processus de pid %d joue PIERRE \n",getpid());
        break;
    case PAPIER:
        printf("Le processus de pid %d joue PAPIER \n",getpid());
        break;
    case CISEAUX:
        printf("Le processus de pid %d joue CISEAUX \n",getpid());
        break;
    }
    exit(alea);
}


int main(int argc, char *argv[])
{
    key_t key;
    int id;
    joueur *player[atoi(argv[1])];
    int i = atoi(argv[2]);
    printf("je suis passé\n");
    key=ftok(".",(char)argv[2]);
    if (key==-1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    id = shmget(key,sizeof(struct joueur),0);
    if (id == -1) {
        switch(errno) {
        case ENOENT:
            printf("pas de segment\n");
            exit(EXIT_SUCCESS);
        default:
            perror("shmget");
            exit(EXIT_FAILURE);
        };
    };
    player[i]=(struct joueur *)shmat (id,NULL,SHM_R | SHM_W );
    player[i]->alpha=aleatoire();
    exit(1);
}
