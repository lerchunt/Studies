package chat;
import java.rmi.*;
import java.util.*;

public interface Conversation extends Remote {

    public void addMessage(String message) throws RemoteException;
    
    public void addhistory(ArrayList<String> messages) throws RemoteException;
    
    
}
