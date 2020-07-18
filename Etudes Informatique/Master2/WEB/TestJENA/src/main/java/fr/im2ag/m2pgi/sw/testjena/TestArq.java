package fr.im2ag.m2pgi.sw.testjena;

import java.sql.ResultSet;
import org.apache.jena.query.Query;
import org.apache.jena.query.QueryExecution;
import org.apache.jena.query.QueryExecutionFactory;
import org.apache.jena.query.QueryFactory;
import org.apache.jena.query.QuerySolution;
import org.apache.jena.query.ResultSetFormatter;
import org.apache.jena.query.Syntax;
import org.apache.jena.sparql.engine.http.QueryEngineHTTP;

public class TestArq {
	public static void main(String[] args) {
		if(args[0]!=null){
			String sparqlEndpoint = "http://localhost:3030/res.ttl/query";
			// get expression values for uniprot acc Q16850
			String sparqlQuery = "" +
					"PREFIX author: <https://toto.com/author/> \n"+
					"PREFIX foaf: <http://xmlns.com/foaf/0.1/>\n"+
					"PREFIX tomate: <http://tomate.com/0.1/> \n"+
					"SELECT DISTINCT ?titre\n"+
					"WHERE { ?b tomate:auteur   author:"+args[0]+"; foaf:title ?titre.}";
			  
			
			Query query = QueryFactory.create(sparqlQuery,Syntax.syntaxARQ);
			// Remote execution.
					QueryEngineHTTP qexec = new QueryEngineHTTP(sparqlEndpoint, query);
			// Set the DBpedia specific timeout.
				   /* org.apache.jena.query.ResultSet results = qexec.execSelect();
				    while (results.hasNext()) {
				      QuerySolution solution = results.next();
				      // get the value of the variables in the select clause
				      String expressionValue = solution.get("expressionValue").asLiteral().getLexicalForm();
				      String pValue = solution.get("pvalue").asLiteral().getLexicalForm();
				      // print the output to stdout
				      System.out.println(expressionValue + "\t" + pValue);
				    }*/
					
					try {
						System.out.println("Execution de la query : "+sparqlQuery+"\n"+"=>");
					      org.apache.jena.query.ResultSet results = (org.apache.jena.query.ResultSet) qexec.execSelect();
					      ResultSetFormatter.out(System.out, results, query);
					    }
					    
					finally {
					      qexec.close();
					    }

		}else{
			System.out.println("Veuillez renseigner le nom de l'auteur (exemple : PaulAuster)");
		}
	}
	
}

