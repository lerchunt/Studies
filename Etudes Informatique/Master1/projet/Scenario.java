
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author lerchunt
 */
public class Scenario {
    
        public static void setup() throws IOException{
        int val=0;
        while(val != 1 && val !=2){
            System.out.println("*****************BATAILLE ESPAGNOLE****************");
            System.out.println("1 : Jouer");
            System.out.println("2 : Quitter");
            BufferedReader inr = new BufferedReader (new InputStreamReader(System.in));
            val = Integer.parseInt(inr.readLine());
                if (val == 1){
                    int menu=0;
    
                    while(menu<1 || menu >3 ){
                        System.out.println("Choisissez le mode de jeu : ");
                        System.out.println("1 : Scenario 1(Automatique)");
                        System.out.println("2 : Scenario 2(Automatique)");
                        System.out.println("3 : Scenario Interactif");
                        BufferedReader menu_r = new BufferedReader (new InputStreamReader(System.in));
                        menu = Integer.parseInt(menu_r.readLine());
                    }
                    switch(menu){
                        case 1: //effectuer le premier scenario
                            Partie p= new Partie(2,1,3);
                            p.genererJoueurs(p.getNbJoueur());
                            p.liste_joueurs.get(0).setNom("J1");
                            p.liste_joueurs.get(1).setNom("J2");
                            for(int i=0;i<3;i++){ //lancement des 3 jeux
                                Jeu j= new Jeu();
                                System.out.println("******** Jeu "+(i+1)+" ********");
                                j.joueurs=p.liste_joueurs;
                                j.generer_pioche();
                                
                                //distribution des cartes
                                j.distribuer();
                                System.out.println("Distribution des cartes effectuée ");
                                
                                //Affichage des cartes des joueurs
                                for(Joueur joueur : p.liste_joueurs)
                                {
                                    System.out.println("Le joueur "+joueur.getNom()+" a les cartes ");
                                    for(Carte c: joueur.cartes)
                                    {
                                        c.afficherCarte(c);
                                    }
                                }
                                
                                //Affichage de la première carte
                                System.out.print("La première carte retournée est ");
                                j.pioche.get(0).afficherCarte(j.pioche.get(0));
                                
                                //choix de l'atout par les joueurs
                                j.joueurs.get(0).refuserAtout(j,j.pioche.get(0)); // le premier joueur refuse l'atout
                                j.joueurs.get(1).accepterAtout(j,j.pioche.get(0)); // le second l'accepte
                                
                                //désignation de l'atout
                                System.out.println("L'atout est " + j.getAtout().toString());
                                
                                j.replacerCarte(j.pioche.get(0),0); //placement de l'atout à la fin de la pioche
                                
                                //Deroulement du jeu
                                j.jouer();
                               
                                //renvoie le gagnant du jeu
                                j.gagnantJeu();
                                
                                System.out.println("****** Fin Jeu "+(i+1)+" ******");
                            }
                            p.Gagnant(); //Renvoie le gagnant de la partie
                            break;
                            
                        case 2: // lancer du deuxième scénario
                            Partie s2= new Partie(4,2,50);
                            s2.genererJoueurs(s2.getNbJoueur());
                            s2.liste_joueurs.get(0).setNom("Sophie");
                            s2.liste_joueurs.get(1).setNom("Adrien");    
                            s2.liste_joueurs.get(2).setNom("Marc"); 
                            s2.liste_joueurs.get(3).setNom("Pauline"); 
                                
                            break;
                        case 3: // Lancement du programme intéractif
                            int val2= 0;
                            while (val2 <2 || val2> 4){
                                System.out.println("Entrez le nombre de joueurs (2-4)");
                                BufferedReader inr2 = new BufferedReader (new InputStreamReader(System.in));
                                val2 = Integer.parseInt(inr2.readLine());
                            }
                            int val3=0;
                            while(val3 != 1 && val3!=2 ){
                                System.out.println("Définissez les règles du jeu");
                                System.out.println("1 : Nombre de jeux max");
                                System.out.println("2 : Nombre de points max");
                                BufferedReader inr3 = new BufferedReader (new InputStreamReader(System.in));
                                val3 = Integer.parseInt(inr3.readLine());
                                System.out.println("val3= " +val3);
                            }
                            if(val3==1){
                                int val4=0;
                                while(val4<=2 || val4 >=20){
                                    System.out.println("Définissez le nombre de jeux max");
                                    BufferedReader inr4 = new BufferedReader (new InputStreamReader(System.in));
                                    val4 = Integer.parseInt(inr4.readLine());
                                }
                                //Partie p= new Partie(val2,val3,val4);

                            }
                            else{
                                int val4=0;
                                while(val4<150 || val4 >=1500){
                                    System.out.println("Définissez le nombre de points max");
                                    BufferedReader inr4 = new BufferedReader (new InputStreamReader(System.in));
                                    val4 = Integer.parseInt(inr4.readLine());
                                }
                                //Partie p=new Partie(val2,val3,val4);

                            }
                            break;
                        
                    }
                }
                else if (val == 2){
                    System.out.println("Au revoir");
                    System.exit(0);
                }
                val =0;
                
        } 
    }
    public static void main(String [] arg) throws IOException{
        Partie p;
        setup();
    }
}
