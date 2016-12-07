# Java实现的文档添加的客户端(Java socket client implement)

## socket wrap
```java
package jiang;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.Socket;

public class SocketClient {
	private String server = "127.0.0.1";
	private int port = 9999;
	private Socket socket;
	private OutputStream os;
	InputStreamReader reader;
	
	public SocketClient(){
		try {
			socket = new Socket(server, port);
			os = socket.getOutputStream();
			reader = new InputStreamReader(socket.getInputStream());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void send(byte[] b){
		try {
			os.write(b);
			os.flush();
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void recv(){
		char[] c = new char[1024];
		StringBuilder sb = new StringBuilder();
		try {
			while((reader.read(c)) != -1){
				sb.append(new String(c));
				System.out.println(sb);
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void close(){
		try {
			os.close();
			socket.close();
			reader.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
}
```
## client
```java
package jiang;

import java.util.Scanner;

public class Main {
	public static void main(String[] args){
		SocketClient client = new SocketClient();
		
		
		byte[] head = new byte[4];
		head[0] = 0x01;
		Scanner scanner = new Scanner(System.in);
		while(scanner.hasNextLine()){
			String str = scanner.nextLine();
			byte[] strByte = str.getBytes();
			Integer len = strByte.length;
			head[1] = (byte) ((byte)0xff & (len >> 16)) ;
			head[2] = (byte) ((byte)0xff & (len >> 8)) ;
			head[3] = (byte) ((byte)0xff & (len));
			byte[] total = new byte[4+len];

			System.out.println(total.length);
			
			for(int i = 0; i < len+4; i++){
				if(i < 4){
					total[i] = head[i];
				}else{
					total[i] = strByte[i-4];
				}
			}
			
			client.send(total);
//			client.send(total);
//			client.send(total);
//			client.send(total);
//			client.send(total);
//			client.send(total);
//			client.send(total);
//			client.send(total);
//			client.send(total);
//			client.send(total);
//			client.send(total);
//			client.send(total);	//模拟粘包问题
		}
		scanner.close();
		
		
	}
}
```