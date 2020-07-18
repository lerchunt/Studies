import java.util.ArrayList;
import java.util.Collections;

public class Jeu {

    private Famille atout;

    public ArrayList<Joueur> joueurs;
    public ArrayList<Carte> pot;
    public ArrayList<Carte> pioche;
    public void Jeu(ArrayList j){ //construire les joueurs à partir des joueurs d'un jeu précédent
        this.joueurs=j;
    }
    public void setup(Partie p){
        generer_pioche();
        for(Carte c:this.pioche){
        }
        this.distribuer();     
    }
    
    public void jouer(){

    }

    public Joueur gagnantMain(ArrayList<Carte> cartesJouees) {
        throw new UnsupportedOperationException("Not supported yet.");
    }
    public void generer_pioche(){
        Famille f;
        for(int i=0;i<3;i++){
            switch (i){
                case 0:
                    f = Famille.Baton;
                    break;
                case 1:
                    f=Famille.Coupe;
                    break;
                case 2:
                    f=Famille.Epee;
                    break;
                default:
                    f=Famille.Or;
                    break;
            }
            for(int j=1;j<= 13;j++)
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
                j.cartes.add(this.pioche.get(i));
                this.pioche.remove(i);
                //suppprimer de pioche
            }
        }
    }
    
    public void setAtout(Famille f){
        this.atout = f;
    }
    public Famille getAtout() {
        return this.atout;
    }
}
