public class Pascal{
	public static void main (String [] arg){
			int n=Integer.parseInt(arg[0]);
			int tab[][]=new int[n][n];
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(j==0)
					tab[i][j]=1;
				if(j>i)
					tab[i][j]=0;
				if(i==j)
					tab[i][j]=1;
			}
		}
		for(int i=2;i<n;i++){
				for(int j=1;j<n;j++)
					tab[i][j]=tab[i-1][j-1]+tab[i-1][j];
		}
		
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				System.out.print(tab[i][j]+" ");
				if(j==n-1)
				System.out.println();
			}	
		}	
	}
}
