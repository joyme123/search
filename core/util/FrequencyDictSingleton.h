#include<iostream>
#include<string>
#include<map>
#include<vector>
#include"config.h"

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
};