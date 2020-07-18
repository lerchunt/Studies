#include "Joueur.h"
#include "jeu_const.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
//=======================================
// Constructeurs
//=======================================
Joueur::Joueur() : Personnage(){}
//=======================================
Joueur::Joueur(int x, int y, int w, int h, int dx, int dy, int vie,bool vivant, int nbVies, int puissance,int puissanceSecondaire) : Personnage(x,y,w,h,dx,dy,vie, vivant){
	_nb_vies=nbVies;
	_puissance = puissance;
	_puissance_secondaire = puissanceSecondaire;
	_clock3.Reset();
}

//=======================================
// Destructeur
//=======================================
Joueur::~Joueur(){}

//=======================================
// Accesseurs en lecture
//=======================================
int Joueur::getNbVies() const{
	return _nb_vies;
}
//========================================
int Joueur::getVie() const
{
	return _vie;
}
//=========================================
int Joueur::getPuissance()const
{
	return _puissance;
}
//=========================================
int Joueur::getPuissanceSecondaire()const
{
	return _puissance_secondaire;
}
//========================================
float Joueur::getClock()const
{
	return _clock3.GetElapsedTime();
}
//====================================
bool Joueur::getTirer()
{
	if (_clock2.GetElapsedTime()>0.1)		//retourne true toutes les 2 secondes, false sinon
	{
		_clock2.Reset();
		return true;
	}
	else
		return false;
}
//====================================
bool Joueur::getTirerSecondaire()
{
	if (_clock3.GetElapsedTime()>5)		//retourne true toutes les 2 secondes, false sinon
	{
		_clock3.Reset();
		return true;
	}
	else
		return false;
}

//========================================
//Methodes
//========================================
void Joueur::deplacerY(bool up)					//prend un booleen en parametre qui indique si le joueur
{																	//se déplace vers le haut ou vers le bas
	if (_clock.GetElapsedTime()>0.005)
	{
		if (up)
		{
			if (_y>=0)	
				_y=_y-_dy;
		}
		else
		{
			if (_y<=MODEL_HEIGHT-_h)
				_y=_y+_dy;
		}	
		_clock.Reset();
	}
}
//=================================
void Joueur::deplacerX(bool left)					//prend un booleen en parametre qui indique si le joueur
{																	//se déplace vers la gauche ou droite
	if (_clock.GetElapsedTime()>0.005)
	{
		if (left)
		{
			if (_x>=0)	
				_x=_x-_dx;
		}
		else
		{
			if (_x<=MODEL_WIDTH-_w)
				_x=_x+_dx;
		}	
		_clock.Reset();
	}
}
//=========================================
void Joueur::arriver(int duree,float temps)			//deplacement du joueur lors du chargement et du restart
{
	_y = (MODEL_HEIGHT-_h)/2;
	_x =1000*temps/duree-950;
}
//=========================================
void Joueur::arriverIntro(int duree,float temps)	//deplacement du joueur lors de l'intro
{
	_x =2000*temps/duree-500;
}

//==========================================
void Joueur::etreTouche(int puissance)
{
	_vie -= puissance;
	
	if(_vie <= 0)
		perdreVie();
}
//=========================================
void Joueur::perdreVie()
{
	if (_nb_vies >1)
	{
		_nb_vies--;
		_vie =JOUEUR_VIE;
	}
	else
		_vivant = false;
}
//=========================================
void Joueur::augmenterPuissance()
{
	if(_puissance < 5)							//5 est la puissance max du joueur
		_puissance+=1;
}
//=========================================
void Joueur::initialiser()						//recentre le joueur et remplit sa vie pour les nouveaux niveaux
{
	_vie = JOUEUR_VIE;
	_y = (MODEL_HEIGHT-_h)/2;
}
//========================================
