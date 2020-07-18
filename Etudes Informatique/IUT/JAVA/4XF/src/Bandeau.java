import processing.core.PApplet;
import processing.core.PImage;


public class Bandeau {
	PImage fond;
	PImage economies;
	PImage attaque;
	PImage science;
	PImage fin;
	Joueur joueur;
	boolean b1,b2,cible,lancerAttaque,perdu=false;
	boolean techno=true;
	Base attaquante,victime;
	
	public void setup(PApplet p, Joueur j){
		this.joueur=j;
		this.fond=p.loadImage("images/bandeau.png");
		this.economies=p.loadImage("images/Economie.png");
		this.attaque=p.loadImage("images/Attaque.png");
		this.science=p.loadImage("images/Science.png");
		this.fin=p.loadImage("images/finDeTour.png");
	}
	
	public void draw(PApplet p,Jeu jeu){
		p.textSize(15);
		p.image(fond,0,0);
		p.image(economies,50, 2);
		p.text(": "+joueur.getRessource(), 80, 20);
		
		p.image(science, 150, 2);
		p.text(": "+joueur.getTechnologie(), 180, 20);
		p.image(attaque,250 ,2);
		p.image(fin,500,0);

	}
	
	public void setJoueur(Joueur j){
		this.joueur = j;
	}
	public void MousePressed(PApplet p,Jeu j){
		if((p.mousePressed)&&(p.mouseX>500)&&(p.mouseX<680) && (p.mouseY<25)&&j.locked==false){
			j.locked=true;
			techno=true;
			for(Joueur jo:j.getJoueurs()){ 
				if (jo instanceof JoueurArtificiel ){
					jo.setRessource(jo.getRessource()+100);
					jo.agir();
					//if(jo.getBase().size()==0)
					//	jo.getJeu().subbJoueur(jo);
					
				}
				else if (jo instanceof JoueurHumain){
					jo.agir();
					jo.setRessource(jo.getRessource()+100);
					}
						
					
				
			}
		}
		if(!p.mousePressed)
			j.locked=false;
		
		this.actionAttaque(p,j);
		if (cible==true){
			selectionerCible(p,j,this.attaquante);
			if(lancerAttaque==true){
				if(j.distance(p, attaquante, victime)<230 && attaquante.getJoueur()!=victime.getJoueur())
				attaquante.attaquerBase(this.victime);
				lancerAttaque=false;
				for(Base base1:j.getBase())
					base1.initAVoisineHumaine();
			}
		}
		selectionerTechno(p, j);
	}
	
	public void actionAttaque(PApplet p,Jeu j){
		if (p.mousePressed && p.mouseX>=250 && p.mouseX<=285 && p.mouseY>=2 && p.mouseY<=27 || this.b1==true){
				if(j.getJoueurPrincipal().getRessource()>60){
				b1=true;
				p.textSize(30);
				p.text("Selectionnez la base attaquante", 655,670 );
					if(p.mousePressed){
							for(Base base:j.getBase())
								if(p.mouseX>=base.getX() && p.mouseX<=base.getX()+60 && p.mouseY>=base.getY() && p.mouseY<=base.getY()+60 && base.getJoueur() instanceof JoueurHumain){
								  	b1=false;
									cible=true;
									attaquante=base;
								}
					}
			}
		}
	}
	public void selectionerCible(PApplet p,Jeu j,Base attaquante){
			if(this.cible==true){
			p.textSize(30);
			p.text("Selectionnez votre cible",655,670);
			if (p.mousePressed){
				for (Base base:j.getBase())
					if(p.mouseX>=base.getX() && p.mouseX<=base.getX()+60 && p.mouseY>=base.getY() && p.mouseY<=base.getY()+60 && !(base.getJoueur() instanceof JoueurHumain)){
						cible=false;
						lancerAttaque=true;
						victime=base;
					}
			}
		}
	}
	public void selectionerTechno(PApplet p, Jeu jeu){
		
		if(((p.mousePressed && p.mouseX >=150 && p.mouseX<=175 && p.mouseY<=28)) && this.techno==true){
			
			if(jeu.getJoueurPrincipal().getRessource()>=100){
				techno=false;
				jeu.getJoueurPrincipal().setTechnologie(jeu.getJoueurPrincipal().getTechnologie()+10);
				jeu.getJoueurPrincipal().setRessource(jeu.getJoueurPrincipal().getRessource()-100);
			}
		}
	}

}
