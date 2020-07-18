//Author : CHABROUX Alexandre & BIENABE Willy 

//Voici la ligne de commande pour compiler le code
//gcc -std=c99 Feistel_CHABROUXAlexandre-BIENABEWilly.c -o Feisel

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

#define NBR_RONDES = 20;
#define LONGUEUR_BLOCS = 64;
#define LONGUEUR_CLE = 32;

void encrypte (bool key[], bool msg[], bool * encrypt) {
	
	int i;
	
	// Découpage de message
	bool tabL[LONGUEUR_CLE];
	bool tabR[LONGUEUR_CLE];
	for (i=0; i<LONGUEUR_CLE; i++) {
		tabL[i] = msg[i];
	}
	for (i=LONGUEUR_CLE; i<LONGUEUR_BLOCS; i++) {
		tabR[i-LONGUEUR_CLE] = msg[i];
	}

	// Boucle des rondes
	for(int k=0; k<NBR_RONDES; k++) {
		
		// Encryptage de left
		for (i=0; i<LONGUEUR_CLE; i++) {
			tabL[i] = tabL[i]^key[i];
		}
		
		// XOR de left et right
		bool tabRslt[LONGUEUR_CLE];
		for (i=0; i<LONGUEUR_CLE; i++) {
			tabRslt[i] = tabL[i]^tabR[i];
		}
		
		// Réaffectation gauche droite
		for (i=0; i<LONGUEUR_CLE; i++) {
			tabL[i] = tabR[i];
			tabR[i] = tabRslt[i];
		}
	}
	
	// Message encrypté
	cout << "encrypt :" << endl;
	for (i=0; i<LONGUEUR_BLOCS; i++) {
		if (i<LONGUEUR_CLE)
			encrypt[i] = tabL[i];
		else
			encrypt[i] = tabR[i-LONGUEUR_CLE];
		cout << encrypt[i] << " ";
	}
	cout << endl;
}

void decrypte (bool key[], bool encrypt[], bool * decrypt) {

	int i;
	
	// Découpage de message
	bool tabL[LONGUEUR_CLE];
	bool tabR[LONGUEUR_CLE];
	for (i=0; i<LONGUEUR_CLE; i++) {
		tabL[i] = encrypt[i];
	}
	for (i=LONGUEUR_CLE; i<LONGUEUR_BLOCS; i++) {
		tabR[i-LONGUEUR_CLE] = encrypt[i];
	}

	// Boucle des rondes
	for(int k=0; k<NBR_RONDES; k++) {
		
		// XOR de left et right
		bool tabRslt[LONGUEUR_CLE];
		for (i=0; i<LONGUEUR_CLE; i++) {
			tabRslt[i] = tabL[i]^tabR[i];
		}
		
		// Decryptage
		for (i=0; i<LONGUEUR_CLE; i++) {
			tabR[i] = tabRslt[i]^key[i];
		}
		
		// Réaffectation gauche droite
		bool tmp;
		for (i=0; i<LONGUEUR_CLE; i++) {
			tmp = tabL[i];
			tabL[i] = tabR[i];
			tabR[i] = tmp;
		}
	}
	
	// Message décrypté
	cout << "decrypt :" << endl;
	for (i=0; i<LONGUEUR_BLOCS; i++) {
		if (i<LONGUEUR_CLE)
			decrypt[i] = tabL[i];
		else
			decrypt[i] = tabR[i-LONGUEUR_CLE];
		cout << decrypt[i] << " ";
	}
	cout << endl;
}


int main (int argc, char ** argv) {

	srand(time(NULL));
	int i;
	
	// Initialisation des tableaux
	bool msg[LONGUEUR_BLOCS], key[LONGUEUR_CLE], encrypt[LONGUEUR_BLOCS], decrypt[LONGUEUR_BLOCS];
	
	// Initialisation et affichage du message
	cout << "Le message est : " << endl;
	for (i=0; i<LONGUEUR_BLOCS; i++) {
		msg[i] = rand()%2;
		cout << msg[i] << " " ;
	}
	cout << endl;
	
	// Initialisation de la clef
	for (i=0; i<LONGUEUR_CLE; i++) {
		key[i] = rand()%2;
	}
	
	// Encryptage du message
	encrypte(key, msg, encrypt);
	
	// Décryptage du message encrypté
	decrypte(key, encrypt, decrypt);
}

