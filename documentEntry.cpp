/**
 * 接受原生文档，比如通过爬虫下载的未处理的网页
 * author:jiangpengfei
 * date: 2016-12-07
 */
#include <string>
#include"core/DocumentController.h"
#include"core/WordController.h"
#include"include/socket/ServerSocket.h"
#include"include/socket/SocketException.h"
#include"core/Package.h"
#include "core/util/SocketStreamParser.h"
#include "core/util/util.h"

void printMap(std::map<std::string,std::vector<int> > map){
	for(std::map<std::string,std::vector<int> >::iterator it = map.begin(); it != map.end(); it++){
		std::cout << it->first << " ";
		std::vector<int> v = it->second;
		for(std::vector<int>::iterator vit = v.begin(); vit != v.end(); vit++){
			std::cout << *vit << ",";
		}
		std::cout << std::endl;
	}
}

void printPostingList(std::shared_ptr<PostingList> p){
    std::cout << "********************" << std::endl;
	while(p!=NULL){
        std::cout << "文档编号" << p->documentId << std::endl;
		std::cout << "出现的位置";
		for(std::vector<int>::iterator it = p->positions.begin(); it != p->positions.end(); it++){
				std::cout << *it << " ";
		}
		std::cout << std::endl;
        p = p->next;
    }
}

int main(int argc, char **argv) {
	google::InitGoogleLogging("1");
	DocumentController docContrl;
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
					int count = docContrl.documentEntry(packs);     //将解析出来的数据包放入documentEntry中进行处理
					LOG(INFO) << "entry.cpp->main()"<<"add or update "<<count<< "word(s)";
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
