#ifndef FOND_SPRITE_H
#define FOND_SPRITE_H
#include "AnimeGraphicElement.h"
#include <SFML/Graphics.hpp>

class FondSprite : public AnimeGraphicElement
{
	private:
		int _x1;		//x1 et x2 sont les coordonnes en x du rectangle de lecture
		int _x2;
		int _dx;
		int _taille;	//_taille est la taille de l'image en px
	public:
	//constructeurs
		FondSprite();
		FondSprite(sf::Image *image, int x, int y,int w, int h, int dx, int taille);
	//destructeur
		~FondSprite();
	//methodes
		void draw( sf::RenderWindow * _window);
		void defiler( sf::RenderWindow * _window);
};
#endif
