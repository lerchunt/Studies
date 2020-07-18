public class Arg{
		public static void main(String [] arg){
					if(arg.length==2){
						if (Integer.parseInt(arg[0])<Integer.parseInt(arg[arg.length-1]))
							System.out.println(arg[0]+" est infèrieur à"+arg[1]);
						else
							System.out.println(arg[1]+" est infèrieur à "+arg[0]);
					}
					else
						System.out.println("mauvais nombre d arguments");
		}

}
