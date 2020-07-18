import java.util.ArrayList;
import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*; 

public class Serveur{
	public ArrayList<Client> clientsConnectés;
	
	public static void main(String [] args){
		try{
		ChatImpl chi = new ChatImpl("Chat 1");
		Chat ch_stub = (Chat) UnicastRemoteObject.exportObject(chi, 0);
		 // Register the remote object in RMI registry with a given identifier
		 Registry registry= LocateRegistry.getRegistry();
		 registry.bind("Chat1", ch_stub);	
		 System.out.println ("Server ready"); 
		 }
		catch(Exception e){
			System.err.println("Error on server :" + e) ;
			e.printStackTrace(); 
		}
	}
	
}
