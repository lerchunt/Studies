import processing.core.PApplet;



public class JoueurArtificiel extends Joueur{
		private int choix;

	JoueurArtificiel(int ressource,String nom) {
		super(ressource,nom);

	}
	public void agir(){
		if(this.getBase().size()!=0){
		choix = (int)(Math.random() * 4);
		switch (choix){
		case 0:
			// Attaquer
			Base att=choisirBaseAttaquante();
			choisirCible(att);


			break;
		case 1:
			// technologie

			if(getRessource()-100>=0){
				setRessource(getRessource()-50);
				setTechnologie(getTechnologie()+10);
				for(Base base1:mes_bases)
					base1.initAVoisineHumaine();
			}
			else
				agir();
			break;
		case 2:
			// Economie
			setRessource(getRessource()+100);
			break;
		case 3:
			// Armée
			if(getRessource()-100>=0){
				setRessource(getRessource()-100);
				for( Base b:mes_bases){
					int unite=b.getUnite();
					b.setUnite(unite+50);
				}
			}
			else
				agir();
			break;

		}
		for(Base b:getBase())
			b.setUnite(b.getUnite()+10+getTechnologie());
		}
		
	}
	public int type(){
		return 3;
	}
	public Base choisirBaseAttaquante(){
		int max=0;
		Base retour=getBase().get(0);
		for(Base b :getBase()){
			if(b.getUnite()>=max){
				retour=b;
				max=b.getUnite();
			}
		}
		return retour;
	}
	public void choisirCible(Base attaquante){
		Base retour=attaquante.getLiee().get(0);
		int min=retour.getUnite();
		for(Base b: attaquante.getLiee())
			if(b.getUnite()<=min && b.getJoueur()!=attaquante.getJoueur()){
				min=b.getUnite();
				retour=b;
			}
		attaquante.attaquerBase(retour);
	} 
}