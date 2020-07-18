import java.util.ArrayList;
import java.util.Collections;

public class Jeu {

    private Famille atout;
    private int index_gagnant;
    public ArrayList<Joueur> joueurs;
    public ArrayList<Carte> pot;
    public ArrayList<Carte> pioche;
    
    public Jeu(){
        this.index_gagnant=0;
        this.pioche= new ArrayList<>();
        this.pot= new ArrayList<>();
        this.joueurs= new ArrayList<>();
    }
    public Jeu(ArrayList j){ //construire les joueurs à partir des joueurs d'un jeu précédent
        this.joueurs=j;
    }
    public void setup(Partie p){
        generer_pioche();
        for(Carte c:this.pioche){
        }
        this.distribuer();     
    }
    
    public void jouer(){
          int i=0;
          int nb;
          boolean nb_cartes_equitable=true;
        for(Joueur j: joueurs){
            j.setScore(0); //remise à zéro du score du joueur pour chaque nouveau jeu
        }
        while((this.pioche.size()>=this.joueurs.size()) && nb_cartes_equitable) { //tant qu'il y a assez de cartes pour les joueurs
            System.out.println("---Main n° "+(i+1)+"---");
            int k = this.index_gagnant;
            for(int l=0;l<this.joueurs.size();l++){
                Joueur j=this.joueurs.get(k);
                j.jouerCarte(this);
                System.out.print(j.getNom()+" pioche ");
                j.piocher(this);
                System.out.println(j.getNom()+" a les cartes ");
                for(Carte c: j.cartes)
                {
                    c.afficherCarte(c);
                }

                k=(k+1)%this.joueurs.size();

            }
            this.gagnantMain();
            // la ième carte jouée sur le pot appartenait au ième joueur de la liste
            i++;
            
            nb=joueurs.get(0).cartes.size();
            for(Joueur j: joueurs){
                if(j.cartes.size()!=nb)
                    nb_cartes_equitable=false;
            }
        }
        for(Joueur j: joueurs){
            j.setScoreFinal((j.getScoreFinal()+j.getScore())); //calcul du score total de chaque joueur au fil des jeux
            j.cartes=new ArrayList(); //supprime les cartes des joueurs restantes avant de refaire un nouveau jeu
        }
    }

    public void gagnantMain() {
        Carte c1=this.pot.get(0);
       // System.out.println(" premiere carte");
        for (Carte c : pot){
            if(c.getType()== this.atout){
               // System.out.println(" premiere carte");
                if(!(c1.getType()==this.atout && c1.getValeur()>c.getValeur()))
                    c1=c;
            }
            else{
                if(c1.getType()!=this.atout)
                {
                    if (c1.getValeur()<=c.getValeur()) {
                        c1=c;
                    }
                }
            }
            
        }
        
        int index; // c'est l i-ème carte qui l'emporte!
        index = pot.indexOf(c1);
        System.out.println("Le gagnant de la main est "+this.joueurs.get(index).getNom());
        
        for(Carte c: pot){
            this.joueurs.get(index).setScore(this.joueurs.get(index).getScore()+ c.getValeur()); // On ajoute au score du joueur la valeur des cartes qu'il vient de remporter.
        }
        this.index_gagnant=index;
        System.out.println("nouveau index :" + this.index_gagnant );
    //vider le pot
        this.pot=new ArrayList<>();
    }
    
    public void gagnantJeu(){
        int max=0;
        for(Joueur j: joueurs){
            System.out.println(j.getNom()+" a un score de "+j.getScore()); //affiche le score de chacun des joueurs
            if(j.getScore()>max)
                max=j.getScore(); //max <- meilleur score
        }
        for (Joueur j:joueurs){
            if(max == j.getScore())
                System.out.println(("Le gagnant du jeu est "+j.getNom())); //affiche le joueur qui a le meilleur score
        }
    }
    
    public void generer_pioche(){
        Famille f=null;
        for(int i=1;i<5;i++){
            switch (i){
                case 1:
                    f = Famille.Baton;
                    break;
                case 2:
                    f=Famille.Coupe;
                    break;
                case 3:
                    f=Famille.Epee;
                    break;
                case 4:
                    f=Famille.Or;
                    break;
            }
            for(int j=1;j<14;j++)
            {
                Carte c = new Carte(); //Definir chaque carte (nom+valeur)
                switch (j){
                    case 1:
                        c.setNom("As");
                        c.setValeur(11);
                        break;
                    case 2:
                        c.setNom("2");
                        c.setValeur(0);
                        break;
                    case 3:
                        c.setNom("3");
                        c.setValeur(10);
                        break;
                    case 4:
                        c.setNom("4");
                        c.setValeur(0);
                        break;
                    case 5:
                        c.setNom("5");
                        c.setValeur(0);
                        break;
                    case 6:
                        c.setNom("6");
                        c.setValeur(0);
                        break;
                    case 7:
                        c.setNom("7");
                        c.setValeur(0);
                        break;
                    case 8:
                        c.setNom("8");
                        c.setValeur(0);
                        break;
                    case 9:
                        c.setNom("9");
                        c.setValeur(0);
                        break;
                    case 10:
                        c.setNom("10");
                        c.setValeur(0);
                        break;
                    case 11:
                        c.setNom("C");
                        c.setValeur(2);
                        break;
                    case 12:
                        c.setNom("Q");
                        c.setValeur(3);
                        break;
                    case 13:
                        c.setNom("K");
                        c.setValeur(4);
                    break;    
                }
                c.setFamille(f);
                pioche.add(c);           
            }
        }
        //Mélanger la pioche
            for(int i = 0; i<10;i++){
                Collections.shuffle(pioche);
            }
                
    }
    
    public void designerAtout() {
        int index = 0;
        while (this.atout ==null){

            for (Joueur j: joueurs){
                j.choisirAtout(this.pioche.get(index),this);
            }
            index=(index+1)%(this.pioche.size());
        }
    }

    public void distribuer() {
        
        for(int i = 0;i<3;i++){
            for(Joueur j :joueurs){
                //selectionner le premier élément de pioche
                j.cartes.add(this.pioche.get(0));
                this.pioche.remove(0);
                //suppprimer de pioche
            }
        }
    }
    public void replacerCarte(Carte c,int index){
        this.pioche.remove(index);
        this.pioche.add(c);
    }
    public void setAtout(Famille f){
        this.atout = f;
    }
    public Famille getAtout() {
        return this.atout;
    }
}
