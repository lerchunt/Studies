
import java.util.ArrayList;

public class Joueur {

    private String nom;

    private int score;
    
    private int scoreFinal;

    public ArrayList<Carte> cartes ;

    private ArrayList<Carte> pot;
    
    public Joueur(){
        this.score=0;
        this.scoreFinal=0;
        this.cartes=new ArrayList<>();
        this.pot=new ArrayList<>();
    }
    public Joueur(String nom,int score){
        this.score=score;
        this.nom=nom;
    }
    
    public int type(){
        return 3;
    }
    public void choisirAtout(Carte c,Jeu j){
        
    }
    public void piocher(Jeu j) {
        //piocher le premier element de la pioche
        //ajouter à sa liste de carte
        if(j.pioche.size()!=0){
            Carte c = new Carte();
            c=j.pioche.get(0);
            this.cartes.add(c);
            c.afficherCarte(c);
            
            j.pioche.remove(0); //supprimer la carte de la pioche
        }
    }

    public void jouerCarte(Jeu j) {
    //Méthode différente pour choisir la carte d'un joueur H ou IA.
    //ajouter la carte au pot
    //supprimer la carte de la liste
    Famille atout= j.getAtout();
       int valeur_max=0;
       int min =11;
       Carte joue = new Carte();
       
       /*Si c'est le premier à jouer, il joue sa meilleure carte*/
       if(joue == this.cartes.get(0)){
           for(Carte c : j.pot)
           {
               if(c.getType()== atout)
               {
                   int valeur = c.getValeur();
                   for(Carte c2 : this.cartes){
                       if(c2.getType().equals(atout) && c2.getValeur()>valeur)
                       {
                           joue= c2;
                       }
                       else{
                           if(c2.getValeur()<= min){
                               joue=c2;
                               min= c2.getValeur();
                           }
                           
                       }
                   }
               }
               else{
                   for(Carte c2 : this.cartes){
                       if(c2.getType().equals(atout)){
                           joue = c2;
                       }
                       else{
                           //regarder la couleur de la premiere carte du pot
                           Famille couleur= j.pot.get(0).getType();
                           //verifier si on a cette couleur et la valeur supèrieure
                           if(c2.getType().equals(couleur)&& c2.getValeur()>j.pot.get(0).getValeur()){
                               joue=c2;
                           }
                       }
                       
                       //sinon jouer la plus petite carte
                       
                   }
               }
           }
       }
       else{
           for(Carte c: this.cartes)
               if(c.getValeur()>=valeur_max){
                   joue=c;
                   valeur_max=c.getValeur();
               }
       }
               
        j.pot.add(joue);
        System.out.print(this.getNom()+" joue ");
        joue.afficherCarte(joue);
        this.cartes.remove(joue);
              
   }

    

    public void calculScore(ArrayList<Carte> pot) {
        for(Carte c :pot)
        {
            this.score+=c.getValeur();
        }
    }
    public void refuserAtout(Jeu j,Carte c){
         System.out.println("Le joueur " + this.getNom() + " refuse l'atout");
    }
    public void accepterAtout(Jeu j, Carte c){
        System.out.println("Le joueur " + this.getNom() + " accepte l'atout");
        j.setAtout(c.getType()); // affectation de l'atout du jeu.
    }
    

    public String getNom() {
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
    
    public void setScoreFinal(int scoreFinal) {
        this.scoreFinal = scoreFinal;
    }

    public int getScoreFinal() {
        return this.scoreFinal;
    }
}
