/**
 * SocketStreamParser的实现
 */

#include "SocketStreamParser.h"
#include<string>

SocketStreamParser::SocketStreamParser(){
    version = 0x01;
    lastBuf = new char[1];        //不够一个数据包的部分会保存在这里，等待新的数据加进来一起解析
    lastLen = 0;
    bodyLen = 0;
}

/**
 * 将两个char*数组合并为新的数组 
 */
char* SocketStreamParser::mergeCharArray(char* first,unsigned int firstLen,char* second,unsigned int secondLen){
    unsigned int new_len = firstLen+secondLen;
    char* new_char = new char[new_len];     //统一使用new开数组
    unsigned int i;
    for( i = 0; i < firstLen;++i){
        new_char[i] = first[i];
    }
    for( ;i < new_len; ++i){
        new_char[i] = second[i - firstLen];
    }
    
    delete []first;
    delete []second;
    first = NULL;
    second = NULL;

    return new_char;
}

std::string SocketStreamParser::subCharArray(char*& cbuf,unsigned int& len,unsigned int start,int subLen){
    char* cstr = new char[subLen+1];
    int limit = start + subLen;
    int pos = -1;
    for(int i = start; i < limit; ++i){
        cstr[++pos] = cbuf[i];
    }

    cstr[++pos] = '\0';

    limit = len - subLen - start;

    for(int i = 0; i < limit; ++i){
        cbuf[i] = cbuf[i + start + subLen];
    }
    len = limit;


    return std::string(cstr);
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