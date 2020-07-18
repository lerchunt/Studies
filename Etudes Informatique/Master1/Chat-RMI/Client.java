import java.io.Serializable;

public class Client implements Serializable{
	
	private String url;
	private String name;
	
	
	public void setName(String s){
		this.name=s;
	}
	public String getName(){
		return this.name;
	}	
	public void setUrl(String s){
		this.url=s;
	}
	public String getUrl(){
		return this.url;
	}

}
