package chat;
import java.rmi.*;

interface Room extends Remote {

    public void addUser(String name) throws RemoteException;

    public void delUser(String name) throws RemoteException;

    public void sendMessage(String name,String message) throws RemoteException;

}
