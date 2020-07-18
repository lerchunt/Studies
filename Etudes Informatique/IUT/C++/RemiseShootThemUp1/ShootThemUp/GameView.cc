#include "GameView.h"
#include <iostream>

using namespace std;
using namespace sf;

//=======================================
// Constructeur
//=======================================
GameView::GameView(int w, int h, int bpp): _w(w), _h(h)
{
	_window = new RenderWindow(sf::VideoMode(w, h, bpp), "Jeu", sf::Style::Close);

	_font = new Font();									
	_font->LoadFromFile("images/Antique Olive.ttf");	
	_texte = new String("hello");						
	
	_rectangle_fond= sf::Shape::Rectangle(13, 73,117,87, sf::Color::Red, 1, sf::Color::White);		
		
	if (!_menu_image.LoadFromFile("images/menu.png") || !_background_image.LoadFromFile("images/fond.png") ||
	 ! _joueur_image.LoadFromFile("images/sorciere.png") || ! _tir_image.LoadFromFile("images/sort.png")
	    || ! _jouer_image.LoadFromFile("images/jouer.png") || ! _fermer_image.LoadFromFile("images/fermer.png")||
	     ! _scores_image.LoadFromFile("images/scores.png") || !_ennemis_image.LoadFromFile("images/dragon.png")
	     || !_ennemis2_image.LoadFromFile("images/dragon2.png")|| !_ennemis3_image.LoadFromFile("images/dragon3.png")
	    || ! _rideau_image.LoadFromFile("images/rideau.png") || ! _coeur_image.LoadFromFile("images/coeur.png")
	    ||! _tir_ennemi_image.LoadFromFile("images/boule.png")|| !_background_image2.LoadFromFile("images/fond2b.png")
	    ||! _tir_ennemi2_image.LoadFromFile("images/boule2.png")||! _tir_ennemi3_image.LoadFromFile("images/boule3.png")
	    ||! _game_over_image.LoadFromFile("images/gameOver.png")|| ! _tir2_image.LoadFromFile("images/sort2.png"))
	{
		_background_sprite = new FondSprite;
		_background_sprite2 = new FondSprite;
		_joueur_sprite = new JoueurSprite;
		_menu_sprite = new GraphicElement;
		_jouer_sprite = new GraphicElement;
		_fermer_sprite = new GraphicElement;
		_scores_sprite = new GraphicElement;	
		_coeur_sprite = new GraphicElement;
		_rideau_sprite = new GraphicElement; 
		_game_over_sprite = new GraphicElement;	 
		_tir_disponible_sprite = new GraphicElement;
	}
	else 
	{
		_background_sprite = new FondSprite(&_background_image,0,0,MODEL_WIDTH,MODEL_HEIGHT,VITESSE_FOND1,TAILLE_FOND1);
		_background_sprite2 = new FondSprite(&_background_image2,0,0,MODEL_WIDTH,MODEL_HEIGHT,VITESSE_FOND2,TAILLE_FOND2);
		_joueur_sprite = new JoueurSprite(&_joueur_image ,w/2,h/2,JOUEUR_WIDTH,JOUEUR_HEIGHT,false,false,false,false);	
		_menu_sprite = new GraphicElement(&_menu_image,0,0,MODEL_WIDTH, MODEL_HEIGHT);
		_jouer_sprite = new GraphicElement(&_jouer_image,150,h/2,250,75);
		_scores_sprite = new GraphicElement(&_scores_image,475,h/2,250,75);
		_fermer_sprite = new GraphicElement(&_fermer_image,800,h/2,250,75);
		_coeur_sprite = new GraphicElement(&_coeur_image,0,0,50,50);
		_rideau_sprite = new GraphicElement(&_rideau_image,0,0,MODEL_WIDTH,MODEL_HEIGHT);
		_game_over_sprite = new GraphicElement(&_game_over_image,0,0,MODEL_WIDTH,MODEL_HEIGHT);
		_tir_disponible_sprite  = new GraphicElement(&_tir2_image,0,0,TIR_WIDTH_SECONDAIRE,TIR_HEIGHT_SECONDAIRE);
	}
	_buffer2.LoadFromFile("musiques/dragon_mort.wav");
	_buffer.LoadFromFile("musiques/tir_sorciere.wav"); 		// source du son du tir de la sorcière
	_sound.SetBuffer(_buffer);								// on associe le buffer au son
				
	_musique_en_cours=false;								// booléen qui sert à démarrer la musique seulement au premier niveau et pas avant
	_musique_de_fond.OpenFromFile("musiques/musique.wav"); 	// source de la musique de fond
	_musique_de_fond.SetLoop(true); 								// la musique tourne en boucle
}

//=======================================
// Destructeur
//=======================================
GameView::~GameView(){
	if(_rideau_sprite != NULL)
		delete _rideau_sprite;
	if(_coeur_sprite != NULL)
		delete _coeur_sprite;
	if(_window!= NULL)
		delete _window;
	if (_joueur_sprite!=NULL)
		delete _joueur_sprite;
	if (_background_sprite!=NULL)
		delete _background_sprite;
	if (_background_sprite2!=NULL)
		delete _background_sprite2;
	if(_font!= NULL)
		delete _font;
	if(_texte!=NULL)
		delete _texte; 
	if (_menu_sprite!=NULL)
		delete _menu_sprite;
	if (_jouer_sprite!=NULL)
		delete _jouer_sprite;
	if (_fermer_sprite!=NULL)
		delete _fermer_sprite;
			
	map<Ennemi*,EnnemiSprite*>::iterator ite;
	for(ite=_ennemisToSprite.begin();ite!=_ennemisToSprite.end();ite++)
		delete ite->second;
		
	map<Tir *, GraphicElement *>::iterator it;
	for(it=_tirsToSprite.begin();it!=_tirsToSprite.end();it++)
		delete it->second;
}

//=======================================
// Accesseurs en écriture
//=======================================
void GameView::setModel(GameModel * model){
	_model = model;
}

//=======================================
// Synchronize
//=======================================
void GameView::synchronize()
{	
	list<Tir*>::iterator it1;
	
//suppression des tirs morts
	list<Tir*>*ptrExTirs = _model->getExTirs();	
	for(it1 = ptrExTirs->begin();it1!=ptrExTirs->end();it1++)		
	{
		delete _tirsToSprite[*it1];
		_tirsToSprite.erase(*it1);
	}
	(*ptrExTirs).clear();					//on vide ensuite la liste du model
	
//ajout des nouveaux tirs		
	list<Tir*>*ptrNewTirs = _model->getNewTirs();
	for(it1=ptrNewTirs->begin();it1!=ptrNewTirs->end();it1++)
	{
		if((*it1)->getAllie())
		{
			if((*it1)->getPuissance()==TIR_PUISSANCE_SECONDAIRE)
				_tirsToSprite[(*it1)]= new GraphicElement(&_tir2_image,(*it1)->getX(),(*it1)->getY(),TIR_WIDTH_SECONDAIRE,TIR_HEIGHT_SECONDAIRE);
			else
				_tirsToSprite[(*it1)]= new GraphicElement(&_tir_image,(*it1)->getX(),(*it1)->getY(),TIR_WIDTH,TIR_HEIGHT);
			
		}
		else
		{
			if((*it1)->getPuissance()==10)
				_tirsToSprite[(*it1)]= new GraphicElement(&_tir_ennemi_image,(*it1)->getX(),(*it1)->getY(),TIR_ENNEMI_WIDTH,TIR_ENNEMI_HEIGHT);
			else if((*it1)->getPuissance()==20)
				_tirsToSprite[(*it1)]= new GraphicElement(&_tir_ennemi2_image,(*it1)->getX(),(*it1)->getY(),TIR_ENNEMI_WIDTH,TIR_ENNEMI_HEIGHT);
			else
				_tirsToSprite[(*it1)]= new GraphicElement(&_tir_ennemi3_image,(*it1)->getX(),(*it1)->getY(),TIR_ENNEMI_WIDTH,TIR_ENNEMI_HEIGHT);	
		}	
	}
	(*ptrNewTirs).clear();				//on vide ensuite la liste du model

//mise à jour du map de tirs
	map<Tir*,GraphicElement*>::iterator it;
	for (it=_tirsToSprite.begin();it!=_tirsToSprite.end();it++)
			it->second->SetPosition(it->first->getX(),it->first->getY());	
			
	
	list<Ennemi*>::iterator it2;	
//suppression des ennemis morts
	list<Ennemi*>*ptrExEnnemis = _model->getExEnnemis();
		
	for(it2 = ptrExEnnemis->begin();it2!=ptrExEnnemis->end();it2++)		
	{
		delete _ennemisToSprite[*it2];
		_ennemisToSprite.erase(*it2);
	}	
	(*ptrExEnnemis).clear();			//on vide ensuite la liste du model

//ajout des nouveaux ennemis
	list<Ennemi*>* ptrEnnemis = _model->getEnnemis();
	if( _ennemisToSprite.empty())				//si le map d'ennemis est vide on le remplit
	{
		for (it2=ptrEnnemis->begin();it2!=ptrEnnemis->end();it2++)
		{
			if ((*it2)->getType()==1)
				_ennemisToSprite[(*it2)] =new EnnemiSprite(&_ennemis_image,(*it2)->getX(),(*it2)->getY(),ENNEMI_WIDTH,ENNEMI_HEIGHT,true,false,_buffer2);
			else if ((*it2)->getType()==2)
				_ennemisToSprite[(*it2)] =new EnnemiSprite(&_ennemis2_image,(*it2)->getX(),(*it2)->getY(),ENNEMI_WIDTH,ENNEMI_HEIGHT,true,false,_buffer2);
			else
				_ennemisToSprite[(*it2)] =new EnnemiSprite(&_ennemis3_image,(*it2)->getX(),(*it2)->getY(),ENNEMI_WIDTH,ENNEMI_HEIGHT,true,false,_buffer2);
		}	
	}
		
//mise à jour du map d'ennemi	
	map<Ennemi*,EnnemiSprite*>::iterator ite;
	for (ite=_ennemisToSprite.begin();ite!=_ennemisToSprite.end();ite++)
	{
		ite->second->SetPosition(ite->first->getX(),ite->first->getY());	
		if(ite->first->getTouche())										
			ite->second->setExplose();									
	}
		
			
//synchro du joueur
	_joueur_sprite->SetPosition(_model->getJoueur()->getX(),_model->getJoueur()->getY());

}

//=======================================
// Fonctions de dessin
//=======================================

//fonction principale
void GameView::draw()
{
	_window->Clear();
	
	if (_model->getIntro())
		drawIntro();
	
	else if (_model->getRecommencerNiveau())
		drawRecommencerNiveau();
		
	else if(_model->getMenu())		
		drawMenu();				
		
	else if(_model->getJeu())		
		drawJeu();					
		
	else if (_model->getChargement())	
		drawChargement();			
		
	else if(_model->getGameOver())
		drawGameOver();

	_window->Display();			
}

//dessin du menu
void GameView::drawMenu()
{
	_menu_sprite->draw(_window);
		
	if (_model->ChoixMenuValide(1)==true)
	{
		_jouer_sprite->resize(300,90);
		_fermer_sprite->resize(250,75);
		_scores_sprite->resize(250,75);
	}
	if (_model->ChoixMenuValide(3)==true)
	{
		_fermer_sprite->resize(300,90);
		_jouer_sprite->resize(250,75);
		_scores_sprite->resize(250,75);
	}
	if (_model->ChoixMenuValide(2)==true)
	{
		_fermer_sprite->resize(250,75);
		_jouer_sprite->resize(250,75);
		_scores_sprite->resize(300,90);
	}
	if (_model->ChoixMenuValide(0)==true)
	{
		_fermer_sprite->resize(250,75);
		_jouer_sprite->resize(250,75);
		_scores_sprite->resize(250,75);
	}
	
	_jouer_sprite->draw(_window);
	_fermer_sprite->draw(_window);
	_scores_sprite->draw(_window);
}

//dessin du jeu
void GameView::drawJeu()
{
	if (_musique_en_cours==false)
		{
			_musique_de_fond.Play();			//on lance la musique
			_musique_en_cours=true;
		}
//affichage du fond
	_background_sprite->defiler(_window);
		
//affichage du joueur
	_joueur_sprite->draw(_window);	
		
//parcours et affichage du map de tirs
	map<Tir*, GraphicElement *>::iterator it;
	for(it = _tirsToSprite.begin();it != _tirsToSprite.end(); ++it)				
		it->second->draw(_window);
		
//parcours et affichage du map d'ennemis		
	map<Ennemi*, EnnemiSprite *>::iterator ite;
	for(ite = _ennemisToSprite.begin();ite != _ennemisToSprite.end(); ++ite)	
		{
			ite->second->draw(_window);
		}
//affichage du fond2		
	_background_sprite2->defiler(_window);	

//affichage des coeurs
	for(int i =0;i<_model->getJoueur()->getNbVies();i++) 		
	{
		_coeur_sprite->SetPosition(i*50,0);
		_coeur_sprite->draw(_window);
	}

//affichage des ennemis tués	
	*_texte = String(_model->EnnemisTuesToString());					
	_texte->SetFont(*_font);
	_texte->SetSize(30.f);
	_texte->SetPosition(300,10);
	_texte->SetColor(sf::Color(50,50,50));
	_window->Draw(*_texte);	
	
//affichage du score
	*_texte = String(_model->ScoreToString());
	_texte->SetFont(*_font);
	_texte->SetSize(30.f);
	_texte->SetPosition(1050,10);
	_texte->SetColor(sf::Color(50,50,50));
	_window->Draw(*_texte);	
	
//dessin des rectangles de vie
	_window->Draw(_rectangle_fond);	
	_window->Draw(sf::Shape::Rectangle(15, 75,_model->getJoueur()->getVie()+15, 85, sf::Color::Green));
	
//dessin du tir secondaire s'il est disponible
	if(_model->getJoueur()->getClock()>5)
	{
		_tir_disponible_sprite->SetPosition(200,20);
		_tir_disponible_sprite->draw(_window);
	}
}

//dessin du chargement
void GameView::drawChargement()
{
	_background_sprite->draw(_window);
	
	_joueur_sprite->setBas(false);				//on selectionne l'animation du sprite
	_joueur_sprite->setHaut(false);	
	_joueur_sprite->draw(_window);
	
	_background_sprite2->draw(_window);	
	
	_rideau_sprite->SetPosition(0,-_model->getClock()*MODEL_HEIGHT/DUREE_CHARGEMENT);	//le rideau bouge proportionnellement à la durée du chargement
	_rideau_sprite->draw(_window);
	
	*_texte = String(_model->NiveauToString());	
	_texte->SetFont(*_font);
	_texte->SetSize(100.f);
	_texte->SetPosition(400,600);
	_texte->SetColor(sf::Color(50,50,50));
	_window->Draw(*_texte);								
}
//dessin du game over
void GameView::drawGameOver()
{
	_game_over_sprite->draw(_window);
	
	*_texte = String(_model->ScoreToString());
	_texte->SetFont(*_font);
	_texte->SetSize(60.f);
	_texte->SetPosition(480,620);
	_texte->SetColor(sf::Color(50,50,50));
	_window->Draw(*_texte);	
}
//dessin de l'intro
void GameView::drawIntro()
{
	_menu_sprite->draw(_window);
	
	_joueur_sprite->setBas(false);
	_joueur_sprite->setHaut(false);	
	_joueur_sprite->draw(_window);
		
	*_texte = String("SHOOT THEM UP!!");
	_texte->SetFont(*_font);
	_texte->SetSize(80.f);
	_texte->SetPosition(250,150);
	_texte->SetColor(sf::Color(50,50,50));
	_window->Draw(*_texte);	
}
//dessin du restart du niveau
void GameView::drawRecommencerNiveau()
{	
	if(_model->getClock()<DUREE_RESTART/3)						//on baisse le rideau
	{
		_background_sprite->defiler(_window);	
		_background_sprite2->defiler(_window);		
				
		_rideau_sprite->SetPosition(0,_model->getClock()*3*MODEL_HEIGHT/DUREE_RESTART-MODEL_HEIGHT);
	}

	else if (_model->getClock()>DUREE_RESTART/3*2)				//on monte le rideau 
	{
		_background_sprite->draw(_window);
		
		_joueur_sprite->setBas(false);
		_joueur_sprite->setHaut(false);	
		_joueur_sprite->draw(_window);	
		
		_background_sprite2->draw(_window);	
		
		_rideau_sprite->SetPosition(0,(2-_model->getClock())*3*MODEL_HEIGHT/DUREE_RESTART);
	}
	
	_rideau_sprite->draw(_window);
	
	*_texte = String("Try again!");
	_texte->SetFont(*_font);
	_texte->SetSize(100.f);
	_texte->SetPosition(400,600);
	_texte->SetColor(sf::Color(50,50,50));
	_window->Draw(*_texte);	
}

//================================================
// Traitement des evenements
// Retourne false si un evenement de fin est reçu
//================================================

//fonction principale
bool GameView::treatEvents(GameModel * model)
{
	bool result = false;

	if(_window->IsOpened())
	{
		result = true;
		Event event;
		while (_window->GetEvent(event)) 
		{
			if ((event.Type == Event::Closed) ||((event.Type == Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)) || model->getQuitter()) 
			{
				_window->Close();
				result = false;
			}
		}	
		
		if(model->getMenu())				
			treatEventsMenu(model,event);	
		
		else if(model->getJeu())					
			treatEventsJeu(model);			
	}	
		return result;
}

//traitement des evenements du jeu
void GameView::treatEventsJeu(GameModel*model)
{
	const sf::Input& input=_window->GetInput();

	if (input.IsKeyDown(sf::Key::Space))		//tir principal
		{	
			if(_clock.GetElapsedTime()>0.1)
		{
			_sound.Play();
			_model->creerTir();				//on demande au modele de creer le tir
			_clock.Reset();
		}			
		}
	
	if (input.IsKeyDown(sf::Key::Return))		//tir secondaire
		_model->creerTirSecondaire();
	
	
	if (input.IsKeyDown(sf::Key::Up))
	{
		model->getJoueur()->deplacerY(true);				//bouge le MovableElement...
		_joueur_sprite->setHaut(true);					//avertit le sprite
		_joueur_sprite->setBas(false);
		_joueur_sprite->setRecule(false);
	}
			
	else if (input.IsKeyDown(sf::Key::Down))
	{
		model->getJoueur()->deplacerY(false);			//bouge le MovableElement...
		_joueur_sprite->setBas(true);					//avertit le sprite
		_joueur_sprite->setHaut(false);
		_joueur_sprite->setRecule(false);
	}
	
	else if (input.IsKeyDown(sf::Key::Left))
	{
		model->getJoueur()->deplacerX(true);			//bouge le MovableElement...
		_joueur_sprite->setBas(false);					//avertit le sprite
		_joueur_sprite->setHaut(false);
		_joueur_sprite->setRecule(true);
	}
	
	else if (input.IsKeyDown(sf::Key::Right))
	{
		model->getJoueur()->deplacerX(false);			//bouge le MovableElement...
		_joueur_sprite->setBas(false);					//avertit le sprite
		_joueur_sprite->setHaut(false);
		_joueur_sprite->setRecule(false);
	}
			
	else
	{
		_joueur_sprite->setBas(false);
		_joueur_sprite->setHaut(false);	
		_joueur_sprite->setRecule(false);	
	}
}

//traitement des evenements du menu
void GameView::treatEventsMenu(GameModel *model,sf::Event event)		//le choix du menu est stocké dans le model
{
	const sf::Input& input=_window->GetInput();
						
	if (input.GetMouseY()>MODEL_HEIGHT/2 && input.GetMouseY()<MODEL_HEIGHT/2+63 && input.GetMouseX()>150 && input.GetMouseX()<400)
		model->setChoixMenu(1);
	else if (input.GetMouseY()>MODEL_HEIGHT/2 && input.GetMouseY()<MODEL_HEIGHT/2+63 && input.GetMouseX()>475 && input.GetMouseX()<725)
		model->setChoixMenu(2);
	else if (input.GetMouseY()>MODEL_HEIGHT/2 && input.GetMouseY()<MODEL_HEIGHT/2+63 && input.GetMouseX()>800 && input.GetMouseX()<1050)
		model->setChoixMenu(3);
	else
		model->setChoixMenu(0);	
		
	if (input.IsMouseButtonDown(sf::Mouse::Left))
		model->validerMenu();		
}




