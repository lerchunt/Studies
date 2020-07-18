#ifndef MOVABLE_ELEMENT_H
#define MOVABLE_ELEMENT_H
#include <SFML/System.hpp>

class MovableElement {
	protected: 
		sf::Clock _clock;		//clock pour gérer la vitesse de déplacement
		int _x, _y;
		int _w, _h;
		int _dx, _dy;
		bool _vivant;
  
	public:
	
	//constructeurs
		MovableElement();
		MovableElement(int x, int y, int w, int h, int dx, int dy,bool vivant);
	//destructeur
		~MovableElement();
	//méthodes
		
	//accesseurs
		int getX() const;
		int getY() const;
		bool getVivant() const;
  

};

#endif
