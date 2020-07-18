#include "AnimeGraphicElement.h"
using namespace sf;
//constructeurs
AnimeGraphicElement::AnimeGraphicElement()
{}
AnimeGraphicElement::AnimeGraphicElement(Image *image, int x, int y, int w,int h):Sprite(*image)
{
	_clock.Reset();
	_w = w;
	_h = h;
}
//destructeur
AnimeGraphicElement::~AnimeGraphicElement()
{}
