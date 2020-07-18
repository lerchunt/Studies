#include "Personnage.h"
#include "jeu_const.h"

//=======================================
// Constructeurs
//=======================================
Personnage::Personnage() : MovableElement(){}
//=======================================
Personnage::Personnage(int x, int y, int w, int h, int dx, int dy, int vie, bool vivant) : MovableElement(x,y,w,h,dx,dy,vivant){
	_vie=vie;
	_clock.Reset();
}

//=======================================
// Destructeur
//=======================================
Personnage::~Personnage(){}



