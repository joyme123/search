#include <iostream>
#include <string>
#include "src/core/util/Trie.h"
#include "src/include/json.hpp"
using namespace std;
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


void fun(){
    locale loc("zh_CN.UTF-8");
    locale::global(loc);
    Trie trie;
    wstring word;
    while(wcin >> word){
        if(word == L"exit"){
            break;
        }
        std::vector<Keyword> keywords =  trie.searchPrefix(word);
        formatKeywordToJson(keywords);
    }
}

int main(){
    fun();
    return 1;
}