这里的文档是过期的
### **文档添加协议**
这个搜索引擎本身是没有文档的添加功能的，所以需要通过外部程序按照一定的规则将文档加入到索引代码中进行索引。

为了支持爬虫和索引服务器的分离，使用socket通信，满足进程间或者网络间的数据传输。根据TCP协议的特点，传输的数据之间可能出现"粘包",为了解决粘包问题，制定了以下的传输协议。

数据包使用二进制流传输,一个数据包分为头部(head)和内容(body)两部分，其中body部分是文档的全部信息，头部主要是为了给分包算法提供支持

**head**

head共有4个字节组成(固定4个字节)，两个部分
 - 第一部分：version,1个字节，代表当前协议的版本号，1~127
 - 第二部分：length，3个字节，代表body部分的<font color="red">长度(请看下方的解释)</font>,0~16777216,这部分需要注意的是，3个字节必须填满，比如body部分的值是20，则传过来的length二进制为00000000 00000000 00010100。

 > 这里的长度指的是body部分以byte为单位的长度

**body**

body部分是一段有指定格式的文本:url\ntype\ncontent
即读到的第一个\n之前的body部分的数据为文档的地址
读到的第一个\n和第二个\n之间的数据为文档的类型，
type = 1 为html网页文档
type = 2 为pdf文档
type = 3 为word文档
之后的内容为网页的全部内容

**java实现的客户端代码示例**:https://github.com/joyme123/search/blob/master/doc/java_socket_client_implement.md

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