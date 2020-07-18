#ifndef ENNEMI_H
#define ENNEMI_H
#include "Personnage.h"

class Ennemi : public Personnage{
	private: 
		int _type;
		bool _touche;
		float _apparition;		//moment d'apparition à l'écran

	public:
	//constructeurs
		Ennemi();
		Ennemi(int x, int y, int w, int h, int dx, int dy, int vie, bool vivant, int type, bool touche,float apparition);
	//destructeur
		~Ennemi();
		
	//accesseurs
		int getType() const;
		float getApparition() const;
		bool getTouche() const;
		bool getTirer();
	//methodes
		void deplacer(int y);
		int mourrir();
		void etreTouche(int puissance);
};

#endif
