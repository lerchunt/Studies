import java.sql.*;

public class Banque {
	
	static final String CONN_URL = "jdbc:oracle:thin:@im2ag-oracle.e.ujf-grenoble.fr:1521:ufrima";
	static final String USER = "lerchunt";
	static final String PASSWD = "bd2015";
		
	private static void menu() {
		System.out.println("*** Choisir une action a effectuer : ***");
		System.out.println("0 : Quitter");
		System.out.println("1 : Afficher la liste des animaux");
		System.out.println("2 : Deplacer un animal de cage");
		System.out.println("3 : Ajouter une maladie");
	}

	private static void listeAnimaux(Connection conn) throws SQLException {
		String nom,sexe,type_an,fonction_cage,pays,annais,nocage,nb_maladies;
		System.out.println("Affichage des animaux : (nom, sexe, type_an, fonction_cage, pays, annee, NO_cage, nb_maladies)");
		Statement  stmt = conn.createStatement ();
		ResultSet  rs = stmt.executeQuery("SELECT* from LesAnimaux");
		while (rs.next()){
			nom=rs.getString("NomA");
			sexe=rs.getString("SEXE");
			type_an=rs.getString("TYPE_AN");
			fonction_cage=rs.getString("FONCTION_CAGE");
			pays=rs.getString("PAYS");
			annais=rs.getString("ANNAIS");
			nocage=rs.getString("NOCAGE");
			nb_maladies=rs.getString("NB_MALADIES");
			System.out.println(nom+" "+sexe+" "+type_an+" " +fonction_cage+" "+pays+" "+annais+" "+nocage+" "+nb_maladies);
		}
	}

	private static void deplacerAnimal(Connection conn) throws SQLException {
		System.out.println("Quel est le nom de l'animal que vous souhaitez déplacer?");
		String action=LectureClavier.lireChaine();
		Statement  stmt = conn.createStatement ();
		String req =" SELECT * from LesAnimaux where NomA like '" + action + "'";
		ResultSet  rs = stmt.executeQuery(req);
		if(!rs.next())
			System.out.println("Animal non trouve");
		else
		{
			System.out.println("Animal trouve");
			int cage=LectureClavier.lireEntier("Dans quelle cage le placer ?");
			req= " Update LesAnimaux Set noCage =" + cage + "Where NomA like '" +action+"'";
			ResultSet  rs2 = stmt.executeQuery(req);
		}	
	}		

	private static void ajouterMaladie(Connection conn) throws SQLException {
		System.out.println("Quel est le nom de l'animal concerné?");
			String animal=LectureClavier.lireChaine();
		System.out.println("Quel est le nom de la maladie?");
			String maladie=LectureClavier.lireChaine();
			Statement  stmt = conn.createStatement ();
			String req ="INSERT into LesMaladies Values("+ "'" + animal +"'"+ "," + "'" + maladie +"' )";
			ResultSet  rs = stmt.executeQuery(req);
			
		
	}		


	private static void commit(Connection conn) throws SQLException {
		Statement  stmt = conn.createStatement ();
		String req = "commit";
		ResultSet  rs = stmt.executeQuery(req);
	}				

	private static void rollback(Connection conn) throws SQLException {
		Statement  stmt = conn.createStatement ();
		String req = "rollback";
		ResultSet  rs = stmt.executeQuery(req);
	}		
	
	private static void getIsolation() throws SQLException {
		// A COMPLETER
	}

	private static void setIsolation() throws SQLException {
		// A COMPLETER
	}	
	
    public static void main(String args[]) {

        try {

		
        
        int action;
        boolean exit = false;

  	    // Enregistrement du driver Oracle
  	    System.out.print("Loading Oracle driver... "); 
  	    Driver myDriver = new oracle.jdbc.driver.OracleDriver();
		DriverManager.registerDriver( myDriver );
  	    // A COMPLETER
  	    System.out.println("loaded");
  	    
  	    // Etablissement de la connection
  	    System.out.print("Connecting to the database... "); 
  	    Connection  conn = DriverManager.getConnection(CONN_URL , USER , PASSWD);
  	    System.out.println("connected");
  	    
  	    // Desactivation de l'autocommit
  	    
  	    conn.setAutoCommit(false);
  	    System.out.println("Autocommit disabled");

  	    while(!exit) {
  	    	menu();
  	    	action = LectureClavier.lireEntier("votre choix ?");
  	    	switch(action) {
  	    		case 0 : exit = true; break;
  	    		case 1 : listeAnimaux(conn); break;
  	    		case 2 : deplacerAnimal(conn); break;
  	    		case 3 : ajouterMaladie(conn); break;
  	    		default : System.out.println("=> choix incorrect"); menu();
  	    	}
  	    } 	    

  	    // Liberation des ressources et fermeture de la connexion...
		// A COMPLETER
  	    conn.close();
  	    System.out.println("au revoir");
  	    
  	    // traitement d'exception
          } catch (SQLException e) {
              System.err.println("failed");
              System.out.println("Affichage de la pile d'erreur");
  	          e.printStackTrace(System.err);
              System.out.println("Affichage du message d'erreur");
              System.out.println(e.getMessage());
              System.out.println("Affichage du code d'erreur");
  	          System.out.println(e.getErrorCode());	    

          }
     }
	

}
