public class Palindrome{

	public static void main (String [] arg){
	String s=arg[0];
		boolean ok = true;
		for(int i=0; i<(s.length()/2);i++){
			if((s.charAt(i))!=(s.charAt(s.length()-i-1))){
				ok=false;
			} 
						
		}
		if(ok==true)
			System.out.println("c est un palindrome");
		else
			System.out.println("ce n est pas un palindrome");
	}

}
