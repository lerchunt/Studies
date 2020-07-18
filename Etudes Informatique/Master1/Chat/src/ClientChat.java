package chat;
import java.io.*;
import java.util.*;
import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*;

public class ClientChat {

    public static void main(String[] args) {
       try {
          if (args.length<1) {
                System.out.println("Usage :\n\tClientChat <server host>");
                return ;
          } 
          String host=args[0];
		//recuperation de la room
          Registry registry = LocateRegistry.getRegistry(12345);
          Room r = (Room) registry.lookup("Room");

                  
          BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
          System.out.println("first name : ");
          String firstName=in.readLine();
          System.out.println("last name : ");
          String lastName=in.readLine();

		//creation of the conversation
          ConversationUser uc=new ConversationUser();
          Conversation conv = (Conversation) UnicastRemoteObject.exportObject(uc,0);
          registry.bind(firstName+" "+lastName,conv); 

          String user=firstName+" "+lastName;
          r.addUser(user);

          System.out.println("please write a message");
          String c= in.readLine();
          while(!c.equals("~quit")){
              r.sendMessage(user,c);
              c=in.readLine();
          }
          r.delUser(user);

       } catch(Exception e){
           e.printStackTrace();
       }
       System.exit(1); 
    }

}
