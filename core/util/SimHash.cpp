#include"SimHash.h"

std::bitset<64> SimHash::calculate(std::map<std::string,int> content,std::map<std::string,double> frequencyDict,int wordCount){
    std::vector<std::pair<std::string,int> > vec(content.begin(),content.end());
    std::sort(vec.begin(),vec.end(),cmpByValue);                                //对词汇按照频次进行排序

    for(int i = 0; i < wordCount; i++){
        CityHash64(vec[i].first,(size_t)vec[i].first.length());
    }
}