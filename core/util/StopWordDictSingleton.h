#ifndef STOPWORDDICTSINGLETON_H
#define STOPWORDDICTSINGLETON_H

#include<map>
#include<vector>
#include"config.h"

class StopWordDictSingleton{
    public:
        std::map<std::string,int> stopWordDict;
        static StopWordDictSingleton* getInstance();
        int getTest(){
            return test;
        }
    private:
        int test;
        StopWordDictSingleton();
        StopWordDictSingleton(const StopWordDictSingleton&);    //禁用
        StopWordDictSingleton& operator=(const StopWordDictSingleton&);  //禁用复制
};

#endif