/**
 * cgi方式的请求平均是200ms耗时
 */
#include <iostream>
#include <vector>  
#include <string>  
#include <stdio.h>  
#include <stdlib.h> 

#include <fcgio.h>
#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>  
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
	// Backup the stdio streambufs
    std::streambuf * cin_streambuf  = std::cin.rdbuf();
    std::streambuf * cout_streambuf = std::cout.rdbuf();
    std::streambuf * cerr_streambuf = std::cerr.rdbuf();

    FCGX_Request request;

    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    while (FCGX_Accept_r(&request) == 0) {
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);

        std::cin.rdbuf(&cin_fcgi_streambuf);
        std::cout.rdbuf(&cout_fcgi_streambuf);
        std::cerr.rdbuf(&cerr_fcgi_streambuf);

		std::cout << cgicc::HTTPHTMLHeader()<< std::endl;
		Cgicc formData;
		
		form_iterator fi = formData.getElement("keyword");  
		form_iterator pageI = formData.getElement("page");
		if(!pageI->isEmpty() && pageI != (*formData).end()){
			pageIndex = stoi((**pageI));
		}


		int PAGESIZE = 10;
		if( !fi->isEmpty() && fi != (*formData).end()) {
			json j;
			j["keyword"] = **fi; 
			WordController wordCtrl;
			InvertedIndexHash invertedIndexHash = wordCtrl.searchWord(**fi);
			j["wordId"] = invertedIndexHash.id;
			j["total"] = invertedIndexHash.totalCount;
			j["docCount"] = invertedIndexHash.docCount;
			std::vector<unsigned int> ids = formatPostingList(invertedIndexHash.postingList);
			std::vector<unsigned int> readIds;
			for(int i = (pageIndex - 1) * PAGESIZE; i < pageIndex * PAGESIZE && i < ids.size(); i++){
				readIds.push_back(ids[i]);
			}
			HtmlDocumentController docCtrl;
			std::vector<Document> docs =  docCtrl.searchDocument(readIds);
			json docJson = formatDocumentToJson(docs);
			j["docs"] = docJson;
			j["pageIndex"] = pageIndex;
			j["pageSize"] = PAGESIZE;
			std::cout << j.dump(4) << std::endl;
		}else{
			std::cout << "search keyword is valid" << std::endl;  
		}
	}
    // restore stdio streambufs
    std::cin.rdbuf(cin_streambuf);
    std::cout.rdbuf(cout_streambuf);
    std::cerr.rdbuf(cerr_streambuf);

    return 0;
}
