package server;

import java.net.*;
import java.util.Scanner;
import java.io.*;

public class TCPServer {
	
	
	public static void main(String[] args) throws IOException {
		
			ServerSocket servSock = new ServerSocket(1333);
			
			String[] s = null;
			File[] f1;
			
			File f=new File(System.getProperty("user.dir"));
			f1=f.listFiles();
			
			/*for(File f2:f1) {
				if(f2.isDirectory())
		            System.out.println(f2.getName() + "\t<DIREKTORIUM>\t" + i);
				if(f2.isFile()) 
					System.out.println(f2.getName() + "\t<DATOTEKA>\t" + i);
				i++;
			}*/
			
				while (true) { 
					
					Socket client = servSock.accept();
					
					InputStream in = client.getInputStream();
					OutputStream out = client.getOutputStream();
					BufferedReader reader = new BufferedReader(new InputStreamReader(in));
					PrintWriter pw = new PrintWriter(out, true);
					String primeno="";
					int i=0;
					s=f.list();
					
					while(true) {
						primeno = reader.readLine();
						
						if(primeno.equals("KRAJ")) break;
						if(primeno.equals("Hello")) {
							f1=f.listFiles();
							s=f.list();
							int dolzina=f1.length;
							pw.println(dolzina);
							i=0;
							for(File f2:f1) {
								if(f2.isDirectory())
						            pw.println(f2.getName() + "\t<DIREKTORIUM>\t" + i);
								if(f2.isFile()) 
						            pw.println(f2.getName() + "\t<DATOTEKA>\t" + i);
								i++;
							}
							pw.println("Opcii: " + "\tFileDownload <FID>" + "\tFileUpload <ime>" + "\tChangeFolder <FID>");

						}
						else if(primeno.contains("FileDownload")) {

							int j=-1;
							try {
								j=Integer.parseInt(primeno.substring(13).trim());
							}catch(NumberFormatException e) { 
								System.err.println("error: " + e);
							}
							
							if(j>0 && j<s.length) {
								FileInputStream fi=new FileInputStream(s[j]);
								byte[] b=new byte[1024];
								System.out.println("file: "+s[j]);

								pw.println(s[j]);
								fi.read(b,0,b.length);
								out.write(b,0,b.length);
							}
						}
						else if(primeno.contains("FileUpload")) {
							byte[] b1=new byte[1024];

							String file=primeno.substring(11).trim();
							FileOutputStream fo=new FileOutputStream("D:\\Eclipse WorkSpace\\proekt\\src\\server\\"+file);
							
							in.read(b1,0,b1.length);
							fo.write(b1,0,b1.length);
							
							
						}
					}
					client.close(); 

				}
			}
			
		}
