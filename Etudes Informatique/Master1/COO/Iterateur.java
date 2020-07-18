import java.util.ArrayList;
import java.util.ListIterator;
import java.util.*;

public class Iterateur{
	public static void main (String [] arg){
		int n=Integer.parseInt(arg[0]);
		int cursal2;
		ArrayList al = new ArrayList <Integer> ();
		ArrayList al2 = new ArrayList <Integer> ();
		Iterator j = al.iterator ();
		if(al.size()==0){
				al.add(1);									
		}
		al2.set(1,1);
		al2.set(0,1);
		
		for( int i=3; i<n; i++) {
			al2.set(1,0);
			cursal2=1;
			while (j.hasNext ()) {
				Integer t= (Integer)j.next();
				Integer y= (Integer)j.next();
				al2.set(cursal2,t+y);
				System.out.print(j);
			}
			
			System.out.println(" ");
			al2=al;
		}
	}
}
