#include <iostream>
#include <vector>  
#include <string>  
#include <stdio.h>  
#include <stdlib.h> 

#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>  

#include"../../core/DocumentController.h"
#include"../../core/WordController.h"

using namespace cgicc;

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

/**
 * print postList info and return document Id vector
 * @param p postList
 * @return vector of document id
 */
std::vector<unsigned int> printPostingList(std::shared_ptr<PostingList> p){
	std::vector<unsigned int> ids;
    std::cout << "********************" << std::endl;
	while(p!=NULL){
		ids.push_back(p->documentId);
        std::cout << "文档编号" << p->documentId << std::endl;
		std::cout << "出现的位置";
		for(std::vector<int>::iterator it = p->positions.begin(); it != p->positions.end(); it++){
				std::cout << *it << " ";
		}
		std::cout << std::endl;
        p = p->next;
    }
    return ids;
}

void printDocument(std::vector<Document> documents){
	for(unsigned int i = 0; i < documents.size(); i++){
		Document doc =  documents[i];
		std::wcout << doc.title;
		std::wcout << doc.createTime;
		std::wcout<<doc.text;
	}
}

void printHtml(){
		std::cout <<"<html><head><title>标题</title><meta charset='utf-8'></head><body>";
}

void printHtmlEnd(){
		std::cout <<"</body></html>";
}

int main(int argc, char **argv) {
	google::InitGoogleLogging("1");
	
	std::cout << cgicc::HTTPHTMLHeader()<< std::endl;
	printHtml();
	Cgicc formData;
	
	form_iterator fi = formData.getElement("keyWord");  
	if( !fi->isEmpty() && fi != (*formData).end()) {
		std::cout << "查询的单词：" << **fi << "<br>";  
		WordController wordCtrl;
		InvertedIndexHash invertedIndexHash = wordCtrl.searchWord(**fi);
		std::cout << "查询的单词编号" << invertedIndexHash.id <<  "<br>";
		std::cout << "单词的总出现次数" << invertedIndexHash.totalCount <<  "<br>";
		std::cout << "总共有多少文档" << invertedIndexHash.docCount <<  "<br>";
		std::vector<unsigned int> ids = printPostingList(invertedIndexHash.postingList);
		
		DocumentController docCtrl;
		std::vector<Document> docs =  docCtrl.searchDocument(ids);
		std::cout << ids.size();
		printDocument(docs);
	}else{
		std::cout << "search keyword is valid" << std::endl;  
	}
	printHtmlEnd();
    return 0;
}
