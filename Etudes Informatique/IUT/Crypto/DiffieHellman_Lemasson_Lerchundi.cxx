#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

using namespace std;

int u=0;
int v=0;
int d=0;

long puissance (int a, int e, int n) {
    int p;

    for (p = 1; e > 0; e = e / 2) {
        if (e % 2 != 0)
            p = (p * a) % n;
        a = (a * a) % n;
    }
    return p;
}


int generePremier(){
	int res =(rand()%100);
	while(res % 2 == 0 || res % 3 == 0 || res % 5 == 0 ||res % 7 == 0)
		res ++;
return res;
}
unsigned int pgcd(unsigned int a, unsigned int b)
{
    return b ? pgcd(b,a%b):a;
}
/*Permet que les deux chiffres soit premiers entre eux */
int generePremier2( int p)
{
	int g;
	do {
	g=rand()%p;
	}
	while(pgcd(g,p)!=1);
	return g;
}

int main(int argc,char** argv) {
	
    srand(time(NULL));
    int p=generePremier();
    int g=generePremier2(p);

    int a=rand()%p;
    int b=rand()%p;

    int cleA = puissance(g,a,p);
    int cleB = puissance(g,b,p);
    int cleAlice= puissance(cleB, a,p);
    int cleBob= puissance(cleA, b,p);

    cout << " p vaut : " << p << " | g vaut : " << g << " | a vaut : " << a << " | b vaut : " << b <<endl;
    cout << " cle d'alice : " << cleAlice << " et cle debob : " << cleBob << endl;
    
    return 0;
}

