#include<map>
#include<vector>
#include<algorithm>
#include<iostream>
#include<bitset>
#include "../../include/cityHash/city.h"
#include"util.h"

class SimHash{
       
        /**
         * 使用simHash的算法提取文档的特征码
         * @param content 已经去除过stopword的Map
         * @param frequencyDict 频率字典
         * @return char* 特征码
         */
        std::bitset<64> calculate(std::map<std::string,int> content,std::map<std::string,double> frequencyDict,int wordCount);

};