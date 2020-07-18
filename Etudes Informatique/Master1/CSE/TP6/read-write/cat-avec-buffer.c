#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
int main(int argc, char **argv){
	char c[];
	char valeur[20];

	int fd = fopen(argv[1], "w+");
	int taille = fseek(fd,SEEK_END, 0);
	fseek(fd, SEEK_SET, 0);
		fread(fd,&valeur, sizeof(char));
		fwrite(c, strlen(c) +1, 1, fd)
		printf( "%c \n",valeur);
		fclose(fd);
  return EXIT_SUCCESS;

}

