#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>

using namespace std;

long p,q;
long n;
long phiN;
long e;
long d;
long m,c;


int nP, nG,nA,nB,nGA,nGB,cleAlice,cleBob;

void generationNP();
unsigned long puissance(unsigned long x,unsigned long x2, unsigned long x3);
int rabin(long a, long premier);

//Fonction pour calculer la clef avec le cryptement Diffie-Hellman
int DiffieHellman(){

    generationNP();
    nG = rand()%nP;
    cout << "P : " << nP << endl;
    cout << "G : " << nG << endl;

    //Génaration de la clef prive d'Alice
    cout << endl << "Alice : " << endl;
    nA = rand();
    cout << "a : " << nA << endl;
    nGA = puissance(nG,nA,nP);
    cout << "(g^a)mod(p) = " << nGA << endl;

    //Génération de la clef privé de Bob
    cout << endl << "Bob" << endl;
    nB = rand();
    cout << "b : " << nB << endl;
    nGB = puissance(nG,nB,nP);
    cout << "(g^b)mod(p) = " << nGB << endl;

    // Calcul de la clef
    cleAlice = puissance(puissance(nG,nB,nP),nA,nP);
    cleBob = puissance(puissance(nG,nA,nP),nB,nP);

    cout << endl << "Clefs echangees : " << endl;
    cout << "Alice : " << cleAlice <<endl;
    cout << "Bob : " << cleBob << endl;



}

//Va générer nP pour Diffie-Hellman
void generationNP(){

    bool test = true;
    int tmp;

    while (test){
        tmp = (int) rand()%300;

        if(rabin(2,tmp) == 0 || rabin(3,tmp) == 0 || rabin(5,tmp) == 0 || rabin(7,tmp) == 0 )
            test = true;
        else
            test = false;
    }

    nP = tmp;



}

// Va retourner d pour le cryptement RSA
void Bezout(int rkm2,int rkm1,int ukm1=0,int vkm1=1,int ukm2=1,int vkm2=0){
    int rk=rkm2%rkm1;
    int qk=(rkm2-rk)/rkm1;
    if(rk==0){
        std::cout<<rkm1<<"=a*"<<ukm1<<"+b*"<<vkm1<<std::endl;
        if(ukm1 > 0)
            d = ukm1;
        else
            d = phiN+ukm1;
    }
    else
        Bezout(rkm1,rk,ukm2-qk*ukm1,vkm2-qk*vkm1,ukm1,vkm1);
    return;
}

// Va effectuer l'exponantiation modulaire
unsigned long puissance(unsigned long x1, unsigned long x2, unsigned long x3)
{
    if (x2==0)
        return 1;
    else
        return (x1*puissance(x1,x2-1,x3))%x3;
}

// Va vérifier la primalité d'un nombre, va retourner 0 si le nombre est composite et 1 si il semble premier
int rabin (long a, long premier) {
  long p, e, m;
  int i, k;

  e = m = premier - 1;
  for (k = 0; e % 2 == 0; k++)
    e = e / 2;

  p = puissance (a, e, premier);
  if (p == 1) return 1;

  for (i = 0; i < k; i++) {
    if (p == m) return 1;
    if (p == 1) return 0;
    p = (p * p) % premier;
  }

  return 0;
}
//Va generer p et q pour le chiffrement RSA
void generationPQ(){

    bool test = true;
    int tmp;

    while (test){
        tmp = (int) rand()%200;

        if(rabin(2,tmp) == 0 || rabin(3,tmp) == 0 || rabin(5,tmp) == 0 || rabin(7,tmp) == 0 )
            test = true;
        else
            test = false;
    }

    cout <<"p : " << tmp << endl;
    p = tmp;


    test = true;
    while (test){
        tmp = (int) rand()%200;

        if(rabin(2,tmp) == 0 || rabin(3,tmp) == 0 || rabin(5,tmp) == 0 || rabin(7,tmp) == 0 )
            test = true;
        else
            test = false;
    }

    cout <<"q : " << tmp << endl;
    q= tmp;

}

int gcd(int a, int b){
     if (b == 0)
        { return a; }
     else
        { return gcd(b, a % b);
     }
}

// Va gnérer e pour le chiffrement RSA
void generationE(){

    int tmpe = rand();

    while(gcd(tmpe,phiN) !=1)
        tmpe = rand();

    e = tmpe;

}

// Va génere les clefs privés et public
int cle(){


generationPQ();
n = p*q;
phiN = (p-1)*(q-1);
generationE();
Bezout(e,phiN);

cout << "Cle publique : ("<< e << "," << n << ")" << endl;
cout << "Cle prive : " << d << endl;

}

// Va chiffrer le message
void chiffrement(){


c = puissance(m,e,n);
cout << "Texte chiffre : " << c << endl;


}

//Va dechiffrer le message
void dechiffrement(){

m = puissance(c,d,n);
cout << "Texte dechiffre : " << m << endl;

}

int main(int argc,char* argv[]){
    srand(time(NULL));

    cout << "RSA : " << endl;
   m = 10;
   cle();
   chiffrement();
   dechiffrement();

   cout << endl << endl << "Diffie-Hellman" << endl;
   DiffieHellman();
   return 0;
}


