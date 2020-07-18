

public class JoueurHumain extends Joueur{

	JoueurHumain(int ressource,String nom) {
		super(ressource,nom);
		// TODO Auto-generated constructor stub
	}
	public void agir(){
		for(Base b:getBase())
			b.setUnite(b.getUnite()+50+getTechnologie());

		
	}
	public int type(){
		return 1;
	}
	
}
