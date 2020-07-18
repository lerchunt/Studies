import java.net.*; 
import java.io.*;
import java.util.*;

public class MonServeurWeb{

	public static void main( String[] args ) throws Exception{
		ServerSocket ss = new ServerSocket(80);
		System.out.println("Mon serveur web en ecoute");
		Socket s = ss.accept();
		System.out.println("******* Connexion etablie *************");
		InputStream is = s.getInputStream();
		LineNumberReader lnr = new LineNumberReader( new InputStreamReader( is ));
		// lecture ligne par ligne de la requete
		String ligne = " ";
		// analyse premiere ligne
		ligne = lnr.readLine();
		String nom=""; String prenom="";
		if (ligne.toUpperCase().indexOf("GET")!=-1){ // ligne contient GET
			System.out.println("Serveur: methode GET utilisee");
			ligne = ligne.substring(ligne.indexOf("?")); // on enleve le debut
			ligne = ligne.substring(0,ligne.indexOf("HTTP")); // on enleve la fin
			StringTokenizer st = new StringTokenizer(ligne, " ?&"); // on decoupe variable par variable
			while (st.hasMoreElements()){
				String variable = st.nextElement().toString(); // recuperation d'une variable
				System.out.println("serveur: "+variable);
				if (variable.startsWith("nom=")) nom=variable.substring(4); // valeur de nom
				if (variable.startsWith("prenom=")) prenom=variable.substring(7); // valeur de prenom
			}
		}

		// autres lignes
		while (ligne.compareTo("")!=0){
			ligne = lnr.readLine();
			System.out.println("Client: "+ligne);
		}
		System.out.println("envoi de la reponse");
		// reponse
		String page = "<HTML><BODY> <H1> Nom saisi: "+nom+" </H1><H2> Prenom saisi: "+prenom+"</H2> </BODY></HTML>";
		String entete = "HTTP/1.1 200 voici la page!!\nDate: Tue, 25 Oct 2005 19:57:48 GMT\nServer: MonServeurWeb\nAccept-Ranges: bytes\nContent-Length: "+page.length()+"\nContent-Type: text/html\n\n";
		
		OutputStream os =s.getOutputStream();
		PrintWriter pw = new PrintWriter(os);
		pw.println(entete);
		pw.println(); // ligne blanche
		pw.println(page);

		pw.flush();
		s.close();
	}

}