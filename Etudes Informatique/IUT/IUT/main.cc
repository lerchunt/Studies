using namespace std;
#include "function.h"
#include "niveau.h"
#include "menu.h"

/************************ isLost ****************************
∗ renvois vrai si la partie est perdu.                      *
******************** Auteur , Dates *************************
* Nom/Date:Éventuellement la version			            *
*********************** Entrées *****************************
∗ niveau n : structure niveau à tester.                     *
*************************************************************/
bool isLost(niveau n){
	if(n.end){
		int cpt=0;
		for(int i=0; i<NB_CANARD_PAR_NIVEAU; i++)
			if(!n.listeCanard[i].alive)
				cpt++;
		if(cpt>=6) return false;
		else      return true;
	}
}

/********************* looseScreen **************************
∗ Affiche l'écran GameOver.                                 *
******************** Auteur , Dates *************************
* Nom/Date:Éventuellement la version			            *
*********************** Entrées *****************************
∗ int score : contient le score pour l'afficher.            *
* ressource r : contient les ressources nécéssaires.        *
*************************************************************/
void looseScreen(int score, ressource r){
	SDL_Surface *screen, *GameOver, *scoreTxtSurface, *scoreSurface;
	
	SDL_Color textColor= {255,255,255};
	fstream f;
	f.open("score",ios::in);
	
	int tabScore[NB_SCORE_A_GARDER], i=0, previousData, data;
	
	for(int k=0; k<NB_SCORE_A_GARDER-1; k++){
		tabScore[k]=NULL;
	}
	
	while(!f.eof()){
		previousData=data;
		f >> data;
		if(data<score){
			if(previousData>score || i==0)
				tabScore[i]=score;
			tabScore[i+1]=data;
		}
		else
			tabScore[i]=data;
		i++;
	}
	f.close();
	f.open("score",ios::out);
	for(int k=0; k<NB_SCORE_A_GARDER-1; k++){
		f << tabScore[k] << " ";
	}
	screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);

	GameOver = TTF_RenderText_Blended(r.fatFonts, "GAME OVER", textColor);
	scoreTxtSurface = TTF_RenderText_Blended(r.mediumFonts, "SCORE:", textColor);
	scoreSurface = TTF_RenderText_Blended(r.mediumFonts, int2string(score).c_str(), textColor);
	
	for(int i=0; i<500; i++){
		SDL_FillRect(screen,&screen->clip_rect,
                  SDL_MapRGB(screen->format,0,193,255));
		applySurface(0,0,r.background,screen,NULL);
		applySurface(SCREEN_WIDTH/2-160,SCREEN_HEIGHT/2-200,GameOver,screen,NULL);
		applySurface(SCREEN_WIDTH/2-100,SCREEN_HEIGHT/2-135,scoreTxtSurface,screen,NULL);
		applySurface(SCREEN_WIDTH/2-100,SCREEN_HEIGHT/2-100,scoreSurface,screen,NULL);
		SDL_Flip(screen);
	}
}

/********************** highScores **************************
∗ Affiche les 10 meilleurs scores.                          *
******************** Auteur , Dates *************************
* Nom/Date:Éventuellement la version			            *
*********************** Entrées *****************************
* ressource r : contient les ressources nécéssaires.        *
*********************** Sorties *****************************
∗ bool &quit : variable qui indique si le jeu doit se fermer.*	                           	  
*************************************************************/
void highScores(ressource r, bool &quit){
	SDL_Surface *screen, *scoreSurface, *scoreTxtSurface;
	SDL_Color textColor, defaultColor={255,255,255}, gold={255,215,0}, silver={206,206,206}, bronze={137,78,26};
	screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
	string line, hightTxt="High Scores";
	scoreTxtSurface = TTF_RenderText_Blended(r.fatFonts, hightTxt.c_str(), defaultColor);
	SDL_Event event;
	
	fstream f;
	f.open("score",ios::in);
	
	int score, j, i=0, tabScore[NB_SCORE_A_GARDER];

	while(!f.eof()){
			f >> tabScore[i];
			i++;
	}
	while(!quit){
		applySurface(0,0,r.title,screen,NULL);
		applySurface(240,20,scoreTxtSurface,screen,NULL);
		for(j=0; j<NB_SCORE_A_GARDER-1; j++){
			switch(j){
				case 0: textColor=gold; break;
				case 1: textColor=silver; break;
				case 2: textColor=bronze; break;
				default: textColor=defaultColor; break;
		}
		
		line=int2string(j+1)+" : "+int2string(tabScore[j]);
		scoreSurface = TTF_RenderText_Blended(r.mediumFonts, line.c_str(), textColor);
		applySurface(300,100+j*40,scoreSurface,screen,NULL);
		SDL_FreeSurface(scoreSurface);
		i++;
		}
		SDL_Delay(100);
		SDL_Flip(screen);
		SDL_FreeSurface(screen);
		
		while(SDL_PollEvent(&event))
			if(event.type==SDL_QUIT)
				quit=true;
	}
}
/////////////////////////////////////////////////////////
//////////////// FONCTION PRINCIPALE ////////////////////
/////////////////////////////////////////////////////////
int main( int argc, char* args[] )
{
	srand(time(NULL));
	SDL_Surface *screen;
	
	SDL_Init(SDL_INIT_EVERYTHING);
    screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,
                            SCREEN_BPP,SDL_SWSURFACE);
    
    niveau n;
    n.level=0;
	n.score=0;
	
    ressource r;
    load(r);
    
    int select;

    bool loose=false, quit=false;

	while(!quit){
		select=menu(r);
		n.level=0;
		n.score=0;
		if(select==0)
			quit=true;
		else if(select==1){
			highScores(r, quit);
		}
		else if(select==2){
			while(!loose && !quit){
				initNiveau(n);
				makeNiveau(n,r,quit);
				loose=isLost(n);
			}
			if(loose && !quit){
				looseScreen(n.score,r);
				loose=false;
			}
		}
	}

 return 0;
}
