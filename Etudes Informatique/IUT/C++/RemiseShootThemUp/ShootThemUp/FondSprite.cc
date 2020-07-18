#include "FondSprite.h"
using namespace sf;

//==============================
//constructeurs
//==============================

FondSprite::FondSprite():AnimeGraphicElement()
{}

FondSprite::FondSprite(Image *image, int x, int y,int w, int h,int dx,int taille) : AnimeGraphicElement(image,x,y,w,h)
{
	_x1 = 0;
	_x2 = _w;	
	_dx = dx;
	_taille = taille;
}

//==============================
//destructeur
//==============================
FondSprite::~FondSprite()
{}

//==============================
//methodes
//==============================

//dessine le fond sans le défiler
void FondSprite::draw(RenderWindow * _window)
{
	_x1 = 0;
	_x2 = _w;
	_clock.Reset();
	
	SetSubRect(sf::IntRect(_x1,0,_x2,_h));
	Resize(_w,_h);
	_window->Draw(*this);	
}

//dessine le fond en défilant
void FondSprite::defiler(sf::RenderWindow * _window)
{
	if(_clock.GetElapsedTime()>=0.001)	//toutes les 0.001 secondes:
	{
		if (_x2>=_taille)				//si le rectangle de lecture a dépassé la taille de l'image
		{
			_x1 = 0;					//on le remet au début
			_x2=_w;
		}
		else 							//sinon on le déplace 
		{
			_x1+=_dx;
			_x2+=_dx;
		}
		_clock.Reset();
	}
	
	SetSubRect(sf::IntRect(_x1,0,_x2,_h));
	Resize(_w,_h);
	_window->Draw(*this);	
}

