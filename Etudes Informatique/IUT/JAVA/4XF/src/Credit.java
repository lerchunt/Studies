import processing.core.PApplet;
import processing.core.PImage;


public class Credit {
	private PImage fond,retourMenu, IUT;
	private Menu m;
	private boolean locked;
	
	public Credit(){}
	public Credit(PApplet p){}
	
	public void setup(PApplet p,Menu m){
		fond = p.loadImage("images/fondCredit.png");
		retourMenu = p.loadImage("images/retourMenu.png");
		IUT=p.loadImage("images/IUT.png");
		this.m=m;
	}
	
	public void draw(PApplet p){
		p.background(fond);
		p.image(retourMenu, 1025, 650);
		p.image(IUT, 100, 100);
		ecrireCredit(p);
	}
	
	public void MousePressed(PApplet p){
		if((p.mousePressed)&&(p.mouseX>1025) && (p.mouseX<1125) && (p.mouseY>650)&& (p.mouseY<700) && this.locked==false){
			locked=true;
			m.MousePressed(p);
			m.setChoix(0);
			locked=false;
			m.setLocked(false);
		}
	}
	public void ecrireCredit(PApplet p){
		p.textSize(15);
		p.text("Tous les sprites ont été réalisé avec Gimp, hormis le sprite de fond qui est libre de droit", 10,400 );
		p.text("Auteurs : Antoine Lemasson, Thomas Lerchundi", 10, 500);
		p.text("Annee 2014, S4P2B", 10, 520);
		
	}
}
