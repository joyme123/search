#include"SimHashCal.h"
#include "../../include/cityHash/city.h"

std::bitset<SimHashCal::BITSET_LENGTH> SimHashCal::calVectorAdd(std::vector<std::vector<int> > res){
    std::vector<int> tmp;
    std::bitset<SimHashCal::BITSET_LENGTH> result;

    for(int i = 0; i < SimHashCal::BITSET_LENGTH; i++){
        int sum = 0;
        for(std::vector<std::vector<int> > :: iterator it = res.begin(); it != res.end(); it++){
            sum = sum + (*it)[i];
        }
        tmp.push_back(sum);
    }

    for(int i = 0; i < SimHashCal::BITSET_LENGTH; i++){
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
* @param content 正文的分词结果(map)
* @param stopWordDict stopWord的字
* @return 去除stopWord后的map
*/
std::map<std::string,std::vector<int> > SimHashCal::removeStopWord(std::map<std::string,std::vector<int> > content,std::map<std::string,int> stopWordDict){
    std::map<std::string,std::vector<int> > res;            //保存结果
    for(std::map<std::string,std::vector<int> >::iterator it = content.begin(); it != content.end(); it++){
        //如果不属于stopWord
        if(stopWordDict[it->first] != 1){
            res.insert(*it);  //属于则从map中清除当前词汇
        }
    }
    return res;
}

/**
 * 使用simHash的算法提取文档的特征码
 * @param content 已经去除过stopword的Map
 * @param frequencyDict 频率字典
 * @param wordCount 要作为特征的单词数
 * @return char* 特征码
 */
std::bitset<SimHashCal::BITSET_LENGTH> SimHashCal::calculate(std::map<std::string,std::vector<int> > content,std::map<std::string,double> frequencyDict,int wordCount){
    std::vector<std::pair<std::string,std::vector<int> > > vec(content.begin(),content.end());
    std::sort(vec.begin(),vec.end(),cmpByValue);                                //对词汇按照频次进行排序

    std::vector<std::vector<int> > res;             //保存每个单词计算过权重的值
    std::bitset<SimHashCal::BITSET_LENGTH> pre(0);

    std::vector<int> tmp;

    int weight = 1;                                 //单词权重
    if(vec.size() >= wordCount){
        //如果分得的词汇过少，则不需要提取关键字
        for(int i = 0; i < wordCount; i++){
            std::cout << "SimHash.cpp中60行--关键字:" << vec[i].first << "--" << std::endl;
            uint64 bit64 = CityHash64(vec[i].first.c_str(),(size_t)vec[i].first.length());
            std::bitset<SimHashCal::BITSET_LENGTH> current(bit64);      //获取单词的64位bitset
            
            if(frequencyDict.find(vec[i].first) != frequencyDict.end()){        //如果当前单词在频率表中
                weight = 1 / frequencyDict[vec[i].first];
            }else{
                weight = 1 / 0.0005;
            }

            for(int i = 0; i < SimHashCal::BITSET_LENGTH; i++){
                tmp.push_back((current[i] == 1 ? current[i] : -1 )*weight);
            }
            res.push_back(tmp);
            tmp.clear();
        }
    }


    return SimHashCal::calVectorAdd(res);          //返回simHash计算处的特征码

}