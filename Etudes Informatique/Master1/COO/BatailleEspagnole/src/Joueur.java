
import java.util.ArrayList;

public class Joueur {

    private String nom;

    private int score;

    private Boolean main;

    public ArrayList<Carte> cartes;

    private ArrayList<Carte> pot;
    
    public Joueur(){
        this.score=0;
    }
    
    public int type(){
        return 3;
    }
    public void choisirAtout(Carte c,Jeu j){
        // est ce que la carte est placée au milieu de la pioche
    }
    public void piocher(ArrayList<Carte> pioche) {
        //piocher le dernier élément de la pioche
        //ajouter à sa liste de carte
        //supprimer la carte de la pioche
    }

    public void jouerCarte(Jeu j) {
    //Méthode différente pour choisir la carte d'un joueur H ou IA.
    //ajouter la carte au pot
    //supprimer la carte de la liste

    }

    public void calculScore(ArrayList<Carte> pot) {
        for(Carte c :pot)
        {
            this.score+=c.getValeur();
        }
    }

    public String getName() {
        return this.nom;
    }

    public int getScore() {
        return this.score;
    }

    public void setScore(int i) {
        this.score= i;
    }
    public void setNom(String nom){
        this.nom=nom;
    }
}
