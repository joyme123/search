#include"SimHash.h"
#include "../../include/cityHash/city.h"

std::bitset<SimHash::BITSET_LENGTH> SimHash::calVectorAdd(std::vector<std::vector<int> > res){
    std::vector<int> tmp;
    std::bitset<SimHash::BITSET_LENGTH> result;

    for(int i = 0; i < SimHash::BITSET_LENGTH; i++){
        int sum = 0;
        for(std::vector<std::vector<int> > :: iterator it = res.begin(); it != res.end(); it++){
            sum = sum + (*it)[i];
        }
        tmp.push_back(sum);
    }

    for(int i = 0; i < SimHash::BITSET_LENGTH; i++){
        if(tmp[i] > 0){
            result[i] = 1;
        }else{
            result[i] = 0;
        }
    }

    return result;
}

/**
 * 移除网页正文的stop word
 * @param content 正文的分词结果(map),引用传参
 * @param stopWordDict stopWord的字典
 */
void SimHash::removeStopWord(std::map<std::string,std::vector<int> >& content,std::map<std::string,int> stopWordDict){
    for(std::map<std::string,std::vector<int> >::iterator it = content.begin(); it != content.end(); it++){
        //检查当前词汇是否属于stopword
        if(stopWordDict[it->first] == 1){
            content.erase(it);  //属于则从map中清除当前词汇
        }
    }
}

/**
 * 使用simHash的算法提取文档的特征码
 * @param content 已经去除过stopword的Map
 * @param frequencyDict 频率字典
 * @param wordCount 要作为特征的单词数
 * @return char* 特征码
 */
std::bitset<SimHash::BITSET_LENGTH> SimHash::calculate(std::map<std::string,std::vector<int> > content,std::map<std::string,double> frequencyDict,int wordCount){
    std::vector<std::pair<std::string,std::vector<int> > > vec(content.begin(),content.end());
    std::sort(vec.begin(),vec.end(),cmpByValue);                                //对词汇按照频次进行排序

    std::vector<std::vector<int> > res;             //保存每个单词计算过权重的值
    std::bitset<SimHash::BITSET_LENGTH> pre(0);

    std::vector<int> tmp;

    int weight = 1;                                 //单词权重
    for(int i = 0; i < wordCount; i++){
        std::bitset<SimHash::BITSET_LENGTH> current(::CityHash64(vec[i].first.c_str(),(size_t)vec[i].first.length()));      //获取单词的64位bitset
        
        if(frequencyDict.find(vec[i].first) != frequencyDict.end()){        //如果当前单词在频率表中
            weight = 100 / frequencyDict[vec[i].first];
        }else{
            weight = 100 / 0.0005;
        }

        for(int i = 0; i < SimHash::BITSET_LENGTH; i++){
            tmp.push_back((current[i] == 1 ? current[i] : -1 )*weight);
        }
        res.push_back(tmp);
        tmp.clear();
    }

    return SimHash::calVectorAdd(res);          //返回simHash计算处的特征码

}