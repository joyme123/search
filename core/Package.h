#ifndef PACKAGE_H
#define PACKAGE_H

#include<iostream>
#include<string>

class Package{
    public:
        char type;
        std::string url;
        std::string content;
        void setBody(std::string body);
};


#endif