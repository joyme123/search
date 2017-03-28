/**
 * filename:Package.h
 * Socket数据包的头文件
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#ifndef PACKAGE_H
#define PACKAGE_H

#include<iostream>
#include<string>
#include"util/config.h"

class Package{
    public:
        DOCUMENT_TYPE type;
        std::string title;
        std::string url;
        std::string content;
        void setBody(std::string body);
};


#endif