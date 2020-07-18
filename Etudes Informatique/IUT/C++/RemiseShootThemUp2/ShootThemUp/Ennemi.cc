#include "Ennemi.h"
#include "jeu_const.h"

#include <iostream>
using namespace std;
//==================================
// Constructeurs
//============================================
Ennemi::Ennemi() : Personnage(){}

Ennemi::Ennemi(int x, int y, int w, int h, int dx, int dy, int vie,bool vivant, int type, bool touche,float apparition) : Personnage(x,y,w,h,dx,dy,vie,vivant){
	_type=type;
	_touche = touche;
	_apparition = apparition;
	switch(_type)		//on initialise la vie en fonction du type d'ennemi
	{
	case 1:
		_vie = 2;
		break;
	case 2:
		_vie = 6;
		break;
	case 3:
		_vie = 15;
		break;
	}
}
//================================
// Destructeur
//===============================
Ennemi::~Ennemi(){}

//=================================
// Accesseurs en lecture
//===================================
int Ennemi::getType() const{
	return _type;
}
//========================================
float Ennemi::getApparition()const{
	return _apparition;
}
//=========================================
bool Ennemi::getTouche() const{
	return _touche;
}
//=========================================
bool Ennemi::getTirer()
{
	if (_clock2.GetElapsedTime()>2)		//retourne true toutes les 2 secondes, false sinon
	{
		_clock2.Reset();
		return true;
	}
	else
		return false;
}

//==============================
//Methodes
//===============================
void Ennemi::deplacer(int y)			//prend en parametre la position en y du joueur
{		
	if(_x<0-_w)							//s'il sort de l'ecran, _vivant passe a false (l'ennemi meurt sans passer par l'état touché)
		_vivant =false;												
		
	if(_clock.GetElapsedTime()>0.02)	//toutes les 0.02s:
	{
		_x -= _dx;

		if(!_touche)					//s'il n'est pas touché 
		{
			if(_y<=y)					//il se déplace vers le joueur
				_y +=_dy;
			else
				_y -= _dy;
		}
		_clock.Reset();
	}
}
//=======================================
int Ennemi::mourrir()					//retourne tout le temps 0 sauf la derniere fois qu'on l'appelle, retourne alors 1 (pour incrementer le score une seule fois)
{
	if (_clock2.GetElapsedTime()>=0.4)	//il reste touché pendant 0.4s puis _vivant passe à false
	{
		_touche = false;
		_vivant = false;
		return 1;
	}	
	else
		return 0;
}
//=====================================
void Ennemi::etreTouche(int puissance)	
{
	_vie -=puissance;
	
	if(_vie <=0)
	{
		_touche = true;
		_clock2.Reset();
	}
}
