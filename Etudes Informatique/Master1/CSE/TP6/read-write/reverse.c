#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <netinet/in.h>

void perror_and_exit_whenever(int assertion)
{
  if (assertion)
    {
      perror("");
      exit(EXIT_FAILURE);
    }
}


void mirror(char *out, char *in, size_t length)
{
  int i,j;
  
  for(i=0,j = length - 1; j >= 0 ; i++,j--)
    out[j] = in[i];
}

int main(int argc, char **argv)
{
	//   struct stat file_attributes;
	char valeur;

	int fd1 = open(argv[1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	int fd2 = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	int taille = lseek(fd1, 0 ,SEEK_END);
	lseek(fd1, 0,SEEK_SET);
	int i;
	for(i = 0; i<taille; ++i){
		read(fd1,&valeur, sizeof(char));
		lseek(fd2,taille-i, SEEK_SET);
		write(fd2, &valeur,sizeof(char));
	}
  return EXIT_SUCCESS;
}
