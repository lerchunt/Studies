#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

int main(int argc,char** argv) {


/*************************************/
/**                                 **/
/**            VARIABLES            **/
/**                                 **/
/*************************************/
    ifstream fichier;
    int ronde = 10;
    int pos =0;
    bool texte[64] ={0,0,1,0,1,0,1,0,1,0,1,1,1,1,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1};
    bool gauche[32];
    bool droite[32];
    bool cle1[32] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,0,1,1,1,1,1,0,0,0,0,0,1,1};

    bool temp;

/******************************************/
/** L'utilisation d'une seul clé limite  **/
/** le nombre de ronde (il ne faut pas   **/
/** utiliser un nombre multiple de 3.    **/
/** Un autre méthode consisterai a générer **/
/** autant de clé que de rondes aléatoirement **/
/********************************************/



cout << "Texte initial : " << endl;
  for(int i = 0; i<64; i++)
    cout<<texte[i];
  cout << endl << endl;


/*************************************/
/**                                 **/
/**         PARTIE CRYPTAGE         **/
/**                                 **/
/*************************************/
  for(int i = 0; i<ronde ;i++){

        for(int k = 0; k<32;k++){
            gauche[k] = texte[k];
        }
        for(int k =0; k<32;k++){
            droite[k]=texte[k+32];
        }
        //On applique le XOR entre la partie gauche et droite
        for(int k=0;k<32;k++){
                temp = (cle1[k] && !droite[k]) || (!cle1[k] && droite[k]);
                cout << temp;
                gauche[k] = (gauche[k] && !temp) || (!gauche[k] && temp);
        }
        cout << endl;

        for(int k = 0; k<32;k++){
            texte[k+32] = gauche[k];
        }

        for(int k =0; k<32;k++){
            texte[k] = droite[k];
        }

  }

    cout << "Texte chiffre :" << endl;
    for(int i = 0; i<64; i++)
        cout<< texte[i];
    cout << endl << endl;

/*************************************/
/**                                 **/
/**        PARTIE DECRYPTAGE        **/
/**                                 **/
/*************************************/
    for(int i = 0; i<ronde;i++)
    {
        for(int k = 0; k<32;k++){
            droite[k] = texte[k];
        }
        for(int k =0; k<32;k++){
            gauche[k]=texte[k+32];
        }

        //On applique le XOR entre la partie gauche et droite
        for(int k=0;k<32;k++){
                temp = (cle1[k] && !droite[k]) || (!cle1[k] && droite[k]);
                gauche[k] = (gauche[k] && !temp) || (!gauche[k] && temp);
        }

        for(int k = 0; k<32;k++){
            texte[k+32] = droite[k];
        }
        for(int k =0; k<32;k++){
            texte[k]=gauche[k];
        }

  }

    cout << "Texte dechiffre :" << endl;
    for(int i = 0; i<64; i++)
        cout<< texte[i];
    cout << endl;
}
