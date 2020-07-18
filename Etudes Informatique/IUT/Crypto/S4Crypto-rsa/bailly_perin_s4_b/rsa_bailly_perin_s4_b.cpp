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

typedef struct solution_
{
    int d;
    int x;
    int y;
}Solution;

int pgcd(int a, int b)
{
    return (b == 0) ? a : pgcd(b,a%b);
}
Solution euclide_etendu(int a, int b) {
    Solution s;
    Solution tmp;

    if (b == 0) {
        s.d = a;
        s.x = 1;
        s.y = 0;

        return s;
    }

    else {
        tmp = euclide_etendu(b,a%b);
        s.d = tmp.d;
        s.x = tmp.y;
        s.y = tmp.x-(floor(a/b)*tmp.y);

        return s;
    }
}

int premier()
{
    int res = rand() % 100;
    while(res%2 == 0 || res%3 == 0 || res%5 == 0 || res%7 ==0)
        res++;
    return res;
}

int main()
{
    srand(time(NULL));
    // Sélection des nombres premiers.
    int p, q;
    do
    {
        p = premier();
        q = premier();
    }
    while(p == 1 || q == 1 || p == q);

    // Calcul de n.
    int n = p * q;

    // Calcul de Phi(n);
    int phi_n = (p-1)*(q-1);

    // Génération de e.
    int e;
    do
    {
        e = (rand() % (phi_n-1)) + 1;
        if( (phi_n%2 == 0 && e%2 == 0) || (phi_n%2 == 1 && e%2 == 1) )
            e++;
    }
    while(pgcd(e, phi_n) != 1);

    // Message initial.
    int m = 99;

    // Chiffrement.
    int c = pModulaire2(m, e, n);

    // Calcul de d à l'aide de Bezout.
    Solution s = euclide_etendu(e,phi_n);
    if(s.x<0)
        s.x = phi_n + s.x;
    int d = s.x;

    // Déchiffrement.
    int m2 = pModulaire2(c, d, n);

    // Affichage du résultat.
    cout << "Le message initial est : " << m << endl;
    cout << "Le message encode est : " << c << endl;
    cout << "Le message decode est : " << m2 << endl;
    cout << endl;
    cout << "Clef publique : " << e << ", " << n << endl;
    cout << "Clef privee : " << d << ", " << n << endl;

    return 0;
}
