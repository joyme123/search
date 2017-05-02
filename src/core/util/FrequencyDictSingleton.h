#ifndef FREQUENCYDICTSINGLETON_H
#define FREQUENCYDICTSINGLETON_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "src/core/util/config.h"

class FrequencyDictSingleton{
    public:
        std::map<std::string,double> frequencyDict;
        static FrequencyDictSingleton* getInstance();
        int getTest(){
            return test;
        }
    private:
        int test;
        FrequencyDictSingleton();
        FrequencyDictSingleton(const FrequencyDictSingleton&);    //禁用
        FrequencyDictSingleton& operator=(const FrequencyDictSingleton&);  //禁用复制
};

#endif