import java.util.ArrayList;
import processing.core.PApplet;
public class Partie extends PApplet {

    private int nbJoueur;
    private int nbJeux;
    private int pointMax;
    static int hJeu,wJeu;

    private Boolean fin;
    private ArrayList <Jeu> liste_jeu;

    public void Partie(){
        Jeu j=new Jeu();
        liste_jeu.add(j);
    }
    public void setup(){
        System.out.println("setup");
     hJeu=Jeu.TAILLEH;
     wJeu=Jeu.TAILLEW;
     size(wJeu,hJeu);
     background(255);
     this.liste_jeu.get(0).setup(this);

    }
    public void draw(){
        this.liste_jeu.get(0).draw(this);
    }
    public Joueur Gagnant() {
        Joueur j= new Joueur();
        //TROUVER LE JOUEUR GAGNANT
        
        return j;
    }

    public void choisirRegle() {
    }



    public int getNbJoueur() {
        return this.nbJoueur; 
    }

    public int getNbJeux() {
        return this.nbJeux;
    }

    public int getPointMax() {
        return this.pointMax;
    }

    public Boolean getFin() {
        return this.fin;
    }
    public static void main(String[] args) {
	PApplet.main("BATAILLE ESPAGNOLE");
    }


}
