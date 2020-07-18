#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
int main(int argc, char **argv){
	char valeur;
	int fd = open(argv[1], O_RDWR| O_CREAT, S_IRUSR | S_IWUSR);
	
	int taille = lseek(fd, 0 ,SEEK_END);
	lseek(fd, 0,SEEK_SET);
	int i;
	for(i = 0; i<taille; ++i){
		read(fd,&valeur, sizeof(char));
		write(fd, &valeur, sizeof(valeur));
	}
  return EXIT_SUCCESS;

}
