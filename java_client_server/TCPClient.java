package client;

import java.net.*;
import java.io.*;
import java.util.Scanner;

public class TCPClient {

	public static void main(String[] args) throws IOException {
		if ((args.length != 2))
		throw new IllegalArgumentException("Parameter(s): <Server> <Port>");
		
		Socket socket = new Socket(args[0], Integer.parseInt(args[1]));
		Scanner vlez = new Scanner(System.in);
		InputStream in = socket.getInputStream();
		OutputStream out = socket.getOutputStream();
		BufferedReader reader = new BufferedReader(new InputStreamReader(in));
		PrintWriter pw = new PrintWriter(out, true);

		
		while(true) {
			String poraka=null, primeno="";
			String dolzina;
			
			poraka = vlez.nextLine();
			pw.println(poraka);
			
			if(poraka.equals("KRAJ")) break; 
			
				if(poraka.equals("Hello")) {
					System.out.println();
					dolzina = reader.readLine();
					for(int i=0;i<Integer.parseInt(dolzina);i++) {
						primeno = reader.readLine();
						System.out.println(primeno);
					}
					System.out.println("\n"+reader.readLine());
				}
				else if(poraka.contains("FileDownload")) {
					byte[] b=new byte[1024];
					File file=new File(reader.readLine().trim());
					FileOutputStream fo=new FileOutputStream("D:\\Eclipse WorkSpace\\proekt\\src\\client\\"+file.getName().trim());
					System.out.println("file: "+file.getName().trim());

					in.read(b,0,b.length);
					fo.write(b,0,b.length);
					
				}
				else if(poraka.contains("FileUpload")) {
					
					
					byte[] b1=new byte[1024];

					String file=poraka.substring(11);
					FileInputStream fi=new FileInputStream("D:\\Eclipse WorkSpace\\proekt\\src\\client\\"+file.trim());
					
					fi.read(b1,0,b1.length);
					out.write(b1,0,b1.length);					
				}
			}
		vlez.close();
		socket.close(); 
	}
}
