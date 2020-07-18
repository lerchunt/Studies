#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;




void feistel(string & f1, string & f2, string k)
{
    string tmp=f1;
    f1=f2;
    f2="";
    int decalage=k[0]-'a';
for(unsigned int i=0; i< tmp.size(); i++)
    {


        char lettreLue;
        int codeLettreLue;
        int codeLettreChiffree;

        lettreLue=tmp[i];

        //Convertir le caractere en entier compris entre 0 et 25
        //avec 'a'=0 ... z='25'
        codeLettreLue=lettreLue-'a';
        //Ajoute le décalage (la clé)
        codeLettreChiffree=(codeLettreLue+decalage)%26;
        //Reconvertit le code du chiffré vers un
        //caractère (en ajoutant le code ascii de 'a' qui vaut 97)
        f2+=codeLettreChiffree+'a';


    }

}
//~ 
void decoupe(ifstream & f,int l, string &f1, string &f2)
{


    for(int i=0; i<l ; i++)
    {
        char lettreLue;

        f >> lettreLue;
        if(i<= (l/2))
            f1+=lettreLue;
        else
        {
            f2+=lettreLue;
        }
    }


}

string recolle(string f1, string f2)
{
	return f1+f2;
}


int main(int argc,char** argv) {

    ifstream fichier;
    string cle;
    int ronde ;
    int longueur=0;
    string f1="";
    string f2="";
    string sr="";



    if(argc<4) {
        cout<<"Usage: "<<argv[0]<<" <fichier> <cle (un caractere en minuscule)> <ronde>"<<endl;
        return -1;
    }

    //Récupère les arguments
	fichier.open(argv[1],ios::in | ios::ate);
    if(fichier.bad()) {
        cout << "Impossible d'ouvrir "<<argv[1]<<endl;
        return -1;
    }

    longueur=fichier.tellg();
    fichier.seekg(0);
	if (longueur<1)
		return -1;
	
    cle=argv[2];


	ronde=atoi(argv[3]);
	
    decoupe(fichier,longueur,f1,f2);
	for(int i=0; i<ronde; i++)
	{
		feistel(f1,f2,cle);
	}
		sr=recolle(f1,f2);
		cout<<sr<<endl;
    return 0;
}


/*

for (int i = 0; i< nbRondes ; i++ ) {

	key k;
	message m ;

	decoupere(m); (done)

	chiffreLeft = right;
	chiffreRight = encrypt(left, k,i)    (+right)

	m = recoller(chiffreLeft, chiffreRight);

*/
