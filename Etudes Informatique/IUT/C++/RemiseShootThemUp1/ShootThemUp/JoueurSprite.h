#ifndef JOUEUR_SPRITE_H
#define JOUEUR_SPRITE_H

#include "AnimeGraphicElement.h"
#include <SFML/Graphics.hpp>

class JoueurSprite : public AnimeGraphicElement {
	private:		
		bool _haut;				//booleens qui definissent quelle animation jouer
		bool _bas;
		bool _explose;
		bool _recule;
		
	public:
	//constructeurs
		JoueurSprite();
		JoueurSprite(sf::Image *image, int x, int y, int w, int h,bool haut,bool bas,bool explose,bool recule);
	//destructeur
		~JoueurSprite();
	//accesseurs	
		void setHaut(bool haut);
		void setBas(bool bas);
		void setExplose(bool explose);
		void setRecule(bool recule);
	//methodes
		void draw( sf::RenderWindow * _window);
};
#endif
