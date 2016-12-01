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
    private:
        const int version = 1;     //版本号为1
        unsigned int length;       //body部分的长度

        /**
         * 解析数据流的头部
         */
        private bool parseHeader();

        /**
         * 解析数据流的body
         */
        private void parseBody();
    public:

        /**
         * 传入接收到的数据包进行解析
         * @param data 要传入的数据
         * @return 返回package数组，并且data变成数据流解析后剩下的部分
         */
        public vector<Package> parse(string& data);


 }

#endif