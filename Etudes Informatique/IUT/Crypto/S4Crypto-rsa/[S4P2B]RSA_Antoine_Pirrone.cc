#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


long expMod (long base, long exp, long m);
void bezout(int rkm2,int rkm1, int& u, int& v, int ukm1=0,int vkm1=1,int ukm2=1,int vkm2=0);
int genererNombrePremier(int min, int max);
int puissance(int a, int n);
	int pgcd(int a, int b);
		
//~ p=11, q=29, n=319
//~ phi(n) = 280
//~ 
//~ ex:
//~ m=100 : message chiffré : 100^p%n
int main(){
	srand(time(NULL));
	int a = 11, b = 280;
	
	do{
		a = genererNombrePremier(0, 10000);
		b = genererNombrePremier(0, 10000);
	}while(a == b);

	int n = a*b;
	int phi = (a-1)*(b-1);
	int e;
	
	do{
		e = genererNombrePremier(0, phi);
	}while(pgcd(e, phi) != 1);
	
	int u, v;
	bezout(e, phi, u, v);
	u = u<0 ? phi+u:u;
	
	int msg = 300;
	
	int crypt = expMod(msg, e, n);
	cout << "Message : " << msg << "   crypté : " << crypt <<endl;
	cout << "décrypté : " << expMod(crypt, u, n) << endl;
}


int pgcd(int a, int b){
	return b?pgcd(b, a%b) : a;
}

long expMod (long base, long exp, long m) { //base^exp%m
	
	long result = 1;
	while(exp>0){
		if((exp & 1) > 0) result = (result*base)%m;
			exp>>=1;
		base = (base*base)%m;
	}
	return result;
}

void bezout(int rkm2,int rkm1, int& u, int& v, int ukm1=0,int vkm1=1,int ukm2=1,int vkm2=0){

    int rk=rkm2%rkm1;
    int qk=(rkm2-rk)/rkm1;
    if(rk==0) {
		u = ukm1;
		v = vkm1;
	}
    else 
        bezout(rkm1,rk, u, v, ukm2-qk*ukm1,vkm2-qk*vkm1,ukm1,vkm1);
    return;
}

int genererNombrePremier(int min, int max){
	int result;
	bool ok;
	do{
		ok = true;
		result = ((rand() % (int)(((max) + 1) - (min))) + (min));
		
		if(!(expMod(2, result, result)==2))
			ok = false;
		if(!(expMod(3, result, result)==3))
			ok = false;	
		if(!(expMod(5, result, result)==5))
			ok = false;	
		if(!(expMod(7, result, result)==7))
			ok = false;	
	}while(!ok);

    return result;
}

int puissance(int a, int n){
	for(int i = 0 ; i < n ; i++)
		a *= a;
		
	return a;
}
