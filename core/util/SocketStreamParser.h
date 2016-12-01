/**
 * 文档接收类，主要是对接收到的数据进行分包处理
 * author:jiangpengfei
 * date:2016-12-01
 */
#ifndef SOCKETSTREAMPARSER_H
#define SOCKETSTREAMPARSER_H

#include<iostream>
#include<vector>
#include"Package.h"

class SocketStreamParser{
    public:
        static char version = 0x01;

        /**
         * 传入接收到的数据包进行解析
         * @param data 要传入的数据
         * @return 返回package数组，并且data变成数据流解析后剩下的部分
         */
        static std::vector<Package> parse(std::string& data);


 }

#endif