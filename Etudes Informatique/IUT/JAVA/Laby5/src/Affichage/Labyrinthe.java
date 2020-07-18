package Affichage;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.ListIterator;

import processing.core.*;

public class Labyrinthe {
	int x, y , color, abs, ord, width, height, enterX, enterY, outX, outY,abs2,ord2, Nb;
	static int TAILLEW, TAILLEH;
	boolean fini = false;
    private ArrayList<Salle> liste = new ArrayList<Salle>();
	private Salle Enter, Out, NewSalle;
	static PImage sol, enter, out, mur, trap;
	Personnage character;
	private String[] loadWay, way, loadWay2, way2; 
	
	public Labyrinthe(PApplet p){}
	
	public void setup(PApplet p)
	{
		sol=p.loadImage("blanc.png");
		enter=p.loadImage("enter.png");
		out=p.loadImage("out.png");
		mur=p.loadImage("fond.jpg");
		trap=p.loadImage("trap.png");
		
		
		loadWay = p.loadStrings("level2.txt");
		way = PApplet.split(loadWay[0],' ');
		TAILLEW = Integer.parseInt(way[0]);
		TAILLEH = Integer.parseInt(way[1]);
			
		way = PApplet.split(loadWay[1],' ');
		enterX = Integer.parseInt(way[0]);
		enterY = Integer.parseInt(way[1]);
			
		way = PApplet.split(loadWay[2],' ');
		outX = Integer.parseInt(way[0]);
		outY = Integer.parseInt(way[1]);
		
		Enter = new Salle(enterX, enterY, 1, false);
		Out = new Salle(outX, outY, 2, false);
		character = new Personnage(Enter);

		p.size(TAILLEW*21,TAILLEH*21);
		entrer(character);
		character.setup(p);
	}	
	
	public void draw(PApplet p){
		dessinerFond(p);
		character.dessinerVie(p, character);

		for(Salle s : liste){
			switch(s.getColor()){
			case 0 : if(s.isTrap())
						 s.dessinerTrap(s,character,p);
					 else
						 s.dessinerSalle(s,character,p);
				     break;
			case 1 : s.dessinerEnter(Enter, character, p);break;
			case 2 : s.dessinerOut(Out, character, p);break;
			}
		}
		
		character.dessinerPersonnage(character.getSalleActuelle(),p);
		sortir(character, p);
	}
	
    public void dessinerLabyrinthe(PApplet p){
    	int i;
    	Salle room;
    	liste.add(Enter);
		liste.add(Out);
    	for(i=3; i<loadWay.length; i++){
        	Nb=(int) p.random(800);
    		way = PApplet.split(loadWay[i],' ');
    		abs = Integer.parseInt(way[0]);
    		ord = Integer.parseInt(way[1]);
    		if (Nb < 40)
    			room = new Salle(abs, ord, 0, true);
    		else
    			room= new Salle(abs, ord, 0, false);
    		liste.add(room);
    	}
    }

	public void entrer(Personnage heros){
		heros.posX = enterX;
		heros.posY = enterY;
	}
	
	public void sortir(Personnage heros, PApplet p){
		if(heros.posX == Out.getY() && heros.posY == Out.getY()){
			System.out.println("GAGNER");
			System.exit(0);
		}

	}
	
	public void keyPressed(PApplet p){
		
		if(p.keyPressed == true){
			switch (p.key){
				case 'z': NewSalle = new Salle(character.getSalleActuelle().x, character.getSalleActuelle().y-1, character.getSalleActuelle().getColor(), character.getSalleActuelle().isTrap());
						  if(voisin(NewSalle)){
								character.setPosY(character.getPosY()-1);
								character.setSalleActuelle(NewSalle);
								for(Salle s:liste){
									if(s.isTrap()&& s.getX()==character.getSalleActuelle().getX() &&s.getY()==character.getSalleActuelle().getY())
									character.setNbVie(character.getNbVie()-1);
								}
						  }
						 
				break;
				
				case 'd': NewSalle = new Salle(character.getSalleActuelle().x+1, character.getSalleActuelle().y, character.getSalleActuelle().getColor(), character.getSalleActuelle().isTrap());
						  if(voisin(NewSalle)){
								character.setPosX(character.getPosX()+1);
								character.setSalleActuelle(NewSalle);
								for(Salle s:liste){
									if(s.isTrap()&& s.getX()==character.getSalleActuelle().getX() &&s.getY()==character.getSalleActuelle().getY())
									character.setNbVie(character.getNbVie()-1);
								}
						  }
						  
						  
				break;
				
				case 'q': NewSalle = new Salle(character.getSalleActuelle().x-1, character.getSalleActuelle().y, character.getSalleActuelle().getColor(), character.getSalleActuelle().isTrap());
						  if(voisin(NewSalle)){
								character.setPosX(character.getPosX()-1);	
								character.setSalleActuelle(NewSalle);
								for(Salle s:liste){
									if(s.isTrap()&& s.getX()==character.getSalleActuelle().getX() &&s.getY()==character.getSalleActuelle().getY())
									character.setNbVie(character.getNbVie()-1);
								}
						  }
						  
						  //character.getSalleActuelle().recevoirPersonnage(character);
				break;
			
				case 's': NewSalle = new Salle(character.getSalleActuelle().x, character.getSalleActuelle().y+1, character.getSalleActuelle().getColor(), character.getSalleActuelle().isTrap());
						  if(voisin(NewSalle)){
								character.setPosY(character.getPosY()+1);
								character.setSalleActuelle(NewSalle);
								for(Salle s:liste){
									if(s.isTrap()&& s.getX()==character.getSalleActuelle().getX() &&s.getY()==character.getSalleActuelle().getY())
									character.setNbVie(character.getNbVie()-1);
								}
						  }
						  
						  //character.getSalleActuelle().recevoirPersonnage(character);
				break;
			}
			System.out.println(character.getNbVie());
		}
	}
	
	public boolean voisin(Salle NewSalle){
		boolean trouve=false;
		Salle s;
		Iterator<Salle> i=liste.iterator();
		while (trouve==false && i.hasNext() ){
			s=i.next();
			if (NewSalle.getX()==s.getX() && NewSalle.getY()==s.getY())
				trouve=true;
		}
		return trouve;
	}
	
	public void dessinerFond(PApplet p){
		p.image(mur,0,0,Dessin.xLaby, Dessin.yLaby);
	}
	
	public int getEnterX(){
		return enterX;
	}
	
	public int getEnterY(){
		return enterY;
	}
	
	public Personnage getCharacter() {
		return character;
	}

	public void setCharacter(Personnage perso) {
		character = perso;
	}
}