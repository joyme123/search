#include "src/core/util/util.h"

int main(){
    std::string s = "Friso是使用c语言开发的一款开源的高性能中文分词器，使用流行的mmseg算法实现。完全基于模块化设计和实现，可以很方便的植入其他程序中，例如：MySQL，PHP，源码无需修改就能在各种平台下编译使用，加载完20万的词条，内存占用稳定为14.5M.";
    std::cout << getUtf8StringLength(s) << std::endl;
    std::cout << substrWithChinese(s,0,10) << std::endl;
}