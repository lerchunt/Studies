#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h> 

using namespace std;
#define MSG_SIZE 64
#define RONDE 4

void showBloc(bool * b, int size){
	for (int i = 0; i < size; i++)
		cout << b[i];
}

void copy(bool *b1, bool *b2, int size){
	for (int i = 0; i < size; i++)
		b1[i]=b2[i];
}

void XOR(bool * b1, bool *b2, bool * b3, int size){
	for (int i = 0; i < size; i++)
		b1[i] = b2[i] xor b3[i];

}

void function(bool * res, bool* b, bool* cle, int size){
	//on peut coder n'importe quelle fonction de cryptage
	XOR(res, b, cle, size);
}

void festeil(bool *blocL, bool *blocR, bool *cle, int size){
	bool blocRTmp[size];
	bool blocLTmp[size];
	
	copy(blocRTmp, blocR, size);
	copy(blocLTmp, blocL, size);
	for (int i = 0; i < RONDE; i++)
	{
		copy(blocL, blocRTmp, size);

		//on met le résultat de la fonction dans blocF
		bool blocF[size];
		function(blocF, blocRTmp, cle, size);
		XOR(blocR, blocLTmp, blocF, size);

		copy(blocRTmp, blocR, size);
		copy(blocLTmp, blocL, size);
	}

	

}

void chiffrage(bool *blocL, bool *blocR, bool *cle, int size){
	cout << "Avant chiffrage" << endl;
	showBloc(blocL, size);
	cout << "   ";
	showBloc(blocR, size);
	cout << endl;

	festeil(blocL, blocR, cle, size);

	cout << "Apres chiffrage" << endl;
	showBloc(blocL, size);
	cout << "   ";
	showBloc(blocR, size);
	cout << endl;

}

void deChiffrage(bool *blocL, bool *blocR, bool *cle, int size){
	cout << "Avant déchiffrage" << endl;
	showBloc(blocL, size);
	cout << "   ";
	showBloc(blocR, size);
	cout << endl;

	festeil(blocL, blocR, cle, size);

	bool blocTmp[size];	
	copy(blocTmp, blocR, size);
	copy(blocR, blocL, size);
	copy(blocL, blocTmp, size);

	cout << "Apres déchiffrage" << endl;
	showBloc(blocL, size);
	cout << "   ";
	showBloc(blocR, size);
	cout << endl;
}

int main(int argc, char const *argv[])
{
	srand (time(NULL));

	bool bloc[MSG_SIZE];
	bool blocL[MSG_SIZE/2];
	bool blocR[MSG_SIZE/2];
	bool cle[32];

	//message aléatoire
	for(int i = 0; i <  MSG_SIZE; i++){
		bloc[i] = rand()%2;
	}
	//clé aléatoire
	for(int i = 0; i <  MSG_SIZE/2; i++){
		cle[i] = rand()%2;
	}

	//séparation du message en deux
	for(int i = 0; i <  MSG_SIZE; i++){
		if(i<MSG_SIZE/2)
			blocL[i]=bloc[i];
		else
			blocR[i-MSG_SIZE/2]=bloc[i];
	}
	
	chiffrage(blocL, blocR, cle, MSG_SIZE/2);
	cout << "===========================================" << endl;
	deChiffrage(blocR, blocL, cle, MSG_SIZE/2);


	return 0;
}
