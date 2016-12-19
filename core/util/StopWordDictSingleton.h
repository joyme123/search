#include<iostream>
#include<string>
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
};