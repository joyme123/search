#include<iostream>
#include"../core/util/DocumentParser.h"
#include<string>
#include<locale>

using namespace std;

void printMap(map<wstring,vector<int> > map){
	for(std::map<wstring,vector<int> >::iterator it = map.begin(); it != map.end(); it++){
		wcout << it->first << " ";
		vector<int> v = it->second;
		for(std::vector<int>::iterator vit = v.begin(); vit != v.end(); vit++){
			wcout << *vit << ",";
		}
		wcout << endl;
	}
}

int main(){
	locale loc("zh_CN.UTF-8");
    locale::global(loc);

	wstring text = L"被引aaa入以告知编译器";
	map<wstring,vector<int> > map1 =  DocumentParser::ngram(text,1);
	printMap(map1);
	
	map<wstring,vector<int> > map2 =  DocumentParser::ngram(text,2);
	printMap(map2);
	
	map<wstring,vector<int> > map3 =  DocumentParser::ngram(text,3);
	printMap(map3);
}