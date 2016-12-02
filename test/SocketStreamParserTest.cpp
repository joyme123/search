#include "../include/socket/ServerSocket.h"
#include "../include/socket/SocketException.h"
#include "../core/util/SocketStreamParser.h"
#include "../core/Package.h"
#include "../core/util/util.h"
#include <string>
#include <iostream>

int main ( int argc, char* argv[] ){
    std::cout << "running....\n";

    try{
        // Create the socket at port 9999
        ServerSocket server (9999);
        std::vector<Package> packs;
        SocketStreamParser parser;      
        while (true){
            parser.reset(); //每一次连接都要重置解析器

            ServerSocket new_sock;
            server.accept (new_sock);
            try{
                //代表连接已经建立，会一直在while中循环，当连接丢失，会进入catch中，跳出循环
                while (true){
                    char* data;
                    int dataLen;
                    new_sock.recvBinary(data,dataLen);
                    packs = parser.parse(data,dataLen);
                    std::cout  <<"长度为:"<< dataLen << "-----解析数据包:" << packs.size() << std::endl;
                }
	        }catch ( SocketException& e) {
                std::cout << "连接丢失:" << e.description() << std::endl;
            }
	    }
    }catch ( SocketException& e ){
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
    return 0;
}