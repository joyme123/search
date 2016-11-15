#include<iostream>
#include"../core/util/DocumentParser.h"
#include<string>

using namespace std;

void printMap(map<string,vector<int> > map){
	for(std::map<string,vector<int> >::iterator it = map.begin(); it != map.end(); it++){
		cout << it->first << " ";
		vector<int> v = it->second;
		for(std::vector<int>::iterator vit = v.begin(); vit != v.end(); vit++){
			cout << *vit << ",";
		}
		cout << endl;
	}
}

int main(){
	string text = " static被引入以告知编译器，将变量存储在程序的静态存储区而非栈上空间，静态数据成员按定义出现的先后顺序依次初始化，注意静态成员嵌套时，要保证所嵌套的成员已经初始化了。消除时的顺序是初始化的反顺序.";
	map<string,vector<int> > map1 =  DocumentParser::ngram(text,1);
	printMap(map1);
	
	map<string,vector<int> > map2 =  DocumentParser::ngram(text,2);
	printMap(map2);
	
	map<string,vector<int> > map3 =  DocumentParser::ngram(text,3);
	printMap(map3);
}