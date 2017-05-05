#include <iostream>
#include <vector>  
#include <string>  

#include <fcgio.h>
#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>  
#include "src/include/json.hpp"
#include "src/core/util/Trie.h"
#include "src/core/model/Keyword.h"
#include "src/core/util/util.h"

using namespace cgicc;
using json = nlohmann::json;

json formatKeywordToJson(std::vector<Keyword> suggesstions){
	json j;
	for(unsigned int i = 0; i < suggesstions.size(); i++){
		json tmp;
		Keyword keyword = suggesstions[i];
		tmp["suggestion"] = keyword.word;
		tmp["count"] = keyword.count;
		j.push_back(tmp);
	}
	return j;
}


int main(int argc, char **argv) {
	FLAGS_log_dir = "/home/jiang/log";
	google::InitGoogleLogging("1");
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
		//实例化Cgicc对象
        Cgicc formData;
        //实例化Trie对象
        Trie trie;  
		std::string keyword;
		form_iterator fi = formData.getElement("keyword");  
		
		if( !fi->isEmpty() && fi != (*formData).end()) {
			json j;
			keyword = **fi; 
			std::vector<Keyword> suggestions = trie.searchPrefix(StringToWstring(keyword));
            j['data'] = formatKeywordToJson(suggestions);
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
