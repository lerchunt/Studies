public class Crible{
	public static void main(String [] arg){
		boolean tab[];
		tab= new boolean[101];
		tab[0]=tab[1]=false;
		for(int i=2;i<=100;i++){
			tab[i]=true;
		}
		for (int i=2;i<=100;i++){
			int j=i;
			while( ((i*j)<=100)){
				tab[i*j]=false;
				j++;
			}
		}
		for(int i=2;i<=100;i++){
			if(tab[i]==true)
				System.out.println(i);
		}
	}
}
