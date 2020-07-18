
import processing.core.PApplet;
import processing.core.PImage;

public class Carte {
    PImage image_carte;
    private Famille type;
    private String nom;
    private int valeur;
    
    public void setup(PApplet p){
            switch (this.type.toString()){
                case "Baton":
                    this.image_carte=p.loadImage("images/Baton.png");
                    break;
                case "Or":
                    this.image_carte=p.loadImage("images/Or.png");
                    break;
                case "Coupe":
                    this.image_carte=p.loadImage("images/Coupe.png");
                    break;
                case "Epee":
                    this.image_carte=p.loadImage("images/Epee.png");
                    break;
          }
    }

    public Famille getType() {
        return this.type;
    }
    public void setFamille(Famille f){
        this.type=f;
    }
    public String getNom() {
        throw new UnsupportedOperationException("Not supported yet.");
    }
    public void setNom(String nom){
        this.nom=nom;
    }

    public int getValeur() {
        throw new UnsupportedOperationException("Not supported yet.");
    }
    public void setValeur(int valeur){
        this.valeur=valeur;
    }
    
    public void setImage(PImage image){
        this.image_carte=image;
    }
    public void afficherCarte(PApplet p, int x, int y){
        p.image(this.image_carte, x, y);
        p.textSize(12);
        p.text(this.getNom(), x+10, y+80);
    }
}
