import java.io.Serializable;

public class Message implements Serializable{
	private String message;
	private String url_dest;
	
	public String getMessage(){
		return this.message;
	}
	public void setMessage(String m){
		this.message=m;
	}
	public String getUrl(){
		return this.url_dest;
	}
	public void setUrl(String m){
		this.url_dest=m;
	}
}
