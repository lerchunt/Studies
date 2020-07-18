#include <cstdlib>
#include <iostream>
#include <time.h>  
#include <string>


using namespace std;

void generateKey(long long &e, long long &n, long long &d);
int genererPremier();
unsigned long pgcd(unsigned long a,unsigned long b);
long bezout(long a, long b);
long expoModulaire (long a, long e, long n);
long encrypt(long e, long n, long m);
long decrypt(long d, long n, long m);

int main(int argc, char** argv)
{
	srand(time(NULL));
	long long e, n, d;
	generateKey(e, n, d);
	int c = encrypt(e,n,1234);
	cout << "msg crypté = " << c << endl;
	int decrypted = decrypt(d,n,c);
	cout << "msg décrypté = " << decrypted << endl;
}

long expoModulaire (long a, long e, long n) {

  long p;
  
  for (p = 1; e > 0; e = e / 2) {
    if (e % 2 != 0)
      p = (p * a) % n;
    a = (a * a) % n;
  }
  return p;
}

long encrypt(long e, long n, long m)
{	return expoModulaire(m,e,n);}

long decrypt(long d, long n,long m)
{	return expoModulaire(m,d,n);}


unsigned long pgcd(unsigned long a,unsigned long b)
{  return b ?  pgcd(b,a%b) : a;	}

int genererPremier()
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
			prime = (expoModulaire(test[i],n,n) % n) == test[i];
	}
	return n;

}

void generateKey(long long &e, long long &n, long long &d)
{
	
	int p = genererPremier();
	int q = genererPremier();

	n = p*q;
	long long phi = (p-1)*(q-1);

	do e = rand()%(phi -1) + 1; 
	while(pgcd(e,phi) != 1);
	d = bezout(e, phi);

	cout << "p = " << p << ", q = " << q << ", n = " << n << ", phi = "  << phi << ", e = " << e << ", d = " << d << endl;
}

long bezout(long a, long b)
{
	int p = 1, q = 0, r = 0, s = 1;
	int b0 = b;

	while (b != 0) { 
	  int c = a % b;
	  int quotient = a/b;
	  a = b;
	  b = c;
	  int nouveau_r = p - quotient * r; 
	  int nouveau_s = q - quotient * s;
	  p = r; q = s;
	  r = nouveau_r; s = nouveau_s;
	}

	return (p < 0) ? p + b0 : p;
}
