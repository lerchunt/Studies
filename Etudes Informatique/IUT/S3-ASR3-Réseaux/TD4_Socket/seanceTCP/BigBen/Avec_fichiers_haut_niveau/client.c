/* exemple Client/Serveur mode connecte TCP */
/* client bigben */
/* Version avec fichiers de haut niveau (cf. polycop systeme) */

/* usage: client machine_serveur port */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

/* Taille maximale d'une ligne recue du serveur */
#define TAILLEMAXLIGNE 8


#define FATAL(err) { perror((char *)err); exit(1); }

static int fd;

int connexion(char *, int); 
char *lireligne(FILE *, char *);
void travail(FILE *);


int main(int argc, char * argv[]) 
{
  int port;
  char *hostname;
  FILE *in;

  if (argc != 3) {
    printf("Usage: %s machine_serveur port\n",argv[0]);
    exit(1);
  };

  /* ouverture de la connexion */
  hostname=argv[1];
  port=atoi(argv[2]);
  fd=connexion(hostname,port);

  /* Ouverture de fichiers de haut niveau (cf. polycop systeme) */
  in  = fdopen(fd,"r");

  /* travail */
  travail(in);

  close(fd);
  exit(0);
}

/* --------------------------------------------------------- */
/* Fonction connexion
   Ouvre la connexion vers un port d'un serveur.
   Retourne la socket ouverte
   Exit en cas d'echec
   */
int connexion(char *hostname, int port)
{
  int fdPort;
  struct sockaddr_in addr_serveur;
  socklen_t lg_addr_serveur = sizeof addr_serveur;
  struct hostent *serveur;

  /* creation de la prise */
  fdPort=socket(AF_INET,SOCK_STREAM,0);
  if (fdPort<0)
    FATAL("socket");
  
  /* recherche de la machine serveur */
  serveur = gethostbyname(hostname);
  if (serveur == NULL)
    FATAL("gethostbyname");

  /* remplissage adresse socket du serveur */
  addr_serveur.sin_family      = AF_INET;
  addr_serveur.sin_port        = htons(port);
  addr_serveur.sin_addr        = *(struct in_addr *) serveur->h_addr;

  /* demande de connexion au serveur */
  if (connect(fdPort,(struct sockaddr *)&addr_serveur, lg_addr_serveur) < 0)
    FATAL("connect");

  return fdPort;
}

/* --------------------------------------------------------- */
/* Fonction travail
   Effectue le dialogue avec le serveur 
   */
char *lireligne(FILE *in, char ligne[])
{
  char *p;
  p = fgets(ligne,TAILLEMAXLIGNE,in);
  return p;
}

void travail(FILE *in) 
{ 
  char h[TAILLEMAXLIGNE],m[TAILLEMAXLIGNE],s[TAILLEMAXLIGNE];

  /* recuperation reponse du serveur */
  lireligne(in,h);
  lireligne(in,m);
  lireligne(in,s);

  printf("Il est %s:%s:%s sur le serveur\n",h,m,s);
}
