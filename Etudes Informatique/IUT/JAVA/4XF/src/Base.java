

import java.util.ArrayList;

import processing.core.PApplet;
import processing.core.PImage;


public class Base {
	
	private int unite;
	private Joueur j;
	int x,y;
	int population;
	PImage fenetre;
	boolean aVoisineHumaine;
	public ArrayList<Base>mes_bases_liees=new ArrayList<Base>();
	Jeu jeu;
	

	Base(int unite, int x, int y, int population)
	{
		this.unite=unite;
		this.x = x;
		this.y=y;
		this.population=population;
	
	}
	public void draw(PApplet p){
		p.image(this.getJoueur().getImage(), this.getX(),this.getY() );
		this.afficherJoueur(p);
		this.afficherInfo(p);
	}
	
	public void afficherJoueur(PApplet p){
		p.textSize(12);
		p.text(this.getJoueur().getNom(), this.getX()+10, this.getY()+80); 

	}
	
	public void afficherInfo(PApplet p){
		if(p.mouseX>this.getX() && p.mouseX<this.getX()+60 && p.mouseY>this.getY() && p.mouseY<this.getY()+60){
			p.image(this.fenetre, this.getX(), this.getY());
			
				if(aVoisineHumaine==true)
				{
					p.textSize(15);
					p.text("unité", this.getX()+45, this.getY()+95);
					p.text(this.getUnite(), this.getX()+90, this.getY()+95);
				}
				else{
					p.textSize(12);
					p.text("Aucune base voisine" ,this.getX()+15, this.getY()+95);
					p.text("Information Masquée" ,this.getX()+15, this.getY()+115);
				}
		}
	}
	public int getUnite(){
		return unite;
	}
	
	public void setUnite(int u){
		this.unite=u;
	}
	public void setJoueur(Joueur j){
		this.j=j;
	}
	public Joueur getJoueur(){
		return this.j;
	}
	public int getX() {
		return x;
	}
	public void setX(int x) {
		this.x = x;
	}
	public int getY() {
		return y;
	}
	public void setY(int y) {
		this.y = y;
	}
	public void setFenetre(PImage fenetre){
		this.fenetre=fenetre;
	}
	public void enregistrerVoisine(PApplet p,Jeu jeu){
		for(Base b:jeu.getBase()){
			if(jeu.distance(p, this, b)<230)
				mes_bases_liees.add(b);
		}
		
	}
	public void attaquerBase(Base b2){
		if(getUnite()>= b2.getUnite()){ 		
			
			b2.setUnite((int) (getUnite()*0.25));
			setUnite((int) (getUnite()-(0.25*getUnite())));
			b2.getJoueur().subbBase(b2);
		
			b2.setJoueur(j);
			j.addBase(b2);
			getJoueur().setRessource(getJoueur().getRessource()-100);
		}
		else{
			b2.setUnite((int) (b2.getUnite()-0.25*(b2.getUnite())));
			setUnite((int) (0.25*b2.getUnite()));
			getJoueur().subbBase(this);
		
			b2.getJoueur().addBase(this);
			setJoueur(b2.getJoueur());
			
		}
		
			
		
	}
	public void initAVoisineHumaine(){
		aVoisineHumaine=false;
		for(Base b:mes_bases_liees)
			if(b.getJoueur() instanceof JoueurHumain)
				aVoisineHumaine=true;
	}
	public ArrayList<Base> getLiee(){
		return this.mes_bases_liees;
	}
	public void setJeu(Jeu jeu){
		this.jeu=jeu;
	}
	public Jeu getJeu(){
		return this.jeu;
	}

}
