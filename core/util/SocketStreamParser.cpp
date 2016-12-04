/**
 * SocketStreamParser的实现
 */

#include "SocketStreamParser.h"
#include "util.h"
#include<string>

SocketStreamParser::SocketStreamParser(){
    version = 0x01;
    lastBuf = new char[1];        //不够一个数据包的部分会保存在这里，等待新的数据加进来一起解析
    lastLen = 0;
    bodyLen = 0;
}

std::vector<Package> SocketStreamParser::parse(char* data,unsigned int dataLen){
    std::vector<Package> packs;
    
    lastBuf = mergeCharArray(lastBuf,lastLen,data,dataLen);     //这个函数会delete[] data和lastBuf的内存，并重新开启内存返回合并值
    lastLen = lastLen + dataLen;

    //校验版本号是否正确并计算body的长度
    if(lastBuf[0] == version){
        bodyLen = lastBuf[1] & 0xff;
        bodyLen = (bodyLen<<8) | (lastBuf[2] & 0xff);
        bodyLen = (bodyLen<<8) | (lastBuf[3] & 0xff);         //计算出body的长度,使用0xff作为掩码是为了将lastBuf[3]声明为无符号数，否则计算结果的高位补１而不是补０
        std::cout << "body长度为" << bodyLen << std::endl;
    }else{
        return packs;
    }

    




    //当剩下的字符串减去头部的长度大于body的长度，说明可以解析出一个数据包
    while(lastLen - 4 >= bodyLen){
        Package pack;
        std::string body;
        body = subCharArray(lastBuf,lastLen,4,bodyLen);      //截取一个body的长度
        std::cout << "内容为" << body << std::endl;

        pack.setBody(body);
        packs.push_back(pack);

        if(lastLen > 0){
            //校验版本号是否正确并计算body的长度
            if(lastBuf[0] == version){
                bodyLen = lastBuf[1];
                bodyLen = (bodyLen<<8) + lastBuf[2];
                bodyLen = (bodyLen<<8) + lastBuf[3];         //计算出body的长度
               
            }else{
                break;      //版本号不对则break
            }
        }else{
            break;
        }
    }

    return packs;
}

void SocketStreamParser:: reset(){
    this->lastLen = 0;      //重置保存的长度
    this->bodyLen = 0;
}