package Affichage;

import processing.core.*;

public class Personnage {
	PImage perso, vie;
	public Salle salleActuelle;
	int posX, posY;
	int nbVie=3;


	float tailleHeros = (float)(Dessin.tailleSalle/1.5);


	public Personnage(){}
	
	public Personnage(Salle salle){
		salleActuelle = salle;
	}
	
	public void setup(PApplet p){
		perso=p.loadImage("personnage.png");
		vie=p.loadImage("vie.png");
	}
	
	public void dessinerPersonnage(Salle SalleActuelle, PApplet p){
		p.image(perso,(SalleActuelle.getX())*Dessin.tailleSalle+(Dessin.tailleSalle-tailleHeros)/2,(SalleActuelle.getY()*Dessin.tailleSalle)+(Dessin.tailleSalle-tailleHeros)/2,tailleHeros,tailleHeros);
	}
	
	public void dessinerVie(PApplet p, Personnage perso){
		switch(perso.getNbVie()){
		case 3 : p.image(vie, Dessin.xLaby-100, Dessin.yLaby-20, Dessin.tailleSalle,Dessin.tailleSalle);
		case 2 : p.image(vie, Dessin.xLaby-60, Dessin.yLaby-20, Dessin.tailleSalle,Dessin.tailleSalle);
		case 1 : p.image(vie, Dessin.xLaby-20, Dessin.yLaby-20, Dessin.tailleSalle,Dessin.tailleSalle);
		}
	}
	
	public int getPosX(){
		return posX;
	}
	
	public int getPosY(){
		return posY;
	}
	
	public Salle getSalleActuelle() {
		return salleActuelle;
	}

	public void setSalleActuelle(Salle NewSalle) {
		salleActuelle = NewSalle;
		
	}

	public void setPosX(int x){
		posX = x; 
	}
	
	public void setPosY(int y){
		posY = y;
	}
	public int getNbVie() {
		return nbVie;
	}

	public void setNbVie(int nbVie) {
		this.nbVie = nbVie;
	}
}
