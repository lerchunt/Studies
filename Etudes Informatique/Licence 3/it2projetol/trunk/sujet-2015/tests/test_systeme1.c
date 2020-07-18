/*
 *   Ce fichier fait partie d'un projet de programmation donné en Licence 3 
 *   à l'Université de Bordeaux
 *
 *   Copyright (C) 2015 Adrien Boussicault
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


#include "automate.h"
#include "outils.h"
#include "ensemble.h"
#include "rationnel.h"

#include <stdarg.h>



int test_systeme(){

		Automate* automate = creer_automate();

		ajouter_etat_final( automate, 8 );
		ajouter_etat_final( automate, 10 );
		ajouter_etat_final( automate, 6 );
		ajouter_etat_initial( automate, 0 );
		ajouter_etat_final( automate, 2 );
		ajouter_etat_final( automate, 3 );
		
        ajouter_transition( automate, 0, 'a', 2 );
		ajouter_transition( automate, 0, 'b', 1 );
		ajouter_transition( automate, 1, 'a', 3 );
		ajouter_transition( automate, 1, 'b', 0 );
		ajouter_transition( automate, 2, 'a', 2 );
		ajouter_transition( automate, 2, 'b', 3 );
		ajouter_transition( automate, 3, 'a', 2 );
		ajouter_transition( automate, 3, 'b', 3 );
		ajouter_transition( automate, 7, 'a', 1 );
		ajouter_transition( automate, 6, 'a', 1 );
		ajouter_transition( automate, 1, 'a', 10 );
		ajouter_transition( automate, 10, 'a', 10 );

    print_systeme(systeme(automate),taille_ensemble(get_etats(automate)));
    return 1;
}

int main(){
    test_systeme();

	return 0;
}
