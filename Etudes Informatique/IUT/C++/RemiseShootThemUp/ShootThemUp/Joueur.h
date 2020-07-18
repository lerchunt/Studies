
#ifndef JOUEUR_H
#define JOUEUR_H
#include "Personnage.h"

class Joueur : public Personnage{
	private: 
		int _nb_vies;
		int _puissance;
		int _puissance_secondaire;
		sf::Clock _clock3;
  
	public:
	//constructeurs
		Joueur();
		Joueur(int x, int y, int w, int h, int dx, int dy, int vie, bool vivant, int nbVies, int puissance,int puissance_secondaire);
	//destructeur
		~Joueur();
		
	//accesseurs
		int getNbVies() const;
		int getVie() const;
		int getPuissance()const;
		int getPuissanceSecondaire()const;
		bool getTirer();				//pas des const car elles reset la clock à chaque appel
		bool getTirerSecondaire();
		float getClock()const;

	//methodes
		void deplacerY(bool up);
		void deplacerX(bool up);
		void arriver(int duree,float temps);
		void arriverIntro(int duree,float temps);
		void etreTouche(int puissance);
		void perdreVie();
		void initialiser();
		void augmenterPuissance();
};

#endif
