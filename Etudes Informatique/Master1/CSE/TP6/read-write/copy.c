#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void 
perror_and_exit_whenever(int assertion)
{
  if (assertion)
    {
      perror("");
      exit(EXIT_FAILURE);
    }
}

int 
main(int argc, char **argv)
{
  int power;
  size_t buffer_size;
 
  if (argc != 4)
    {
      fprintf(stderr,"%s : <input file name>"
	      " <output filename> <log2 of buffer length> \n", argv[0]);
      return EXIT_FAILURE;
    }
  
  power = strtoul(argv[3], NULL, 10);
  buffer_size = 1 << power;
  
	int fd = fopen(argv[1], "r");
	int fd2 = fopen(argv[1], "w+");
  
  return EXIT_SUCCESS;
}
