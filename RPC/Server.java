import java.util.*;
import java.io.*;
import java.net.*;

public class Server {

	public static void main(String[] args) throws Exception{
        ServerSocket sersock= new ServerSocket(5555);
        System.out.println("Server Ready...");
        Socket sock = sersock.accept();                 //establishes connection and waits for the client
	  	
        BufferedReader keyRead = new BufferedReader(new InputStreamReader(System.in));
        OutputStream ostream = sock.getOutputStream();
        PrintWriter pwrite = new PrintWriter(ostream, true);
        InputStream istream = sock.getInputStream();
        BufferedReader receiveRead = new BufferedReader(new InputStreamReader(istream));
        
        String receiveMessage, sendMessage, var;  //here var is temp

        int a, b;
        float c;
        while(true){
            var = receiveRead.readLine();
            System.out.println("Operation : " + var);

            a = Integer.parseInt(receiveRead.readLine());              // parseInt used to convert string to integer
            System.out.println("Parameter 1 : " + a);
            b = Integer.parseInt(receiveRead.readLine());
            System.out.println("Parameter 2 : " + b);

            if (var.compareTo("1") == 0) {
                c = a + b;
                System.out.println("Addition = " + c);
                pwrite.println("Addition = " + c);
            }
            else if (var.compareTo("2") == 0) {
                c = Math.abs(a - b);
                System.out.println("Subtraction = " + c);
                pwrite.println("Subtraction = " + c);
            }
            else if (var.compareTo("3") == 0) {
                c = a * b;
                System.out.println("Multplication = " + c);
                pwrite.println("Multplication = " + c);
            }
            else if (var.compareTo("4") == 0) {
                try{
                    c = a / b;
                    System.out.println("Division = " + c);
                    pwrite.println("Division = " + c);
                }
	
            catch (ArithmeticException e) {
                // Exception handler
               System.out.println("Divided by zero operation cannot possible");
               pwrite.println("Divided by zero operation cannot possible");
           }
            }           
            System.out.flush();
        }      
	}
}
