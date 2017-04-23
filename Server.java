//package b10;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.*;
import java.util.Scanner;
//import java.util.concurrent.TimeUnit;

public class Server implements Runnable {
	public static Scanner sc=new Scanner(System.in);
	public Socket sock;
	public Server(Socket s)
	{
		sock=s;
	}
	
	public static void main(String[] args) throws InterruptedException 
	{
		ServerSocket ss;
		System.out.println("Enter the port to listen on:\n");
//		int port=sc.nextInt();
		try
		{
			ss=new ServerSocket(25000);
			while(true)
			{
				System.out.println("Listening...");
//				TimeUnit.SECONDS.sleep(1);
				Socket server =ss.accept();
				Server Serv=new Server(server);
				(new Thread(Serv)).start();
			}
			
			
		}catch(IOException e)
		{
			e.printStackTrace();
		}
		
		

	}

	@Override
	public void run() 
	{
		System.out.println("Connected to : "+sock.getRemoteSocketAddress()+" on port "+sock.getPort());
		try
		{
			DataInputStream in=new DataInputStream(sock.getInputStream());
			long threadId=Thread.currentThread().getId();
			String Id="Current Thread Id is: "+threadId;
			Id+=in.readUTF();
			System.out.println(Id);
			
			DataOutputStream out=new DataOutputStream(sock.getOutputStream());
			out.writeUTF("Connected...\n");
			out.writeUTF("Do you want to Quit? (y/n)");
			char ch=in.readChar();
			while(ch!='y' && ch!='Y')
			{
				out.writeUTF("Write your Message:\n");
				System.out.println("Echoing: "+in.readUTF());
				out.writeUTF("Do you want to Quit? (y/n)");
				ch=in.readChar();
			}
			System.out.println("Thread with Id: "+threadId+" closed.");
			sock.close();
			
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally{
			
		}
		
		
	}

}
