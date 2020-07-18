#include <stdlib.h>
#include <stdio.h>

int main ()
{
  if (fork()==0) {
    // le fils dort 10 secondes puis termine
    printf("Le fils (pid %d) dort... ", getpid()); fflush(stdout);
    sleep(10);
    printf("et termine...\n"); fflush(stdout);
    exit(0);
  } else {
    // le pere boucle...
    while (1) pause();
  }
}
