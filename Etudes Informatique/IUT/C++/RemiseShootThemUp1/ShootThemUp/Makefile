CXXFLAGS= -g -Wall -pedantic
LDFLAGS= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system 

%: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS)  -o $@ $^ $(LDFLAGS) 

execs     = jeu

all: $(execs)

jeu: jeu.o Personnage.o  GameModel.o  GameView.o  MovableElement.o Joueur.o Ennemi.o Tir.o EnnemiSprite.o JoueurSprite.o FondSprite.o AnimeGraphicElement.o GraphicElement.o 

# -------------------------------------------------------------
clean:
	$(RM) *~ *.o *.bak 

mrproper: clean
	$(RM) $(execs)

#----------------------------------------------------------------
# pour mettre à jour les dépendances ci-dessous
depend:
	makedepend -Y *.cc

# DO NOT DELETE

jeu.o: GameView.h GameModel.h 

GameModel.o: GameModel.h Joueur.h Ennemi.h Tir.h jeu_const.h
GameView.o: GameView.h GameModel.h JoueurSprite.h EnnemiSprite.h FondSprite.h GraphicElement.h 

MovableElement.o: MovableElement.h jeu_const.h
Tir.o: Tir.h 
Vaisseau.o: Vaisseau.h 
Ennemi.o: Ennemi.h 
Joueur.o: Joueur.h 

AnimeGraphicElement: AnimeGraphicElement.h
EnnemiSprite: EnnemiSprite.h 
JoueurSprite: JoueurSprite.h 
FondSprite: FondSprite.h 
GraphicElement.o: GraphicElement.h
