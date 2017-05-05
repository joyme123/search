#include <iostream>
#include <string>
#include "src/core/util/Trie.h"

using namespace std;

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
        for(auto it = keywords.begin(); it != keywords.end(); it++){
            wcout << L"搜索词:" << it->word << L"|||||搜索次数" << it->count << endl;
        }
    }
}

int main(){
    fun();
    return 1;
}