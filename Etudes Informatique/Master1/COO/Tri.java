/* tri a bulle*/
public class Tri {
    public static void bulle (int [] tab){
		for(int i=0;i<tab.length;i++){
			if(tab[i]>tab[0]){
				tmp=tab[0];
				tab[0]=tab[i];
				tab[i]=tmp;
			}
		}
    }	
    
    public static void main (String [] arg){
   	 int t[] = {2,3,7,5,6,11,0};
   	 System.out.println("Avant");
   	 for (int i=0; i<t.length; i++){
   		 System.out.println(t[i] + " ");
   	 }
   	 System.out.println("Apres");
   	 Tri.bulle(t);	 
   	 for (int i=0; i<t.length; i++){
   		 System.out.println(t[i] + " ");
   	 }
    }
}
