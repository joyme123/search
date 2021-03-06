#include <iostream>
#include <string>
#include <locale>
#include "src/core/util/WordSplitSingleton.h"
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
	WordSplitSingleton *wordSpilt = WordSplitSingleton::getInstance(__FRISO_COMPLEX_MODE__);

	string text = "Friso是使用c语言开发的一款开源的高性能中文分词器，使用流行的mmseg算法实现。完全基于模块化设计和实现，可以很方便的植入其他程序中，例如：MySQL，PHP，源码无需修改就能在各种平台下编译使用，加载完20万的词条，内存占用稳定为14.5M.电话号码:15000895132";
    
    /**
     * typedef enum {
        __FRISO_SIMPLE_MODE__   = 1,
        __FRISO_COMPLEX_MODE__  = 2,
        __FRISO_DETECT_MODE__   = 3
    } friso_mode_t;
    */
    
	map<string,vector<int> > map1 =  wordSpilt->splitWord(text);
	printMap(map1);

}
