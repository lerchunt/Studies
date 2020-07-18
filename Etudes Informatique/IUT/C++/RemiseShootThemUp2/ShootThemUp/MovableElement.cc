#include "MovableElement.h"
#include "jeu_const.h"

//=======================================
// Constructeurs
//=======================================
MovableElement::MovableElement() 
	: _x(0), _y(0), _w(0), _h(0), _dx(0), _dy(0)
	{
		_clock.Reset();
	}
//=======================================
MovableElement::MovableElement(int x, int y, int w, int h, int dx, int dy,bool vivant)
	:_x(x), _y(y), _w(w), _h(h), _dx(dx), _dy(dy),_vivant(vivant)
	{
		_clock.Reset();
	}

//=======================================
// Destructeur
//=======================================
MovableElement::~MovableElement(){}

//=======================================
// Accesseurs en lecture
//=======================================
int MovableElement::getX() const {
	return _x;
}
//=======================================
int MovableElement::getY() const {
	return _y;
}
//=======================================
//=======================================
bool MovableElement::getVivant() const {
	return _vivant;
}
//=======================================



