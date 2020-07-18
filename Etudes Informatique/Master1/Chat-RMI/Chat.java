import java.rmi.*;
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Chat extends Remote {
	void Connect(Client c) throws RemoteException;;
	void talk(Message m, Client c) throws RemoteException;
	void Disconnect(Client c) throws RemoteException;;
}
