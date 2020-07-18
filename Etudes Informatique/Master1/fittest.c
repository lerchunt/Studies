#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <sys/time.h>


#define TAILLE_BUFFER 128
#define TAILLE_MEMOIRE 128
static char memoire[TAILLE_MEMOIRE];

#define MAX_ALLOC 32
static int nb_free, nb_busy;
static void *allocs[MAX_ALLOC];
static size_t sizes[MAX_ALLOC];
static size_t free_size[MAX_ALLOC];
static size_t busy_size[MAX_ALLOC];
static int position;
static intptr_t mem_align=0;

void decompte_zone(void *adresse, size_t taille, int free) {
    if (free)
        free_size[nb_free++] = taille;
    else
        busy_size[nb_busy++] = taille;
}

void afficher_zone(void *adresse, size_t taille, int free) {
    decompte_zone(adresse, taille, free);
    printf("Zone %s, Adresse : %lx, Taille : %lu\n", free?"libre":"occupée",
           (unsigned long) adresse, (unsigned long) taille);
}

void my_mem_init(void *mem, size_t s) {
    position = 0;
    mem_init(mem, s);
}

void *my_mem_alloc(size_t s) {
    void *result = mem_alloc(s);
    sizes[position] = s;
    allocs[position++] = result;
    printf("Allocation de %lu octets en %lx\n", (unsigned long) s,(unsigned long) result);
    mem_align |= (intptr_t)result;
    return result;
}

void my_mem_free(int num) {
    printf("Liberation de la zone en %lx\n", (unsigned long) allocs[num]);
    mem_free(allocs[num]);
}

void my_mem_show(void (*print)(void *, size_t, int free)) {
    nb_free = 0;
    nb_busy = 0;
    mem_show(print);
}

int main()
{
	//int i;
	/*size_t size;
	size = 16;
	
	my_mem_init(memoire, TAILLE_MEMOIRE);
  	my_mem_show(afficher_zone);
	printf("Utilisation de la fonction fit first : \n ");
  	my_mem_alloc(8);
  	my_mem_alloc(16);
  	my_mem_alloc(4);
  	my_mem_alloc(12);
  	printf("Etat de la memoire :\n");
  	my_mem_show(afficher_zone);
	*/
	my_mem_init(memoire, TAILLE_MEMOIRE);
  	
  	printf("Utilisation de la fonction fit best : \n ");
  	mem_fit(mem_fit_best);

  	my_mem_alloc(130);
 

	printf("Etat de la memoire :\n");

  	my_mem_show(afficher_zone);
	
	/*for(i=0;i<TAILLE_MEMOIRE/size;i++)
	{
		if(i%2)
		{
			my_mem_free(i);
		}
	}*/
	
	printf("Utilisation de la fonction fit worst : \n ");

	return 0;
}
