package Affichage;

import processing.core.*;

public class Dessin extends PApplet{
	static int tailleSalle = 20;
	static int taillePiege =20;
	Labyrinthe laby = new Labyrinthe(this);
	static int xLaby, yLaby;
	public void setup(){
		laby.setup(this);
		laby.dessinerLabyrinthe(this);
		xLaby = (Labyrinthe.TAILLEW+2)*tailleSalle;
		yLaby = (Labyrinthe.TAILLEH+2)*tailleSalle;
		textSize(18);
	}
	
	public void draw(){
		frameRate(20);
		laby.keyPressed(this);
		laby.draw(this);
	}

	public static void main (String[] args){
		PApplet.main("Application");
	}	
}