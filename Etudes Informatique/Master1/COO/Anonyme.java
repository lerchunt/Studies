public class Anonyme { 
    public static void A (int un, int un1, int cpt){ 
   int un2=un + un1; 
   if (cpt<31){ 
   cpt++; 
   A(un1, un2, cpt); 
   } 
   System.out.println(un2); 
    } 
   
    public static void main (String [] arg){ 
   A(1, 1, 2); 
   System.out.println("1"); 
   System.out.println("1"); 
   }
 }
