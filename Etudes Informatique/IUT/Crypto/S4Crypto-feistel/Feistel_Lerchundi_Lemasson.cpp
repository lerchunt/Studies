#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

//Fonction qui génère les sous-clés
void genKey(bool k[],int j){
	int i;
	bool newkey[8];
	
	cout << "la cle intermediaire "<<endl;
	for(i=1*j;i<=j*8;i++){
		newkey[i%8]=k[i-1];
		cout << newkey[i%8];
	}
	cout << endl;
	for(i=0;i<32;i++)
	{
		k[i]=newkey[i%8];
	}
}
int main(int argc,char* argv[]){
	bool key[32];
	bool cle[32];
	int i;
	int j;
	
	//Notre bloc de 64
	bool tab[64];
	
	//On initialise les clés
	cout << "la cle :" << endl;
	for(i=0;i<32;i++){
		if(i%3==0)
			key[i]=true;
		else
			key[i]=false;
		cout<<key[i];
		cle[i]=key[i];
	}
	cout<<endl;

	cout << "le bloc :" << endl;
	for(i = 0; i<64;i++){
		if (i<32)
			tab[i] = false;
		else
			tab[i] = true;
		cout<<tab[i];
		
	}
	cout<<endl;
	cout<<endl;
	
	for(j=1;j<=4;j++)
	{
		cout << "Le tour n" << j << endl;
		for(i=0;i<32;i++)
			cle[i]=key[i];
		
		//Genération de clé
		genKey(cle,j);
		
		//Bloc de gauche
		bool l[32];
		for(i=0;i<32;i++)
			l[i]=tab[i];
		
		//Bloc de droite
		bool r[32];
		for(i=32;i<64;i++)
			r[i-32]=tab[i];

		cout << "premier xor sur l :" << endl;
		for (i=0;i<32;i++){
			l[i]= l[i] xor r[i];
		}
		
		for(i = 0; i<32;i++)
			cout << l[i];
		cout<<endl;
		
		cout<<"cryptage de l"<<endl;
		
		//On crypte l avec la clé
		for(i=0;i<32;i++){
			l[i]= l[i] xor cle[i];
			cout<<l[i];
		}
		cout<<endl;
		
		cout<<"le bloc crypte "<<endl;
		//On passe le bloc de gauche à droite et vice versa.
		for(i=0;i<64;i++){
			if (i<32)
				tab[i]=r[i];
			else
				tab[i]=l[i-32];
			cout<<tab[i];
		}
		cout<<endl;
		cout << endl;
	}
		
    return 0;
}
