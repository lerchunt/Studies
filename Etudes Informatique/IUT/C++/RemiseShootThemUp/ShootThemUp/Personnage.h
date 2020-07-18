#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <SFML/Graphics.hpp>
#include "MovableElement.h"

class Personnage : public MovableElement{
	protected: 
		int _vie;
		sf::Clock _clock2;		//une deuxieme clock pour gerer le temps de recharge entre chaque tir 
  
	public:
	//constructeurs
		Personnage();
		Personnage(int x, int y, int w, int h, int dx, int dy, int vie, bool vivant);
	//destructeur
		virtual ~Personnage();
	//methodes
		virtual void etreTouche(int puissance)=0;
	//accesseurs
		virtual bool getTirer() = 0;
};

#endif
