#include "GraphicElement.h"
#include <iostream>

using namespace std;
using namespace sf;

//=======================================
// Constructeur
//=======================================
GraphicElement::GraphicElement():  Sprite(), _x(0), _y(0)
{}
//=========================================
GraphicElement::GraphicElement(Image *image, int x, int y,int w,int h)
	:  Sprite(*image), _x(x), _y(y), _w(w), _h(h)
{
	Resize(w, h);
	SetPosition(x,y);
}
//=============================================
GraphicElement::~GraphicElement()
{}

//=======================================
// Methodes
//=======================================
void GraphicElement::resize(int w, int h){
	_x -=(w-_w)/2;		//recentre le sprite
	_y -=(h-_h)/2;		//
	
	_w = w;
	_h = h;
	
	Resize(_w, _h);
	SetPosition(_x,_y);
}
//========================================
void GraphicElement::draw(RenderWindow * window){
	window->Draw(*this);
}
