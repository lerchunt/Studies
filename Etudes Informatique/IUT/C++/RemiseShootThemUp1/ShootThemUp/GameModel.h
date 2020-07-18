#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <SFML/System.hpp>
#include "Joueur.h"
#include "Ennemi.h"
#include "Tir.h"
#include "jeu_const.h"
#include <vector>
#include <list>

class GameModel {
	private:
		sf::Clock _clock;
		
		int _w, _h;
		int _nb_ennemis_de_base;		//nombre d'ennemis des 3 premiers niveuax
		int _nb_ennemis;				//nombre d'ennemis du niveau
		int _nb_ennemis_touches;		
		int _duree_niveau;
		int _duree_chargement;
		int _duree_intro;
		int _duree_restart;
		int _niveau;					
		int _score_niveau;				//score courant (à soustraire si on recommence le niveau)
		int _score_total;
		int _vies_joueur;
		
		bool _menu;						//booleens qui définissent à quel état du jeu on est
		bool _jeu;		
		bool _chargement;
		bool _quitter;
		bool _game_over;
		bool _recommencer_niveau;
		bool _intro;
		
		int _choix_menu;				//int qui prend 1,2,3 selon les choix du menu
			
		Joueur * _joueur;				//pointeur vers le joueur
		std::list<Tir*>_tirs;			//liste de pointeurs de tirs 
		std::list<Ennemi*>_ennemis; 	//liste de pointeurs d'ennemis
		
		std::list<Tir*>_new_tirs;		//liste de tirs rajoutée au cours du nextStep ou lors d'un tir allié
		std::list<Tir*>_ex_tirs;		//liste de tir supprimés au cours du nextStep
		std::list<Ennemi*>_ex_ennemis;	//liste d'ennemis supprimés au cours du nextStep

	
		public:
//constructeurs
		GameModel();
		GameModel(int w, int h);
//destructeur
		~GameModel();
 
//accesseurs
		 
		Joueur* const getJoueur() const; 
		
		std::list<Ennemi*>* getEnnemis();			//pointeur vers la liste d'ennemis
		
		std::list<Tir*>*getNewTirs();			//pointeur vers la liste de nouveaux tirs 
		std::list<Tir*>*getExTirs();			//pointeur vers la liste de tirs supprimés
		std::list<Ennemi*>*getExEnnemis();		//pointeur vers la liste d'ennemis supprimés
		
				 
		void setChoixMenu(int choix);			
		
		bool getMenu() const;
		bool getJeu() const;
		bool getQuitter()const;
		bool getChargement()const;
		bool getGameOver()const;
		bool getIntro()const;
		bool getRecommencerNiveau()const;
		float getClock()const;
 
//methodes 
		void nextStep();
		std::string NiveauToString() const; 
		std::string EnnemisTuesToString() const; 
		std::string ScoreToString()const;
		void ajouterTir(Tir *t);
		void nouveauJeu();						
		void creerNiveau();						
		void charger();
		void creerTir();
		void creerTirSecondaire();
		void introduire();
		void restart();
		void jouer();
				
		bool ChoixMenuValide(int choix) const;
		void validerMenu();
};
#endif
