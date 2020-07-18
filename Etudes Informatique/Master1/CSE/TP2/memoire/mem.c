#include "mem.h"
#include <stdio.h> /* a supprimer */

char* memoire; /* adresse de debut de la memoire consideree */
size_t taille_memoire; /* taille totale de la memoire consideree */
struct fb * zones_libres; /* liste chainee contenant les adresses croissantes des zones libres */
mem_fit_function_t * mem_fit_function; /* fonction de recherche utilisee */


struct fb{ /* fb pour free block */
	size_t size; /* taille totale de la zone libre */
	struct fb *next; /* adresse de la zone libre suivante */
};
struct ob{ /* ob pour occupied block */
	size_t size; /* taille totale de la zone occupee */
};


/* initialise la liste des zones libres avec l'ensemble du tableau memoire */
void mem_init(char* mem, size_t taille){
	memoire = mem;
	taille_memoire = taille;
	struct fb *zone = (struct fb*)mem;
	zone->size = taille;
	zone->next = NULL;
	zones_libres = zone;
	mem_fit(mem_fit_first);
}

/* permet de regler la taille a un nombre multiple de sizeof(void*) pour maintenir les adresses alignees */
size_t alignement_taille(size_t size){
	if(size % sizeof(void*) !=0)
	{
		size = size + (sizeof(void*) - size % sizeof(void*)); /* la taille de la zone allouee devient multiple de sizeof(void*) */
	}
	/* la taille demandee de zone a allouer est trop petite : on remplace la taille totale par sizeof(struct fb) pour avoir assez de place pour eventuellement la liberer plus tard */
	if(size < sizeof(struct fb)) 
	{
		size = sizeof(struct fb);
	}
	return size;
}

/* recoit en paramatre d'une taille a allouer et renvoie, si possible, l'adresse correspondante */
void* mem_alloc(size_t size){
	struct fb* adr_libre = (*mem_fit_function)(zones_libres,size);
	struct fb* adr_zl, *pre_adr_zl ;
	struct ob* adr_allouee;
	size_t taille_totale = sizeof(size_t) + size; /* ajout de la taille de la structure dans la taille */
	
	taille_totale = alignement_taille(taille_totale);

	if(adr_libre==NULL) /* pas d'allocation possible */
	{
		return NULL;
	}
	else
	{
		adr_allouee = (struct ob*) adr_libre;
		/* Mise a jour de la liste chainee des zones libres : */
		if(zones_libres == adr_libre) /* l'adresse de la zone a allouer est le premier element de la liste chainee des zones libres */
		{
			if(adr_libre->size - taille_totale < sizeof(struct fb)) /* s'il n'y a pas possibilite de créer une nouvelle zone libre 	*/
			{
				adr_allouee->size = zones_libres->size;
				zones_libres = zones_libres->next;
			}
			else	/* creation de la zone libre à la suite de la zone occupee*/
			{
				zones_libres = (struct fb*)((void*)adr_libre + taille_totale);
				zones_libres->next = adr_libre->next;
				zones_libres->size = adr_libre->size - taille_totale;
				adr_allouee->size = taille_totale;
			}

		}
		else	/* l'adresse de la zone a allouer se trouve apres la premier element de la liste chainee des zones libres */
		{
			pre_adr_zl = zones_libres;
			adr_zl = zones_libres->next;
			while(adr_zl != adr_libre)
			{
				pre_adr_zl = adr_zl;
				adr_zl = adr_zl->next;
			}
			if(adr_libre->size - taille_totale < sizeof(struct fb)) /* s'il n'y a pas possibilite de creer une nouvelle zone libre 	*/
			{
				adr_allouee->size = adr_zl->size;
				pre_adr_zl->next = adr_zl->next;
			}
			else /* creation de la zone libre à la suite de la zone occupee */
			{
				adr_zl = (struct fb*)((void*)adr_libre + taille_totale);
				adr_zl->next = adr_libre->next;
				adr_zl->size = adr_libre->size - taille_totale;
				pre_adr_zl->next = adr_zl;
				adr_allouee->size = taille_totale;
			}
		}

		return (struct ob*)((void*)adr_allouee + sizeof(struct ob)); /* l adresse renvoyee correspond directement a l endroit ou l on peut ecrire des donnees*/
	}
}

/* recoit en parametre l adresse de la zone occupee. La fonction met a jour les zone libres*/
void mem_free(void* zone){
	struct ob* zone_o = (struct ob*) ((void*)zone - sizeof(struct ob));
	size_t taille_zone = zone_o->size;
	char * adr_fin = (char*)((void*)zone_o + taille_zone);
	char * adr_fin_zl;	
	struct fb * adr_zl = zones_libres;
	struct fb *pre_adr_zl, *zone_l;

	if(zones_libres==NULL) /* si toute la memoire est occupee*/
	{
		zones_libres = (struct fb*) zone_o;
		zones_libres->size = taille_zone;
		zones_libres->next = NULL;
	}
	else if((char*)zones_libres > (char*)zone_o) /* si la zone occupee est avant la premiere zone libre */
	{
		zone_l = (struct fb*) zone_o;
		if(adr_fin == (char*) zones_libres)	/*si la fin de la zone occupee correspond a l adresse de debut de la premiere zone libre, on les fusionne  */
		{
			zone_l->size = taille_zone + zones_libres->size;
			zone_l->next = zones_libres->next;
		}
		else	/* creation d une nouvelle zone libre*/
		{
			zone_l->size = taille_zone;
			zone_l->next = zones_libres;
		}
		zones_libres = zone_l;
	}
	else /* si l adresse de la zone occupee est apres l adresse de la premiere zone libre */
	{
		pre_adr_zl = zones_libres;
		adr_zl = zones_libres->next;
		while(adr_zl != NULL && (char*)adr_zl < (char *)zone_o)
		{
			pre_adr_zl = adr_zl;
			adr_zl = adr_zl->next;
		}
		adr_fin_zl = (char*)((void*)pre_adr_zl + pre_adr_zl->size);
		if(adr_zl==NULL) /* la zone occupee se trouve apres l ensemble des zones libres */
		{
			if(adr_fin == (char*) zone_o)	/* si la zone qui precede la zone occupee est libre: on fusionne*/
			{
				pre_adr_zl->size = pre_adr_zl->size + taille_zone;
			}
			else /* sinon on cree une zone libre a la place de la zone occupee*/
			{
				zone_l = (struct fb*) zone_o;
				zone_l->size = taille_zone;
				zone_l->next = NULL;
				pre_adr_zl->next = zone_l;
			}
		}
		else /*l adresse de la zone occupee est entre deux zones libres */
		{
			if((char*)adr_zl == adr_fin && (char*)adr_fin_zl == (char*) zone_o) /* si on peut fusionner la zone occupee avec les deux zones libres*/
			{
				pre_adr_zl->size = pre_adr_zl->size + taille_zone + adr_zl->size;
				pre_adr_zl->next = adr_zl->next;
			}
			else if(adr_fin_zl == (char *) zone_o) /* si on peut fusionner la zone libre precedente avec la zone occupee*/
			{
				pre_adr_zl->size = pre_adr_zl->size + taille_zone;
			}
			else if((char*)adr_zl == adr_fin)	/* si on peut fusionner la zone libre suivante avec la zone occupee*/
			{
				zone_l = (struct fb*) zone_o;
				zone_l->size = taille_zone + adr_zl->size;
				zone_l->next = adr_zl->next;
				pre_adr_zl->next = zone_l;
			}
			/*else if(pre_adr_zl == zones_libres && (char*)pre_adr_zl == adr_fin) 
			{
				zone_l = (struct fb*) zone_o;
				zone_l->size = taille_zone+ zones_libres->size;
				zone_l->next = zones_libres->next;
				zones_libres = zone_l;
			}*/
			else	/* sinon on cree une zone libre a la place de la zone occupee*/
			{
				zone_l = (struct fb*) zone_o;
				zone_l->size = taille_zone;
				zone_l->next = adr_zl;
				pre_adr_zl->next = zone_l;
			}
		}
	}
}
/* procedure qui recoit en parametre l adresse d une zone allouee et renvoie le maximum d octets que l utilisateur peut stocker dans la zone */
size_t mem_get_size(void *zone){
	struct ob* zone_o = (struct ob*) ((void*)zone - sizeof(struct ob));
	struct fb * adr_zl = zones_libres;
	char * adr_fin = (char*)((void*)zone + zone_o->size);
	size_t size;

	while(adr_zl != NULL && adr_fin == (char*) adr_zl) /* on cherche une zone libre juste apres la zone allouee */
	{
		adr_zl = adr_zl->next;
	}
	if(adr_zl==NULL) /* il n y a pas de zone libre disponible apres la zone allouee*/
	{
		size = zone_o->size - sizeof(struct ob);
	}
	else	/* on peut utiliser la zone libre qui se trouve apres*/
	{		
		size = zone_o->size - sizeof(struct ob) + adr_zl->size; 
	}

	return (size_t) size;
}

/* affiche l etat de la memoire */
void mem_show(void (*print)(void *, size_t, int free)){
	char* adr_courante = memoire;
	char* adr_fin = (char*) ((void*) memoire + taille_memoire); 
	struct fb * adr_zl = zones_libres;	
	struct ob * adr_zo;
	size_t taille_zone;
	int libre;
	while(adr_courante != adr_fin)
	{
		if(adr_courante == (char *) adr_zl) /* On rencontre une zone libre */
		{
			libre = 1;
			taille_zone = adr_zl->size;
			adr_zl = adr_zl->next;
		}
		else /* On rencontre une zone occupee */
		{
			libre = 0;
			adr_zo = (struct ob*) adr_courante;
			taille_zone = adr_zo->size;
		}
		(*print)(adr_courante,taille_zone,libre);
		adr_courante = (char*)((void*)adr_courante + taille_zone);	
	}
}

void mem_fit(mem_fit_function_t* fit_function){
	mem_fit_function = fit_function;
}

struct fb* mem_fit_first(struct fb* tete_libres, size_t size){
	struct fb* adr_courante = tete_libres;
	while(adr_courante != NULL && adr_courante->size < size + sizeof(size))
	{
		adr_courante = adr_courante->next;
	}
	return adr_courante;
}
	
struct fb* mem_fit_best(struct fb* tete_libres, size_t size){
	struct fb* adr_courante = tete_libres;
	struct fb* adr_min=NULL;
	size_t taille_min=taille_memoire;
	while(adr_courante != NULL){
		if(adr_courante->size < size + sizeof(size) && adr_courante->size < taille_min )
		{
			taille_min = adr_courante->size;
			adr_min = adr_courante;
		}
	}
	return adr_min;
}



