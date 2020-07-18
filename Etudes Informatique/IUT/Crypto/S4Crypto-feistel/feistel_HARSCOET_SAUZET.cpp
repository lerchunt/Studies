#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

int block_size = 8;
int key_size = 4;
int nb_rondes = 12; //Quand on passe un nombre de rondes multiple de 3, le message ne change pas

void xorEncrypt(char* s1, char* s2)
{
	for(int i=0; i < block_size/2; i++)
		s1[i] = s1[i] ^ s2[i];

}

void encrypt(char* m, char* key)
{
	//On peut mettre la fonction de cryptage que l'on veut
	xorEncrypt(m,key);
}


void ronde(char* LBlock, char* RBlock, char* cle)
{
	char tmp[block_size/2] ; //On sauvegarde le bloc de droite
	for(int i =0; i < block_size/2; i++)
		tmp[i] = RBlock[i];

	encrypt(RBlock, cle); // f 
	xorEncrypt(RBlock, LBlock);

	for(int i =0; i < block_size/2; i++)
		LBlock[i] = tmp[i]; //On met le bloc droit de départ dans le bloc gauche

}

int main(int argc,char** argv) {

    ifstream fichier;
    ofstream output;
    char* cle;

    if(argc<3) {
        cout<<"Usage: "<<argv[0]<<" <fichier> <cle (chaine de caracteres minuscules)>"<<endl;
        return -1;
    }

    //Récupère les arguments
    fichier.open(argv[1],ios::binary | ios::ate);
    if(fichier.bad()) {
        cout << "Impossible d'ouvrir "<<argv[1]<<endl;
        return -1;
    }

    cle = argv[2];

	int filesize = fichier.tellg(); //On récupère la position du curseur une fois à la fin, donc la taille
	fichier.seekg(0); //retour au début

	char contenu[filesize];	
	char crypted[filesize];

	for(int i =0; !fichier.eof(); i++) //On recopie le fichier dans contenu
		fichier >> contenu[i];
	
	int nb_blocks = filesize/block_size + 1; //On calcule le nombre de blocs
	char blocks[nb_blocks][block_size];

	for(int i=0; i < nb_blocks; i++) //remplissage des blocs
		for(int j=0; j < block_size; j++)
			blocks[i][j] = contenu[block_size*i+j];


	for(int i=0; i < nb_blocks; i++)
	{
		char LBlock[block_size/2], RBlock[block_size/2];

		for(int j=0; j < block_size/2; j++) //On divise le bloc en deux
			LBlock[j] = blocks[i][j];
		for(int j = block_size/2; j < block_size; j++)
			RBlock[j - block_size/2] = blocks[i][j];


		for(int j = 0; j < nb_rondes ; j++) 
			ronde(LBlock, RBlock,cle); 
	

		for(int j = 0; j < block_size/2; j++) //On ajoute les blocs cryptés dans la chaine crypted
			crypted[block_size*i + j] = LBlock[j];
		for(int j = block_size/2; j < block_size; j++)
			crypted[block_size*i + j] = RBlock[j  - block_size/2];
		
	}

	output.open("crypted.txt");
	for(int i = 0; i < filesize; i++)
	{
		printf("%c\n", crypted[i] );
		output << crypted[i];
	}	
		printf("\n" );


    return 0;
}
