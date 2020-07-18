/*
 * TP Cryptographie : Reseau de Feistel
 * Binome : Paul ESMIEU & Hitinui ROBERT (S4p2C)
 * Date de derniere modification : 16 mars 2014
*/

/*
 * ++++++++++ MODE D'EMPLOI ++++++++++
 * Le programme prend deux arguments : 
 * - un fichier contenant le message a chiffrer
 * - un fichier contenant la cle
 * 
 * Attention : 
 * - le fichier doit contenir un message "en binaire" (sans espaces), 
 * c'est-a-dire une chaine de caracteres avec uniquement des 0 et des 1
 * - le message doit avoir une longueur exacte de 64 caracteres. En 
 * effet, on ne traite qu'un seul bloc de taille 64 qui correspond a la 
 * longueur du message
 * - de même, le fichier contenant la cle doit etre compose d'exactement
 * 32 caracteres (des 0 et des 1 uniquement)
*/ 
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

// -----------------------------------
// 			  CONSTANTES
// -----------------------------------
const int BLOC_LENGTH = 64;
const int KEY_LENGTH = 32;
const int NB_ROUNDS = 12;

// -----------------------------------
// 		DECLARATION DES FONCTIONS
// -----------------------------------
/* genere la cle ki a partir de la cle de depart k et du 
 *  numero de ronde i dans lequel on se trouve */
void generateKey(bool k[], int i, bool ki[]);
/* decoupe le tableau contenant un message m[] en deux taleaux
 * left[] et right[] */
void cutBloc(bool m[], int size, bool left[], bool right[]);
/* effectue une copie du tableau src[] dans le tableau dest[] */
void copyTab(bool src[], bool dest[], int size);
/* effectue un XOR entre la partie de gauche et la cle de numero i et 
 * place le resultat dans result[] */
void f(bool left[], bool ki[], bool result[], int size);
/* effectue le cryptage : on appelle f puis on fait un XOR avec la 
 * partie de droite */
void encrypt(bool left[], bool right[], bool ki[], bool result[], int size);
/* "concatene" deux tableaux de booleens */
void concat(bool left[], bool right[], int size, bool result[]);
/* affiche le contenu d'un tableau */
void displayTab(bool tab[], int size);

// -----------------------------------
// 		FONCTION PRINCIPALE
// -----------------------------------
int main(int argc,char* argv[])
{
	if(argc<3)
	{
		cout<<"Usage: " << argv[0] << " <fichier_mess> <fichier_cle>" << endl;
		return -1;
	}
	
	ifstream file_mess;
	ifstream file_key;
	
	bool mess[BLOC_LENGTH]; // tableau de booleens qui va servir a 
							// stocker le message
	bool key[KEY_LENGTH]; // table de booleens qui va servir a 
						  // stocker la cle

	// on recupere les arguments
	file_mess.open(argv[1], ios::in);
	if(file_mess.bad())
	{
		cout << "Impossible d'ouvrir " << argv[1] << endl;
		return -1;
	}
	file_key.open(argv[2], ios::in);
	if(file_key.bad())
	{
		cout << "Impossible d'ouvrir " << argv[2] << endl;
		return -1;
	}
	
	// on remplit notre tableau de booleens avec le message par lecture
	// du fichier caractere par caractere
	int j = 0;
	while(!file_mess.eof())
	{
		char c;
		file_mess >> c;
		
		if (c == '0')
			mess[j] = 0;
		else if (c == '1')
			mess[j] = 1;
		else
			cout << "Erreur dans l'initialisation du tableau contenant le message." << endl;
		
		j++;
	}
	
	// on remplit notre autre tableau de booleens avec la cle par 
	// lecture du fichier caractere par caractere
	int k = 0;
	while(!file_key.eof())
	{
		char c;
		file_key >> c;
		
		if (c == '0')
			key[k] = 0;
		else if (c == '1')
			key[k] = 1;
		else
			cout << "Erreur dans l'initialisation du tableau contenant la cle." << endl;
			
		k++;
	}
	
	// fermeture des fichiers
	file_mess.close();
	file_key.close();
	
	bool mess_encrypt[BLOC_LENGTH]; // tableau de booleens qui va servir
									// a stocker le message chiffre
	// on l'initialise en faisant une copie du message (non crypte)
	copyTab(mess, mess_encrypt, BLOC_LENGTH);
	
	
	/*	Boucle principale */
	for (int i = 0; i < NB_ROUNDS; i++) {
		bool m[BLOC_LENGTH]; // le bloc sur lequel on travaille
		// on utilise le message obtenu au tour de boucle precedent
		copyTab(mess_encrypt, m, BLOC_LENGTH);
		
		// on genere la cle specifique a cette ronde
		bool keyI[KEY_LENGTH];
		generateKey(key, i, keyI);
		
		// on divise notre bloc en deux
		bool left[BLOC_LENGTH/2];
		bool right[BLOC_LENGTH/2];
		cutBloc(m, BLOC_LENGTH, left, right);
		
		bool left_encrypt[BLOC_LENGTH/2];
		bool right_encrypt[BLOC_LENGTH/2];
		// le bloc de droite est recopie tel quel a gauche
		copyTab(right, left_encrypt, BLOC_LENGTH/2);
		// le bloc de gauche est crypte et place a droite
		encrypt(left, right, keyI, right_encrypt, BLOC_LENGTH/2);
	
		// on "concatene" les deux blocs issus du cryptage
		concat(left_encrypt, right_encrypt, BLOC_LENGTH, mess_encrypt);
	}
	
	// on affiche le message chiffre
	displayTab(mess_encrypt, BLOC_LENGTH);
	
	return 0;
}

// -----------------------------------
// 	  IMPLEMENTATION DES FONCTIONS
// -----------------------------------
void generateKey(bool k[], int i, bool ki[])
{
	// on recopie notre cle de depart
	copyTab(k, ki, KEY_LENGTH);
	// on change la cle ki en mettant un 1 a la ieme position
	ki[i] = 1;
}

void cutBloc(bool m[], int size, bool left[], bool right[])
{
	for (int i = 0; i < size/2; i++)
	{
		left[i] = m[i];
	}
	for (int i = 0; i < size/2; i++)
	{	
		right[i] = m[i+size/2];
	}
}

void copyTab(bool src[], bool dest[], int size)
{
	for (int i = 0; i < size; i++)
	{
		dest[i] = src[i];
	}
}

void f(bool left[], bool ki[], bool result[], int size)
{
	for (int i = 0; i < size; ++i) {
		result[i] = left[i] xor ki[i];
	}
}

void encrypt(bool left[], bool right[], bool ki[], bool result[], int size)
{
	f(left, ki, result, size);
	for (int i = 0; i < size; i++)
	{
		result[i] = result[i] xor right[i];
	}
}

void concat(bool left[], bool right[], int size, bool result[])
{
	// recopiage de la partie gauche
	for (int i = 0; i < size/2; i++)
	{
		result[i] = left[i];
	}
	// recopiage de la partie droite
	for (int i = 0; i < size/2; i++)
	{
		result[i+size/2] = right[i];
	}
}

void displayTab(bool tab[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << tab[i];
	}
	cout << endl;
}
