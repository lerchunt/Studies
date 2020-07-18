#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

using namespace std;

long u=0;
long v=0;
long d=0;


long expModulaire(long b, long e, long n)
{
    long s=1;
    for(long i=0; i<e; i++)
    {
        s*=b;
        s=s%n;
    }
    return s;
}

long puissance (long a, long e, long n) {
    long p;

    for (p = 1; e > 0; e = e / 2) {
        if (e % 2 != 0)
            p = (p * a) % n;
        a = (a * a) % n;
    }
    return p;
}


long generatePremier()
{

    long n;
    bool prime = false;
    long test[7] = {2,3,5,7,11,13,19};
    while(!prime)
    {
        prime=true;
        n=rand()%10000;
        n=(n%2) ? n: n+1;
        for(long i= 0; i<7 && prime; i++) {

            prime =(puissance(test[i],n,n)%n) == test[i];
        }
    }

    return n;
}

long chiffrer(long m,long e,long n)
{
    long c;
    c=puissance(m,e,n);
    return c;

}
unsigned long pgcd(unsigned long a, unsigned long b)
{
    return b ? pgcd(b,a%b):a;
}

long generatePremieravecPremier( long p)
{
	long g;
	do {
	g=rand()%p;
	}
	while(pgcd(g,p)!=1);
	return g;
}

int main(int argc,char** argv) {


    cout << "__________________________________________________"<< endl;
    cout << "|             Cryptage Deffie-Hellman            |"<< endl;
    cout << "|________________________________________________|"<< endl << endl;
    srand(time(NULL));
    long p=generatePremier();
    long g=generatePremieravecPremier(p);

    long a=rand()%p;
    long b=rand()%p;

    long cleA = puissance(g,a,p);
    long cleB = puissance(g,b,p);
    long cleFAlice= puissance(cleB, a,p);
    long cleFBob= puissance(cleA, b,p);

    cout << " p vaut : " << p << " et g vaut : " << g << endl;
    cout << " a vaut : " << a << " et b vaut : " << b << endl;
    cout << " cle d'alice : " << cleFAlice << " et cle d'bob : " << cleFBob << endl;



    return 0;
}
