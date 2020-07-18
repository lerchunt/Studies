#ifndef ENNEMI_SPRITE_H
#define ENNEMI_SPRITE_H

#include "AnimeGraphicElement.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class EnnemiSprite : public AnimeGraphicElement {
	private:
		bool _anime;		//boolens qui definissent quelles animations on doit jouer
		bool _explose;		
		sf::SoundBuffer _buffer;
		sf::Sound _sound;	//son lors de la mort
	public:
	//constructeurs
		EnnemiSprite();
		EnnemiSprite(sf::Image *image, int x, int y, int w, int h,bool anime,bool explose);
	//destructeur
		~EnnemiSprite();
	//accesseurs	
		void setAnime(bool anime);
		void setExplose();
	//methodes
		void draw( sf::RenderWindow * _window);
};
#endif
