


import java.util.ArrayList;

import processing.core.PImage;

public abstract class Joueur {
	int ressource;
	int technologie=0;
	String nom;
	private PImage image;
	ArrayList<Base>mes_bases=new ArrayList<Base>();
	Jeu j;
	
	
	Joueur(int ressource,String nom){
		this.ressource=ressource;
		this.nom=nom;
	}
	public void addBase(Base b){
		this.mes_bases.add(b);
	}
	public void subbBase(Base b){
		for (int i=0; i<mes_bases.size(); i++) {
			 Base b1 = mes_bases.get(i);
			 	if (b1 == b) {
			 		mes_bases.remove(i);
			 		break;
			 	} 
        }
	}
	public void setImage(PImage image){
		this.image=image;
	}
	public PImage getImage(){
		return this.image;
	}
	public void agir(){

	}
	public String getNom(){
		return this.nom;
	}
	public int getRessource(){
		return this.ressource;
	}
	public int getTechnologie(){
		return this.technologie;
	}
	public void setRessource(int ressource) {
		this.ressource = ressource;
	}
	public void setTechnologie(int technologie) {
		this.technologie = technologie;
	}
	public void setNom(String nom){
		this.nom=nom;
	}
	public ArrayList<Base> getBase(){
		return this.mes_bases;
	}
	public void subbJoueur(){
		this.j.getJoueurs().remove(this);
	}
	public Jeu getJeu(){
		return this.j;
	}
}
