/*
 * RSA.cpp
 * 
 * Copyright 2014 Hadrien Tran <hatran@info-zokusujix>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */


#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

long p;
long q;
long n;
long phiN;
long e;
long pgcd;
long message;
long crypte;


typedef struct solution_ {
    int d;
    int x;
    int y;
}Solution;


Solution Bezout(int a, int b) {
    Solution s;
    Solution tmp;
 
    if (b == 0) {
        s.d = a;
        s.x = 1;
        s.y = 0;
 
        return s;
    }
 
    else {
        tmp = Bezout(b,a%b);
        s.d = tmp.d;
        s.x = tmp.y;
        s.y = tmp.x-(floor(a/b)*tmp.y);
 
        return s;
    }
}


//Exponantiation Modulaire
unsigned long expMod (unsigned long mm, unsigned long ee, unsigned long nn){
	if(ee == 0)
		return 1;
	else
		return(mm*expMod(mm,ee-1,nn))%nn;
}


void chiffrer()
{
	crypte = expMod(message, e, n);
	cout << "Message crypté = " << crypte << endl;
}


void dechiffrer()
{
	message = expMod(crypte, pgcd, n);
	cout << "Message décrypté = " << message << endl;
}


int main(int argc, char **argv)
{
	message = 3333;
	p = 31;
	q = 137;
	e = 967;
	n = p*q;
	phiN = (p-1)*(q-1);
	
	cout << "Message = " << message << endl;
	
	Solution s = Bezout(e, phiN);
	pgcd = s.d;
		
	chiffrer();
	dechiffrer();
	
	return 0;
}

