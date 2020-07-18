#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>

#define LECTEUR 0
#define REDACTEUR 1

#define NB_THREAD_LECT 5
#define NB_THREAD_REDA 5

/* Cellule pour la fifo representant la file d'attente */
typedef struct temp {
	
	int ticket; // Ticket du numero de passage
	int action; // Lecteur ou redacteur
	pthread_cond_t condition ; // Condition de liberation du thread occupant le siege
	struct temp *suivant;
	
} siege_attente;

/* Pour le passage d'argument au thread*/
typedef struct {
	
	sem_t* mutex; 
	
	/* Contiendra les tickets des threads en attente
	 * L'indice correspondant au ticket correspondra à l'indice du tableau
	 * mutex_cond qui correspondra à la condition d'attente du thread
	 */
	int index_condition[NB_THREAD_LECT + NB_THREAD_REDA]; 
	pthread_mutex_t mutex_cond[NB_THREAD_LECT + NB_THREAD_REDA];

} argument_thread;

/*Variable globale*/
int ticket = 0;
siege_attente* file;
int nb_lecteur = 0;
int nb_redacteur = 0;

/*Met en attente un thread lecteur ou redacteur
 * i.e. ajout en queue de file*/
siege_attente* mise_en_attente(int action){
	
	siege_attente* precedent = NULL;
	siege_attente* actuel = file;
	
	/*Prise d'un ticket*/
	ticket++;
	
	/*On cherche la fin de la file*/
	while(actuel!=NULL){
		precedent = actuel;
		actuel = actuel->suivant;
	}
	
	/*precedent est le dernier element de la file*/
	if(precedent==NULL){
		
		/*La file est vide*/
		file = malloc(sizeof(siege_attente));
		file->action = action;
		pthread_cond_init(&(file->condition), NULL);
		file->suivant = NULL;
		file->ticket = ticket;
	
		return file;

	}else{

		/*Creation de la nouvelle cellule*/
		siege_attente* nouveau = malloc(sizeof(siege_attente));
		nouveau->action = action;
		pthread_cond_init(&(nouveau->condition), NULL);
		nouveau->suivant = NULL;
		nouveau->ticket = ticket;
		
		/*Mise en file*/
		precedent->suivant = nouveau;
		
		return nouveau;
	}
}

/*Ajoute le ticket dans un espace vide du tableau index_condition
 * retourne la valeur de l'index de l'espace vide trouve, -1 s'il n'existe pas
*/
int ajouter_condition(int index_condition[NB_THREAD_LECT + NB_THREAD_REDA], int ticket){
	int i = 0;
	int trouve = 0;
	while(i<(NB_THREAD_LECT + NB_THREAD_REDA) && !trouve){
		if(index_condition[i] == -1){
			index_condition[i] = ticket;
			return i;
		}
		i++;
	}
	return -1;
}

/*Afficher l'etat de la file*/
void afficher_file(siege_attente* file){
	
	siege_attente* temp = file;
	
	printf("Etat de la file:\n");
	
	while(temp != NULL){
		
		if(temp->action == LECTEUR){
			printf("ticket: %d -- Je suis un lecteur.\n", temp->ticket);
		}else{
			printf("ticket: %d -- Je suis un redacteur.\n", temp->ticket);
		}
		
		temp = temp->suivant;
	}
}

/*Gestion du thread - mise en file, mise en attente du thread*/
void gestionnaire(sem_t* m, int a, pthread_mutex_t mutex_cond[NB_THREAD_LECT + NB_THREAD_REDA], int index_condition[NB_THREAD_LECT + NB_THREAD_REDA]){

	/*Entree dans la file d'attente*/
	sem_wait(m);
		siege_attente* siege_donne = mise_en_attente(a);
		int index = ajouter_condition(index_condition, siege_donne->ticket);
		pthread_mutex_init(&mutex_cond[index], NULL);
	sem_post(m);
	
	/*Mise en attente du thread*/
	pthread_cond_wait(&(siege_donne->condition), mutex_cond);
	
	/*On libere son index dans le tableau, on en a plus besoin*/
	index_condition[index] = -1;
}

/*Thread lecteur*/
void* lecture(void* arg){
	
	argument_thread* argument = (argument_thread*) arg;
	
	while(1){
		
		/*Demande la ressource et l'attend */
		gestionnaire(argument->mutex, LECTEUR, argument->mutex_cond, argument->index_condition);
		
		/*Fin de la lecture*/
		sem_wait(argument->mutex);
			nb_lecteur--;
		sem_post(argument->mutex);
	}
}

/*Thread redacteur*/
void* ecriture(void* arg){
	
	argument_thread* argument = (argument_thread*) arg;
	
	while(1){
		
		/*Demande la ressource et l'attend */
		gestionnaire(argument->mutex, REDACTEUR, argument->mutex_cond, argument->index_condition);
		
		/*Fin de l'ecriture*/
		sem_wait(argument->mutex);
			nb_redacteur--;
		sem_post(argument->mutex);
	}
}

/*Initialise l'argument des fonctions threads*/
void init_arg_thread(argument_thread* arg, sem_t* m){
	arg->mutex = m;
	int i;
	for(i = 0 ; i<(NB_THREAD_LECT + NB_THREAD_REDA) ; i++){
		arg->index_condition[i] = -1;
	}
}

/*Pre-condition: file non vide*/
void liberer_tete_file(){

	if(file->action == LECTEUR){
		printf("--- Liberation: ticket %d, type: LECTEUR\n", file->ticket);
	}else{
		printf("--- Liberation: ticket %d, type: REDACTEUR\n", file->ticket);
	}
	
	/*Liberation du thread*/
	pthread_cond_signal(&(file->condition));

	/*Sort de la file*/
	file = file->suivant;
}

/*Distribution des ressources à la tete de file
 * Tant que ce sont des lecteurs on libere
 * Si c'est un redacteur, on en libere qu'un seul
 */
void distribuer_ressource(){
	
	/*Affichage de l'etat de la file*/
	afficher_file(file);
	
	printf("\nDistribution de la ressource:\n");
	
	/*File vide ==> on passe*/
	if(file == NULL) return;
	
	/*La file n'est pas vide : si le premier est un lecteur ou redacteur*/
	int action_du_premier = file->action;
	
	switch(action_du_premier){
		case LECTEUR:
			
			while(file != NULL && file->action == LECTEUR){
				liberer_tete_file();
				nb_lecteur++;
			}
			
			break;
		case REDACTEUR:
				liberer_tete_file();
				nb_redacteur++;
			break;
	}
	
	/*Affichage de l'etat de la file*/
	afficher_file(file);
}

int main(){
	
	sem_t mutex;
	sem_init(&mutex, 0, 1);
	file = malloc(sizeof(siege_attente));
	file = NULL;
	
	/*Creation de l'espace memoire pour identifier les threads*/
	pthread_t *tids;
	tids = malloc((NB_THREAD_LECT+NB_THREAD_REDA)*sizeof(pthread_t));
	
	/*Creation des threads lecteur avec les arguments respectifs
	 * En divisant la creation des threads en deux temps on assure une alternance lect/redacteur
	 * afin d'obtenir un test pertinent
	 */
	argument_thread* argument = malloc(sizeof(argument_thread));
	init_arg_thread(argument, &mutex);
	
	int i;
	for(i=0 ; i<NB_THREAD_LECT/2 ; i++){
		pthread_create(&tids[i], NULL, lecture, argument);
	}
	
	for(i=0 ; i<NB_THREAD_REDA/2 ; i++){
		pthread_create(&tids[i], NULL, ecriture, argument);
	}
	
	for(i=NB_THREAD_LECT/2 ; i<NB_THREAD_LECT ; i++){
		pthread_create(&tids[i], NULL, lecture, argument);
	}
	
	for(i=NB_THREAD_REDA/2 ; i<NB_THREAD_REDA ; i++){
		pthread_create(&tids[i], NULL, ecriture, argument);
	}
	
	/*Boucle principale*/
	while(1){
		
		printf("\nAppuyer sur une touche pour continuer\n");
		getchar();

		sem_wait(&mutex);
			/*On distribue la ressource si elle n'est pas occupee i.e. ni lecteur ni redacteur*/
			if(nb_lecteur == 0 && nb_redacteur == 0){
				distribuer_ressource();
			}else{
				printf("La ressource est ocupee par %d lecteur(s) et %d redacteur(s).\n", nb_lecteur, nb_redacteur);
				afficher_file(file);
			}
		sem_post(&mutex);
	}

	/*Wait until every thread ened*/
	for(i=0; i < NB_THREAD_LECT + NB_THREAD_REDA; i++){
		pthread_join(tids[i], NULL);
	}
	
	/*Liberation de la memoire*/
	free(tids);
	free(argument);
	free(file);

	return EXIT_SUCCESS;
}
