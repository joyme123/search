#include "../include/socket/ServerSocket.h"
#include "../include/socket/SocketException.h"
#include <string>
#include <iostream>

int main ( int argc, char* argv[] ){
    std::cout << "running....\n";

    try
    {
        // Create the socket at port 9999
        ServerSocket server (9999);
        while (true){
            ServerSocket new_sock;
            server.accept (new_sock);
            try{
                //代表连接已经建立，会一直在while中循环，当连接丢失，会进入catch中，跳出循环
                while (true){
                    std::string data;
                    new_sock >> data;
                    new_sock << data;
                    std::cout << "收到的数据为:" << data << std::endl;
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