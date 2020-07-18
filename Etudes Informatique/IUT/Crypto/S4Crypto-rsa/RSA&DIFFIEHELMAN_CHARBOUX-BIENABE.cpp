/*
	CHABROUX Alexandre
	BIENABE Willy 

	Version 5.0 (Ajout de l'algorithme de DiffieHelman)
*/



#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

using namespace std;

unsigned int modulaire(unsigned int a, unsigned int e, unsigned int m)
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

typedef struct Resultat_
{
    int d;
    int x;
    int y;
}Resultat;

int pgcd(int a, int b)
{
    return (b == 0) ? a : pgcd(b,a%b);
}

Resultat euclide(int a, int b) {
    Resultat s;
    Resultat tmp;

    if (b == 0) {
        s.d = a;
        s.x = 1;
        s.y = 0;

        return s;
    }

    else {
        tmp = euclide(b,a%b);
        s.d = tmp.d;
        s.x = tmp.y;
        s.y = tmp.x-(floor(a/b)*tmp.y);

        return s;
    }
}

int nbPremier()
{
    int res = rand() % 100;
    while(res%2 == 0 || res%3 == 0 || res%5 == 0 || res%7 ==0)
        res++;
    return res;
}

void diffieHelman()
{
    double p;
    double g;
    double a;
    double b;
    double ga;
    double gb;

    do {
        p = random( 0, DOUBLE_MAX );
    } while (!miller(p, 7));
    do{
        g = random(1,p);
    } while ( pgcd(g, p) != 1 );

    a = random(1,p);
    b = random(1,p);

    ga = modpow(g,a,p);
    gb = modpow(g,b,p);

    cout << endl << "Algorithme DiffieHelman :" << endl;
    cout << "p=" << p << endl;
    cout << "a=" << a << endl << "b=" << b << endl;
    cout << "ga=" << ga << endl << "gb=" << gb << endl;
    cout << "A=" << modpow(ga,b,p) << endl << "B=" << modpow(gb,a,p) << endl;
}

int main()
{
    srand(time(NULL));

    // Nombres nbPremiers

    int p, q;
    do
    {
        p = nbPremier();
        q = nbPremier();
    }
    while(p == 1 || q == 1 || p == q);

    // Calcul n

    int n = p * q;

    // Calcul O(n)
    int phi_n = (p-1)*(q-1);

    // On génère e

    int e;
    do
    {
        e = (rand() % (phi_n-1)) + 1;
        if( (phi_n%2 == 0 && e%2 == 0) || (phi_n%2 == 1 && e%2 == 1) )
            e++;
    }
    while(pgcd(e, phi_n) != 1);

    // M = 99
    int m = 99;

    // Chiffrement
    int c = modulaire(m, e, n);

    // Bezout
    Resultat s = euclide(e,phi_n);
    if(s.x<0)
        s.x = phi_n + s.x;
    int d = s.x;

    // Déchiffrement
    int m2 = modulaire(c, d, n);

    // Résultat
    cout << "Le message initial : " << m << endl;
    cout << "Le message encode : " << c << endl;
    cout << "Le message decode : " << m2 << endl;
    cout << endl;
    cout << "Cle publique : " << e << ", " << n << endl;
    cout << "Cle privee : " << d << ", " << n << endl;

    // Exécution de Diffie Helman
    diffieHelman();    

    return 0;
}
