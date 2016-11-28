#include <iostream>
#include <string>
#include"core/DocumentController.h"
#include"core/WordController.h"

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
	//title|type|author|url|text
	std::wstring documentFormat = L"Java虚拟机学习记录(九)——类文件结构(上)|1|joyme|http://myway5.com/?post=54|Friso是使用c语言开发的一款开源的高性能中文分词器，使用流行的mmseg算法实现。完全基于模块化设计和实现，可以很方便的植入其他程序中，例如：MySQL，PHP，源码无需修改就能在各种平台下编译使用，加载完20万的词条，内存占用稳定为14.5M.";
	DocumentController docContrl;
    int count = docContrl.documentEntry(documentFormat);
    
	std::cout << "add or update "<<count<< "word(s)" << std::endl;
    
	WordController wordCtrl;
	InvertedIndexHash invertedIndexHash = wordCtrl.searchWord("实现");
	std::cout << "查询的单词编号" << invertedIndexHash.id << std::endl;
	std::cout << "单词的总出现次数" << invertedIndexHash.totalCount << std::endl;
	std::cout << "总共有多少文档" << invertedIndexHash.docCount << std::endl;
	printPostingList(invertedIndexHash.postingList);
	
    return 0;
}
