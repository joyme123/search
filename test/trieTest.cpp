#include <iostream>
#include <string>
#include <fstream>
#include "src/core/util/Trie.h"
#include "src/include/json.hpp"
using namespace std;
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
    cout << j.dump(4) << endl;
	return j;
}


void fun(){
    
    locale loc("zh_CN.UTF-8");
    locale::global(loc);
    Trie trie;
    std::ifstream ifstream("/home/jiang/projects/search/test/bin/trie_persistent_db.txt",std::ios::binary);
    trie.read(ifstream);
    wstring word;
    cout << "输入exit退出程序" << endl;
    while(wcin >> word){
        if(word == L"exit"){
            break;
        }
        std::vector<Keyword> keywords =  trie.searchPrefix(word);   //搜索
        trie.addWordToTrie(word);                                   //添加到树中
        formatKeywordToJson(keywords);
    }
    std::ofstream stream("/home/jiang/projects/search/test/bin/trie_persistent.txt",std::ios::binary);
    trie.persist(stream);

}

int main(){
    fun();
    return 1;
}