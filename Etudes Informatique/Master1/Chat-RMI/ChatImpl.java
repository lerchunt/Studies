import java.rmi.RemoteException;
import java.rmi.*;
import java.rmi.server.*; 

public class ChatImpl implements Chat{
	String nom_app;
	public ChatImpl(String s){
		
		this.nom_app=s;
	}
	@Override
	public void Connect(Client c) throws RemoteException {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void talk(Message m, Client c) throws RemoteException {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void Disconnect(Client c) throws RemoteException {
		// TODO Auto-generated method stub
		
	}

}
