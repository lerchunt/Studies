#include "GameView.h"
#include "GameModel.h"
#include "jeu_const.h"
#include <iostream>
using namespace std;

int main(){
 
  GameModel * model = new GameModel(MODEL_WIDTH, MODEL_HEIGHT);
  GameView * view = new GameView(VIEW_WIDTH, VIEW_HEIGHT, VIEW_BPP);
  view->setModel(model);
  
	while(view->treatEvents(model))
	{
		model->nextStep();
		view->synchronize();
		view->draw();
	}

  delete view;
  delete model;
  
  return EXIT_SUCCESS;
}
