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
//	locale loc("zh_CN.UTF-8");
//    locale::global(loc);

	wstring text = L"Friso是使用c语言开发的一款开源的高性能中文分词器，使用流行的mmseg算法实现。完全基于模块化设计和实现，可以很方便的植入其他程序中，例如：MySQL，PHP，源码无需修改就能在各种平台下编译使用，加载完20万的词条，内存占用稳定为14.5M.";
    
    /**
     * typedef enum {
        __FRISO_SIMPLE_MODE__   = 1,
        __FRISO_COMPLEX_MODE__  = 2,
        __FRISO_DETECT_MODE__   = 3
    } friso_mode_t;
    */
    
	map<wstring,vector<int> > map1 =  DocumentParser::splitWord(text,__FRISO_COMPLEX_MODE__);
	printMap(map1);

}
