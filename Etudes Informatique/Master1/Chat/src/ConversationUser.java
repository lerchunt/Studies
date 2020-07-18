package chat;
import java.rmi.*;
import java.util.*;

public class ConversationUser implements Conversation {
    private ArrayList<String> messages;

    public ConversationUser(){
        this.messages=new ArrayList<String>();
    }

    public void addMessage(String message) throws RemoteException {
        messages.add(message);
        System.out.println(message);
    }
    
    public void addhistory(ArrayList<String> messages){
		this.messages=messages;
		for(String s :  messages){
			System.out.println(s);
		}
	}

}
