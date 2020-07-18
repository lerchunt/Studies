//feistel.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;


void encrypt(int left[], int chiffreRight[], int key [])
{
    for (int i = 0; i < 32; i++)
    {
        if (left[i]==key[i])
            chiffreRight[i]=0;
        else
            chiffreRight[i]=1;
    }

}


void createRandomKey (int key[]) {
	
	srand (time(NULL));
	   for (int c = 0; c < 32; c=c++)
    {
				key[c]=rand() % 2;
    }
	
}


int main(int argc, char **argv)
{
	
    int message[64];
    int key[32];
    int left[32];
    int right[32];
    int chiffreLeft[32];
    int chiffreRight[32];

    //création du message
    for (int v = 0; v < 64; v++)
    {
        message[v]=0;
    }
    
    
    
//////////////////////// AFFICHAGE /////////////////////////////	
    cout << "Message à l'origine : " ;
    
    for (int i = 0; i < 64; i++)
	{
		cout << message[i] << " " ;
	}
	cout << endl;
	cout << endl;
////////////////////////////////////////////////////////////////


createRandomKey(key);


//////////////////////// AFFICHAGE /////////////////////////////	
	 cout << "Clé de cryptage : " ;
    
    for (int i = 0; i < 32; i++)
	{
		cout << key[i] << " " ;
	}
	cout << endl;
	cout << endl;
////////////////////////////////////////////////////////////////


for (int o = 0; o < 2; o++)
{
	
    //Séparation du messsage
    for (int i = 0; i < 32; i++)
    {
        left[i]=message[i];
    }

    for (int j = 32; j < 64 ; j++)
    {
        right[j-32]=message[j];
    }



    //encryptage partie gauche
    for (int l = 0; l < 32; l++)
    {
        chiffreLeft[l]=right[l];
    }


    //encryptage partie droite
    encrypt(left,chiffreRight,key);



    //recollage des morceaux
    for (int p = 0; p < 32; p++)
    {
        message[p]=chiffreLeft[p];
    }

    for (int b = 0; b < 32; b++)
    {
        message[b+32]=chiffreRight[b];
    }


}




//////////////////////// AFFICHAGE /////////////////////////////	
     cout << "Message chiffré : " ;
    
    for (int i = 0; i < 64; i++)
	{
		cout << message[i] << " " ;
	}
	cout << endl;
	cout << endl;
////////////////////////////////////////////////////////////////
    

///////////////////////////////////////////////////// DECHIFFRAGE ////////////////////////////////////////////////////////////
    
    
    for (int o = 0; o < 2; o++)
{
	
    //Séparation du messsage
    for (int i = 0; i < 32; i++)
    {
        left[i]=message[i];
    }

    for (int j = 32; j < 64 ; j++)
    {
        right[j-32]=message[j];
    }



    //encryptage partie gauche
    for (int l = 0; l < 32; l++)
    {
        chiffreLeft[l]=right[l];
    }



    //encryptage partie droite
    encrypt(left,chiffreRight,key);



    //recollage des morceaux
    for (int p = 0; p < 32; p++)
    {
        message[p]=chiffreLeft[p];
    }

    for (int b = 0; b < 32; b++)
    {
        message[b+32]=chiffreRight[b];
    }


}
    
    
    
    
    
    
    
    
    
    
//////////////////////// AFFICHAGE /////////////////////////////	        

 cout << "Message déchiffré : " ;
    
    for (int i = 0; i < 64; i++)
	{
		cout << message[i] << " " ;
	}
	cout << endl;
	cout << endl;

////////////////////////////////////////////////////////////////

    return 0;
}

