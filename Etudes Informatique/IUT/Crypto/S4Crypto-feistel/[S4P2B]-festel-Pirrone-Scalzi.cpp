#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#define NB_ROUND 5
#define NB_KEY 4

using namespace std;

bool crypt(bool a, bool b){
	return a=(b)?a:!a;
}

int main(int argc,char** argv) {

	ifstream fichier;

	if(argc<2) {
		cout<<"Usage: "<<argv[0]<<endl;
		return -1;
	}
	bool bytes[2048], temp[2048];

	//Récupère les arguments
	fichier.open(argv[1],ios::in);
	if(fichier.bad()) {
		cout << "Impossible d'ouvrir "<<argv[1]<<endl;
		return -1;
	}

	int position=0;
	bool key[NB_KEY][8] = {
		{0,0,1,0,1,1,0,0},
		{1,1,0,1,0,0,1,1},
		{1,0,0,1,1,0,0,1},
		{0,1,0,0,1,0,1,1}
	};

	while(true) {
		char lettreLue;
		fichier >> lettreLue;

		for (int i=0; i<8; ++i)
			bytes[ (position+1)*8 - i -1 ] = ( ( (lettreLue >> i) & 1 ) == 1 ) ? true : false;

		if(fichier.eof())
			break;

		position++;
	}


	//CRYPTAGE

	for (int j=0; j<NB_ROUND; ++j){

		// Déplacement R non crypté sur gauche
		for (int i = position * 4; i< position * 8; ++i)
			temp[i - position * 4 ] = bytes[i];

		// Application de la clé sur R
		for (int i = position * 4; i< position * 8; ++i)
			bytes[i] = (bytes[i] ^ key[ j%NB_KEY ][ i%8 ]);

		// L XOR (R crypté)
		for (int i = 0; i< position * 4; ++i)
			temp[i + position * 4 ] = (bytes[i] ^ bytes[ i + position * 4 ]);

		// Application de crypt
		for (int i = position * 4; i< position * 8; ++i)
			temp[i] = crypt( temp[i] ,i%2);

		// Copie
		for (int i = 0; i< position * 8; ++i)
			bytes[i] = temp[i];
	}


	string encryption = "";
	int c;
	for (int i = 0; i<position *8; i+=8){
		c=0;
		for (int j = 0; j<8; ++j)
			c = (c << 1) + bytes[i+j];
		encryption += (char) c;
	}

	cout << encryption << endl;

	return 0;
}
