/**
 * SocketStreamParser的实现
 */

#include "SocketStreamParser.h"
#include<string>

std::vector<Package> SocketStreamParser::parse(std::string &data){
    std::vector<Package> packs;
    char v = data[0];
    unsigned int strLen = data.length();

    Package pack;
    string body;
    unsigned int length;
    //校验版本号
    if(v == version){
        length = data[1];
        length = length<<8+data[2];
        length = length<<8+data[3];         //计算出length的大小
    }

    //可以截取到一个数据包
    if(strLen - 4 >= length){
        body = data.substr()
    }

    return packs;
}
