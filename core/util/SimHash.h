#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<bitset>
#include"util.h"

/**
 * 使用SimHash算法，对文章进行特征码提取
 * author:jiangpengfei12@gmail.com 
 * date；2016-12-16
 */
class SimHash{
    public:
        static const int BITSET_LENGTH = 64;       
    private:
        /**
         * simHash算法中的词汇bit码*weight后的结果的相加计算
         * @param res bit码*weight后的结果
         * @return 二进制特征码
         */
         std::bitset<SimHash::BITSET_LENGTH> calVectorAdd(std::vector<std::vector<int> > res);
    public:
         /**
         * 移除网页正文的stop word
         * @param content 正文的分词结果(map)
         * @param stopWordDict stopWord的字
         * @return 去除stopWord后的map
         */
        std::map<std::string,std::vector<int> > removeStopWord(std::map<std::string,std::vector<int> > content,std::map<std::string,int> stopWordDict);


        /**
         * 使用simHash的算法提取文档的特征码
         * @param content 已经去除过stopword的Map
         * @param frequencyDict 频率字典
         * @return char* 特征码
         */
        std::bitset<SimHash::BITSET_LENGTH> calculate(std::map<std::string,std::vector<int> > content,std::map<std::string,double> frequencyDict,int wordCount = 6);

};