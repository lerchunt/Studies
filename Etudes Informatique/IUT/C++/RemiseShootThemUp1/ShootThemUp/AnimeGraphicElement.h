#ifndef ANIME_GRAPHIC_ELEMENT_H
#define ANIME_GRAPHIC_ELEMENT_H

#include <SFML/Graphics.hpp>

class AnimeGraphicElement : public sf::Sprite {
	protected:	
				
		sf::Clock _clock;		//une clock qui sert a gerer l'animation de l'élément
			
		int _w;
		int _h;
			
	public:
	//constructeurs
		AnimeGraphicElement();
		AnimeGraphicElement(sf::Image *image, int x, int y, int w, int h);
	//destructeur
		~AnimeGraphicElement();
	//methodes
		virtual void draw( sf::RenderWindow * _window) =0;
};
#endif
