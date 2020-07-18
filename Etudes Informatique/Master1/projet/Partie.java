import java.util.ArrayList;

public class Partie {

    private int nbJoueur;
    private int nbJeux;
    private int pointMax;
    int regleChoisie;
    private Boolean fin;
    public ArrayList <Jeu> liste_jeu;
    public ArrayList <Joueur> liste_joueurs;

    public Partie(int nb_joueurs,int numero_regle,int nb_max ){
        this.liste_jeu = new ArrayList<>();
        this.liste_joueurs = new ArrayList<>();
        
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
        Joueur j;
        for (int i=0;i<nb;i++){
            j=new Joueur();
            this.liste_joueurs.add(j);
        }
    }

    public void Gagnant() {
        int max=0;
        for(Joueur j: this.liste_joueurs){
            System.out.println(j.getNom()+" a un score final de "+j.getScoreFinal()); //affiche le score final de chacun des joueurs
            if(j.getScoreFinal()>max)
                max=j.getScoreFinal(); //max <- meilleur score
        }
        for (Joueur j:this.liste_joueurs){
            if(max == j.getScoreFinal())
                System.out.println(("Bravo! Le grand gagnant de la partie est "+j.getNom())); //affiche le joueur qui a le meilleur score
        }
    
    }
    public boolean verifierRegle(){
        return true;
    }
    public void commencer_jeux(){
        if(this.regleChoisie==1){
            for(int i=0; i< this.nbJeux;i++){
                Jeu j= new Jeu();
                liste_jeu.add(j);
                j.joueurs= this.liste_joueurs;
                j.generer_pioche();
                
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
