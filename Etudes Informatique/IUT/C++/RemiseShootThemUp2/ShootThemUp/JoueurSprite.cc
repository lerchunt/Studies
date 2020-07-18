#include "JoueurSprite.h"
using namespace sf;
//==============================
//constructeurs
//===============================
JoueurSprite::JoueurSprite() : AnimeGraphicElement()
{}
//==============================
JoueurSprite::JoueurSprite(Image *image, int x, int y, int w, int h,bool haut,bool bas,bool explose,bool recule):AnimeGraphicElement(image,x,y,w,h)
{
	_haut = haut;
	_bas = bas;
	_explose = explose;
	_recule = recule;

}

//==============================
//destructeur
//==============================
JoueurSprite::~JoueurSprite()
{}

//==============================
//accesseurs	
//==============================

void JoueurSprite::setHaut(bool haut)
{
	_haut = haut;
}
//==============================
void JoueurSprite::setBas(bool bas)
{ 
	_bas =bas;
}
//==============================
void JoueurSprite::setExplose(bool explose)
{
	_explose = explose;
}
//===========================
void JoueurSprite::setRecule(bool recule)
{
	_recule = recule;
}
//==============================
//methodes
//==============================

void JoueurSprite::draw(RenderWindow * _window)
{
	if(_recule)
		SetSubRect(sf::IntRect(0, 0, 120, 100));
		
	else if (_haut)
	{
		if(_clock.GetElapsedTime() <=0.2)
			SetSubRect(sf::IntRect(0, 100, 120, 200));
		else
			SetSubRect(sf::IntRect(120, 100, 240, 200));
			
		if(_clock.GetElapsedTime()>0.4)
			_clock.Reset();
	}
	else if (_bas)
	{
		if(_clock.GetElapsedTime() <=0.2)
			SetSubRect(sf::IntRect(0, 200, 120, 300));
		else
			SetSubRect(sf::IntRect(120, 200, 240, 300));
			
		if(_clock.GetElapsedTime()>0.4)
			_clock.Reset();
	}
	else
	{
		if(_clock.GetElapsedTime() <=1.5)
			SetSubRect(sf::IntRect(0, 0, 120, 100));
		else if (_clock.GetElapsedTime() <=1.7)
			SetSubRect(sf::IntRect(120, 0, 240, 100));
		else if (_clock.GetElapsedTime() <=1.9)
			SetSubRect(sf::IntRect(240, 0, 360, 100));
		else if (_clock.GetElapsedTime() <=2.1)
			SetSubRect(sf::IntRect(360, 0, 480, 100));
		else if (_clock.GetElapsedTime() <=2.3)
			SetSubRect(sf::IntRect(480, 0, 600, 100));
		else
			SetSubRect(sf::IntRect(600, 0, 720, 100));	
			
		if(_clock.GetElapsedTime()>2.4)
			_clock.Reset();
	}
	Resize(_w,_h);
	_window->Draw(*this);
}
