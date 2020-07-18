package chat;
import java.rmi.*;
import java.rmi.registry.*;
import java.util.*;
import java.text.*;

public class ChatRoom implements Room {

    private String name;
    private ArrayList<String> users;
    private ArrayList<Conversation> conversations;
    private ArrayList<String> history;

    public ChatRoom(String name) {
        this.name=name;
        this.users= new ArrayList<String>();
        this.conversations= new ArrayList<Conversation>();
        this.history = new ArrayList<String>();
    }
    
    public void addUser(String name) throws RemoteException {
        try{
            users.add(name);
            //get the remote conversation
            Registry registry = LocateRegistry.getRegistry(12345);
            Conversation a = (Conversation) registry.lookup(name);
            //add the remote conversation to the conversation list
            conversations.add(a);
            //push the join message to the others users
            for (Conversation conv : conversations ) {
                conv.addMessage(name+" join the room "+this.name);
            }
            //add the current history to the remote conversation
            a.addhistory(history);
            //add the join message to the history with the date
            DateFormat dateFormat = new SimpleDateFormat(" [HH:mm] ");
			Date date = new Date();
            history.add(name+dateFormat.format(date)+" join the room "+this.name);
            //~ System.out.println(name+" join the room "+this.name);
        } catch(Exception e){
           e.printStackTrace();
       }
    }

    public void delUser(String name) throws RemoteException {
		//~ System.out.println(name+" leave the room "+this.name);
        int i= users.indexOf(name);
        conversations.remove(i);
        users.remove(name);
        //push the leave message to the others users
         for (Conversation conv : conversations ) {
                conv.addMessage(name+" leave the room "+this.name);
            }
		DateFormat dateFormat = new SimpleDateFormat(" [HH:mm] ");
		Date date = new Date();
        history.add(name+dateFormat.format(date)+" leave the room "+this.name);

    }

    public void sendMessage(String name,String message) throws RemoteException {
        //push the message to the others users
        for (Conversation conv : conversations ) {
            conv.addMessage(name+" : "+message);
        }
		DateFormat dateFormat = new SimpleDateFormat(" [HH:mm] ");
		Date date = new Date();
        history.add(name+dateFormat.format(date)+" : "+message);
    }

}
