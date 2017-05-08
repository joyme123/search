#include <iostream>
#include <vector>  
#include <string>  

#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>  
#include "FCgiIO.h"

#include "src/include/json.hpp"
#include "src/core/util/Trie.h"
#include "src/core/model/Keyword.h"
#include "src/core/util/util.h"
#include <glog/logging.h>
using namespace cgicc;
using json = nlohmann::json;

json formatKeywordToJson(std::vector<Keyword> suggesstions){
	json j;
	for(unsigned int i = 0; i < suggesstions.size(); i++){
		json tmp;
		Keyword keyword = suggesstions[i];
		tmp["suggestion"] = WstringToString(keyword.word);
		tmp["count"] = keyword.count;
		j.push_back(tmp);
	}
	return j;
}


int main(int argc, char **argv) {
	FLAGS_log_dir = "/home/jiang/log";
	google::InitGoogleLogging("1");

    FCGX_Request request;
    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);
	//实例化Trie对象
    Trie trie;  
    while (FCGX_Accept_r(&request) == 0) {
		FCgiIO IO(request);
		try{
			
			Cgicc formData(&IO);	//实例化Cgicc对象
			IO << cgicc::HTTPHTMLHeader()<< std::endl;
			std::string keyword;
			form_iterator fi = formData.getElement("keyword");  	//关键字
			form_iterator ai = formData.getElement("add");			//是否添加到索引中
			form_iterator ni = formData.getElement("num");			//需要的提示数
			bool add = false;
			int  num = -1;
			if(!ai->isEmpty() && ai != (*formData).end()){
				if(**ai == "1"){
					add = true;
					
				}
			}

			if(!ni->isEmpty() && ni != (*formData).end()){
				num = std::stoi(**ni);
			}

			if( !fi->isEmpty() && fi != (*formData).end()) {

				json j;
				keyword = **fi; 
				if(add){
					trie.addWordToTrie(StringToWstring(keyword));
					j["add"] = "ok";
					IO << j.dump() << std::endl;
				}else{
					std::vector<Keyword> suggestions = trie.searchPrefix(StringToWstring(keyword),num);
					j["words"] = formatKeywordToJson(suggestions);
					IO << j.dump() << std::endl;
				}
				
			}else{
				IO << "no input here" << std::endl;  
			}
		}catch(const std::exception& e){
				IO << "error happened" << std::endl;
		}
		FCGX_Finish_r(&request);
	}

    return 0;
}
