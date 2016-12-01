#include <iostream>
#include <string>
#include"core/DocumentController.h"
#include"core/WordController.h"
#include"include/socket/ServerSocket.h"
#include"include/socket/SocketException.h"

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
	try
    {
        // Create the socket at port 9999
        ServerSocket server (9999);
        while (true){
            ServerSocket new_sock;
            server.accept (new_sock);
            try{
                while (true){
                    std::string data;
                    new_sock >> data;			//接收到数据并赋值到data中
                    //new_sock << data;
                    std::cout << "收到的数据为:" << data << std::endl;
    				int count = docContrl.documentEntry(data);
					LOG(INFO) << "entry.cpp->main()"<<"add or update "<<count<< "word(s)";
                }
	        }catch ( SocketException& e) {
				LOG(INFO) << "entry.cpp->main()"<<"连接结束:"<< e.description();
			}
	    }
    }catch ( SocketException& e ){
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

	//title|type|author|url|text
	//std::string documentFormat = "Java虚拟机学习记录(九)——类文件结构(上)|1|joyme|http://myway5.com/?post=54|Friso是使用c语言开发的一款开源的高性能中文分词器，使用流行的mmseg算法实现。完全基于模块化设计和实现，可以很方便的植入其他程序中，例如：MySQL，PHP，源码无需修改就能在各种平台下编译使用，加载完20万的词条，内存占用稳定为14.5M.";
	
    return 0;
}
