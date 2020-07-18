import java.util.ArrayList;
import java.io.*;

public class Partie {

    private int nbJoueur;
    private int nbJeux;
    private int pointMax;
    int regleChoisie;
    private Boolean fin;
    private ArrayList <Jeu> liste_jeu;
    private ArrayList <Joueur> liste_joueurs;

    public Partie(int nb_joueurs,int numero_regle,int nb_max ){
        this.nbJoueur=nb_joueurs;
        if(numero_regle == 1)
        {
            this.regleChoisie=numero_regle;
            this.nbJeux=nb_max;
        }
        else{
            this.regleChoisie=numero_regle;
            this.pointMax=nb_max;
        } 
        System.out.println("Création partie...");
    }
    public void initPartie(){
        this.genererJoueurs(this.nbJoueur);
    }
    public void genererJoueurs(int nb){
        
        for (int i=0;i<nb;i++){
        Joueur j =new Joueur();
        j.setNom("Joueur "+i);
        liste_joueurs.add(j);
        }
    }
    public Joueur Gagnant() {
        Joueur j= new Joueur();
        //TROUVER LE JOUEUR GAGNANT
        
        return j;
    }
    public boolean verifierRegle(){
        return true;
    }
    public void commencer(){
        for(Jeu j : liste_jeu){
            if(verifierRegle()){
                j.jouer();
            }
                
        }
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
}
