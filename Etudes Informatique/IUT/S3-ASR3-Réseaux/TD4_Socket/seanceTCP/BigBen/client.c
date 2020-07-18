/* exemple Client/Serveur mode connecte TCP */
/* client bigben */

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

#define FATAL(err) { perror((char *)err); exit(1); }

static int fd;

int connexion(char *, int); 
void travail(int); 


int main(int argc, char * argv[]) 
{
  int port;
  char *hostname;

  if (argc != 3) {
    printf("Usage: %s machine_serveur port\n",argv[0]);
    exit(1);
  };

  /* ouverture de la connexion */
  hostname=argv[1];
  port=atoi(argv[2]);
  fd=connexion(hostname,port);

  /* travail */
  travail(fd);

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
void travail(int fd) 
{ 
  char h[3],m[3],s[3];

  /* recuperation reponse du serveur */
  if (read(fd,h,2) != 2) FATAL("read h");
  h[2]='\0';
  if (read(fd,m,2) != 2) FATAL("read m");
  m[2]='\0';
  if (read(fd,s,2) != 2) FATAL("read s");
  s[2]='\0';

  printf("Il est %s:%s:%s sur le serveur\n",h,m,s);
}
