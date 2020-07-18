#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

string encrypte(string chaine1, string chaine2);
string decalage(string bloc, string &bloc_gauche, string &bloc_droit, int taille_bloc, string cle);

int main(int argc,char** argv) {

    ifstream fichier;
    string cle;
	int taille_bloc = 8;
	int nb_boucles = 12;
	int taille_cle = 4;
	string contenu;	
	string message;
	

    if(argc<3) {
        cout<<"Usage: "<<argv[0]<<" <fichier> <cle (chaine de caracteres minuscules)>"<<endl;
        return -1;
    }

    fichier.open(argv[1],ios::binary | ios::ate);
    if(fichier.bad()) {
        cout << "Impossible d'ouvrir "<<argv[1]<<endl;
        return -1;
    }

	cle = argv[2];

	int taille_fichier = fichier.tellg();
	cout << "La taille du fichier : " << taille_fichier << endl;

	fichier.seekg(0); //On déplace le curseur au début


	for(int i =0; !fichier.eof(); i++)
		fichier >> contenu[i];
	
	int nb_blocs = taille_fichier/taille_bloc + 1;
	string blocs[nb_blocs];


	for(int i=0; i < nb_blocs; i++)
		for(int j=0; j < taille_bloc; j++)
			if(contenu[taille_bloc*i+j] != '\0')
				blocs[i] += contenu[taille_bloc*i+j];

	for(int i = 0; i < nb_blocs; i++)
		cout << blocs[i] << endl;

	for(int i=0; i < nb_blocs; i++)
	{
		string bloc_gauche, bloc_droit;
		for(int j = 0; j < nb_boucles ; j++){
			decalage(blocs[i], bloc_gauche, bloc_droit, taille_bloc, cle); }
	
		message+= bloc_gauche;
		message += bloc_droit;

		
	}

	cout << "Message :" << message << endl;	

    return 0;
}

string encrypte(string chaine1, string chaine2)
{
	string message;
	for(int i=0; i < chaine1.size(); i++)
		message[i] = chaine1[i] ^ chaine2[i];

	return message;
}

void decalage(string bloc, string &bloc_gauche, string &bloc_droit, int taille_bloc, string cle)
{


	for(int j=0; j < taille_bloc/2 && j < bloc.size(); j++)
		bloc_gauche += bloc[j];
	for(int j = taille_bloc/2; j < taille_bloc && j < bloc.size(); j++)
		bloc_droit += bloc[j];
	bloc_gauche = bloc_droit; 
	bloc_droit = encrypte(bloc_droit, cle); 
	bloc_droit = encrypte(bloc_droit, bloc_gauche);

}
