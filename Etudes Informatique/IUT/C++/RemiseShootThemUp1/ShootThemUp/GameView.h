#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SFML/Graphics.hpp>
#include "EnnemiSprite.h"
#include "JoueurSprite.h"
#include "FondSprite.h"
#include "GameModel.h"
#include "jeu_const.h"
#include "GraphicElement.h"
#include <SFML/Audio.hpp>

class GameModel;

class GameView {
	private:
		sf::Clock _clock;
		
		int _w, _h;
		
		GameModel * _model;			
		sf::RenderWindow * _window;
		
		sf::Font* _font;			
		sf::Image _background_image;	//images des fonds
		sf::Image _background_image2;
		sf::Image _game_over_image;
		
		sf::Image _joueur_image;		//image du joueur
		
		sf::Image _coeur_image;			//coeur qui indique les vies du joueur
		sf::Shape _rectangle_fond;		//rectangle du fond de la barre de vie	
	
		sf::Image _tir_image;			//images des tirs
		sf::Image _tir2_image;
		sf::Image _tir_ennemi_image;
		sf::Image _tir_ennemi2_image;
		sf::Image _tir_ennemi3_image;
		
		sf::Image _ennemis_image;		//images des ennemis
		sf::Image _ennemis2_image;
		sf::Image _ennemis3_image;
		
		sf::Image _menu_image;			//fond du menu
		sf::Image _jouer_image;			//boutons du menu
		sf::Image _fermer_image;
		sf::Image _scores_image;
		
		sf::Image _rideau_image;		//rideau du chargement

		sf::SoundBuffer _buffer;	//gestion des sons
		sf::SoundBuffer _buffer2;
		sf::Sound _sound;
		sf::Music _musique_de_fond;
		bool _musique_en_cours;
		
		FondSprite *_background_sprite;
		FondSprite *_background_sprite2;
		JoueurSprite *_joueur_sprite; 
		GraphicElement * _tir_disponible_sprite;
		GraphicElement * _coeur_sprite;
		GraphicElement *_rideau_sprite;
		GraphicElement *_menu_sprite;
		GraphicElement *_jouer_sprite;
		GraphicElement *_fermer_sprite;
		GraphicElement *_scores_sprite;
		GraphicElement *_game_over_sprite;
		
		sf::String *_texte;	//string qui contiendra ce qu'on voudra

		std::map<Tir*, GraphicElement *> _tirsToSprite; //map qui associe à des Tir à des GraphicElement
		std::map<Ennemi*,EnnemiSprite*> _ennemisToSprite; // map qui associe à des Ennemi à des GraphicElement
	
	public:
	//constructeur
		GameView(int w, int h, int bpp);
	//destructeur
		~GameView();
		
	//accesseur
		void setModel(GameModel * model);
		
	//methodes		
		void synchronize();
		
		void draw();
		void drawMenu();
		void drawJeu();
		void drawChargement();
		void drawGameOver();
		void drawIntro();
		void drawRecommencerNiveau();
		
		bool treatEvents(GameModel *model);
		void treatEventsJeu(GameModel *model);
		void treatEventsMenu(GameModel *model,sf::Event event);

};
#endif
