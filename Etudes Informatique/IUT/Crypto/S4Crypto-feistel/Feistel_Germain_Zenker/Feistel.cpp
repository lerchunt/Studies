#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>



using namespace std;





void encoder(bool cle[32], bool block[32]) {
	for (int i=0; i< 32; i++) 
		block[i] = (block[i] ^ cle[i]);
}



void decoup( bool left[32], bool right[32], bool mot[64], bool temp[64])
{
	int i=0;
	
	for ( i=0; i<32; i++) 
			left[i] = mot[i];
	for ( i=32; i<64;i++)
	{	
			right[i-32] = mot[i];
			temp[i-32] = mot[i];
		}
	
}

void fill (bool left[32], bool right[32], bool mot[64])
{
	int j=0;
	for (j = 0; j<32; j++) 
				mot[j] = right[j];
	for (j=32;j<64;j++)
				mot[j] = left[j-32];
		
}

void affiche ( bool mot[])
{
	for ( int t =0; t< 64;t++)
	cout << mot[t] ;
	
	cout << endl;
	
}
void inverse(bool left[32], bool right[32], bool temp[32])
{
	for ( int i =0;i< 32; i++)
	{
		right[i] = left[i] ^ temp[i];
		left[i] = temp[i];
		
	}
	
}

void decode( bool mot[64])
{
	for (int i=0;i < 32;i++)
		mot[i] = !mot[i];
}
int main(int argc, char* argv[])
{
	
	ifstream fichier;
	char c;
	fichier.open("feistel.txt", ios::in);
	bool clePrimaire[32];
	bool left[32];
	bool right[32];
	bool temp[64]; // temp sert ici a servir de variable temporaire pour la partie droite.
	bool cleSecondaire[32];
	int ronde =11;
		
  
	bool mot[64];
	int j=0;
	for (int i =0; i<32; i++)
		clePrimaire[i] = true;
	while(true) {

    //Lit un caractere du fichier
    fichier >> c;
    
    
    if ( c == '1')
    mot[j] = true;
    
    if ( c == '0')
    mot[j] = false;

    
    j++;
    if(fichier.eof()) {
		break;
	}
}
	
fichier.close();
// on code
for (int i =0; i< ronde; i++){
		
		//on découpe temp = la partie droite
		decoup(left, right, mot, temp);
		//encodage de la partie droite : temp est la variable temporaire pour la partie droite
		encoder(clePrimaire, right);
		encoder(clePrimaire, temp);
		// on inverse Càd que la partie droite = la partie gauche XOR la partie droite ( ici temp = partie droite)  et  la partie gauche = la partie droite
		inverse(left, right, temp);
		
		//remplissage du mot avec les blocks
		fill(left,right,mot);
		
		
}

//affiche(mot);
//affiche(mot);

ofstream fichier2("f_crypt.txt", ios::out | ios::trunc);

for (int i =0; i< 64; i++)	
	fichier2 << mot[i];

fichier.close();


// on décode
for (int i =0; i< ronde; i++){
		
		//on découpe temp = la partie droite
		decoup(left, right, mot, temp);
		//encodage de la partie droite : temp est la variable temporaire pour la partie droite
		encoder(clePrimaire, right);
		encoder(clePrimaire, temp);
		// on inverse Càd que la partie droite = la partie gauche XOR la partie droite ( ici temp = partie droite)  et  la partie gauche = la partie droite
		inverse(left, right, temp);
		
		//remplissage du mot avec les blocks
		fill(left,right,mot);	
}


	
decode(mot);
ofstream fichier3("f_decrypt.txt", ios::out | ios::trunc);

for (int i =0; i< 64; i++)	
	fichier3 << mot[i];

fichier.close();	
//affiche(mot);
return 0;
}
