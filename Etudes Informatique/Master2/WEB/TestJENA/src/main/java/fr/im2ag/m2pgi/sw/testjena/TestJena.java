package fr.im2ag.m2pgi.sw.testjena;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import org.apache.jena.rdf.model.Literal;
import org.apache.jena.rdf.model.Model;
import org.apache.jena.rdf.model.ModelFactory;
import org.apache.jena.rdf.model.Property;
import org.apache.jena.rdf.model.Resource;
import org.apache.jena.rdf.model.Statement;
import org.apache.jena.rdf.model.StmtIterator;

/**
 * Tests to experiment with the Jena Core RDF API.
 *
 * @author Philippe Genoud - Philippe.Genoud@imag.fr
 */
public class TestJena {

    private static final String MODEL_PREFIX = "http://mondomaine.org/test#";

    public static void displayStatements(StmtIterator stmtIterator) {
        for (; stmtIterator.hasNext();) {
            Statement st = stmtIterator.nextStatement();
            System.out.println(st);
        }
    }
    
    public static void main(String[] args) throws IOException {
        //  create a new empty model
    	
    	if(args[0]!=null && args[1] != null){
    		File f=new File(args[0]+"."+args[1]);
    		f.createNewFile();
    		FileWriter ff = new FileWriter(f);
    		
	        Model model = ModelFactory.createDefaultModel();
	        model.setNsPrefix("", MODEL_PREFIX);
	        
	        // create some resources, properties and literals
	        Resource r1 = model.createResource(MODEL_PREFIX + "r1");
	        Resource r2 = model.createResource(MODEL_PREFIX + "r2");
	        Resource r3 = model.createResource(MODEL_PREFIX + "r3");
	        Property p1 = model.createProperty(MODEL_PREFIX + "p1");
	        Property p2 = model.createProperty(MODEL_PREFIX + "p2");
	        Property p3 = model.createProperty(MODEL_PREFIX + "p3");
	        Literal l1 = model.createLiteral("literal1");
	
	        // create a statement
	        Statement stmt = model.createStatement(r1, p1, l1);
	        // the statement must be explicitly added to the model
	        model.add(stmt);
	
	        // create new statement with resource r1 as subject
	        // the statement is implicitly added to the model
	        r1.addProperty(p2, r2);
	        
	        // create new statements with resource r2 as subject
	        r2.addProperty(p3, MODEL_PREFIX + "r3");
	        r2.addProperty(p2,r3).addLiteral(p3, "r1");
	        // create new statement with resource r3 as subject
	        r3.addLiteral(p2, l1);
	
	        // display all the statements on the console
	        System.out.println("All the statements");
	        displayStatements(model.listStatements());
	
	        // display the RDF in RDF/XML serialization format
	        System.out.println("\n----------------------------\nThe model in RDF/XML serialization\n");
	        model.write(ff, "RDF/XML", "http://mondomaine.org/test#");
    	}
    	else{
    		System.out.println("Erreur veuillez renseigner un nom(arg1) pour le fichier de sortie, et son format de serialization (arg2)");
    	}
    }
}
