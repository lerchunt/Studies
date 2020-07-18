import java.io.*;
//Saisie un entier au clavier
public class Saisie {
    public static void main (String [] arg) throws IOException {
   	 BufferedReader inr = new BufferedReader (new InputStreamReader(System.in));
   	 System.out.println("Taper une valeur entiere au clavier");
   	 int val = Integer.parseInt(inr.readLine());
   	 int somme= 0;
   	 while (val != -1){
   		 somme += val;
   		 System.out.println("Taper une valeur entiere au clavier");
   	  	 val = Integer.parseInt(inr.readLine());
   	 }
   	 System.out.println("La somme des nombres que vous avez saisis est " + somme);
    }
}
