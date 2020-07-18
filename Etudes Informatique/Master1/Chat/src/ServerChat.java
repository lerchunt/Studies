package chat;
import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*;

public class ServerChat {

    public static void main(String[] args) {
        try {
            ChatRoom cr=new ChatRoom("room1");
            Room r_stub = (Room) UnicastRemoteObject.exportObject(cr,0);

            Registry registry = LocateRegistry.createRegistry(12345);
            registry.bind("Room", r_stub);

        } catch(Exception e){
            e.printStackTrace();
        } 
    }

}
