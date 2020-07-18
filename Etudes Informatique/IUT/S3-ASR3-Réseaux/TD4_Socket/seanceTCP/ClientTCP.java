import java.net.*; import java.io.*;
public class ClientTCP{
public static void main( String[] args ) throws Exception{
    String message="Hello Bob, ici Greg, tout va bien?";
    
	for (int j=0; j<1000; j++){
	long start = System.currentTimeMillis();
    for (int i=0; i<message.length(); i++)
    {
    Socket s = new Socket("localhost",5432);
    OutputStream os = s.getOutputStream();
    os.write(message.charAt(i));
    s.close();
    }
    long end = System.currentTimeMillis();
    System.out.println("TCP: Message envoye: temps d'emission = "+(end-start)+"ms");
}
}}
