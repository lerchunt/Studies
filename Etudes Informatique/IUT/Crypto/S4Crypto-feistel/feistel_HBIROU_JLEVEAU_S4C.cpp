#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>

//feistel.cpp par Birou Hugo et Julien Leveau

using namespace std;
const int tailleMessage = 64;
const int tailleCle = tailleMessage/2;

void encode(int left[], int chiffreRight[], int key []);
void randomKey (int key[]);

int main(int argc, char **argv)
{
    int message[tailleMessage];
    int key[tailleCle];
    int left[tailleCle];
    int right[tailleCle];
    int chiffreLeft[tailleCle];
    int chiffreRight[tailleCle];

    for (int i = 0; i < tailleMessage; i++)
        message[i]=0;

    cout << "Message d'entrée : " ;
    for (int i = 0; i < tailleMessage; i++)
        cout << message[i] << " ";
    cout << endl;

    randomKey(key);
    cout << "Clé d'encodage : " << endl;

    for (int i = 0; i < tailleCle; i++)
        cout << key[i] << " " ;
    cout << endl;

    for (int o = 0; o < 2; o++)
    {
        for (int i = 0; i < tailleCle; i++)
            left[i]=message[i];

        for (int j = tailleCle; j < tailleMessage ; j++)
            right[j-tailleCle]=message[j];

        //Encryptage de la partie gauche
        for (int l = 0; l < tailleCle; l++)
            chiffreLeft[l]=right[l];

        //Encryptage de la partie droite
        encode(left,chiffreRight,key);

        //Concaténation des deux morceaux
        for (int p = 0; p < tailleCle; p++)
            message[p]=chiffreLeft[p];

        for (int b = 0; b < tailleCle; b++)
            message[b+tailleCle]=chiffreRight[b];
    }
    
    cout << "Message de sortie: " << endl ;

    for (int i = 0; i < tailleMessage; i++)
        cout << message[i] << " " ;

    for (int o = 0; o < 2; o++)
    {
        //Clivage du message en deux parties
        for (int i = 0; i < tailleCle; i++)
            left[i]=message[i];

        for (int j = tailleCle; j < tailleMessage ; j++)
            right[j-tailleCle]=message[j];

        for (int l = 0; l < tailleCle; l++)
            chiffreLeft[l]=right[l];

        encode(left,chiffreRight,key);

        for (int p = 0; p < tailleCle; p++)
            message[p]=chiffreLeft[p];

        for (int b = 0; b < tailleCle; b++)
            message[b+tailleCle]=chiffreRight[b];
    }

    cout << "Message décrypté : " << endl;
    for (int i = 0; i < tailleMessage; i++)
        cout << message[i] << " " ;
    cout << endl<< endl;
    
    return 0;
}


void encode(int left[], int chiffreRight[], int key [])
{
    for (int i = 0; i < tailleCle; i++)
    {
        if (left[i]==key[i])
            chiffreRight[i]=0;
        else
            chiffreRight[i]=1;
    }
}

void randomKey (int key[]) {
    srand (time(NULL));
    for (int c = 0; c < tailleCle; c=c++)
        key[c]=rand() % 2;
}

