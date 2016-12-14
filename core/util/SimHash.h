#include<map>
#include<vector>
#include<algorithm>
#include<iostream>
#include<bitset>
#include"util.h"

class SimHash{
    public:
        static const int BITSET_LENGTH = 64;       
    private:
        static std::bitset<SimHash::BITSET_LENGTH> calVectorAdd(std::vector<std::vector<int> > res);
    public:
         /**
         * 移除网页正文的stop word
         * @param content 正文的分词结果(map),引用传参
         * @param stopWordDict stopWord的字典
         */
         static void removeStopWord(std::map<std::string,int>& content,std::map<std::string,int> stopWordDict);


        /**
         * 使用simHash的算法提取文档的特征码
         * @param content 已经去除过stopword的Map
         * @param frequencyDict 频率字典
         * @return char* 特征码
         */
        static std::bitset<SimHash::BITSET_LENGTH> calculate(std::map<std::string,int> content,std::map<std::string,double> frequencyDict,int wordCount);

};