#ifndef STOPWORDDICTSINGLETON_H
#define STOPWORDDICTSINGLETON_H

#include <map>
#include <vector>
#include "src/core/util/ConfigReader.h"

class StopWordDictSingleton{
    public:
        std::map<std::string,int> stopWordDict;
        static StopWordDictSingleton* getInstance();
    private:
        StopWordDictSingleton();
        StopWordDictSingleton(const StopWordDictSingleton&);    //禁用
        StopWordDictSingleton& operator=(const StopWordDictSingleton&);  //禁用复制
};

#endif