package Affichage;

import processing.core.PApplet;

/**
 * @author johgarci
 *
 */
public class Salle {
	int x, y , color;
	boolean trap= false;
	
	public Salle(){};
	
	public Salle(int a, int b, int couleur, boolean piege){
		x=a; y=b; color=couleur; trap=piege;
	}
	
	public int getX(){
		return x;
	}
	
	public int getY(){
		return y;
	}
	
	public int getColor() {
		return color;
	}

	public void setColor(int color) {
		this.color = color;
	}
	
	public boolean isTrap() {
		return trap;
	}

	public void setTrap(boolean piege) {
		this.trap = piege;
	}
	
	public void dessinerSalle(Salle salle, Personnage character, PApplet p){
		float distance = distance2(p,character.salleActuelle, salle);
		dessinEclairee(distance, p);
		p.image(Labyrinthe.sol,salle.getX()*Dessin.tailleSalle,salle.getY()*Dessin.tailleSalle,Dessin.tailleSalle,Dessin.tailleSalle);
		p.noTint();
	}

	public void dessinerEnter(Salle Enter,Personnage character,PApplet p){
		float distance = distance2(p,character.salleActuelle, Enter);
		dessinEclairee(distance, p);
		p.image(Labyrinthe.enter,Enter.getX()*Dessin.tailleSalle,Enter.getY()*Dessin.tailleSalle,Dessin.tailleSalle,Dessin.tailleSalle);
		p.noTint();
	}
	
	public void dessinerOut(Salle Out,Personnage character, PApplet p){
		float distance = distance2(p,character.salleActuelle, Out);
		dessinEclairee(distance, p);
		p.image(Labyrinthe.out,Out.getX()*Dessin.tailleSalle,Out.getY()*Dessin.tailleSalle,Dessin.tailleSalle,Dessin.tailleSalle);
		p.noTint();
	}	
	
	public void dessinerTrap(Salle salle, Personnage character, PApplet p){
		float distance = distance2(p,character.salleActuelle, salle);
		dessinEclairee(distance, p);
		p.image(Labyrinthe.trap,salle.getX()*Dessin.tailleSalle,salle.getY()*Dessin.tailleSalle,Dessin.tailleSalle,Dessin.tailleSalle);
		p.noTint();
	}
	
	public void dessinEclairee(float distance, PApplet p){
		if(distance < 5){
			if(distance < 5 && distance>4)
				p.tint(255,40);
			
			if(distance >2 && distance<=4)
				p.tint(255,122);
				
			if(distance <=2)
				p.tint(255);
		}
		else
			p.tint(255, 0);
	}
	
	public float distance2(PApplet p, Salle c, Salle s){
		return p.dist(c.getX(), c.getY(), s.getX(), s.getY());
		
	}
}
