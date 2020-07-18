public class Carte {
    private Famille type;
    private String nom;
    private int valeur;

    public Carte(){
    }

    public Famille getType() {
        return this.type;
    }
    public void setFamille(Famille f){
        this.type=f;
    }
    public String getNom() {
        return this.nom;
    }
    public void setNom(String nom){
        this.nom=nom;
    }

    public int getValeur() {
        return this.valeur;
    }
    public void setValeur(int valeur){
        this.valeur=valeur;
    }
    
    public void afficherCarte(Carte c){
        System.out.println("|"+c.getType()+" "+c.getNom()+"|");
    }
    
    public void afficherFamille(Carte c){
        System.out.println(c.getType());
    }
}
