#include <iostream>
#include <string>
#include "core/DocumentDAO.h"
#include "core/WordDAO.h"
#include "core/Document.h"
#include "core/util/DocumentParser.h"

void printMap(std::map<std::wstring,std::vector<int> > map){
	for(std::map<std::wstring,std::vector<int> >::iterator it = map.begin(); it != map.end(); it++){
		std::wcout << it->first << " ";
		std::vector<int> v = it->second;
		for(std::vector<int>::iterator vit = v.begin(); vit != v.end(); vit++){
			std::wcout << *vit << ",";
		}
		std::wcout << std::endl;
	}
}

int main(int argc, char **argv) {
	google::InitGoogleLogging("1");
	//title|type|author|url|text
	std::wstring documentFormat = L"Java虚拟机学习记录(九)——类文件结构(上)|1|joyme|http://myway5.com/?post=54|Friso是使用c语言开发的一款开源的高性能中文分词器，使用流行的mmseg算法实现。完全基于模块化设计和实现，可以很方便的植入其他程序中，例如：MySQL，PHP，源码无需修改就能在各种平台下编译使用，加载完20万的词条，内存占用稳定为14.5M.";
	Document document = DocumentParser::documentFormat(documentFormat);
	DocumentDAO doc;
    int id = doc.addDocument(document);
 	document.id = id;
    
    
	std::map<std::wstring,std::vector<int> > map = DocumentParser::splitWord(document.text,__FRISO_COMPLEX_MODE__);
    
	WordDAO wordDao;
	for(std::map<std::wstring,std::vector<int> >::iterator it = map.begin(); it != map.end(); it++){
			std::wstring word = it->first;
			
			PostingList posts;
			posts.document = document;
			posts.positions = it->second;
			
			std::shared_ptr<PostingList> ppp = std::make_shared<PostingList>(posts);
			wordDao.addWord(word,ppp);
	}

	std::cout << id << std::endl;
    return 0;
}
