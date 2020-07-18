#include "GameModel.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


///***************************************************
///CONSTRUCTEURS
///***************************************************

//=======================================
// Constructeur par défaut
//=======================================
GameModel::GameModel() 
	: _w(MODEL_WIDTH), _h(MODEL_HEIGHT) {
	_joueur = new Joueur();		
}
//=======================================
//constructeur paramétré
//=======================================
GameModel::GameModel(int w, int h)
	:  _w(w), _h(h){
		
	_nb_ennemis_de_base=_nb_ennemis = NOMBRE_ENNEMIS;
	_duree_niveau=DUREE_NIVEAU;
	_duree_chargement =  DUREE_CHARGEMENT;
	_duree_intro = DUREE_INTRO;
	_duree_restart = DUREE_RESTART;
	_intro = true;
	
	_joueur = new Joueur(50, (h-JOUEUR_HEIGHT)/2, JOUEUR_WIDTH, JOUEUR_HEIGHT, JOUEUR_X_SPEED, JOUEUR_Y_SPEED, JOUEUR_VIE, true, NB_VIES,TIR_PUISSANCE,TIR_PUISSANCE_SECONDAIRE);
	
	_clock.Reset();
}
//=======================================
// Destructeur
//=======================================
GameModel::~GameModel(){
	if(_joueur != NULL)
		delete _joueur;
		
	std::list<Tir*>::iterator it1;
	for (it1=_tirs.begin();it1!=_tirs.end();it1++)		
		delete *it1;	
		
	std::list<Ennemi*>::iterator it2;
	for (it2=_ennemis.begin();it2!=_ennemis.end();it2++)		
		delete *it2;	
}


///***************************************************
///ACCESSEURS
///***************************************************
//==================================
std::list<Ennemi*>* GameModel::getEnnemis() 
{
	return &_ennemis;
}
//========================================
Joueur* const GameModel::getJoueur() const
{
	return _joueur;
}
//=============================================
std::list<Tir*>* GameModel::getNewTirs()
{
	return & _new_tirs;
}
//================================================
std::list<Tir*>*GameModel::getExTirs()
{
	return &_ex_tirs;
}
//================================================
std::list<Ennemi*>*GameModel::getExEnnemis()
{
	return &_ex_ennemis;
}
//======================================
bool GameModel::getQuitter()const
{
	return _quitter;
}
//========================================
bool GameModel::getMenu()const
{
	return _menu;
}
//======================================
bool GameModel::getJeu()const
{
	return _jeu;
}
//========================================
bool GameModel::getChargement()const
{
	return _chargement;
}
//========================================
bool GameModel::getGameOver()const
{
	return _game_over;
}
//========================================
bool GameModel::getIntro()const
{
	return _intro;
}
//========================================
bool GameModel::getRecommencerNiveau()const
{
	return _recommencer_niveau;
}
//==============================================
void GameModel::setChoixMenu(int choix)
{
	_choix_menu = choix;
}

//========================================
float GameModel::getClock()const
{
	return _clock.GetElapsedTime();
}
//=======================================


///***************************************************
///FONCTIONS DU NEXTSTEP
///***************************************************

//=======================================
//fonction principale
//=======================================
void GameModel::nextStep()					
{		
	if(_intro)
		introduire();
		
	else if(_chargement)															
		charger();								
		
	else if(_jeu)									//si on est en jeu
	{	
		if(_clock.GetElapsedTime()<_duree_niveau)	//et que le niveau n'est pas fini...on joue
			jouer();								
		else 										//si le niveau est fini (le joueur a réussi)
		{		
			_jeu = false;							//on lance le chargement
			_niveau++;
			_joueur->augmenterPuissance();			//on augmente la puissance du joueur
			_clock.Reset();
			_chargement =true;
		}		
	}
	else if (_game_over)						//si on est au game over
	{
		if (_clock.GetElapsedTime()>4)			//on reste ainsi pendant 4 sec
			nouveauJeu();						//et on relance le jeu
	}

	else if (_recommencer_niveau)				
		restart();
}

//======================================
//jeu
//=====================================
void GameModel::jouer()
{
	std::list<Tir*>::iterator it1;
	std::list<Ennemi*>::iterator ite;
	std::list<Tir*>::iterator it2;										
			
//deplacement des ennemis et gestion des états
	for (ite=_ennemis.begin(); ite!= _ennemis.end();)
	{
		if((*ite)->getApparition()<=_clock.GetElapsedTime())			//s'il est l'heure pour l'ennemi de se bouger:
		{
			(*ite)->deplacer(_joueur->getY());								//on le deplace
									
			if ((*ite)->getTouche())										//s'il est touché:
			{
				_nb_ennemis_touches+=(*ite)->mourrir();							//on incremente le nombre d'ennemi touché et les scores
				_score_total += (*ite)->mourrir()*(*ite)->getType();
				_score_niveau += (*ite)->mourrir()*(*ite)->getType();
			}
			else 															//sinon il tire et on gere la collision avec le joueur
			{
				if((*ite)->getTirer()){
					_new_tirs.push_back(new Tir((*ite)->getX(),(*ite)->getY()+ENNEMI_HEIGHT*2/3-TIR_HEIGHT/2,	//ajout du tir dans la liste de nouveaux tirs
					TIR_WIDTH,TIR_HEIGHT,TIR_ENNEMI_X_SPEED,TIR_Y_SPEED,(*ite)->getType()*10,true, false));
				}
							
				if(_joueur->getY()>(*ite)->getY() && _joueur->getY()+JOUEUR_HEIGHT<(*ite)->getY()+ENNEMI_HEIGHT		
					&& _joueur->getX()>(*ite)->getX() && _joueur->getX()+JOUEUR_WIDTH<(*ite)->getX()+ENNEMI_WIDTH)
					_joueur->perdreVie();
					
			}					
		}
					
		if (!(*ite)->getVivant())										//s'il est mort:
		{
			_ex_ennemis.push_back(*ite);								//on l'ajoute à la liste d'ennemis supprimés
			delete *ite;												//et on delete+supprime
			ite=_ennemis.erase(ite);
		}
						
		else
			++ite;
		
	}


//remplissage de la liste de tirs avec les tirs créés
	for(it2 = _new_tirs.begin();it2 !=_new_tirs.end();it2++)
		_tirs.push_back(*it2);		
		
//deplacement des tirs et collision 
	for (it1=_tirs.begin(); it1!= _tirs.end();)
	{	
		if (!(*it1)->getVivant())				//si le tir est mort:
		{
			_ex_tirs.push_back(*it1);				//on l'ajoute à la liste de tirs supprimés
			delete (*it1);							//et on le delete+supprime
			it1=_tirs.erase(it1);			
		}
		else
		{												
			(*it1)->deplacer();
						
			if((*it1)->getAllie())																					//si c'est un tir allie collision avec les ennemis
			{
				for (ite=_ennemis.begin(); ite!= _ennemis.end();ite++)		
				{	
					if((*it1)->getPuissance() == TIR_PUISSANCE_SECONDAIRE)
					{
						if((*it1)->getY()>(*ite)->getY() && (*it1)->getY()+TIR_HEIGHT_SECONDAIRE<(*ite)->getY()+ENNEMI_HEIGHT		
						&& (*it1)->getX()>(*ite)->getX() && (*it1)->getX()+TIR_WIDTH_SECONDAIRE<(*ite)->getX()+ENNEMI_WIDTH 			
						&& !(*ite)->getTouche()&& (*it1)->getVivant())														
							(*ite)->etreTouche((*it1)->getPuissance());														
					}
																					
					else if((*it1)->getY()>(*ite)->getY() && (*it1)->getY()+TIR_HEIGHT<(*ite)->getY()+ENNEMI_HEIGHT		
					&& (*it1)->getX()>(*ite)->getX() && (*it1)->getX()+TIR_WIDTH<(*ite)->getX()+ENNEMI_WIDTH 			
					&& !(*ite)->getTouche()&& (*it1)->getVivant())														
					{
						(*ite)->etreTouche((*it1)->getPuissance());														
						(*it1)->setVivant(false);																		
					}
				}
			}
			else if((*it1)->getY()>_joueur->getY() && (*it1)->getY()+TIR_HEIGHT<_joueur->getY()+JOUEUR_HEIGHT		//si c'est un tir ennemi collision anvec le joueur
					&& (*it1)->getX()>_joueur->getX() && (*it1)->getX()<_joueur->getX()+JOUEUR_WIDTH
					&& (*it1)->getVivant())
			{
				_joueur->etreTouche((*it1)->getPuissance());
				(*it1)->setVivant(false);
			}					
			it1++;
		}
	}
	
//gestion du joueur					
	if (!_joueur->getVivant())						//s'il est mort on passe au game over
	{
		_clock.Reset();
		_jeu = false;
		_game_over=true;
	}
	else if(_joueur->getNbVies()<_vies_joueur)		//s'il a perdu une vie
	{												// on recommence le niveau
		_vies_joueur--;
		_jeu = false;
		_recommencer_niveau =true;
		_clock.Reset();			
	}
}	

//========================================
//chargement
//======================================
void GameModel::charger()
{
	if(_clock.GetElapsedTime()<_duree_chargement)						//pendant le chargement on gere l'animation de la sorciere
		_joueur->arriver(_duree_chargement,_clock.GetElapsedTime());

	else
	{
		_chargement = false;											//a la fin du chargement on crée le niveau et on passe au jeu
		_jeu = true;	
		creerNiveau();
	}
}

//==================================
//introduction
//==================================
void GameModel::introduire()
{
	if (_clock.GetElapsedTime()>_duree_intro)			
	{
		_intro = false;
		nouveauJeu();	
	}
	else
		_joueur->arriverIntro(_duree_intro,_clock.GetElapsedTime());   //animation de l'intro
	
}
//======================================
//restart du niveau apres perte d'une vie
//=====================================
void GameModel::restart()
{
	if (_clock.GetElapsedTime()>_duree_restart)			
	{
		_score_total-=_score_niveau;					//on enleve les points gagnés pendant le niveau
		creerNiveau();									//on recree le niveau
		_recommencer_niveau = false;
		_jeu = true;
	}	
	else if (_clock.GetElapsedTime()>_duree_restart/3)
		_joueur->arriver(_duree_restart/3,_clock.GetElapsedTime()-2);	//animation de la sorciere
}

///***************************************************
///METHODES DIVERSES
///***************************************************

//=================================
//création d'un tir
//==================================
void GameModel::creerTir()
{
	if (_joueur->getTirer())
	{
		Tir *t = new Tir(_joueur->getX()+JOUEUR_WIDTH,_joueur->getY()+JOUEUR_HEIGHT/2-TIR_HEIGHT/2,TIR_WIDTH,TIR_HEIGHT,TIR_X_SPEED,TIR_Y_SPEED,_joueur->getPuissance(),true,true);
		_new_tirs.push_back(t);				//il est ajouté à la liste de nouveaux tirs
	}
}
//==============================
void GameModel::creerTirSecondaire()
{
	if (_joueur->getTirerSecondaire())
	{
		Tir *t = new Tir(_joueur->getX()+JOUEUR_WIDTH,_joueur->getY()+JOUEUR_HEIGHT/2-TIR_HEIGHT/2,TIR_WIDTH_SECONDAIRE,TIR_HEIGHT_SECONDAIRE,TIR_X_SPEED_SECONDAIRE,TIR_Y_SPEED,_joueur->getPuissanceSecondaire(),true,true);
		_new_tirs.push_back(t);				//il est ajouté à la liste de nouveaux tirs
	}
}
//=======================================
// Fonctions pour afficher les infos
//=======================================

std::string GameModel::NiveauToString() const
{	
	std::ostringstream s;
	s<<"Niveau: "<<_niveau;
	return s.str();	
}
//=================================
std::string GameModel::EnnemisTuesToString() const
{	
	std::ostringstream s;
	s<<"Ennemis tues: "<<_nb_ennemis_touches<<"/"<<_nb_ennemis;
	return s.str();	
}
//=================================
std::string GameModel::ScoreToString() const
{	
	std::ostringstream s;
	s<<"Score: "<<_score_total;
	return s.str();	
}

//===================================
//création d'un niveau
//=================================
void GameModel::creerNiveau()
{				
	_nb_ennemis_touches =0;
	_score_niveau =0;
	
	std::list<Tir*>::iterator it1;	
	for (it1=_tirs.begin();it1!=_tirs.end();it1++)		
	{
		_ex_tirs.push_back(*it1);
		delete (*it1);
	}
	_tirs.clear();	
	
	for (it1=_new_tirs.begin();it1!=_new_tirs.end();it1++)		
	{
		_ex_tirs.push_back(*it1);
		delete (*it1);
	}
	_new_tirs.clear();	

	std::list<Ennemi*>::iterator it2;	
	for (it2=_ennemis.begin();it2!=_ennemis.end();it2++)		
	{
		_ex_ennemis.push_back(*it2);
		delete (*it2);
	}
	_ennemis.clear();
	

//creation des ennemis	
	int type =_niveau;
	if (_niveau >3)
	{
		type = 3;	
		_nb_ennemis=_niveau*5;
	}
	else
		_nb_ennemis=_nb_ennemis_de_base;
			
	for(int i =0;i<_nb_ennemis;i++)				
	{
		int proba = rand() % MODEL_HEIGHT;										//definit aléatoirement la pos
		float moment = (rand()%((_duree_niveau-12)*10))/10.0;					//definit aleatoirement le moment d'apparition entre 0 et le temps max du niveau-12
		_ennemis.push_back(new Ennemi(MODEL_WIDTH+ENNEMI_WIDTH,proba,ENNEMI_WIDTH, ENNEMI_HEIGHT,ENNEMI_X_SPEED,ENNEMI_Y_SPEED,type*2,true,type,false,moment));
	}
	
	_joueur->initialiser();
	_clock.Reset();
}
//==============================
//nouveau jeu
//=============================
void GameModel::nouveauJeu()
{	
	delete _joueur;
	_joueur = new Joueur(50, (_h-JOUEUR_HEIGHT)/2, JOUEUR_WIDTH, JOUEUR_HEIGHT, JOUEUR_X_SPEED, JOUEUR_Y_SPEED, JOUEUR_VIE, true, NB_VIES,TIR_PUISSANCE,TIR_PUISSANCE_SECONDAIRE);
	
	_niveau =0;
	_choix_menu = 0;
	_nb_ennemis_touches=0;
	_score_total =0;
	_score_niveau = 0;
	_vies_joueur=NB_VIES;
		
	_menu = true;
	_jeu = false;
	_chargement = false;
	_quitter = false;
	_game_over =false;
	_recommencer_niveau = false;
}

///***************************************************
///FONCTIONS RELATIVES AU MENU
///***************************************************

//=========================================
//valide le choix du menu courant
//========================================
void GameModel::validerMenu()
{
	switch (_choix_menu)
	{
		case ( 1):
		{
			_menu = false;
			_quitter = false;
			_jeu = false;
			_niveau++;
			creerNiveau();	
			_chargement = true;
			break;
		}

		case ( 2):
		{
			_menu = false;
			break;
		}
		case ( 3):
		{
			_jeu = false;
			_menu = false;
			_chargement = false;
			_quitter = true;
			break;
		}
		default:
		{
			_menu = true;
			_jeu = false;
			_quitter = false;
			_chargement = false;
			break;
		}
	}
}
//=======================================
//compare le choix courant avec un entier en parametre
//========================================
bool GameModel::ChoixMenuValide(int choix) const
{
	if(_choix_menu == choix)
		return true;
	else
		return false;
}


