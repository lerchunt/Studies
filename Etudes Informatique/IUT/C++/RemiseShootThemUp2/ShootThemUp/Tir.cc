#include "Tir.h"
#include "jeu_const.h"
#include <iostream>
using namespace std;

//=======================================
// Constructeurs
//=======================================
Tir::Tir() : MovableElement(){}
//=======================================
Tir::Tir(int x, int y, int w, int h, int dx, int dy, int puissance, bool vivant, bool allie) : MovableElement(x,y,w,h,dx,dy,vivant)
{
	_w = w;
	_h = h;
	
	_puissance = puissance;
	_allie = allie;
}

//=======================================
// Destructeur
//=======================================
Tir::~Tir(){}

//=======================================
// Accesseurs en lecture
//=======================================
int Tir::getPuissance() const{
	return _puissance;
}
//=======================================
void Tir::setVivant(bool vivant){
	_vivant = vivant;
}
//======================================
bool Tir::getAllie()const
{
	return _allie;
}
//========================================
//Methodes
//=======================================
void Tir::deplacer()
{
	if (!_allie)
	{
		if (_clock.GetElapsedTime()> 0.01)
		{
			_x-=_dx;
			_clock.Reset();	
		}
		
		if (_x<-_w)
			_vivant = false;
	}
	else
	{
		if (_clock.GetElapsedTime()> 0.01)
		{
			_x+=_dx;
			_clock.Reset();	
		}
		
		if (_x>MODEL_WIDTH)
			_vivant = false;
	}
}

