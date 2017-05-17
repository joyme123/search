/**
 * cgi方式的请求平均是200ms耗时
 */
#include <iostream>
#include <vector>  
#include <string>  
#include <stdio.h>  
#include <stdlib.h> 

#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>  
#include "src/core/util/FCgiIO.h"

#include "src/include/json.hpp"
#include "src/core/controller/HtmlDocumentController.h"
#include "src/core/controller/WordController.h"

using namespace cgicc;
using json = nlohmann::json;

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

/**
 * print postList info and return document Id vector
 * @param p postList
 * @return vector of document id
 */
std::vector<unsigned int> formatPostingList(std::shared_ptr<PostingList> p){
	std::vector<unsigned int> ids;
	while(p!=NULL){
		ids.push_back(p->documentId);
		// for(std::vector<int>::iterator it = p->positions.begin(); it != p->positions.end(); it++){
		// 		std::cout << *it << " ";
		// }
        p = p->next;
    }
    return ids;
}

json formatDocumentToJson(std::vector<Document> documents){
	json j;
	for(unsigned int i = 0; i < documents.size(); i++){
		json tmp;
		Document doc = documents[i];
		tmp["title"] = doc.title;
		tmp["url"] = doc.url;
		tmp["updateTime"] = doc.updateTime;
		tmp["text"] = doc.text;
		j.push_back(tmp);
	}
	return j;
}

void printHtml(){
		std::cout <<"<html><head><title>GSearch搜索引擎</title><meta charset='utf-8'></head><body>";
}

void printHtmlEnd(){
		std::cout <<"</body></html>";
}

int main(int argc, char **argv) {
	FLAGS_log_dir = "/home/jiang/log";
	google::InitGoogleLogging("1");
	int pageIndex = 1;

    FCGX_Request request;

    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);
	WordController wordCtrl;
	int docCount = 0;
    while (FCGX_Accept_r(&request) == 0) {
		FCgiIO IO(request);
		try{
			Cgicc formData(&IO);
			IO << cgicc::HTTPHTMLHeader()<< std::endl;
			
			form_iterator fi = formData.getElement("keyword");  
			form_iterator pageI = formData.getElement("page");
			if(!pageI->isEmpty() && pageI != (*formData).end()){
				pageIndex = stoi((**pageI));
			}

			int PAGESIZE = 10;
			if( !fi->isEmpty() && fi != (*formData).end()) {
				json j;
				std::string sentence = **fi; 
				std::vector<Document> docs =  wordCtrl.searchWithSentence(sentence,docCount,pageIndex,PAGESIZE);
				json docJson = formatDocumentToJson(docs);
				j["docCount"] = docCount;
				j["docs"] = docJson;
				j["pageIndex"] = pageIndex;
				j["pageSize"] = PAGESIZE;
				IO << j.dump() << std::endl;
			}else{
				IO << "search keyword is invalid" << std::endl;  
			}
		}catch(const std::exception& e){
			IO << "error happened!" << std::endl;
		}

		FCGX_Finish_r(&request);
	}
    return 0;
}
