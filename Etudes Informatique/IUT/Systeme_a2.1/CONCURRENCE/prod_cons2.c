#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 256
#define NB_PRODUCTEUR 2
#define NB_CONSOMATEUR 2
char tube[MAX][NB_PRODUCTEUR];

int cpt1=0;
int cpt2=0;

void* producteur(void* arg)
{
    printf("producteur\n");
    int i=0;
    char c='a';
    for(i=0; i<MAX; i++)
    {
        tube[i][cpt1]=c;
        c++;
        if(c>'z')
            c='a';
    }
    cpt1++;
    return NULL;
}

void* consommateur(void* arg)
{
    int cpt=0;
    cpt2=0;
    printf("consommateur\n");
    char c;
    int i;
    int j;
    for (j=0; j<NB_PRODUCTEUR; j++) {
        cpt2++;
        for(i=0; i<MAX; i++)
        {
            while(tube[i][j] == 0)
            {
                sleep(1);
                printf("%d\n",cpt);
            }
            printf("conso : lu prod %d: %c\n", cpt2, tube[i][j]);
            tube[i][j]=0;
            cpt++;
        }
    }

    return NULL;
}

int main(int argc, char** argv)
{
    pthread_t prod, cons;
    memset(tube, 0, MAX);
    int i=0;

    pthread_create(&prod, NULL, producteur, NULL);
    pthread_create(&cons, NULL, consommateur, NULL);

    for (i = 0; i <NB_PRODUCTEUR ; i++)
    {
        pthread_join(prod, NULL);

    }
    pthread_join(cons, NULL);
    return 0;
}
