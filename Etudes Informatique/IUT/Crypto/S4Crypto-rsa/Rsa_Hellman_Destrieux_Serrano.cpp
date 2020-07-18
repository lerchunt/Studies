#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;

void diffieHellman();
long pgcd (long a, long b, long *u, long *v);
long chiffDechiff (long a, long e, long n) ;
//~ unsigned int chiffDechiff(unsigned int a, unsigned int e, unsigned int m);
int nbPrem();
bool prem(int enumber);
long u, v;

int main(int argc,char** argv) {
	int nbr;
	int p, q, e;
	while(!prem(p)){
		p=nbPrem();
	}
		while(!prem(q)){
		q=nbPrem();
	}
		while(!prem(e)){
		e=nbPrem();
	}
	int mod;
	int n=p*q;
	
	cout << "Entrer un nombre plus petit que " << n << " :" << endl;
	cin >> nbr;
	int d=0;
	mod=(p-1)*(q-1);
	
	pgcd(e, mod,  &u, &v);
	if(u<0)
		d=mod+u;
	else
		d=u;
	 
	cout<<"Phi(n) : " << mod << endl;
	cout << "p : " << p << endl;
	cout << "q : " << q << endl;
	cout << "Clef de Chiffrement : " << e << endl;
	
	cout << "Clef de dechiffrement : " << d << endl ;
	int adechiff= chiffDechiff(nbr,e,n);
	cout << "Message chiffre de " << nbr << " :  " << adechiff << endl; 
	cout << "Message dechiffre de  " << adechiff << " : " << chiffDechiff(adechiff, d, n) << endl;
	
	
	cout << endl << endl;
	
	cout<<"Diffie Hellman" << endl; 
	
	diffieHellman();
	
	
	
	return 0;
}

int nbPrem()
{
	//~ return rand()%(20-10) +10;
	return rand()%(200-100) +100;
}

bool prem(int enumber){
	int a = 2;
	if(enumber%a!=0){
		a=3;
		if(enumber%a!=0){
			a=5;
			if(enumber%a!=0){
				a=7;
				if(enumber%a!=0){
					return true;
				}
			}
		}
	}
	return false;
}

//~ unsigned int chiffDechiff(unsigned int a, unsigned int e, unsigned int m){
	//~ unsigned result = 1;
//~ 
	   //~ while (e > 0) {
		  //~ if (e & 1 > 0) result = (result * a) % m;
		  //~ e >>= 1;
		  //~ a = (a * a) % m;
	   //~ }
	   //~ 
	   //~ return result;
//~ }

void diffieHellman(){
    long p,g,a,b, modga, modgb;

    while(!prem(p)){
		p=nbPrem();
	}
    while(!prem(g) || g>p){
		g=nbPrem();
	}
	cout << "g = " << g << endl;
	cout << "p = " << p<< endl;
	
    a = nbPrem();
    b = nbPrem();

	cout << "choisit a = " << a << endl;
	cout << "choisit b = " << b << endl;
    
    modga = chiffDechiff(g,a,p);
    modgb = chiffDechiff(g,b,p);
    
    cout << "Formule de a : " << modga << endl;
    cout << "Formule de b : " << modgb << endl;
    
    long clefModga=chiffDechiff(modgb,a,p);
    long clefModgb=chiffDechiff(modga,b,p);
    
    cout << "clef de ga : " << clefModga << endl;
    cout << "clef de gb : " << clefModgb << endl;
    
    if (clefModga == clefModgb)
		cout << "Les deux clées sont bien égal" << endl;
	else
		cout << "Erreur, les clées sont différentes" << endl;
    //pour clé
	long c=a*b;
	long cle=chiffDechiff(g,c,p);
	cout << "Verification par la formule : g^ab mod p = " << cle << endl;
     
}



long chiffDechiff (long a, long e, long n) {
  long p;
  
  for (p = 1; e > 0; e = e / 2) {
    if (e % 2 != 0)
      p = (p * a) % n;
    a = (a * a) % n;
  }
  return p;
}

long pgcd (long a, long b, long *u, long *v) {
  long q, r, d, s, t;
  
  q = a / b;
  r = a % b;
  if (r == 0) {
    *u = 0;
    *v = 1;
    return b;
  }
  d = pgcd (b, r, &s, &t);
  *u = t;
  *v = s - q * t;
  return d;
}
