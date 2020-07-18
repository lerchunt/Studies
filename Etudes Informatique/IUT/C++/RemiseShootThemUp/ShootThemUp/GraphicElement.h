#ifndef GRAPHIC_ELEMENT_H
#define GRAPHIC_ELEMENT_H

#include <SFML/Graphics.hpp>

class GraphicElement : public sf::Sprite {
	private:
		int _x, _y;
		int _w,_h;
		
	public:
//constructeurs
		GraphicElement();
		GraphicElement(sf::Image *image, int x, int y, int w, int h);
//destructeur 
		~GraphicElement();
//methodes
		virtual void draw(  sf::RenderWindow * _window);
		void resize(int w, int h);
};
#endif
