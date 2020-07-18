import processing.core.PApplet;

public class Application extends PApplet {

static int hJeu,wJeu;
	private Jeu j;
	private Menu m;
	private Regles r;
	private Bandeau b;
	private Credit c;
	
	public Application(){		

		j = new Jeu();
		m = new Menu();
		r = new Regles();
		b = new Bandeau();
		c = new Credit();
	}

	public void setup(){
		hJeu=Jeu.TAILLEH;
		wJeu=Jeu.TAILLEW;
		size(wJeu,hJeu);
		background(255);
		m.setup(this);
		j.setup(this);
		j.initialiser_bases(this);
		b.setup(this,j.getJoueurPrincipal());
	}

	public void draw(){
		m.MousePressed(this);
		if(m.getChoix() == 0){
			m.draw(this);
		}
		if(m.getChoix() == 1){
			j.draw(this);
			b.draw(this,j);
			b.MousePressed(this,j);
		}
		if(m.getChoix() == 2){
			r.setup(this, m);
			r.draw(this);
			r.MousePressed(this);
			System.out.println("Choix nÂ°2");
		}
		if(m.getChoix() == 3){
			m.MousePressed(this);
			System.out.println("choix 3");
			System.exit(0);
		}
		if(m.getChoix() == 4){
			c.setup(this,m);
			c.draw(this);
			System.out.println("c");
			c.MousePressed(this);
			System.out.println("Choix n°4 : Credits");
		}
	}

	public static void main(String[] args) {
		PApplet.main("Application");
	}
	public int getWidth(){
		return this.width;
	}
	public int getHeight(){
		return this.height;
	}

	public Jeu getJ() {
		return j;
	}

}