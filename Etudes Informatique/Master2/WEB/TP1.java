import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

//import org.apache.http.impl.io.SocketOutputBuffer;

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
        System.out.println("@prefix xml: <http://www.w3.org/XML/1998/namespace> .");
        System.out.println("@prefix xsd: <http://www.w3.org/2001/XMLSchema#> .");
        System.out.println("@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .");
        System.out.println("@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .");
        System.out.println("@prefix owl: <http://www.w3.org/2002/07/owl#> .");
		System.out.println("@prefix tomate: <http://tomate.com/0.1/> .");
		System.out.println("@prefix dbr: <http://dbpedia.org/resource/> .");
        System.out.println("@prefix foaf: <http://xmlns.com/foaf/0.1/> .");
		int cpt =0;
		while(ligne !=null){
			ligne = ficTexte.readLine();
			cpt++;
			if (ligne != null) {
                ligne = ligne.replaceAll("\'", "");
                ligne = ligne.replaceAll(":", "");
                ligne = ligne.replaceAll("\\?", "");
                ligne = ligne.replaceAll("&", "");
                ligne = ligne.replaceAll("-", "");
                ligne = ligne.replaceAll("!", "");
                ligne = ligne.replaceAll("\\.", "");
                ligne = ligne.replaceAll("\\/", "");
                ligne = ligne.replaceAll(" ", "");
                String[] v = ligne.split(",(?=([^\"]*\"[^\"]*\")*[^\"]*$)", -1);
                for(int i=0;i<v.length;i++){
                    v[i] = v[i].replaceAll("\"", "");
                    v[i] = v[i].replaceAll(",", "");
                }
                
				if(auteurs.get(v[0]+v[1])==null){
					auteurs.put(v[0]+v[1], "https://toto.com/author/"+v[0]+v[1]);
					//ajout de l'auteur en ressource

					System.out.println("author:"+v[0]+v[1]+" rdf:type owl:NamedIndividual , foaf:Person ;\n\t\t\tfoaf:familyName "+'"'+v[1]+'"'+";\n\t\t\tfoaf:givenName "+'"'+v[0]+'"'+".\n");

				}

				if(editeurs.get(v[5])==null){
					editeurs.put(v[5],  "http://toto.com/publisher/"+cpt);
					System.out.println("publisher:"+cpt+" rdf:type owl:NamedIndividual , foaf:Person ;\n\t\t\tfoaf:familyName "+'"'+v[5]+'"'+".\n");

				}
                v[2] = v[2].replaceAll(" ", "");
                v[2] = v[2].replaceAll("[()]","");

				System.out.println("book:"+v[2]+" tomate:nbpage "+v[3]+";\n\t\t\ttomate:isbn "+'"'+v[4]+'"'+";\n\t\t\tfoaf:title "+'"'+v[2]+'"'+";\n\t\t\t"+"tomate:auteur author:"+v[0]+v[1]+";\n\t\t\t" +"tomate:editeur publisher:"+cpt+" .\n");



			}
		}
		int cpt2 =0;
		while(ligne2 !=null){
			boolean doublon=false;
			ligne2 = ficTexte2.readLine();
			if (ligne2 != null) {
				
				ligne2 = ligne2.replaceAll("\"", "");
				String v2[]=ligne2.split(",");
				String rs = v2[0];
				rs=rs.replaceAll("http://dbpedia.org/resource/", "");
				String rs_tiret= rs;
				rs=rs.replace("_", "");
				if(auteurs.get(v2[1]+v2[2])!=null){
					System.out.println("author:"+v2[1]+v2[2]+" owl:sameAs dbr:"+ v2[1]+"_"+v2[2]+" .\n");
					cpt2++;
					doublon=true;
				}
				
				if(auteurs.get(rs)!=null && doublon == false){
					System.out.println("author:"+rs+" owl:sameAs dbr:"+rs_tiret+" .\n");
					cpt2++;
					
				}
			}

		}
		//System.out.println("IL y a "+ cpt2 +" correspondances");
	}

}


