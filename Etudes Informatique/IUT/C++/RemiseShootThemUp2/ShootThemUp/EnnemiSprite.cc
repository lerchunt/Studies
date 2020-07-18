#include "EnnemiSprite.h"
using namespace sf;

//==============================
//constructeurs
//==============================
EnnemiSprite::EnnemiSprite() : AnimeGraphicElement()
{}
//==============================
EnnemiSprite::EnnemiSprite(Image *image, int x, int y, int w, int h,bool anime, bool explose,SoundBuffer *buffer)	:  AnimeGraphicElement(image,x,y,w,h)
{
	_anime = anime;
	_explose=explose;
	
	_sound.SetBuffer(*buffer);	//on set le son selon celui donné en parametres
}

//==============================
//destructeur
//==============================
EnnemiSprite::~EnnemiSprite(){}

//==============================
//accesseurs
//==============================
void EnnemiSprite::setExplose()
{	
	if(_explose ==false)
		_clock.Reset();
		
	_explose = true;
	_anime = false;

}
//==============================
void EnnemiSprite::setAnime(bool anime)
{
	_anime=anime;
	_explose=!anime;
}

//==============================
//methodes
//==============================

void EnnemiSprite::draw(RenderWindow * _window)
{
	if (_anime)												//animation de l'ennemi:
	{
		if(_clock.GetElapsedTime() <=0.1)					// en fonction de la valeur de la clock
			SetSubRect(sf::IntRect(0, 0, 150, 100));		//on ajuste le rectangle de lecture
		else if (_clock.GetElapsedTime() <=0.2)
			SetSubRect(sf::IntRect(150, 0, 300, 100));
		else if (_clock.GetElapsedTime() <=0.3)
			SetSubRect(sf::IntRect(300, 0, 450, 100));
		else if (_clock.GetElapsedTime() <=0.4)
			SetSubRect(sf::IntRect(450, 0, 600, 100));
		else if (_clock.GetElapsedTime() <=0.5)
			SetSubRect(sf::IntRect(600, 0, 750, 100));
		else
			SetSubRect(sf::IntRect(750, 0, 900, 100));	
			
		if(_clock.GetElapsedTime()>0.6)						//en fin d'animation on reset la clock pour recommencer
			_clock.Reset();
	}
	if(_explose)
	{
		if(_clock.GetElapsedTime() <=0.1)
			{
				_sound.Play();
				SetSubRect(sf::IntRect(0, 100, 150, 200));
			}
		else if (_clock.GetElapsedTime() <=0.2)
			SetSubRect(sf::IntRect(150, 100, 300, 200));
		else if (_clock.GetElapsedTime() <=0.3)
			SetSubRect(sf::IntRect(300, 100, 450, 200));
		else
			SetSubRect(sf::IntRect(450, 100, 600, 200));
	}

	Resize(_w,_h);
	_window->Draw(*this);
}
