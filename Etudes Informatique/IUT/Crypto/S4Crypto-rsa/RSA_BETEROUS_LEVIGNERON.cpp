//RSA.cpp
//

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

void Bezout(int r2,int r1,int u1=0,int v1=1,int u2=1,int v2=0){
    int rest=r2%r1;
    int q=(r2-rest)/r1;
    if(rest==0){
        if(u1 > 0)
            d = u1;
        else
            d = phiN+u1;
    }
    else
        Bezout(r1,rest,u2-q*u1,v2-q*v1,u1,v1);
}

unsigned long exponantiationModulaire(unsigned long mm, unsigned long ee, unsigned long nn)
{
    if (ee==0)
        return 1;
    else
        return (mm*exponantiationModulaire(mm,ee-1,nn))%nn;
}

void chiffrer()
{
	c = exponantiationModulaire(m,e,n);
	cout << c << endl;
}

void dechiffrer()
{
	m = exponantiationModulaire(c,d,n);
	cout << m << endl;
}

bool premier(long x)
{
	int tab[4]={2,3,5,7};
	for(int i;i<4;i++)
	{	
		if (exponantiationModulaire(tab[i],x-1,x)!=1)
			return false;
	}
	return true;
}


void randomPQ()
{
	do{
		p=rand()%1000;
	}while(!premier(p));
	
	do{
		q=rand()%1000;
	}while(!premier(q));
}

int main (int argc, char* argv[])
{
	m=3333;
	//randomPQ(); //fait un segment fault lors du décryptage
	p=31;
	q=137;
	e=967;
	n=q*p;
	phiN=(q-1)*(p-1);
	Bezout(e,phiN);
	chiffrer();
	dechiffrer();
	
	return 0;
}
