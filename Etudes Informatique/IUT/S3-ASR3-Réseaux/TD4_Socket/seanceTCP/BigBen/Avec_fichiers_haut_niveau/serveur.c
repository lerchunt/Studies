/* exemple Client/Serveur mode connecte TCP */
/* serveur Bigben */
/* Version avec fichiers de haut niveau (cf. polycop systeme) */

/* usage: serveur port */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Taille maximale d'une ligne envoyee par serveur */
#define TAILLEMAXLIGNE 8


#define FATAL(err) { perror((char *)err); exit(1); }


static int fd;

void Interruption() {
  close(fd);
  printf("Interruption : fin du serveur\n");
  exit(0);
}

int init_service(int);
void ecrireligne(FILE *, char *);
void travail_fils(FILE *);


int main(int argc, char * argv[]) 
{
  int fdTravail, port;
  FILE *out;

  if (argc != 2) {
    printf("usage: %s port\n",argv[0]);
    exit(1);
  };

  /* positionnement du signal d'interruption */
  signal(SIGINT,Interruption);

  /* initialisation du service */
  port=atoi(argv[1]);
  fd=init_service(port);

  /* gestion des connexions de clients */
  while(1) {
    /* acceptation d'une connexion */
    fdTravail=accept(fd,NULL,NULL);
    if (fdTravail<=0)
      FATAL("accept");
    
    if (fork()==0) { /* fils : gestion du dialogue avec client */
      close(fd);
      /* Ouverture de fichiers de haut niveau (cf. polycop systeme) */
      out = fdopen(fdTravail,"w");
      /* travail */
      travail_fils(out);
      close(fdTravail);
      exit(0);
    } 
    else { /* pere : repart a l'ecoute d'une autre connexion */
      close(fdTravail);
    }
  }
}

/* --------------------------------------------------------- */
/* Fonction init_service
   Ouvre le service sur un port
   Retourne la socket ouverte
   Exit en cas d'echec
   */
int init_service(int port)
{
  int fdPort;
  struct sockaddr_in addr_serveur;
  socklen_t lg_addr_serveur = sizeof addr_serveur;

  /* creation de la prise */
  fdPort=socket(AF_INET,SOCK_STREAM,0);
  if (fdPort<0)
    FATAL("socket");
  
  /* nommage de la prise */
  addr_serveur.sin_family      = AF_INET;
  addr_serveur.sin_addr.s_addr = INADDR_ANY;
  addr_serveur.sin_port        = htons(port);
  if (bind(fdPort,(struct sockaddr *)&addr_serveur, lg_addr_serveur) < 0)
    FATAL("bind");

  /* Recuperation du nom de la prise */
  if (getsockname(fdPort,(struct sockaddr *)&addr_serveur, &lg_addr_serveur) < 0)
    FATAL("getsockname");

  /* Le serveur est a l'ecoute */
  printf("Le serveur ecoute le port %d\n",ntohs(addr_serveur.sin_port));

  /* ouverture du service */
  listen(fdPort,4);

  return fdPort;
}

/* --------------------------------------------------------- */
/* Fonction travail_fils
   Effectue le dialogue avec le client sur une autre socket
   Execute par le processus fils pendant le pere s'est remis
   a l'ecoute sur la socket du service
   */
void ecrireligne(FILE *out, char ligne[])
{
  fprintf(out,"%s\n",ligne);
  fflush(out);
}

void travail_fils(FILE *out)
{
  long horloge;
  struct tm *temps;
  char tampon[TAILLEMAXLIGNE];
  int h,m,s;

  /* preparation de la reponse */
  time(&horloge);
  temps=localtime(&horloge);
  h = temps->tm_hour;
  m = temps->tm_min;
  s = temps->tm_sec;

  /* envoi de la reponse */
  sprintf(tampon, "%02d", h);
  ecrireligne(out,tampon);
  sprintf(tampon, "%02d", m);
  ecrireligne(out,tampon);
  sprintf(tampon, "%02d", s);
  ecrireligne(out,tampon);
}
