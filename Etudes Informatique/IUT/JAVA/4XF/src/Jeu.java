import java.io.File;
import java.util.ArrayList;
import processing.core.PApplet;
import processing.core.PImage;


public class Jeu {
	
	
	private ArrayList<Base> bases = new ArrayList<Base>() ;
	private ArrayList<Joueur> joueurs = new ArrayList<Joueur>();
	private Joueur jp;
	static PImage fond, joueurHumain, joueurEnnemi0,joueurEnnemi1,joueurEnnemi2,joueurEnnemi3, joueurNeutre, fin,fenetreBase;
	
	static int TAILLEW=1152;
	static int TAILLEH=720;
	private int abs,ord,jou;
	
	private String[] loadWay, way;
	public boolean locked=false;
	
	
	public Jeu(){}
	public Jeu(PApplet p){}
	
	public void setup(PApplet p){
		File baseFic = new File("bases.txt");
		fond=p.loadImage("images/fond.png");
		joueurHumain=p.loadImage("images/Humain.png");
		joueurNeutre=p.loadImage("images/Neutre.png");
		joueurEnnemi0=p.loadImage("images/Ennemi0.png");
		joueurEnnemi1=p.loadImage("images/Ennemi1.png");
		joueurEnnemi2=p.loadImage("images/Ennemi2.png");
		joueurEnnemi3=p.loadImage("images/Ennemi3.png");
		loadWay=p.loadStrings("bases.txt");
		fin=p.loadImage("images/finDeTour.png");
		fenetreBase=p.loadImage("images/fenetreBase.png");
	}
	
	public void draw(PApplet p){
		p.image(fond,0,0,TAILLEW,TAILLEH);
		p.image(fin, 0, 0,20,20);
		for(Base b:bases){
			for(Base b1:bases)
				if(b1!=b)
					this.dessinerTrait(p, b, b1);
		}
		
		for(Base b:bases)
			b.draw(p);
		if(this.Gagner()){
			p.textSize(32);
			p.text("Bravo,  vous avez gagné!!!",655, 670);
			p.noLoop();
		}
		if (this.Perdu()){
			p.textSize(32);
			p.text("Perdu", 655, 670);		
			p.noLoop();
		}
	}
	public void initialiser_bases(PApplet p){
		int i;
		Base b;
		Joueur j;
		for (i=0; i<loadWay.length; i++){
			way = PApplet.split(loadWay[i],' ');
    		abs = Integer.parseInt(way[0]);
    		ord = Integer.parseInt(way[1]);
    		jou =Integer.parseInt(way[2]);
    		b=new Base(100,abs,ord,1);
    		b.setFenetre(fenetreBase);
    		b.setJeu(this);
    		Joueur jn=new JoueurNeutre(0,"Neutre");
    		joueurs.add(jn);
    		jn.setImage(joueurNeutre);
    		
    		switch (jou){
	    		case 1: 
	    				j=new JoueurHumain(100,"Humains");
	    				joueurs.add(j);
	    				jp=j;
	    				j.setImage(joueurHumain);
	    				b.setJoueur(j);
	    				j.addBase(b);
	    			break;
	    		case 2: 
	    				b.setJoueur(jn);
	    				jn.addBase(b);
	    				b.setUnite(0);
	    			break;
	    		case 3: 
	      				j=new JoueurArtificiel(100,"Ennemi"+i);
	      				joueurs.add(j);
		      				if(i==0)
		      					j.setImage(joueurEnnemi0);
		      				else if(i==1)
		      					j.setImage(joueurEnnemi1);
		      				else if(i==2)
		      					j.setImage(joueurEnnemi2);
		      				else
		      					j.setImage(joueurEnnemi3);
	    				b.setJoueur(j);
	    				j.addBase(b);
	    			break;
    		}

    		bases.add(b);
    		for(Base s:bases)
    			s.enregistrerVoisine(p,this);
    		for(Base s:bases)
    			s.initAVoisineHumaine();
		}
	}
	
	public void dessinerTrait(PApplet p, Base b1, Base b2){
		if(distance(p,b1,b2)<230){
			p.stroke(255);
			p.line(b1.getX()+30, b1.getY()+30, b2.getX()+30, b2.getY()+30);
		}
	}
	/*Calcule la distance entre 2 bases et la retourne*/
	public float distance(PApplet p, Base c, Base s){
		return PApplet.dist(c.getX(), c.getY(), s.getX(), s.getY());
	}
	public ArrayList<Base> getBase(){
		return bases;	
	}
	public Joueur getJoueurPrincipal(){
		return jp;
	}
	public ArrayList<Joueur> getJoueurs(){
		return joueurs;
	}
	public ArrayList<Base> getBases(){
		return bases;
	}
	
	/* Méthode qui rencoie true si le joueur est vainqueur (victoire par technologie ou par conquete */
	public boolean Gagner(){
		boolean g=true;
		boolean t=false;
		for(Base b: bases){
			if(!(b.getJoueur() instanceof JoueurHumain))
				g=false;
		}
		if (getJoueurPrincipal().getTechnologie()>=200)
			t =true;
		return (g||t);
	}
	/* Méthode qui rencoie true si le joueur a perdu (un joueur ennemi ne peut gagner que par conquete */
	public boolean Perdu(){
		boolean p=true;
		for(Base b:bases){
			if(b.getJoueur() instanceof JoueurHumain)
				p=false;
		}
		return p;
	}
}