#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

string Cesar(string s, string c)
{ 
  string cle;
  cle=c;
  string Sc;
  int decalage=cle[0]-'a';

  //Lit le string caractère par caractère
  for(unsigned int i=0;i<s.size();i++) {
    char lettreLue;
    int codeLettreLue;
    char lettreChiffree;
    int codeLettreChiffree;

    //Lit un caractere du string
    lettreLue=s.at(i);

    //Convertir le caractere en entier compris entre 0 et 25
    //avec 'a'=0 ... z='25'
    codeLettreLue=lettreLue-'a';
	//Ajoute le décalage (la clé)
    codeLettreChiffree=(codeLettreLue+decalage)%26;
	//Reconvertit le code du chiffré vers un 
	//caractère (en ajoutant le code ascii de 'a' qui vaut 97)
    lettreChiffree=codeLettreChiffree+'a';
    
    Sc=Sc+lettreChiffree;
   
  }
  return Sc;
}

int getTaille(ifstream &fichier)
{
	char lettreLue;
	int j=0;
	while (true)
	{
		fichier >> lettreLue;
		j++;
		//Fin de fichier ?
		if(fichier.eof()) {
			break;
		}
	}
	return j;
}


int main(int argc,char** argv)
{  
  ifstream fichier;
  string cle;

  if(argc<3) {
    cout<<"Usage: "<<argv[0]<<" <fichier> <cle (chaine de caracteres minuscules)>"<<endl;
    return -1;
  }
	cle=argv[2];
	
	for(int rond=0;rond<4;rond++)
	{

	  //Récupère les arguments
	  fichier.open(argv[1],ios::in);
	  if(fichier.bad()) {
		cout << "Impossible d'ouvrir "<<argv[1]<<" en lecture"<<endl;
		return -1;
	  }

	  int taille = getTaille(fichier);
	  string S1="";
	  string S2="";
	  char lettreLue;
	  for(int i=0; i<taille;i++)
	  {
		fichier >> lettreLue;
		if(i<taille/2)
			S1=S1+lettreLue;
		else
			S2=S2+lettreLue;
	  }
	  
	  S2=Cesar(S2,cle);
	  
	  fichier.close();
	  fichier.open("test.txt",ios::out | ios::trunc);
	  if(fichier.bad()) {
		cout << "Impossible d'ouvrir "<<argv[1]<<" en ecriture"<<endl;
		return -1;
	  }
	  fichier << S2 << S1;
	  fichier.close();
	}
  return 0;
}
