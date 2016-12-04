/**
 * 文档接收类，主要是对接收到的数据进行分包处理
 * author:jiangpengfei
 * date:2016-12-01
 */
#ifndef SOCKETSTREAMPARSER_H
#define SOCKETSTREAMPARSER_H

#include<iostream>
#include<vector>
#include "../Package.h"

class SocketStreamParser{
    public:
        char version;
        char* lastBuf;          //不够一个数据包的部分会保存在这里，等待新的数据加进来一起解析
        unsigned int lastLen;
        unsigned int bodyLen;   //当一次消息过长，socket会分包，这里保存body的长度
        
        SocketStreamParser();

        /**
         * 传入接收到的数据包进行解析
         * @param data 要传入的数据
         * @return 返回package数组，并且data变成数据流解析后剩下的部分
         */
        std::vector<Package> parse(char* data,unsigned int length);

        void reset();

 };

#endif