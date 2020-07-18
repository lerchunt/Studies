/* exemple Client/Serveur mode connecte TCP */
/* serveur test echo longs messages */

/* usage: serveur port */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


#define FATAL(err) { perror((char *)err); exit(1); }


static int fd;

void Interruption() {
  close(fd);
  printf("Interruption : fin du serveur\n");
  exit(0);
}

int init_service(int);
void travail_fils(int);


int main(int argc, char * argv[]) 
{
  int fdTravail, port;

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
      travail_fils(fdTravail);
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
void travail_fils(int fd)
{
  char tampon[4096];
  int rep, env;

  /* reception de la chaine */
  rep=read(fd, tampon, 4096);
  printf("recu   : %d\n",rep);

  /* envoi de la chaine recue */
  env=write(fd, tampon, rep);
  printf("envoye : %d\n\n",env);
}
