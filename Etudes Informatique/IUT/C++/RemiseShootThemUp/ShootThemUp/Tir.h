#ifndef TIR_H
#define TIR_H
#include "MovableElement.h"

class Tir : public MovableElement{
	private: 
		int _puissance;
		bool _allie;
  
	public:
	//constructeurs
		Tir();
		Tir(int x, int y, int w, int h, int dx, int dy, int puissance,bool vivant,bool allie);
	//destructeur
		~Tir();
	//methodes
		void deplacer();
		
	//accesseurs
		int getPuissance() const;
		void setVivant(bool vivant);
		bool getAllie()const;
};

#endif
