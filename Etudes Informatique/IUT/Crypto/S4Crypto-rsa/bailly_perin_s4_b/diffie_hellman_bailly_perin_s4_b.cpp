/*

CODE ECRIT PAR : CHARLES BAILLY & HERVE PERIN
GROUPE : S4 B

*/

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

using namespace std;

int premier()
{
    int res = rand() % 100;
    while(res%2 == 0 || res%3 == 0 || res%5 == 0 || res%7 ==0)
        res++;
    return res;
}

int pgcd(int a, int b)
{
    return (b == 0) ? a : pgcd(b,a%b);
}

unsigned int pModulaire2(unsigned int a, unsigned int e, unsigned int m)
{
    unsigned result = 1;
    while (e > 0)
    {
        if (e & 1 > 0) result = (result * a) % m;
        e >>= 1;
        a = (a * a) % m;
    }
    return result;
}

int main()
{
    srand(time(NULL));
    
    // Choix de p et g
    int p, g;
    do
    {
		p = premier();
		g = rand() % 100;
	}
	while(pgcd(p,g)!=1); // Vérification que p et g sont premier entre eux.
	//~ cout << "p et g : " << p << " et " << g << endl;

	// Alice
	int a = rand() % (p-2);
	int A = pModulaire2(g, a, p);
	//~ cout << "a et A : " << a << " et " << A << endl;

	// Bob
	int b = rand() % (p-2);
	int B = pModulaire2(g, b, p);
	//~ cout << "b et B : " << b << " et " << B << endl;
	
	// Vérification
	if(pModulaire2(B, a, p) == pModulaire2(A, b, p))
		cout << "La clef est : " << pModulaire2(B, a, p) << endl;
	else
		cout << "Erreur lors de la génération de la clef ..." << endl;

    return 0;
}
