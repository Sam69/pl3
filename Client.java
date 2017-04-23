//package b10;
import java.net.*;
import java.io.*;
import java.util.Scanner;

public class Client {
	public static Scanner sc=new Scanner(System.in);
	public Client() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) throws UnknownHostException, IOException {
		
		String ip="localhost";
		int port=25000;
		try
		{
			Socket cl=new Socket(ip,port);
			System.out.println("You are now connected to "+cl.getRemoteSocketAddress());
			DataOutputStream out=new DataOutputStream(cl.getOutputStream());
			DataInputStream in=new DataInputStream(cl.getInputStream());
			
			out.writeUTF("I am a new Client");
			
			System.out.println("Server says:\n"+in.readUTF());
			System.out.println("Do you wish to quit? (y/n)");
			char ch=sc.nextLine().charAt(0);
			while(ch!='y' && ch!='Y')
			{
				System.out.println("Server responded: "+in.readUTF());
				System.out.println("Do you wish to quit? (y/n)");
				ch=sc.nextLine().charAt(0);
			}
			cl.close();
		}catch(IOException e)
		{
			e.printStackTrace();
		}

	}

}
