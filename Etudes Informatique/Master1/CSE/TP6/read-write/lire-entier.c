#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <netinet/in.h>


int main(int argc, char **argv){
	uint32_t valeur=htonl((uint32_t) atoi(argv[2]));
	
	int fd= open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	read(fd,&valeur, sizeof(uint32_t));
	valeur=ntohl(valeur);
	write(fd,&valeur, sizeof valeur);
	
	close (fd);
	printf("%d\n",valeur);
	return EXIT_SUCCESS;
}
