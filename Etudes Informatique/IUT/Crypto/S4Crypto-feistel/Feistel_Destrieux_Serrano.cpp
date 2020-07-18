#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;


void f(int tmp[], int  g[], int k[], int taille){
	
	for(int i=0; i<taille; i++)
	{
		if(g[i]!=k[i])
			tmp[i]=1;
			
		else
			tmp[i]=0;
	}
} 

void tableau( int a[], int b[], int deb, int fin){
	for(int i=deb;i<fin;i++){
		a[i]=b[i];
	}
}


int main(int argc,char** argv) {
	int message[64];
	for(int k=0; k<64;k++){
		message[k]=1;
	}
	cout<< "message de base :";
	for(int m=0; m<64; m++){
		cout << message[m]<<" ";
	}
	cout << endl;
	int clef[32];
		for(int l=0; l<32;l++){
			message[l]=l%2;
	}
	int messageCrypte[64];
	int ptrG[32];
	int ptrD[32];
	int tmp[32];
	int ronde=12;
	
	tableau(ptrG,message, 0, 32);
	tableau(ptrD,message, 32, 64);
	
	for(int i=0; i<ronde;i++){
		
		f(tmp,ptrG, clef, 32);
		tableau(ptrG,ptrD,0,32);
		tableau(ptrD, tmp,0,32);
		
	}
	
	tableau(messageCrypte, ptrG,0,32);
	tableau(messageCrypte, ptrD,32,64);
	
	cout<< "message crypté :" ;
	for(int j=0; j<64; j++){
		cout<< messageCrypte[j]<<" ";
	}
	cout << endl;

}
