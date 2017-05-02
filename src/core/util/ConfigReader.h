#include<iostream>
#include<string>
#include<fstream>
#include<map>

#ifndef CONFIGREADER_H
#define CONFIGREADER_H
class ConfigReader{
    public:
        void open(const char* path);
        std::string get(const std::string key);
    protected:


    private:
        std::map<std::string,std::string> config;
};
#endif