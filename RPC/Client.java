import java.util.*;
import java.net.*;
import java.io.*;

public class Client{
    public static void main(String [] args) throws Exception{
        Socket sock= new Socket("127.0.0.1", 5555);
        
        BufferedReader keyRead= new BufferedReader(new InputStreamReader(System.in));  // BufferedReader used to read input from console, InputStreamReader used to get data from user
        OutputStream ostream= sock.getOutputStream();								   // returns an output stream for writing bytes to this socket, returns an output stream for the given socket.
        PrintWriter pwrite= new PrintWriter(ostream,true);							   // used to print the formatted representation of objects to the text-output stream
        InputStream istream= sock.getInputStream();									   // returns an input stream for reading bytes from this socket, returns an input stream for the given socket
        BufferedReader receiveRead= new BufferedReader(new InputStreamReader(istream));

        System.out.println("Client Ready, Press Enter key");
        String receiveMessage, sendMessage, temp;
        
        while(true){
            System.out.println("Enter the operation you want to perform:");
            System.out.println("1.Addition");
            System.out.println("2.Subtraction");
	        System.out.println("3.Multplication");
	        System.out.println("4.Division");

	        // input 1 or 2 or 3 or even 1.addition will work
            temp= keyRead.readLine();                                          //It is used for reading a line of text
            sendMessage= temp.toLowerCase(); 
            pwrite.println(sendMessage);

            System.out.println("Enter first parameter for the operation  :");
            sendMessage = keyRead.readLine();
            pwrite.println(sendMessage);

            System.out.println("Enter second parameter for the operation : ");
            sendMessage = keyRead.readLine();
            pwrite.println(sendMessage);

            System.out.flush();
            receiveMessage = receiveRead.readLine();
            System.out.println(receiveMessage);
        }
    }
}






//if ((receiveMessage = receiveRead.readLine()) != null) {
//    System.out.println(receiveMessage);
//}
