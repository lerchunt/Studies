
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
    
        public static Partie setup() throws IOException{
        int val=0;
        while(val != 1 && val !=2){
            System.out.println("*****************BATAILLE ESPAGNOLE****************");
            System.out.println("1 : Jouer");
            System.out.println("2 : Quitter");
            BufferedReader inr = new BufferedReader (new InputStreamReader(System.in));
            val = Integer.parseInt(inr.readLine());
                if (val == 1){
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
                        Partie p= new Partie(val2,val3,val4);
                        return p;
                    }
                    else{
                        int val4=0;
                        while(val4<150 || val4 >=1500){
                            System.out.println("Définissez le nombre de points max");
                            BufferedReader inr4 = new BufferedReader (new InputStreamReader(System.in));
                            val4 = Integer.parseInt(inr4.readLine());
                        }
                        Partie p=new Partie(val2,val3,val4);
                        return p;
                    }
                }
                else if (val == 2){
                    System.out.println("Au revoir");
                    System.exit(0);
                }
                
        } 
        return null;
    }
    public static void main(String [] arg) throws IOException{
        Partie p;
        p=setup();
        p.initPartie();
    }
}
