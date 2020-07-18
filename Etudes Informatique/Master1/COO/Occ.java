public class Occ{
	public static void main(String [] arg){
		if(arg.length>1){
			int i;
			i=1;
			boolean valeur;
			valeur=false;
			while(arg.length>i){
				if (arg[0].equals(arg[i]))
					valeur=true;
				i++;
			}
			if(valeur)
				System.out.println("Trouve");
			else
				System.out.println("Pas Trouve");
				
				
			
		}
		else
			System.out.println("pas assez d arguments");
	}
}
