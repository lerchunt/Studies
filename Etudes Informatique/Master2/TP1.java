import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

import org.apache.http.impl.io.SocketOutputBuffer;

public class TP1 {

	public static void main(String[] args) throws IOException{

		HashMap<String,String> auteurs= new HashMap<>();
		HashMap<String,String> editeurs= new HashMap<>();


		BufferedReader ficTexte = new BufferedReader(new FileReader(new File("booksCatalog.csv")));
		BufferedReader ficTexte2 = new BufferedReader(new FileReader(new File("sparql.csv")));
		String ligne = ficTexte.readLine();
		String ligne2 = ficTexte2.readLine();
		System.out.println("@prefix author: <https://toto.com/author/> .");
		System.out.println("@prefix book: <https://toto.com/book/> .");
		System.out.println("@prefix publisher: <https://toto.com/publisher/> .");
		System.out.print("@prefix xml: <http://www.w3.org/XML/1998/namespace> .\n@prefix xsd: <http://www.w3.org/2001/XMLSchema#> .\n@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n@prefix owl: <http://www.w3.org/2002/07/owl#> .");
		System.out.print("@prefix tomate: http://tomate.com/0.1/> .");
		System.out.print("@prefix owl: <http://www.w3.org/2002/07/owl#> .");
		System.out.print("@prefix dbr: <http://dbpedia.org/resource/> .");
		int cpt =0;
		while(ligne !=null){
			ligne = ficTexte.readLine();
			cpt++;
			if (ligne != null) {
				String v[]=ligne.split(",");
				if(auteurs.get(v[0]+v[1])==null){
					auteurs.put(v[0]+v[1], "https://toto.com/author/"+v[0]+v[1]);
					//ajout de l'auteur en ressource

					System.out.print("author:"+v[0]+v[1]+" rdf:type owl:NamedIndividual ,\nfoaf:Person ;\nfoaf:familyName "+'"'+v[1]+'"'+";\nfoaf:givenName "+'"'+v[0]+'"'+";\n");

				}

				if(editeurs.get(v[5])==null){
					editeurs.put(v[5],  "http://toto.com/publisher/"+cpt);
					System.out.print("publisher:"+cpt+" rdf:type owl:NamedIndividual ,\nfoaf:Person ;\nfoaf:familyName "+'"'+v[5]+'"'+";\n");	

				}

				System.out.print("book:"+v[2].replaceAll(" ", "")+";\ntomate:nbpage "+v[3]+";\ntomate:isbn "+v[4]+";\nfoaf:title "+'"'+v[2]+'"'+";\n"+"author: "+v[0]+v[1]+";\n" +"publisher:"+cpt+" .\n");	



			}
		}
		int cpt2 =0;
		while(ligne2 !=null){
			ligne2 = ficTexte2.readLine();
			if (ligne2 != null) {
				ligne2 = ligne2.replaceAll("\"", "");
				String v2[]=ligne2.split(",");
				System.out.println(v2[1]+v2[2]);
				if(auteurs.get(v2[1]+v2[2])!=null){
					System.out.println("author:"+v2[1]+v2[2]+" owl:sameAs dbr:"+ v2[0]+"\n");
					cpt2++;
				}
			}

		}
		//System.out.println("IL y a "+ cpt2 +" correspondances");
	}

}


