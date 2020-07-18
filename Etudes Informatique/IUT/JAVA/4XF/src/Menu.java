import processing.core.PApplet;
import processing.core.PImage;


public class Menu {

	static int TAILLEW=1152;
	static int TAILLEH=720;
	int choix = 0;

	PImage jeu,regleJeu,quitter,fond,regles,credits;
	private boolean locked = false;
	
	public Menu(PApplet p){}
	public Menu() {}
	
	public void setup(PApplet p){
		fond=p.loadImage("images/fond.png");
		jeu=p.loadImage("images/boutonJouer.jpg");
		regleJeu=p.loadImage("images/boutonRegle.jpg");
		quitter=p.loadImage("images/boutonQuitter.jpg");
		credits=p.loadImage("images/boutonCredit.png");
		regles=p.loadImage("images/fondRegles2.png");
		
	}
	
	public void draw(PApplet p){
		p.background(fond);
		p.image(jeu, TAILLEW/2-100, 70);
		p.image(regleJeu, TAILLEW/2-100, 230);
		p.image(quitter, TAILLEW/2-100, 390);
		p.image(credits, TAILLEW/2-100, 540);
	}
	
	public void MousePressed(PApplet p){
		if((p.mousePressed) && (p.mouseX>TAILLEW/2-100) && (p.mouseX<TAILLEW/2+100) && (p.mouseY>70)&& (p.mouseY<170) && this.locked==false){
			this.locked=true;
			this.setChoix(1);
		}
		if((p.mousePressed) && (p.mouseX>TAILLEW/2-100) && (p.mouseX<TAILLEW/2+100) && (p.mouseY>230)&& (p.mouseY<330) && this.locked==false){
			this.locked=true;
			this.setChoix(2);
		}
		if((p.mousePressed) && (p.mouseX>TAILLEW/2-100) && (p.mouseX<TAILLEW/2+100) && (p.mouseY>390)&& (p.mouseY<490) && this.locked==false){
			this.locked=true;
			this.setChoix(3);
		}
		if((p.mousePressed)&&(p.mouseX>TAILLEW/2-100) && (p.mouseX<TAILLEW/2+100) && (p.mouseY>540)&& (p.mouseY<640) && this.locked==false){
			this.locked=true;
			this.setChoix(4);
		}
	}
	
	public int getChoix() {
		return choix;
	}
	
	public void setChoix(int choix) {
		this.choix = choix;
	}
	public void setLocked(boolean b){
		this.locked=b;
	}
}