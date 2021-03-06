/*
 *   Ce fichier fait partie d'un projet de programmation donné en Licence 3 
 *   à l'Université de Bordeaux.
 *
 *   Copyright (C) 2015 Giuliana Bianchi, Adrien Boussicault, Thomas Place, Marc Zeitoun
 *
 *    This Library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This Library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "rationnel.h"
#include "ensemble.h"
#include "automate.h"
#include "parse.h"
#include "scan.h"
#include "outils.h"

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int yyparse(Rationnel **rationnel, yyscan_t scanner);
//int numero_courrent = 1; // Le numéro qui sera donné à la lettre à numéroter
Rationnel *rationnel(Noeud etiquette, char lettre, int position_min, int position_max, void *data, Rationnel *gauche, Rationnel *droit, Rationnel *pere)
{
   Rationnel *rat;
   rat = (Rationnel *) malloc(sizeof(Rationnel));

   rat->etiquette = etiquette;
   rat->lettre = lettre;
   rat->position_min = position_min;
   rat->position_max = position_max;
   rat->data = data;
   rat->gauche = gauche;
   rat->droit = droit;
   rat->pere = pere;
   return rat;
}

Rationnel *Epsilon()
{
   return rationnel(EPSILON, 0, 0, 0, NULL, NULL, NULL, NULL);
}

Rationnel *Lettre(char l)
{
   return rationnel(LETTRE, l, 0, 0, NULL, NULL, NULL, NULL);
}

Rationnel *Union(Rationnel* rat1, Rationnel* rat2)
{
   // Cas particulier où rat1 est vide
   if (!rat1)
      return rat2;

   // Cas particulier où rat2 est vide
   if (!rat2)
      return rat1;
   
   return rationnel(UNION, 0, 0, 0, NULL, rat1, rat2, NULL);
}

Rationnel *Concat(Rationnel* rat1, Rationnel* rat2)
{
   if (!rat1 || !rat2)
      return NULL;

   if (get_etiquette(rat1) == EPSILON)
      return rat2;

   if (get_etiquette(rat2) == EPSILON)
      return rat1;
   
   return rationnel(CONCAT, 0, 0, 0, NULL, rat1, rat2, NULL);
}

Rationnel *Star(Rationnel* rat)
{
   return rationnel(STAR, 0, 0, 0, NULL, rat, NULL, NULL);
}

bool est_racine(Rationnel* rat)
{
   return (rat->pere == NULL);
}

Noeud get_etiquette(Rationnel* rat)
{
   return rat->etiquette;
}

char get_lettre(Rationnel* rat)
{
   assert (get_etiquette(rat) == LETTRE);
   return rat->lettre;
}

int get_position_min(Rationnel* rat)
{
   return rat->position_min;
}

int get_position_max(Rationnel* rat)
{
   return rat->position_max;
}

void set_position_min(Rationnel* rat, int valeur)
{
   rat->position_min = valeur;
   return;
}

void set_position_max(Rationnel* rat, int valeur)
{
   rat->position_max = valeur;
   return;
}

Rationnel *fils_gauche(Rationnel* rat)
{
   assert((get_etiquette(rat) == CONCAT) || (get_etiquette(rat) == UNION));
   return rat->gauche;
}

Rationnel *fils_droit(Rationnel* rat)
{
   assert((get_etiquette(rat) == CONCAT) || (get_etiquette(rat) == UNION));
   return rat->droit;
}

Rationnel *fils(Rationnel* rat)
{
   assert(get_etiquette(rat) == STAR);
   return rat->gauche;
}

Rationnel *pere(Rationnel* rat)
{
   assert(!est_racine(rat));
   return rat->pere;
}

void print_rationnel(Rationnel* rat)
{
    if (rat == NULL)
    {
        printf("∅");
        return;
    }
    
    switch(get_etiquette(rat))
    {
        case EPSILON:
            printf("ε");
            break;
            
        case LETTRE:
            printf("%c", get_lettre(rat));
            break;
            
        case UNION:
            printf("(");
            print_rationnel(fils_gauche(rat));
            printf(" + ");
            print_rationnel(fils_droit(rat));
            printf(")");
            break;
            
        case CONCAT:
            printf("[");
            print_rationnel(fils_gauche(rat));
            printf(" . ");
            print_rationnel(fils_droit(rat));
            printf("]");
            break;
            
        case STAR:
            printf("{");
            print_rationnel(fils(rat));
            printf("}*");         
            break;
            
        default:
            break;
    }
}


Rationnel *expression_to_rationnel(const char *expr)
{
    Rationnel *rat;
    yyscan_t scanner;
    YY_BUFFER_STATE state;

    // Initialisation du scanner
    if (yylex_init(&scanner))
        return NULL;
 
    state = yy_scan_string(expr, scanner);

    // Test si parsing ok.
    if (yyparse(&rat, scanner)) 
        return NULL;
    
    // Libération mémoire
    yy_delete_buffer(state, scanner);
 
    yylex_destroy(scanner);
 
    return rat;
}

void rationnel_to_dot(Rationnel *rat, char* nom_fichier)
{
   FILE *fp = fopen(nom_fichier, "w+");
   rationnel_to_dot_aux(rat, fp, -1, 1);
}

int rationnel_to_dot_aux(Rationnel *rat, FILE *output, int pere, int noeud_courant)
{   
   int saved_pere = noeud_courant;

   if (pere >= 1)
      fprintf(output, "\tnode%d -> node%d;\n", pere, noeud_courant);
   else
      fprintf(output, "digraph G{\n");
   
   switch(get_etiquette(rat))
   {
      case LETTRE:
         fprintf(output, "\tnode%d [label = \"%c-%d\"];\n", noeud_courant, get_lettre(rat), rat->position_min);
         noeud_courant++;
         break;

      case EPSILON:
         fprintf(output, "\tnode%d [label = \"ε-%d\"];\n", noeud_courant, rat->position_min);
         noeud_courant++;
         break;

      case UNION:
         fprintf(output, "\tnode%d [label = \"+ (%d/%d)\"];\n", noeud_courant, rat->position_min, rat->position_max);
         noeud_courant = rationnel_to_dot_aux(fils_gauche(rat), output, noeud_courant, noeud_courant+1);
         noeud_courant = rationnel_to_dot_aux(fils_droit(rat), output, saved_pere, noeud_courant+1);
         break;

      case CONCAT:
         fprintf(output, "\tnode%d [label = \". (%d/%d)\"];\n", noeud_courant, rat->position_min, rat->position_max);
         noeud_courant = rationnel_to_dot_aux(fils_gauche(rat), output, noeud_courant, noeud_courant+1);
         noeud_courant = rationnel_to_dot_aux(fils_droit(rat), output, saved_pere, noeud_courant+1);
         break;

      case STAR:
         fprintf(output, "\tnode%d [label = \"* (%d/%d)\"];\n", noeud_courant, rat->position_min, rat->position_max);
         noeud_courant = rationnel_to_dot_aux(fils(rat), output, noeud_courant, noeud_courant+1);
         break;
         
      default:
         assert(false);
         break;
   }
   if (pere < 0)
      fprintf(output, "}\n");
   return noeud_courant;
}

void numeroter_rationnel_aux(Rationnel *rat, int *numero_courrent)
{
	/* Il n'y a que si l'étiquette du rationnel est une lettre qu'on numérote. Si ce n'est pas une lettre, on va chercher le fils gauche et le fils droit pour UNION et CONCAT mais seulement le gauhche pour STAR*/
	
	   switch (get_etiquette(rat)) {
		case LETTRE:
			set_position_min(rat, *numero_courrent);			
			set_position_max(rat,get_position_min(rat));
			*numero_courrent = *numero_courrent + 1;
			break;
		case EPSILON:
			break;
		case UNION:
		case CONCAT:
			numeroter_rationnel_aux(rat->gauche, numero_courrent);
			if (get_etiquette(rat->gauche) == EPSILON)
			{
				set_position_min(rat, rat->droit->position_min);				
			} 
			else {										
				set_position_min(rat, rat->gauche->position_min);								
			}
			
			numeroter_rationnel_aux(rat->droit, numero_courrent);
			if (get_etiquette(rat->droit) == EPSILON)
			{
				set_position_max(rat, rat->gauche->position_max);				
			} 
			else {			
				set_position_max(rat, rat->droit->position_max);				
			}
			break;
		case STAR:
			numeroter_rationnel_aux(rat->gauche, numero_courrent);
			if (get_etiquette(rat->gauche) != EPSILON)
			{			
				set_position_min(rat, rat->gauche->position_min);				
				set_position_max(rat, rat->gauche->position_max);
			}
						
			break;
		default:
			assert(false);
			break;


   }
}


void numeroter_rationnel(Rationnel *rat)
{
	// Le numero qui va servir à numeroter les lettres
	int   numero_courrent = 1; 
	numeroter_rationnel_aux(rat, &numero_courrent);
}

bool contient_mot_vide(Rationnel *rat)
{
	/* On regarde l'étiquette du rationnel. Si on a EPSILON ou STAR, le mot est effaçable. Sinon, on va chercher le fils gauche et le fils droit pour UNION et CONCAT mais seulement le gauhche pour STAR*/
	switch (get_etiquette(rat)) {
		case LETTRE:
				return false;
				break;
		case STAR:
			return true;
			break;
		case UNION:
			return (contient_mot_vide(rat->gauche) || contient_mot_vide(rat->droit));
		case CONCAT:
			return (contient_mot_vide(rat->gauche) && contient_mot_vide(rat->droit));
			break;
		case EPSILON:
			return true;
			break;
		default:
			assert(false);
			break;
	}

}

void premier_aux(Rationnel *rat, Ensemble *e)
{
	/*On ajoute à l'ensemble passé en paramètres les lettres qui peuvent apparaitre en première position de rat.*/
   	switch (get_etiquette(rat)) {
		case LETTRE:
			ajouter_element(e, rat->position_min);
			break;
		case STAR:
			 premier_aux(rat->gauche, e);
			break;
		case UNION:		
			premier_aux(rat->gauche, e);
			premier_aux(rat->droit, e);
			break;
		case CONCAT:
			if (contient_mot_vide(rat->gauche))
			{			
				premier_aux(rat->gauche, e);
				premier_aux(rat->droit, e);
			}
			else {
				 (premier_aux(rat->gauche, e));
			}
			break;
		case EPSILON:
			break;
		default:
			assert(false);
			break;
	}
}

Ensemble *premier(Rationnel *rat)
{
	// Ensemble qui contiendra les premeiers de rat
	Ensemble *e = creer_ensemble(NULL, NULL, NULL) ;
	
	premier_aux(rat, e);
	return e;
}

void dernier_aux(Rationnel *rat, Ensemble *e)
{
	/*On ajoute à l'ensemble passé en paramètres les lettres qui peuvent apparaitre en dernière position de rat.*/
   	switch (get_etiquette(rat)) {
		case LETTRE:
				ajouter_element(e, rat->position_min);								
				break;
		case STAR:
			 dernier_aux(rat->gauche, e);
			break;
		case UNION:		
			dernier_aux(rat->gauche, e);
			dernier_aux(rat->droit, e);
			break;
		case CONCAT:
			if (contient_mot_vide(rat->droit))
			{			
				dernier_aux(rat->gauche, e);
				dernier_aux(rat->droit, e);
			}
			else {
				 dernier_aux(rat->droit, e);
			}
			break;
		case EPSILON:
			break;
		default:
			assert(false);
			break;
	}
}

Ensemble *dernier(Rationnel *rat)
{
	// Ensemble qui contiendra les premeiers de rat
   	Ensemble *e = creer_ensemble(NULL, NULL, NULL) ;
	
	dernier_aux(rat, e);
	return e;
}


void suivant_aux(Rationnel *rat, Ensemble *e,int position)
{
    //ensemble qui contiendra les suivants de rat à partir d'une expression rationnelle
   	switch (get_etiquette(rat)) {
		case LETTRE:
				break;
		case STAR:
            suivant_aux(rat->gauche,e,position);
            if(est_dans_l_ensemble(dernier(rat->gauche),position))
                premier_aux(rat->gauche,e);
			break;
		case UNION:
            if(position<=rat->gauche->position_max)
                suivant_aux(rat->gauche,e,position);
            if(position>=rat->droit->position_min)
                suivant_aux(rat->droit,e,position);
			break;
		case CONCAT:
            if(position<=rat->gauche->position_max)
                suivant_aux(rat->gauche,e,position);
            if(position>=rat->droit->position_min)
                suivant_aux(rat->droit,e,position);
            if(est_dans_l_ensemble(dernier(rat->gauche),position))
                premier_aux(rat->droit,e);
        
			break;
		case EPSILON:
			break;
		default:
			assert(false);
			break;
	}	
}
Ensemble *suivant(Rationnel *rat, int position)
{
   	Ensemble *e = creer_ensemble(NULL, NULL, NULL) ;
	
	suivant_aux(rat, e, position);
	return e;
}

void lettre_from_position_aux(Rationnel *rat, int position, char *lettre){
	//permet d'obtenir la lettre de la feuille en fonction de sa position
	   	switch (get_etiquette(rat)) {
		case LETTRE:
				if (position == rat->position_min)
				{
					*lettre = rat->lettre;
				}									
				break;
		case STAR:
			 lettre_from_position_aux(rat->gauche, position, lettre);
			break;
		case CONCAT:
		case UNION:		
			lettre_from_position_aux(rat->gauche, position, lettre);
			lettre_from_position_aux(rat->droit, position, lettre);
			break;
		case EPSILON:
			break;
		default:
			assert(false);
			break;
	}
}
char lettre_from_position(Rationnel *rat,int position){
   
   char lettre = ' ';
   lettre_from_position_aux(rat, position, &lettre);
   
   return lettre;
   
}

Automate *Glushkov(Rationnel *rat)
{
    int i,j;
    Automate *glu =creer_automate();
    Ensemble *premier_glu = premier(rat);
    
    ajouter_etat_initial(glu,0); // ajout de l'état initial    
    
    for(i=1;i<=rat->position_max;i++) //création des autres états
        ajouter_etat(glu,i);    
    
    Ensemble_iterateur it= premier_iterateur_ensemble(premier_glu);
    
    for(i=1;i<=taille_ensemble(premier_glu);i++)
    {
        ajouter_transition(glu,0,lettre_from_position(rat,get_element(it)),get_element(it));        
        it= iterateur_suivant_ensemble(it);
    }
    /* jusqu'ici je crée tous les états, puis pour tous les premiers, je créé une transition du premier état vers eux */
    
    /*
     *  Pour chaque état de 1 à max, créer une transition de l'état vers chacun de ces suivant.
     */
    for(i=1;i<=rat->position_max;i++)
    {
        it=premier_iterateur_ensemble(suivant(rat,i));

        //verifier si ensemble non vide
        if(iterateur_ensemble_est_vide(it)==0){
			
			for(j=1;j<=taille_ensemble(suivant(rat,i));j++)
			{
				ajouter_transition(glu,i,lettre_from_position(rat,get_element(it)),get_element(it));				
				it= iterateur_suivant_ensemble(it);
			}
		}
    }
    /*
     Pour chacun des derniers => état final
     */
   if (contient_mot_vide(rat))
   {
	   ajouter_etat_final(glu,0);
   }  
    it=premier_iterateur_ensemble(dernier(rat));
    if(iterateur_ensemble_est_vide(it)==0){
    for(j=0;j<taille_ensemble(dernier(rat));j++){
		ajouter_etat_final(glu,get_element(it));
		it= iterateur_suivant_ensemble(it);
	}
        
	}
    
    return glu;
}

bool meme_langage (const char *expr1, const char* expr2)
{
    /*Création de deux automates à partir des exppressions*/
    Rationnel * rat1;
    rat1 = expression_to_rationnel(expr1);
    numeroter_rationnel(rat1);
    Automate * automate1 = Glushkov(rat1);
    
    Rationnel * rat2;
    rat2 = expression_to_rationnel(expr2);
    numeroter_rationnel(rat2);
    Automate * automate2 = Glushkov(rat2);
    
    // On déterminise les automates
    automate1 = creer_automate_deterministe(automate1);
    automate2 = creer_automate_deterministe(automate2);
    
    // On minimise les automates
    automate1 = creer_automate_minimal(automate1);
    automate2 = creer_automate_minimal(automate2);
    
    bool result = true;
    
    // On vérifie s'ils ont les mêmes états initiaux
    if (taille_ensemble(get_initiaux(automate1)) == taille_ensemble(get_initiaux(automate2)) && result == true)
    {
        result = true;
    }
    else{
        result = false;
    }
    
    // On vérifie s'ils ont les mêmes états finaux
    if (taille_ensemble(get_finaux(automate1)) == taille_ensemble(get_finaux(automate2)) && result == true)
    {
        result = true;
    }
    else{
        result = false;
    }
    
    const Ensemble *alphabet1 = get_alphabet(automate1);
    const Ensemble *alphabet2 = get_alphabet(automate2);
    // On vérifie s'ils ont le même alphabet
    if (taille_ensemble(alphabet1) == taille_ensemble(alphabet2) && result == true)
    {
        result = true;
    }
    else{
        result = false;
    }
    
    Ensemble *accessibles1 = accessibles(automate1);
    Ensemble *accessibles2 = accessibles(automate2);
    // On vérifie s'ils ont les mêmes états accéssibles à partir de l'état initial
    if (taille_ensemble(accessibles1) == taille_ensemble(accessibles1) && result == true)
    {
        result = true;
    }
    else{
        result = false;
    }
    
    liberer_ensemble(accessibles1);
    liberer_ensemble(accessibles2);
    
    const Ensemble *etats1 = get_etats(automate1);
    const Ensemble *etats2 = get_etats(automate2);
    
    if (taille_ensemble(etats1) == taille_ensemble(etats2) && result == true)
    {
        /* Les ensembles qui sont accéssibles en partant d'un état X et lisant une lettre y*/
        Ensemble * delta1;
        Ensemble * delta2;
        
        Ensemble_iterateur it = premier_iterateur_ensemble(alphabet1);
        /*Pour chaque état, dans automate 1 et automate 2, on compare le nombre d'états qu'ils peuvent atteindre en lisant la même lettre*/
        for(int i=0;i<taille_ensemble(alphabet1);i++)
        {
            delta1 = delta(automate1,etats1, get_element(it));
            delta2 = delta(automate2,etats2, get_element(it));
            if (taille_ensemble(delta1) == taille_ensemble(delta2) && result == true)
            {
                it= iterateur_suivant_ensemble(it);
                result = true;
            }
            else {
                result = false;
            }       
            
        }
        liberer_ensemble(delta1);
        liberer_ensemble(delta2);
    }
    
    return result;
}

/*Systeme systeme(Automate *automate)
{
    printf("c'est bon");
    int nb=taille_ensemble(get_etats(automate));
    int nb_lettre=taille_ensemble(get_alphabet(automate));
    
    Systeme sys = malloc(sizeof(Rationnel **)*(nb+1));
    int i,j,k;
    for(i=1;i<=nb;i++)
        sys[i]=malloc(sizeof(Rationnel *)*nb);
    printf("c'est bon");
    //le systeme a nb lignes, et nb+1 colonne
    if(nb_lettre>=0)
        if(nb!=0){
            
            Ensemble_iterateur it= premier_iterateur_ensemble(get_alphabet(automate));
            Ensemble_iterateur it_lettre= premier_iterateur_ensemble(get_etats(automate));
            Ensemble_iterateur it_general=premier_iterateur_ensemble(get_alphabet(automate));
            int nb_lettre=taille_ensemble(get_alphabet(automate));
            printf("c'est bon");
            for(i=1;i<=nb;i++){ //pour chaque etat
                for(j=1;j<=nb;j++){ //on verifie s'il y a transition vers les autres états
                    for(k=1;k<=nb_lettre;k++){ //pour chaque lettre
                        if (est_une_transition_de_l_automate(automate,get_element(it),get_element(it_lettre),get_element(it_general))==1){
                            
                            //remplir au bon endroit
                            sys[i][j]=Lettre(get_element(it_lettre)); // affectation de la lettre
                            
                            printf("c'est bon");
                            it_general= iterateur_suivant_ensemble(it_general);
                        }
                        it_lettre= iterateur_suivant_ensemble(it_lettre); // lettre suivante
                    }
                    it_general=	premier_iterateur_ensemble(get_alphabet(automate));
                    
                }
                
                if(est_un_etat_final_de_l_automate(automate,get_element(it))==1)
                    sys[i][nb+1]= Epsilon();
                    it= iterateur_suivant_ensemble(it);
            }
        }
 //pour chaque état
		//pour chaque transition de cet état syst[etat_actuel][n-ième transition]=lettre puis Etat d'arrivée de la transition
		
	
	return sys;
    
}*/

Systeme systeme(Automate *automate){
    
    Ensemble_iterateur it_etat,it_etat2,it_lettre;
    size_t n = taille_ensemble(get_etats(automate));
    
    Systeme sys = malloc((n+1)*sizeof(Rationnel **));
    for(int i=0;i<n;i++){
        sys[i] = malloc(n*sizeof(Rationnel *));
    }
    
    Ensemble *finaux = automate->finaux;
    for( it_etat = premier_iterateur_ensemble(automate->etats);! iterateur_ensemble_est_vide(it_etat);it_etat = iterateur_suivant_ensemble(it_etat)){
        for(it_etat2 = premier_iterateur_ensemble(get_etats(automate));! iterateur_ensemble_est_vide(it_etat2);it_etat2 = iterateur_suivant_ensemble(it_etat2)){
            for(it_lettre = premier_iterateur_ensemble(automate->alphabet);! iterateur_ensemble_est_vide(it_lettre);it_lettre = iterateur_suivant_ensemble(it_lettre)){
                if(est_une_transition_de_l_automate(automate,get_element(it_etat),get_element(it_lettre),get_element(it_etat2))){
                    if (sys[get_element(it_etat)][get_element(it_etat2)])
                        sys[get_element(it_etat)][get_element(it_etat2)] = Union(sys[get_element(it_etat)][get_element(it_etat2)],Lettre(get_element(it_lettre)));
                    else
                        sys[get_element(it_etat)][get_element(it_etat2)]=Lettre(get_element(it_lettre));
                }
            }     
        }
        if(est_dans_l_ensemble(finaux,get_element(it_etat)))
            sys[get_element(it_etat)][n]=Epsilon();
    }
    return sys;
}

void print_ligne(Rationnel **ligne, int n)
{
   for (int j = 0; j <=n; j++)
      {
         print_rationnel(ligne[j]);
         if (j<n)
            printf("X%d\t+\t", j);
      }
   printf("\n");
}

void print_systeme(Systeme systeme, int n)
{
   for (int i = 0; i <= n-1; i++)
   {
      printf("X%d\t= ", i);
      print_ligne(systeme[i], n);
   }
}

bool arden_possible(Rationnel ** ligne,int numero_variable, int n){
    int cpt=0;
    if(ligne[numero_variable]!=NULL){
        for(int i=0;i<n;i++)
            if(ligne[n]!=NULL){
                cpt++;
                return(cpt>1);
            }
            else{
                return false;
            }
    }
    return false;
}

Rationnel **resoudre_variable_arden(Rationnel **ligne, int numero_variable, int n)
{
    
    Rationnel ** res = malloc((n+1)*sizeof(Rationnel *));
    if(arden_possible(ligne,numero_variable,n))
    for (int i=0;i<=n;i++)
        if(i!=numero_variable){
            if (ligne[i])
                res[i] = Concat(Star(ligne[numero_variable]),ligne[i]);
            else
                res[i] = NULL;
        }
        res[numero_variable]=NULL;
    return res;
}

Rationnel **substituer_variable(Rationnel **ligne, int numero_variable, Rationnel **valeur_variable, int n)
{
    Rationnel ** res = malloc((n+1)*sizeof(Rationnel *));
    for (int i=0;i<=n;i++)
        if (valeur_variable[i])
            res[i] = Concat(ligne[numero_variable],valeur_variable[i]); // Ne pas perdre l'info du facteur
    
    ligne[numero_variable] = NULL;
    for (int i=0;i<=n;i++) {
        if (res[i] && ligne[i])
            res[i] = Union(ligne[i],res[i]);
        if (ligne[i] && !res[i])
            res[i] = ligne[i];
    }  
    return res;

}


Systeme resoudre_systeme(Systeme systeme, int n)
{
    for(int i=n-1;i>=0;i--){
        if(systeme[i][i]!=NULL){
            systeme[i]=resoudre_variable_arden(systeme[i],i,n);
        }
        
        for(int j=0;j<i;j++)
            systeme[j]=substituer_variable(systeme[j],i,systeme[i],n);
    }
    for(int i=1;i<n;i++){
        for(int j=0;j<i;j++)
            systeme[i]=substituer_variable(systeme[i],j,systeme[j],n);
    }

    return systeme;
}

Rationnel *Arden(Automate *automate)
{
   A_FAIRE_RETURN(NULL);
}

