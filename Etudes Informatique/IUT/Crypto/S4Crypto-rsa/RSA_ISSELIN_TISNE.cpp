#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

using namespace std;


struct Solution
{
    int d;
    int x;
    int y;
};

int pgcd(int a, int b)
{
    return (b == 0) ? a : pgcd(b,a%b);
}

int premier()
{
    int res = rand() % 100;
    while(res%2 == 0 || res%3 == 0 || res%5 == 0 || res%7 ==0)
        res++;
    return res;
}

unsigned int exponentiationModulaire(unsigned int a, unsigned int e, unsigned int m)
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

Solution euclideEtendu(int a, int b) {
    Solution s;
    Solution tmp;

    if (b == 0) {
        s.d = a;
        s.x = 1;
        s.y = 0;

        return s;
    }

    else {
        tmp = euclideEtendu(b,a%b);
        s.d = tmp.d;
        s.x = tmp.y;
        s.y = tmp.x-(floor(a/b)*tmp.y);

        return s;
    }
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
    int phi = (p-1)*(q-1);

    // Génération de e nombre premier.
    int e;
    do
    {
        e = (rand() % (phi-1)) + 1;
        if( (phi%2 == 0 && e%2 == 0) || (phi%2 == 1 && e%2 == 1) )
            e++;
    }
    while(pgcd(e, phi) != 1);

   	cout << "Entrez le nombre a chiffrer : ";
    // Message à chiffrer.
    int m;
    cin >> m;

    // Chiffrement.
    int c = exponentiationModulaire(m, e, n);

    // Calcul de d à l'aide de l'algorithme d'euclide étendu (théorème de Bezout).
    Solution s = euclideEtendu(e,phi);
    if(s.x<0)
        s.x = phi + s.x;
    int d = s.x;

    // Déchiffrement.
    int m2 = exponentiationModulaire(c, d, n);

    // Affichage du résultat.
    cout << "Le message a chiffrer est : " << m << endl;
    cout << "Le message chiffre est : " << c << endl;
    cout << "Le message dechiffre est : " << m2 << endl;
    cout << endl;
    cout << "Clef publique : " << e << ", " << n << endl;
    cout << "Clef privee : " << d << ", " << n << endl;

    return 0;
}
