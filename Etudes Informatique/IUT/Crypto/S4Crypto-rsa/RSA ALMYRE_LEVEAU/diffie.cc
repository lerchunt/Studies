#include <stdlib.h>
#include <iostream>
#include <vector> 
#include <fstream>
#include <time.h> 
#include <cmath>

using namespace std;

long exponentiationModulaire (long a, long e, long n) {

  long p;
  
  for (p = 1; e > 0; e = e / 2) {
    if (e % 2 != 0)
      p = (p * a) % n;
    a = (a * a) % n;
  }
  return p;
}

unsigned long pgcd(unsigned long a,unsigned long b){  
	return b ?  pgcd(b,a%b) : a;
}

int generatePrime()
{

bool prime = false;
int test[4] = {2,3,5,7};
int n;

while(!prime)
{
prime = true;
n = rand() %10000;
n = (n%2) ? n: n + 1;

for(int i =0; i < 4 && prime; i++)
prime = (exponentiationModulaire(test[i],n,n) % n) == test[i];
}
return n;

}



int main()
{
	srand(time(NULL));
	
	int p=generatePrime();
	int g=generatePrime();
	while (!pgcd(p,g)==1 && g<p){
		g=generatePrime();
	}
	cout << " p = " << p << " g = " << g << endl << endl;
	cout << "Alice genere un entier a " << endl;
	int a = rand()%10000;
	cout << a << endl;
	cout << "Alice envoi g**a mod p " << endl;
	long ga=exponentiationModulaire(g,a,p);
	cout << ga << endl<< endl;
	
	cout << "Bob genere un entier b " << endl;
	int b = rand()%10000;
	cout << b << endl;
	cout << "Bob envoi g**b mod p " << endl;
	long gb=exponentiationModulaire(g,b,p);
	cout << gb << endl<< endl;
	
	long cle=exponentiationModulaire(g,a*b,p);
	cout << "La clé générée vaut : " << cle << endl;
	
	return 0;
	}
