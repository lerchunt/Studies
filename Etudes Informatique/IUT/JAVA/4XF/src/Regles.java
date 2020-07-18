import processing.core.PApplet;
import processing.core.PImage;


public class Regles {
	
	private PImage fond,retourMenu,imageJoueur,imageEnnemi,imageNeutre,science,attaque,finTour;
	private Menu m;
	private boolean locked;

	public Regles(){}
	public Regles(PApplet p){}
	
	//chargement des images, initialisation du menu
	public void setup(PApplet p,Menu m){
		fond = p.loadImage("images/fondRegles2.png");
		retourMenu = p.loadImage("images/retourMenu.png");
		imageJoueur = p.loadImage("images/Humain.png");
		imageEnnemi = p.loadImage("images/Ennemi1.png");
		imageNeutre = p.loadImage("images/Neutre.png");
		science = p.loadImage("images/Science.png");
		attaque = p.loadImage("images/Attaque.png");
		finTour=p.loadImage("images/finDeTour.png");
		
		this.m=m;
	}
	public void draw(PApplet p){
		p.background(fond);
		p.image(retourMenu, 1025, 650);
		ecrireRegles(p);
	}
	public void MousePressed(PApplet p) {
		if((p.mousePressed)&&(p.mouseX>1025) && (p.mouseX<1125) && (p.mouseY>650)&& (p.mouseY<750) && this.locked==false){
			locked=true;
			m.MousePressed(p);
			m.setChoix(0);
			locked=false;
			m.setLocked(false);
		}
	}

	public void ecrireRegles(PApplet p){
		p.text("Bienvenu sur notre projet, nous allons vous expliquer comment devenir un pro a ce jeu fabuleux!", 10, 200);
		p.text("Tout d'abord, vous etes le dirigean de la planete verte qui ressemble a ca !",10, 230);
		p.image(imageJoueur, 500,210);
		p.text("Vos ennemis sont les planetes qui sont identifiees par Ennemi0, Ennemi1 et Ennemi2",10 ,300);
		p.image(imageEnnemi, 580, 270);
		p.text("Vous avez aussi des planetes neutres que vous pouvez conquerir pour vous agrandir",10,350);
		p.text("Ce sont les planetes qui resemblent a ca -->", 10, 400);
		p.image(imageNeutre, 300, 360);
		
		p.text("Vous avez deux victoires possibles :", 10, 430);
		p.text("La victoire par conquete -> vous devez eradiquer toutes les planetes et dominer la carte !", 10, 450);
		p.text("La victoire par technologie -> Arrivez a 200 de technologie !", 10, 470);
	
		p.text("A chaque tour, vous gagnez 100 $, c'est la ressource de base du jeu. Chaque action vous coute 100$",10, 500);
		p.text("Avec cela plusieurs choix s'offrent a vous. Vous pouvez augmenter votre technologie grace cette petite icone", 10, 515);
		p.image(science, 700, 500);
		p.text("Vous pouvez attaquer grace a  l'icone :", 10, 540);
		p.image(attaque, 270, 520);
		p.text("Vous pouvez attaquer tant que vous avez des sous mais vous pouvez faire de la technologie qu'une seule fois par tour", 10, 560);
		p.text("Quand vous avez fini, cliquez sur 'Fin de tour'", 10 ,580 );
		p.image(finTour, 300, 570);
	}
}