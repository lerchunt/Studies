import java.net.*;
import java.io.*;
public class ServeurTCP{
public static void main( String[] args ) throws Exception{
    ServerSocket ecoute = new ServerSocket(5432,5);
    Socket service = (Socket)null;
    System.out.println("Serveur TCP en attente");
    while(true) {
        service = ecoute.accept();
        InputStream  is = service.getInputStream();
        System.out.print((char) is.read());
        service.close();
    }
}}