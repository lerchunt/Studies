
import java.util.ArrayList;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author lerchunt
 */
public class JoueurIA extends Joueur {
    
   public int type(){
		return 1;
   } 
   public void choisirAtout(Carte c,Jeu j){
        if(Math.random()>0.5){
            Famille f = c.getType();
            j.setAtout(f);
            j.pioche.add(c); // carte replacée sous le tas
            j.pioche.remove(0); // on supprime la première carte
       }
    }
   
   public void jouerCarte(Jeu jeu) {
       Famille atout= jeu.getAtout();
       int valeur_max=0;
       int min =11;
       Carte joue = new Carte();
       Carte c1 = jeu.pot.get(0);
       
       /*Si c'est le premier à jouer, il joue sa meilleure carte*/
       if(c1==null){
           for(Carte c: this.cartes)
               if(c.getValeur()>=valeur_max){
                   joue=c;
                   valeur_max=c.getValeur();
                }
       }
       else{
           for(Carte c : jeu.pot)
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
                            Famille couleur= jeu.pot.get(0).getType();  
                            //verifier si on a cette couleur et la valeur supèrieure
                            if(c2.getType().equals(couleur)&& c2.getValeur()>jeu.pot.get(0).getValeur()){
                                joue=c2;
                            }
                        }
                            
                        //sinon jouer la plus petite carte
              
                    }
                }
           }
       }

              jeu.pot.add(joue);
              this.cartes.remove(joue);
   }
}
