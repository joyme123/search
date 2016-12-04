#ifndef PACKAGE_H
#define PACKAGE_H

#include<iostream>
#include<string>
#include"util/config.h"

class Package{
    public:
        DOCUMENT_TYPE type;
        std::string url;
        std::string content;
        void setBody(std::string body);
};


#endif