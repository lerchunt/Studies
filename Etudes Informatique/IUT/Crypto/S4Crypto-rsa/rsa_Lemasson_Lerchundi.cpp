#include <iostream>
#include <time.h>
#include <stdlib.h>

/*Auteurs: Thomas Lerchundi et Antoine Lemasson
 * S4P2B
 * Cryptage et décryptage fonctionnel sans erreurs.
 * */
 
using namespace std;

/*retourne le u de au+bv*/
int bezout(int rkm2,int rkm1,int ukm1=0,int vkm1=1,int ukm2=1,int vkm2=0){

    int rk=rkm2%rkm1;
    int qk=(rkm2-rk)/rkm1;
    if(rk==0){ 
        cout<<rkm1<<"=a*"<<ukm1<<"+b*"<<vkm1<<endl;
        int d= ukm1;
	}
    else 
        ukm1=bezout(rkm1,rk,ukm2-qk*ukm1,vkm2-qk*vkm1,ukm1,vkm1);
        
    return ukm1;
}

int pgcd(int a,int b)
{
    return b ?  pgcd(b,a%b) : a;
}

int puissance (int a, int b){
	int res = 1;
	for(int i= 0; i<=b; i++)
		res = res*a;
	return res;
}

int pModulaire(int a,int e,int m){
   int result = 1;

   while (e > 0) {
      if (e & 1 > 0) result = (result * a) % m;
      e >>= 1;
      a = (a * a) % m;
   }

   return result;
}
/*On s'interesse au cryptage d'un message pas plus grand que 100, on vérifie donc tous les nombre premier entre 1 et Racine(100)*/
int generePremier(){
	int res =(rand()%100);
	while(res % 2 == 0 || res % 3 == 0 || res % 5 == 0 ||res % 7 == 0)
		res ++;
return res;
}

int main()
{
	srand(time(NULL));
    int a,b,c,d,e,m,u;
    a = generePremier();
    b = generePremier();
    
    cout << a << " " << b << endl;
    
    cout << "Entrez votre message à crypter" << endl;
    cin >> m;
    
    int n = a*b; 
    int phi = (a-1)*(b-1);
    
    e = (rand()%100);
    u=bezout(e,phi);
    while(pgcd(e,phi) != 1){
		e++;
		u=bezout(e,phi);
	}
	c = pModulaire(m,e,n);
    cout<<"e ="<<e<<"phi ="<<phi<<endl;
    
    if(u<0)
		d = phi + u;
	else
		d =u;
		
    cout << "d = " << d << endl;
	cout << "Le message crypté c = " << c << endl;
	
	m =pModulaire(c,d,n);
	cout << "Le message décrypté m = " << m << endl;

    
    
    return 0;
}
